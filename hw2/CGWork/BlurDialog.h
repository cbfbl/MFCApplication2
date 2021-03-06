#pragma once


// BlurDialog dialog

class BlurDialog : public CDialog
{
	DECLARE_DYNAMIC(BlurDialog)

public:
	BlurDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BlurDialog();
    double getBlur() const;
    void setBlur(double blur);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BlurDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    double blur;

	DECLARE_MESSAGE_MAP()
};
