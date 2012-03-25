
#include "stdafx.h"
#include "processor/thread.h"

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

TOneWriterMultiReader::TOneWriterMultiReader() 
{
/*	// Initially no readers want access, no writers want access, and 
	// no threads are accessing the resource
	m_nWaitingReaders = 0;
	m_nWaitingWriters = 0;
	m_nActive = 0;
	m_hsemReaders = CreateSemaphore(NULL, 0, MAXLONG, NULL);
	m_hsemWriters = CreateSemaphore(NULL, 0, MAXLONG, NULL);*/
}

TOneWriterMultiReader::~TOneWriterMultiReader() 
{
/*	m_nWaitingReaders = 0;
	m_nWaitingWriters = 0;
	m_nActive = 0;
	CloseHandle(m_hsemReaders);
	CloseHandle(m_hsemWriters);*/
}

void TOneWriterMultiReader::WaitForRead() 
{
	m_cs.Enter();
/*	bool fResourceWritePending = false;
	{
		// Ensure exclusive access to the member variables
		TEnterCriticalSection lock(&m_cs);

		// Are there writers waiting or is a writer writing?
		fResourceWritePending = (m_nWaitingWriters || (m_nActive < 0));

		if( fResourceWritePending ) 
		{	// This reader must wait, increment the count of waiting readers
			m_nWaitingReaders++;
		} 
		else 
		{	// This reader can read, increment the count of active readers
			m_nActive++;
		}
	}

	if( fResourceWritePending ) 
	{	// This thread must wait
		WaitForSingleObject(m_hsemReaders, INFINITE);
	}*/
}

void TOneWriterMultiReader::WaitForWrite() 
{
	m_cs.Enter();
	/*bool fResourceOwned = false;
	{
		// Ensure exclusive access to the member variables
		TEnterCriticalSection lock(&m_cs);

		// Are there any threads accessing the resource?
		fResourceOwned = (m_nActive != 0);

		if( fResourceOwned ) 
		{	// This writer must wait, increment the count of waiting writers
			m_nWaitingWriters++;
		} 
		else 
		{	// This writer can write, decrement the count of active writers
			m_nActive = -1;
		}
	}

	if( fResourceOwned ) 
	{	// This thread must wait
		WaitForSingleObject(m_hsemWriters, INFINITE);
	}*/
}

void TOneWriterMultiReader::Done() 
{
	m_cs.Leave();
/*	HANDLE hsem = NULL;  // Assume no threads are waiting
	LONG lCount = 1;     // Assume only 1 waiter wakes; always true for writers

	{
		// Ensure exclusive access to the member variables
		TEnterCriticalSection lock(&m_cs);

		if( m_nActive > 0 ) 
		{	// Readers have control so a reader must be done
			m_nActive--;
		} 
		else 
		{	// Writers have control so a writer must be done
			m_nActive++;
		}

		if( m_nActive == 0 )  	
		{	// No thread has access, who should wake up?
			// NOTE: It is possible that readers could never get access
			//       if there are always writers wanting to write

			if( m_nWaitingWriters > 0 ) 
			{	// Writers are waiting and they take priority over readers
				m_nActive = -1;         // A writer will get access
				m_nWaitingWriters--;    // One less writer will be waiting
				hsem = m_hsemWriters;   // Writers wait on this semaphore
				// NOTE: The semaphore will release only 1 writer thread
			} 
			else if( m_nWaitingReaders > 0 ) 
			{	// Readers are waiting and no writers are waiting
				m_nActive = m_nWaitingReaders;   // All readers will get access
				m_nWaitingReaders = 0;           // No readers will be waiting
				hsem = m_hsemReaders;            // Readers wait on this semaphore
				lCount = m_nActive;              // Semaphore releases all readers
			} 
			else 
			{	// There are no threads waiting at all; no semaphore gets released
			}
		}
	}

	if( hsem != NULL ) 
	{	// Some threads are to be released
		ReleaseSemaphore(hsem, lCount, NULL);
	}*/
}

TEnterRead::TEnterRead(TOneWriterMultiReader* a_OWMR, bool a_Block)
{
	m_OWMR = a_OWMR;
	m_Block = a_Block;
	if( m_Block )
		m_OWMR->WaitForRead();
}

TEnterRead::~TEnterRead()
{
	if( m_Block )
		m_OWMR->Done();
}

TEnterWrite::TEnterWrite(TOneWriterMultiReader* a_OWMR, bool a_Block)
{
	m_OWMR = a_OWMR;
	m_Block = a_Block;
	if( m_Block )
		m_OWMR->WaitForWrite();
}

TEnterWrite::~TEnterWrite()
{
	if( m_Block )
		m_OWMR->Done();
}
