/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include "main.h"

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// application class implementation 
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit()
{
	SetTopWindow( new MainDialog( NULL ) );
	GetTopWindow()->Show();
	
	// true = enter the main loop
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation 
////////////////////////////////////////////////////////////////////////////////

MainDialog::MainDialog(wxWindow *parent) : MainDialogBase( parent )
{
	if (!m_Driver.Init())
	{
		wxMessageBox(_T("Error open file /dev/lpt_data"));
		Destroy();
	}
}

MainDialog::~MainDialog()
{
}

void MainDialog::OnCloseDialog(wxCloseEvent& event)
{
	Destroy();
}

void MainDialog::OnOKClick(wxCommandEvent& event)
{
	Destroy();
}

void MainDialog::OnCancelClick(wxCommandEvent& event)
{
	Destroy();
}

void MainDialog::OnCheck1(wxCommandEvent& event)
{
	OnCheck();
}

void MainDialog::OnCheck2(wxCommandEvent& event)
{
	OnCheck();
}

void MainDialog::OnCheck3(wxCommandEvent& event)
{
	OnCheck();
}

void MainDialog::OnCheck4(wxCommandEvent& event)
{
	OnCheck();
}

void MainDialog::OnLeft(wxCommandEvent& event)
{
}

void MainDialog::OnRight(wxCommandEvent& event)
{
}

void MainDialog::OnCheck()
{
	size_t checkMask = (m_checkBox1->IsChecked() << 3) +
		(m_checkBox2->IsChecked() << 2) + 
		(m_checkBox3->IsChecked() << 1) +
		(m_checkBox4->IsChecked());
	
	OperationData data;
	data.CurPos = checkMask;
	data.Type = opt_Set;
	data.MotorID = GetMotorID();
	
	m_LatsCheckOperation = m_Driver.GetOperation(data);
	m_LatsCheckOperation->Run();
}

size_t MainDialog::GetMotorID()
{
	if (m_motor1->GetValue())
		return 1 << 3;
	if (m_motor2->GetValue())
		return 1 << 2;
	if (m_motor3->GetValue())
		return 1 << 1;
	if (m_motor4->GetValue())
		return 1;
}

void MainDialog::OnLeftOrRight(bool a_Left)
{
	OperationData data;
	if (a_Left)
	{
		if (m_LeftOp && m_LeftOp->IsRunning())
		{
			m_LeftOp->Cancel();
			m_LeftOp.reset();
			return;
		}
		data.Type = opt_Left;
	}
	else
	{
		if (m_RightOp && m_RightOp->IsRunning())
		{
			m_RightOp->Cancel();
			m_RightOp.reset();
			return;
		}
		data.Type = opt_Right;
	}
	
	data.MotorID	= GetMotorID();
	data.BufSteps	= GetBufSteps();
	data.Interval	= GetInterval();
	
	if (a_Left)
	{
		m_LeftOp = m_Driver.GetOperation(data);
		m_LeftOp->Run();
	}	
	else
	{
		m_RightOp = m_Driver.GetOperation(data);
		m_RightOp->Run();
	}	
}

std::vector<Byte> MainDialog::GetBufSteps()
{
	wxString sSteps = m_comboBoxSteps->GetValue();
	std::vector<Byte> result;
	
	result.push_back(1);
	result.push_back(4);
	result.push_back(2);
	result.push_back(8);
	
	return result;
}

size_t MainDialog::GetInterval()
{
	wxString sInerval = m_comboBoxInterval->GetValue();
	unsigned long ret = 0;
	sInerval.ToULong(&ret);
	return ret;
}

