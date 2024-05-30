#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>



GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	
}

void GUIMyFrame1::showInfo(wxMouseEvent& event)
{
}

void GUIMyFrame1::enterFunction(wxCommandEvent& event)
{
	function = textCtrlFunkcja->GetValue().ToStdString();
	//sprawdziæ czy funkcja poprawnie wprowadzona!
}

void GUIMyFrame1::enterXMin(wxCommandEvent& event)
{
}

void GUIMyFrame1::enterXMax(wxCommandEvent& event)
{
}

void GUIMyFrame1::enterYMin(wxCommandEvent& event)
{
}

void GUIMyFrame1::enterYMax(wxCommandEvent& event)
{
}

void GUIMyFrame1::enterZMin(wxCommandEvent& event)
{
}

void GUIMyFrame1::enterZMax(wxCommandEvent& event)
{
}

void GUIMyFrame1::perspectiveClick(wxMouseEvent& event)
{
	if ( radioRzut.is)
}

void GUIMyFrame1::outlineClick(wxMouseEvent& event)
{
}

void GUIMyFrame1::printClick(wxMouseEvent& event)
{
}

void GUIMyFrame1::saveClick(wxMouseEvent& event)
{
}

void GUIMyFrame1::generateClick(wxMouseEvent& event)
{
}

bool GUIMyFrame1::checkFunction(string f) const
{
	return false;
}
