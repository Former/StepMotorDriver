#include <fcntl.h>
#include "step_motor_driver.h"

#define ToPointer(a_Ptr)	((Pointer)reinterpret_cast<long long>(a_Ptr))

OperationData::OperationData()
{
	MotorID 	= 0;
	Type 		= opt_Set;
	CurPos 		= 0; 	
	Interval	= 0;
	MaxCount	= 0;
	CurStepIndex = 0;
}

////////////////////////////////////////////////////

StepOperation::StepOperation(StepMotorDriver* a_Driver, OperationData a_Data)
{
	m_Driver	= a_Driver;
	m_Data		= a_Data;
	m_ID		= 0;
}

StepOperation::~StepOperation()
{
	Cancel();
}

void StepOperation::Cancel()
{
	TEnterCriticalSection guard(&m_Guard);
	
	if (!IsRunning())
		return;
	
	m_Driver->RemoveOperation(m_ID);
	m_ID = 0;
}

bool StepOperation::IsRunning()
{
	TEnterCriticalSection guard(&m_Guard);

	return !!m_ID;
}

void StepOperation::Run()
{
	TEnterCriticalSection guard(&m_Guard);

	if (IsRunning())
		return;
	
	m_ID = m_Driver->AddOperation(m_Data, m_This);	
}

size_t StepOperation::StepCount()
{
	TEnterCriticalSection guard(&m_Guard);
	
	// not implemented
	return 0;
}

void StepOperation::SetThis(StepOperationWPtr a_This)
{
	m_This = a_This;
}

////////////////////////////////////////////////////

StepMotorDriver::StepMotorDriver()
{
	m_LptDataFile = -1;
}

StepMotorDriver::~StepMotorDriver()
{
	close(m_LptDataFile);
}

OperationID StepMotorDriver::AddOperation(OperationData a_Data, StepOperationWPtr a_Op)
{
	TEnterCriticalSection guard(&m_Guard);
	
	DriverOperation op;
	op.Data = a_Data;
	op.NextStepTime = m_CurTime;
	op.StepCount = 0;
	op.Operation = a_Op;
	
	OperationID result = ToPointer(a_Op.lock().get());
	m_Operations[result] = op;
	
	return result;
}

void StepMotorDriver::RemoveOperation(OperationID a_ID)
{
	TEnterCriticalSection guard(&m_Guard);

	wxASSERT(m_Operations.find((Pointer)a_ID) != m_Operations.end());
	
	m_Operations.erase((Pointer)a_ID);
}

StepOperationPtr StepMotorDriver::DoStepWork()
{
	TEnterCriticalSection guard(&m_Guard);
	
	DriverOperation* nextOp = GetNextOperation();
	if (!nextOp)
	{
		const size_t sleepTime = 100000;
		{
			TLeaveCriticalSection leave(&m_Guard);
			usleep(sleepTime);		
		}
		m_CurTime += sleepTime;
		return StepOperationPtr();	
	}
	
	if (m_CurTime < nextOp->NextStepTime)	
	{
		{
			TLeaveCriticalSection leave(&m_Guard);
			usleep(nextOp->NextStepTime - m_CurTime);
		}
		m_CurTime = nextOp->NextStepTime;		
	}	
	
	OperationData* data = &nextOp->Data;
	
	nextOp->NextStepTime += data->Interval;
	nextOp->StepCount++;
	
	switch(data->Type)
	{
	case opt_Set:
		WriteToLPT(data->MotorID, data->CurPos);
		return nextOp->Operation.lock();

	case opt_Left:
		data->CurStepIndex--;
	case opt_Right:
		if (opt_Right == data->Type)
			data->CurStepIndex++;
		
		data->CurStepIndex = data->CurStepIndex % data->BufSteps.size();
		data->CurPos = data->BufSteps[data->CurStepIndex];
		WriteToLPT(data->MotorID, data->CurPos);
		
		if (nextOp->StepCount >= data->MaxCount)
			return nextOp->Operation.lock();		
		
		break;
	}
	return StepOperationPtr();
}

DriverOperation* StepMotorDriver::GetNextOperation()
{
	TEnterCriticalSection guard(&m_Guard);
	
	if (!m_Operations.size())
		return 0;
	
	DriverOperation* nextOp = 0;
	for (OpMap::iterator it = m_Operations.begin(); it != m_Operations.end(); it++)
	{
		if (!nextOp)
			nextOp = &it->second;
		
		if (it->second.NextStepTime < nextOp->NextStepTime)
			nextOp = &it->second;
	}
	
	return nextOp;
}


StepMotorDriver::ThreadRet StepMotorDriver::EntryPoint(UserData a_UserData)
{
	while(true)
	{
		if (CheckForStop())
			break;
		
		StepOperationPtr cancelOp = DoStepWork();
		if (cancelOp)
			cancelOp->Cancel();
	}
	return 0;
}

StepOperationPtr StepMotorDriver::GetOperation(OperationData a_Data)
{
	StepOperationPtr result(new StepOperation(this, a_Data));
	result->SetThis(result);	
	return result;
}

void StepMotorDriver::WriteToLPT(size_t a_MotorID, unsigned char a_Data)
{
	unsigned char data = ((1 << a_MotorID) << 4) | a_Data;
	write(m_LptDataFile, &data, 1);
	usleep(10);
	m_CurTime += 10;

	// Обнуляем данные на ЛПТ порте, чтобы не повлияла скорость записи в порт, на данные в другом MotorID 
	unsigned char zeroID = a_Data;
	write(m_LptDataFile, &zeroID, 1);
}

bool StepMotorDriver::Init()
{
	m_LptDataFile = open("/dev/lpt_data", O_WRONLY);
	if (m_LptDataFile < 0)
		return false;
	
	if (!Start())
		return false;
	
	return true;
}

