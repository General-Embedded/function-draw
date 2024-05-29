#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"
#include <math.h>
#include <iostream>

struct Point {
	float x, y, z;
	Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
	int R, G, B;
	Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
	Point begin, end;
	Color color;
	Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

double countFunction(double x, double y) {

	return x * x + y * y;
}

double xmax = 1;
double xmin = -1;
double ymax = 1;
double ymin = -1;
int sample = 50;

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
	m_staticText25->SetLabel(_("Obr\u00F3t X:"));
	m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
	m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

	WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
	WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
	WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(134);

	WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
	WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
	WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(44);

	WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
	WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
	WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);

	double move = std::max(((xmax - xmin) / sample), (ymax - ymin) / sample);
	double movex = std::min((xmax - xmin), move);
	double movey = std::min((ymax - ymin), move);
	double zmax = 1;
	double zmin = -1;


	for (double x = xmin; x <= (xmax); x += movex) {

		for (double y = ymin; y <= (ymax); y += movey) {

			double z = countFunction(x, y);
			double z1 = countFunction(x, y + movey);
			double z2 = countFunction(x + movex, y);

			data.push_back(Segment(Point(x, y, z), Point(x, y + movey, z1), Color(255, 0, 255)));
			data.push_back(Segment(Point(x, y, z), Point(x + movex, y, z2), Color(255, 0, 255)));
		}
		double z = countFunction(x, ymax);
		double z3 = countFunction(x + movex, ymax);

		data.push_back(Segment(Point(x, ymax, z), Point(x + movex, ymax, z3), Color(255, 0, 255)));
	}

	for (double y = ymin; y <= ymax; y += movey) {

		double z = countFunction(xmax, y);
		double z3 = countFunction(xmax, y + movey);

		data.push_back(Segment(Point(xmax, y, z), Point(xmax, y + movey, z3), Color(255, 0, 255)));
	}

	double grid = std::max(xmax - xmin, std::max(ymax - ymin, zmax - zmin)) / 10;

	data.push_back(Segment(Point(xmin, 0, 0), Point(xmax, 0, 0), Color(255, 0, 0)));
	for (double i = 0; i < M_PI / 2; i += 0.3) {
		data.push_back(Segment(Point(xmax - grid / 2, 0.03 * sqrt(1 - pow(sin(i), 2)), 0.03 * sqrt(1 - pow(cos(i), 2))), Point(1, 0, 0), Color(255, 0, 0)));
		data.push_back(Segment(Point(xmax - grid / 2, -0.03 * sqrt(1 - pow(sin(i), 2)), -0.03 * sqrt(1 - pow(cos(i), 2))), Point(1, 0, 0), Color(255, 0, 0)));
		data.push_back(Segment(Point(xmax - grid / 2, 0.03 * sqrt(1 - pow(sin(i), 2)), -0.03 * sqrt(1 - pow(cos(i), 2))), Point(1, 0, 0), Color(255, 0, 0)));
		data.push_back(Segment(Point(xmax - grid / 2, -0.03 * sqrt(1 - pow(sin(i), 2)), 0.03 * sqrt(1 - pow(cos(i), 2))), Point(1, 0, 0), Color(255, 0, 0)));
	}

	data.push_back(Segment(Point(0, -1, 0), Point(0, 1, 0), Color(0, 255, 0)));
	for (double i = 0; i < M_PI / 2; i += 0.3) {
		data.push_back(Segment(Point(0.03 * sqrt(1 - pow(sin(i), 2)), ymax - grid / 2, 0.03 * sqrt(1 - pow(cos(i), 2))), Point(0, 1, 0), Color(0, 255, 0)));
		data.push_back(Segment(Point(-0.03 * sqrt(1 - pow(sin(i), 2)), ymax - grid / 2, 0.03 * sqrt(1 - pow(cos(i), 2))), Point(0, 1, 0), Color(0, 255, 0)));
		data.push_back(Segment(Point(-0.03 * sqrt(1 - pow(sin(i), 2)), ymax - grid / 2, -0.03 * sqrt(1 - pow(cos(i), 2))), Point(0, 1, 0), Color(0, 255, 0)));
		data.push_back(Segment(Point(0.03 * sqrt(1 - pow(sin(i), 2)), ymax - grid / 2, -0.03 * sqrt(1 - pow(cos(i), 2))), Point(0, 1, 0), Color(0, 255, 0)));
	}

	data.push_back(Segment(Point(0, 0, -1), Point(0, 0, 1), Color(0, 0, 255)));
	for (double i = 0; i < M_PI / 2; i += 0.3) {
		data.push_back(Segment(Point(0.03 * sqrt(1 - pow(cos(i), 2)), 0.03 * sqrt(1 - pow(sin(i), 2)), zmax - grid / 2), Point(0, 0, 1), Color(0, 0, 255)));
		data.push_back(Segment(Point(-0.03 * sqrt(1 - pow(cos(i), 2)), 0.03 * sqrt(1 - pow(sin(i), 2)), zmax - grid / 2), Point(0, 0, 1), Color(0, 0, 255)));
		data.push_back(Segment(Point(-0.03 * sqrt(1 - pow(cos(i), 2)), -0.03 * sqrt(1 - pow(sin(i), 2)), zmax - grid / 2), Point(0, 0, 1), Color(0, 0, 255)));
		data.push_back(Segment(Point(0.03 * sqrt(1 - pow(cos(i), 2)), -0.03 * sqrt(1 - pow(sin(i), 2)), zmax - grid / 2), Point(0, 0, 1), Color(0, 0, 255)));
	}
}

void GUIMyFrame1::WxPanel_Repaint(wxUpdateUIEvent& event)
{
	Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click(wxCommandEvent& event)
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	getMinYMaxY();

	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		double x1, y1, z1, x2, y2, z2;
		int r, g, b;

		std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
		if (in.is_open())
		{
			data.clear();
			while (!in.eof())
			{
				in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
				data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
			}
			in.close();
		}
	}
}

void GUIMyFrame1::Scrolls_Updated(wxScrollEvent& event)
{
	WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
	WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
	WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

	WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
	WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
	WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

	WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
	WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
	WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


	Repaint();
}

Matrix4 GUIMyFrame1::XRotation(double alpha) {

	Matrix4 matrix;
	alpha = ((alpha + 252) * M_PI) / 180.0;

	matrix.data[0][0] = 1;
	matrix.data[1][1] = cos(alpha);
	matrix.data[1][2] = -sin(alpha);
	matrix.data[2][1] = sin(alpha);
	matrix.data[2][2] = cos(alpha);
	matrix.data[3][3] = 1.0;

	return matrix;
}

Matrix4 GUIMyFrame1::YRotation(double alpha) {

	Matrix4 matrix;
	alpha = (alpha * M_PI) / 180.0;

	matrix.data[0][0] = cos(alpha);
	matrix.data[0][2] = -sin(alpha);
	matrix.data[1][1] = 1.0;
	matrix.data[2][0] = sin(alpha);
	matrix.data[2][2] = cos(alpha);
	matrix.data[3][3] = 1.0;

	return matrix;
}

Matrix4 GUIMyFrame1::ZRotation(double alpha) {

	Matrix4 matrix;
	alpha = (alpha * M_PI) / 180.0;

	matrix.data[0][0] = cos(alpha);
	matrix.data[0][1] = -sin(alpha);
	matrix.data[1][0] = sin(alpha);
	matrix.data[1][1] = cos(alpha);
	matrix.data[2][2] = 1.0;
	matrix.data[3][3] = 1.0;

	return matrix;
}

void GUIMyFrame1::GenerateTransformMatrix() {

	Matrix4 m1;
	m1.data[0][0] = 1;
	m1.data[1][1] = 1;
	m1.data[3][2] = 1.0 / 2.0;

	Matrix4 m2;
	m2.data[0][0] = WxPanel->GetSize().GetWidth() / 2;
	m2.data[1][1] = -WxPanel->GetSize().GetHeight() / 2;
	m2.data[0][3] = WxPanel->GetSize().GetWidth() / 2;
	m2.data[1][3] = WxPanel->GetSize().GetHeight() / 2;

	Matrix4 matrix; // transformata skalowania
	matrix.data[0][0] = WxSB_ScaleX->GetValue() / 100.0;
	matrix.data[1][1] = WxSB_ScaleY->GetValue() / 100.0;
	matrix.data[2][2] = WxSB_ScaleZ->GetValue() / 100.0;

	Matrix4 matrix2; // transformata przesuni�cia
	matrix2.data[0][0] = matrix2.data[1][1] = matrix2.data[2][2] = 1;
	matrix2.data[0][3] = (WxSB_TranslationX->GetValue() - 100.0) / 50;
	matrix2.data[1][3] = (WxSB_TranslationY->GetValue() - 100.0) / 50;
	matrix2.data[2][3] = (WxSB_TranslationZ->GetValue() - 100.0) / 50;

	Matrix4 matrix3; // transformata obrotu
	matrix3 = XRotation(WxSB_RotateX->GetValue()) * YRotation(WxSB_RotateY->GetValue()) * ZRotation(WxSB_RotateZ->GetValue());

	t = matrix2 * matrix3 * matrix;
	t1 = m2 * m1;
}

void GUIMyFrame1::getMinYMaxY() {

	if (!(maxY == -1.0e30 && minY == 1.0e30)) {

		return;
	}

	for (int i = 0; i < data.size(); i++) {

		maxY = ((double)data[i].begin.z > maxY ? (double)data[i].begin.z : maxY);
		minY = ((double)data[i].begin.z < minY ? (double)data[i].begin.z : minY);
	}
}

void GUIMyFrame1::Repaint()
{
	// tu rysowac
	wxClientDC DC(WxPanel);
	wxBufferedDC BufferedDC(&DC);
	int width;
	int height;
	WxPanel->GetSize(&width, &height);
	BufferedDC.SetBackground(wxBrush(wxColour("white")));
	BufferedDC.Clear();

	GenerateTransformMatrix();

	getMinYMaxY();

	double colorR = 255;
	double colorB = 0;

	for (int i = 0; i < data.size(); i++) {

		Vector4 begin, end;

		colorR = 255 * ((maxY - data[i].begin.z) * 10000 / (maxY - minY)) / 10000;
		colorB = 255 * ((data[i].begin.z - minY) * 10000 / (maxY - minY)) / 10000;

		BufferedDC.SetPen(wxPen(wxColour(colorR, 0, colorB)));

		BufferedDC.SetPen(wxPen(wxColour(data[i].color.R, data[i].color.G, data[i].color.B)));

		begin.Set(data[i].begin.x, data[i].begin.y, data[i].begin.z);
		end.Set(data[i].end.x, data[i].end.y, data[i].end.z);

		begin = t * begin;
		end = t * end;

		begin.data[0] /= begin.data[3];
		begin.data[1] /= begin.data[3];
		begin.data[2] /= begin.data[3];

		end.data[0] /= end.data[3];
		end.data[1] /= end.data[3];
		end.data[2] /= end.data[3];

		if ((begin.GetZ() > -2.0 && end.GetZ() <= -2.0) || (end.GetZ() > -2.0 && begin.GetZ() <= -2.0)) {

			Vector4 temp1 = end.GetZ() <= -2.0 ? end : begin;
			Vector4 temp2 = end.GetZ() <= -2.0 ? begin : end;
			double r = abs((-2.0 - temp1.data[2]) / (temp2.data[2] - temp1.data[2]));
			temp1.data[0] = (temp2.data[0] - temp1.data[0]) * r + temp1.data[0];
			temp1.data[1] = (temp2.data[1] - temp1.data[1]) * r + temp1.data[1];
			temp1.data[2] = -2.0;

			begin = t1 * temp1;
			end = t1 * temp2;

			begin.data[0] /= begin.data[3];
			begin.data[1] /= begin.data[3];
			begin.data[2] /= begin.data[3];

			end.data[0] /= end.data[3];
			end.data[1] /= end.data[3];
			end.data[2] /= end.data[3];

		}
		else if (begin.GetZ() <= -2.0 && end.GetZ() <= -2.0) {
			continue;
		}
		else {
			begin = t1 * begin;
			end = t1 * end;

			begin.data[0] /= begin.data[3];
			begin.data[1] /= begin.data[3];
			begin.data[2] /= begin.data[3];

			end.data[0] /= end.data[3];
			end.data[1] /= end.data[3];
			end.data[2] /= end.data[3];
		}

		BufferedDC.DrawLine(begin.GetX(), begin.GetY(), end.GetX(), end.GetY());
	}
}