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

bool GUIMyFrame1::checkFunction()
{	
	if ( true ) {
		function = "";
		textCtrlFunkcja->SetValue("");

		return false;
	}

	return true;
}

bool GUIMyFrame1::checkNumbers()
{
	if (!stod(textCtrlXMin->GetValue().ToStdString())) {
		textCtrlXMin->SetValue("");
		return false;
	}
	xMin = stod(textCtrlXMin->GetValue().ToStdString());

	if (!stod(textCtrlXMax->GetValue().ToStdString())) {
		textCtrlXMax->SetValue("");
		return false;
	}
	xMax = stod(textCtrlXMin->GetValue().ToStdString());

	if (!stod(textCtrlYMin->GetValue().ToStdString())) {
		textCtrlYMin->SetValue("");
		return false;
	}
	yMin = stod(textCtrlXMin->GetValue().ToStdString());

	if (!stod(textCtrlYMax->GetValue().ToStdString())) {
		textCtrlYMax->SetValue("");
		return false;
	}
	yMax = stod(textCtrlXMin->GetValue().ToStdString());

	if (!stod(textCtrlZMin->GetValue().ToStdString())) {
		textCtrlZMin->SetValue("");
		return false;
	}
	zMin = stod(textCtrlZMax->GetValue().ToStdString());

	if (!stod(textCtrlXMin->GetValue().ToStdString())) {
		textCtrlZMax->SetValue("");
		return false;
	}
	zMax = stod(textCtrlXMin->GetValue().ToStdString());


	return true;
}

void GUIMyFrame1::perspectiveClick(wxMouseEvent& event)
{
	if (radioRzut->GetValue()) {
		radioMapa->SetValue(false);
		inPerspective = true;
		inMap = false;
	}
	else {
		radioRzut->SetValue(true);
	}
}

void GUIMyFrame1::outlineClick(wxMouseEvent& event)
{
	if (radioMapa->GetValue()) {
		radioRzut->SetValue(false);
		inPerspective = false;
		inMap = true;
	}
	else {
		radioMapa->SetValue(true);
	}
}

void GUIMyFrame1::printClick(wxMouseEvent& event)
{
}

void GUIMyFrame1::saveClick(wxMouseEvent& event)
{
	wxFileDialog saveFileDialog(this, "Choose a file", "", "", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

	//zapisywanie obrazu
	wxClientDC dc(panelNaWykres);
	wxSize size = panelNaWykres->GetSize();
	wxBitmap bitmap(size);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmap);
	memDC.Blit(0, 0, size.GetWidth(), size.GetHeight(), &dc, 0, 0);
	memDC.SelectObject(wxNullBitmap);
	wxImage savePicture = bitmap.ConvertToImage();
	savePicture.AddHandler(new wxJPEGHandler);
	savePicture.AddHandler(new wxPNGHandler);
	savePicture.SaveFile(saveFileDialog.GetPath());
}

void GUIMyFrame1::generateClick(wxMouseEvent& event)
{
	if ( !checkFunction() || !checkNumbers() ) return;

	//gerneruj wykres
	if (isPerspective()) {
		//generuj rzut perspektywiczny
		buttonGenerate->SetBackgroundColour(*wxLIGHT_GREY);
	}
	else {
		//generuj mape konturowa
	}
}
