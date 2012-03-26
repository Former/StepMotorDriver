
#pragma once

#include <wx/thread.h>

class TCriticalSection
{
public:
	TCriticalSection();
	~TCriticalSection();
	
	void Enter();
	void Leave();

private:
	wxCriticalSection m_CS;
	wxThreadIdType m_TreadID;
	int m_NestedEntres;
};

class ThreadClass : public wxThread
{
public:
	typedef unsigned int ThreadRet;
	typedef unsigned int Time;
	typedef unsigned int UserData;

	ThreadClass();
	~ThreadClass();

	bool		Start(UserData a_UserData = 0);
	void		SendStop();
	ThreadRet	WaitClose();
	bool		CheckForStop();

protected:
	virtual ThreadRet 	EntryPoint(UserData a_UserData) = 0;
	virtual ExitCode 	Entry();

	int			m_Stop;
	TCriticalSection m_StopGuard;
private:
	bool 		m_IsStarted;
	UserData 	m_UserData;
	ThreadRet	m_ExitCode;
};

class TEnterCriticalSection
{
public:
	TEnterCriticalSection(TCriticalSection* a_Mutex, bool a_Block = true);
	~TEnterCriticalSection();

private:
	TCriticalSection*	m_Mutex;
	bool				m_Block;
};
