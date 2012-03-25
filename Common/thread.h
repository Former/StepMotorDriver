
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

// GP_OneWriterMultiReaderMutex: Copyright (c) 2000 Jeffrey Richter (SWMRG)
class TOneWriterMultiReader 
{
public:
	TOneWriterMultiReader();         // Constructor
	~TOneWriterMultiReader();        // Destructor

	void				WaitForRead();       // Call this to gain shared read access
	void				WaitForWrite();      // Call this to gain exclusive write access
	void				Done();             // Call this when done accessing the resource
private:

	TCriticalSection	m_cs;				// Permits exclusive access to other members
/*	HANDLE				m_hsemReaders;		// Readers wait on this if a writer has access
	HANDLE				m_hsemWriters;		// Writers wait on this if a reader has access
	int					m_nWaitingReaders;	// Number of readers waiting for access
	int					m_nWaitingWriters;	// Number of writers waiting for access
	int					m_nActive;			// Number of threads currently with access
	*/										//   (0=no threads, >0=# of readers, -1=1 writer)
};

class TEnterRead
{
public:
	TEnterRead(TOneWriterMultiReader* a_OWMR, bool a_Block = true);
	~TEnterRead();

private:
	TOneWriterMultiReader*	m_OWMR;
	bool					m_Block;
};

class TEnterWrite
{
public:
	TEnterWrite(TOneWriterMultiReader* a_OWMR, bool a_Block = true);
	~TEnterWrite();

private:
	TOneWriterMultiReader*	m_OWMR;
	bool					m_Block;
};
