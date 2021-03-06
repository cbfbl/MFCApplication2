#pragma once

// PngRenderDialog dialog

class PngRenderDialog : public CDialog {
    DECLARE_DYNAMIC(PngRenderDialog)

public:
    PngRenderDialog(CWnd* pParent = nullptr); // standard constructor
    virtual ~PngRenderDialog();
    void SetDialogData(int width, int height);
    int getWidth();
    int getHeight();

    int m_height;
    int m_width;

// Dialog Data
#ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_PngRenderDialog };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};
