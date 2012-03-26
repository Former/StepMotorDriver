#pragma once

#include <stdint.h>
#include <vector>
#include <tr1/memory>
#include <thread.h>

typedef unsigned char Byte;
typedef size_t OperationID;
typedef uint64_t Time;

enum OperationType
{
	opt_Left,
	opt_Right,
	opt_Set,
};

struct OperationData
{
	OperationData();
	
	size_t 				MotorID;
	OperationType 		Type;
	// Для opt_Set
	Byte				CurPos; 	
	//  Для opt_Left, opt_Right
	std::vector<Byte>	BufSteps; 
	size_t				CurStepIndex;
	size_t				Interval;
	size_t 				MaxCount;
};

class StepMotorDriver;
class StepOperation;

typedef std::tr1::shared_ptr<StepOperation>	StepOperationPtr;
typedef std::tr1::weak_ptr<StepOperation>	StepOperationWPtr;

class StepOperation
{
	friend class StepMotorDriver;
public:
	StepOperation(StepMotorDriver* a_Driver, OperationData a_Data);
	~StepOperation();
	
	bool 	IsRuning();
	void 	Run();
	void 	Cancel();
	size_t 	StepCount();
	
protected:
	void 	SetThis(StepOperationWPtr a_This);

	OperationData 	m_Data;
	OperationID 	m_ID;
	StepMotorDriver*m_Driver;
	TCriticalSection m_Guard;
	StepOperationWPtr m_This;
};

struct DriverOperation
{	
	OperationData 	Data;
	Time 			NextStepTime;
	size_t 			StepCount;
	StepOperationWPtr Operation;
};

class StepMotorDriver : public ThreadClass
{
	friend class StepOperation;
public:
	StepMotorDriver();
	~StepMotorDriver();

	StepOperationPtr GetOperation(OperationData a_Data);
	
protected:
	OperationID	AddOperation(OperationData a_Data, StepOperationWPtr a_Op);
	void 		RemoveOperation(OperationID a_ID);
		
private:
	virtual ThreadRet 	EntryPoint(UserData a_UserData);

	StepOperationPtr DoStepWork();
	DriverOperation* GetNextOperation();
	
	void 		WriteToLPT(size_t a_MotorID, unsigned char a_Data);
	
	TCriticalSection m_Guard;
	Time		m_CurTime;
	std::vector<DriverOperation> m_Operations;
	int 		m_LptDataFile;
};

