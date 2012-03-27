#include <stdint.h>
#include "thread.h"

#define PointerToInteger(a_Ptr) (reinterpret_cast<intptr_t>(a_Ptr))

ThreadClass::ThreadClass() : wxThread(wxTHREAD_JOINABLE)
{
	m_IsStarted = false;
	m_ExitCode 	= 0;
	m_Stop 		= 0;
}

ThreadClass::~ThreadClass()
{
	if (m_IsStarted)
	{
		SendStop();
		Wait();
	}
}

bool ThreadClass::Start(UserData a_UserData)
{
	if (m_IsStarted)
		return false;
	m_UserData = a_UserData;
	if (Create() != wxTHREAD_NO_ERROR)
		return false;
	SetPriority(WXTHREAD_MIN_PRIORITY);
	m_IsStarted = (Run() == wxTHREAD_NO_ERROR);
	return m_IsStarted;
}

void ThreadClass::SendStop()
{
	TEnterCriticalSection guard(&m_StopGuard);
	
	m_Stop = 1;
}

ThreadClass::ThreadRet ThreadClass::WaitClose()
{
	return ThreadClass::ThreadRet(PointerToInteger(Wait()));
}

bool ThreadClass::CheckForStop()
{
	TEnterCriticalSection guard(&m_StopGuard);
	return m_Stop ? true: false;
		
}

ThreadClass::ExitCode ThreadClass::Entry()
{
	m_ExitCode = EntryPoint(m_UserData);
	m_IsStarted = false;
	return ExitCode(m_ExitCode);
}

///////////////////////////////////////////////////////////////////

TCriticalSection::TCriticalSection()
{
	m_TreadID = 0;
	m_NestedEntres = 0;
}

TCriticalSection::~TCriticalSection()
{
}

void TCriticalSection::Enter()
{
	if (m_TreadID == wxThread::GetCurrentId())
	{
		// Мы уже вошли
		m_NestedEntres++;
		return;
	}
	m_CS.Enter();
	if (!m_TreadID)
		m_TreadID = wxThread::GetCurrentId();
}

void TCriticalSection::Leave()
{
	if (m_TreadID == wxThread::GetCurrentId())
	{
		if (m_NestedEntres == 0)
		{
			m_TreadID = 0;
			m_CS.Leave();
		}
		else
			m_NestedEntres--;
		return;
	}
	m_CS.Leave();
}

/////////////////////////////////////////////////////////////////////////////

TEnterCriticalSection::TEnterCriticalSection(TCriticalSection* a_Mutex, bool a_Block)
{
	m_Mutex = a_Mutex;
	m_Block = a_Block;
	if( m_Block )
		m_Mutex->Enter();
}

TEnterCriticalSection::~TEnterCriticalSection()
{
	if( m_Block )
		m_Mutex->Leave();
}

/////////////////////////////////////////////////

TLeaveCriticalSection::TLeaveCriticalSection(TCriticalSection* a_Mutex, bool a_Block)
{
	m_Mutex = a_Mutex;
	m_Block = a_Block;
	if( m_Block )
		m_Mutex->Leave();
}

TLeaveCriticalSection::~TLeaveCriticalSection()
{
	if( m_Block )
		m_Mutex->Enter();
}