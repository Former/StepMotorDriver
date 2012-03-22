///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainDialogBase::MainDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_BackGroundPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText3 = new wxStaticText( m_BackGroundPanel, wxID_ANY, _("Motor"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer2->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_motor1 = new wxRadioButton( m_BackGroundPanel, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_motor1->SetValue( true ); 
	bSizer5->Add( m_motor1, 0, wxALL, 5 );
	
	m_motor2 = new wxRadioButton( m_BackGroundPanel, wxID_ANY, _("2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_motor2, 0, wxALL, 5 );
	
	m_motor3 = new wxRadioButton( m_BackGroundPanel, wxID_ANY, _("3"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_motor3, 0, wxALL, 5 );
	
	m_motor4 = new wxRadioButton( m_BackGroundPanel, wxID_ANY, _("4"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_motor4, 0, wxALL, 5 );
	
	bSizer2->Add( bSizer5, 0, wxALIGN_CENTER, 5 );
	
	m_staticline1 = new wxStaticLine( m_BackGroundPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( m_BackGroundPanel, wxID_ANY, _("Steps"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer8->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticText2 = new wxStaticText( m_BackGroundPanel, wxID_ANY, _("Interval"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer8->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	bSizer9->Add( bSizer8, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_comboBoxSteps = new wxComboBox( m_BackGroundPanel, wxID_ANY, _("1,2,4,8"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBoxSteps->Append( _("1,2,4,8") );
	m_comboBoxSteps->Append( _("1,3,2,6,4,12,8,9") );
	bSizer10->Add( m_comboBoxSteps, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_comboBoxInterval = new wxComboBox( m_BackGroundPanel, wxID_ANY, _("5000"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBoxInterval->Append( _("5000") );
	m_comboBoxInterval->Append( _("2500") );
	m_comboBoxInterval->Append( _("500000") );
	bSizer10->Add( m_comboBoxInterval, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer9->Add( bSizer10, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer2->Add( bSizer9, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonLeft = new wxButton( m_BackGroundPanel, wxID_ANY, _("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonLeft->SetMinSize( wxSize( -1,60 ) );
	
	bSizer11->Add( m_buttonLeft, 0, wxALL, 5 );
	
	m_buttonRight = new wxButton( m_BackGroundPanel, wxID_ANY, _("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRight->SetMinSize( wxSize( -1,60 ) );
	
	bSizer11->Add( m_buttonRight, 0, wxALL, 5 );
	
	bSizer2->Add( bSizer11, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText4 = new wxStaticText( m_BackGroundPanel, wxID_ANY, _("Bytes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer2->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBox1 = new wxCheckBox( m_BackGroundPanel, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_checkBox1, 0, wxALL, 5 );
	
	m_checkBox2 = new wxCheckBox( m_BackGroundPanel, wxID_ANY, _("2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_checkBox2, 0, wxALL, 5 );
	
	m_checkBox3 = new wxCheckBox( m_BackGroundPanel, wxID_ANY, _("3"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_checkBox3, 0, wxALL, 5 );
	
	m_checkBox4 = new wxCheckBox( m_BackGroundPanel, wxID_ANY, _("4"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_checkBox4, 0, wxALL, 5 );
	
	bSizer2->Add( bSizer13, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_BackGroundPanel->SetSizer( bSizer2 );
	m_BackGroundPanel->Layout();
	bSizer2->Fit( m_BackGroundPanel );
	mainSizer->Add( m_BackGroundPanel, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialogBase::OnCloseDialog ) );
}

MainDialogBase::~MainDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialogBase::OnCloseDialog ) );
	
}
