#include "step_motor_driver.h"

OperationData::OperationData()
{
	MotorID 	= 0;
	Type 		= 0;
	CurPos 		= 0; 	
	Interval	= 0;
	MaxCount	= 0;
}

StepOperation::StepOperation(StepMotorDriver* a_Driver, OperationData a_Data)
{
	m_Driver	= a_Driver;
	m_Data		= a_Data;
	m_ID		= -1;
}

StepOperation::~StepOperation()
{
	Cancel();
}

void StepOperation::Cancel()
{
	if (!IsRuning())
		return;
	
	m_Driver->RemoveOperation(m_ID);
	m_ID = -1;
}

void StepOperation::IsRuning()
{
	return (m_ID != -1);
}

void StepOperation::Run()
{
	if (IsRuning())
		return;
	
	m_ID = m_Driver->AddOperation(m_Data);	
}

size_t StepOperation::StepCount()
{
}

StepMotorDriver::StepMotorDriver()
{
}

StepMotorDriver::~StepMotorDriver()
{
}

OperationID StepMotorDriver::AddOperation(OperationData a_Data)
{
}

void StepMotorDriver::DoStepWork()
{
}

DriverOperation StepMotorDriver::GetNextOperation()
{
}

void StepMotorDriver::RemoveOperation(OperationID a_ID)
{
}



