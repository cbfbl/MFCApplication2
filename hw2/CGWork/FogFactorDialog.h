#pragma once


// FogFactorDialog dialog

class FogFactorDialog : public CDialog
{
	DECLARE_DYNAMIC(FogFactorDialog)

public:
	FogFactorDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~FogFactorDialog();
    void SetDialogData(double fogStart, double fogEnd);
    double getFogStart();
    double getFogEnd();
    

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FogFactorDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    double fogStart;
    double fogEnd;
	DECLARE_MESSAGE_MAP()
};
