#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include

#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
protected:
	// Handlers for MyFrame1 events;

public:
	/** Constructor */
	GUIMyFrame1(wxWindow* parent);
	//// end generated class members
	void Repaint();
};

#endif // __GUIMyFrame1__