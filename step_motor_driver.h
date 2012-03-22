#pragma once

#include <stdint.h>
#include <vector>
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
	size_t 				MotorID;
	OperationType 		Type;
	// Для opt_Set
	Byte				CurPos; 	
	//  Для opt_Left, opt_Right
	std::vector<Byte>	BufSteps; 
	size_t				Interval;
	size_t 				MaxCount;
};

class StepOperation
{
public:
	StepOperation(OperationData a_Data);
	~StepOperation();
	
	void 	Run();
	void 	Cancel();
	size_t 	StepCount();
	
protected:
	OperationData 	m_Data;
	OperationID 	m_ID;
	bool			m_IsRuning;
};

struct DriverOperation
{	
	OperationData 	Data;
	Time 			NextStepTime;
	size_t 			StepCount;
};

class StepMotorDriver
{
	friend class StepOperation;
public:
	StepMotorDriver();
	~StepMotorDriver();
	
protected:
	OperationID	AddOperation(OperationData a_Data);
	void 		RemoveOperation(OperationID a_ID);
		
private:
	void 		DoStepWork();
	DriverOperation GetNextOperation();
	
	Time		m_CurTime;
	std::vector<DriverOperation> m_Operations;
};

