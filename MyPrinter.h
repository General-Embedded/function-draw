#ifndef __MY_P__
#define __MY_P__

#include <wx/wx.h>
#include <wx/print.h>
#include <wx/printdlg.h>

#include <memory>

class ImagePrintout : public wxPrintout {
public:
    ImagePrintout(const wxString& title, const wxImage& image)
        : wxPrintout(title), m_image(image) {}

    bool OnPrintPage(int pageNum) override {
        wxDC* dc = GetDC();
        if (dc) {
            int* widthPtr = new int();
            int* heightPtr = new int();
            GetPageSizePixels(widthPtr, heightPtr);

            FitThisSizeToPage(wxSize(m_image.GetWidth(), m_image.GetHeight()));
            wxCoord xOffset = (*widthPtr - m_image.GetWidth()) / 2;
            wxCoord yOffset = (*heightPtr - m_image.GetHeight()) / 2;
            wxBitmap bitmap(m_image);
            dc->DrawBitmap(bitmap, xOffset, yOffset, false);

            delete widthPtr;
            delete heightPtr;

            return true;
        }
        return false;
    }

    bool HasPage(int pageNum) override {
        return pageNum == 1;
    }

private:
    wxImage m_image;
};

#endif
