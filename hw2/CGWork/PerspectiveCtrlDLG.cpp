// PerspectiveCtrlDLG.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "PerspectiveCtrlDLG.h"
#include "afxdialogex.h"


// PerspectiveCtrlDLG dialog

IMPLEMENT_DYNAMIC(PerspectiveCtrlDLG, CDialogEx)

PerspectiveCtrlDLG::PerspectiveCtrlDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSPECTIVE_CONTROL, pParent)
	, m_d(2.71828)
	, m_a(1)
{

}

PerspectiveCtrlDLG::~PerspectiveCtrlDLG()
{
}

void PerspectiveCtrlDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_d);
	DDV_MinMaxDouble(pDX, m_d, 0.5, 3.5);
	DDX_Text(pDX, IDC_EDIT3, m_a);
	DDV_MinMaxDouble(pDX, m_a, 0.5, 1.5);
}


BEGIN_MESSAGE_MAP(PerspectiveCtrlDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &PerspectiveCtrlDLG::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &PerspectiveCtrlDLG::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &PerspectiveCtrlDLG::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &PerspectiveCtrlDLG::OnEnChangeEdit3)
END_MESSAGE_MAP()


// PerspectiveCtrlDLG message handlers








void PerspectiveCtrlDLG::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void PerspectiveCtrlDLG::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

double PerspectiveCtrlDLG::getDValue()
{
	return m_d;
}

double PerspectiveCtrlDLG::getAValue()
{
	return m_a;
}


void PerspectiveCtrlDLG::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void PerspectiveCtrlDLG::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
