#ifndef __MY_P__
#define __MY_P__

#include <wx/wx.h>
#include <wx/print.h>
#include <wx/printdlg.h>

#include <memory>

class ImagePrintout : public wxPrintout {
public:
    ImagePrintout(const wxString& title, const wxImage& image)
        : wxPrintout(title), pImage(image) {}

    bool OnPrintPage(int pageNum) override {
        wxDC* dc = GetDC();
        if (dc) {
            int* widthPtr = new int();
            int* heightPtr = new int();
            GetPageSizePixels(widthPtr, heightPtr);

            FitThisSizeToPage(wxSize(pImage.GetWidth(), pImage.GetHeight()));
            wxCoord xOffset = (*widthPtr - pImage.GetWidth()) / 2;
            wxCoord yOffset = (*heightPtr - pImage.GetHeight()) / 2;
            wxBitmap bitmap(pImage);
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
    wxImage pImage;
};

#endif
