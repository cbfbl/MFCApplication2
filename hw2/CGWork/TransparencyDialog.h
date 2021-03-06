#pragma once


// TransparencyDialog dialog

class TransparencyDialog : public CDialog
{
	DECLARE_DYNAMIC(TransparencyDialog)

public:
	TransparencyDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TransparencyDialog();
    double getTransparency() const;
    void setTransparency(double transparency);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TransparencyDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    double transparency;

	DECLARE_MESSAGE_MAP()
};
