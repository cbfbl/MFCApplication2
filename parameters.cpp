// parameters.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "parameters.h"
#include "afxdialogex.h"


// parameters dialog

IMPLEMENT_DYNAMIC(parameters, CDialogEx)

parameters::parameters(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, a_input(0)
	, b_input(0)
	, s_input(0)
{

}

parameters::~parameters()
{
}

void parameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, a_input);
	DDV_MinMaxInt(pDX, a_input, 1, INT_MAX);
	DDX_Text(pDX, IDC_EDIT2, b_input);
	DDV_MinMaxInt(pDX, b_input, 1, INT_MAX);
	DDX_Text(pDX, IDC_EDIT3, s_input);
	DDV_MinMaxInt(pDX, s_input, 1, INT_MAX);
}


BEGIN_MESSAGE_MAP(parameters, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &parameters::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &parameters::OnBnClickedButton1)
END_MESSAGE_MAP()


// parameters message handlers


void parameters::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void parameters::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
