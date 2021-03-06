#pragma once

// FineNessDialog dialog

class FineNessDialog : public CDialog {
    DECLARE_DYNAMIC(FineNessDialog)

public:
    FineNessDialog(CWnd* pParent = nullptr); // standard constructor
    virtual ~FineNessDialog();
    int getFineNess() const;
    void setFineNess(int newFineNess);

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_FineNessDialog };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CSliderCtrl sliderFineNess;
    CStatic textFineNess;
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
    int fineNess;
    void updateStaticText();

public:
    virtual BOOL OnInitDialog();
};
