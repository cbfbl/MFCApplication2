#pragma once


// PerspectiveCtrlDLG dialog

class PerspectiveCtrlDLG : public CDialogEx
{
	DECLARE_DYNAMIC(PerspectiveCtrlDLG)

public:
	PerspectiveCtrlDLG(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PerspectiveCtrlDLG();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSPECTIVE_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	double getDValue();
	double getAValue();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	double m_d;
	double m_a;
};
