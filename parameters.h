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
	int m_a_input;
	afx_msg void OnEnChangeEdit2();
	int m_b_input;
	int m_s_input;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
