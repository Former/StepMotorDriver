///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainDialogBase
///////////////////////////////////////////////////////////////////////////////
class MainDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_BackGroundPanel;
		wxStaticText* m_staticText3;
		wxRadioButton* m_motor1;
		wxRadioButton* m_motor2;
		wxRadioButton* m_motor3;
		wxRadioButton* m_motor4;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxComboBox* m_comboBoxSteps;
		wxComboBox* m_comboBoxInterval;
		wxButton* m_buttonLeft;
		wxButton* m_buttonRight;
		wxStaticText* m_staticText4;
		wxCheckBox* m_checkBox1;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox3;
		wxCheckBox* m_checkBox4;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Step Motor Driver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,-1 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE );
		~MainDialogBase();
	
};

#endif //__gui__
