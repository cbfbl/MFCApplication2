#pragma once


// parameters dialog

class parameters : public CDialogEx
{
	DECLARE_DYNAMIC(parameters)

public:
	parameters(CWnd* pParent = nullptr);   // standard constructor
	virtual ~parameters();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int a_input;
	afx_msg void OnEnChangeEdit2();
	int b_input;
	int s_input;
	afx_msg void OnBnClickedButton1();
};
