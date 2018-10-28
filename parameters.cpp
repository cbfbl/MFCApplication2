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
	, m_a_input(0)
	, m_b_input(0)
	, m_s_input(0)
{

}

parameters::~parameters()
{
}

void parameters::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_a_input);
	DDV_MinMaxInt(pDX, m_a_input, 1, INT_MAX);
	DDX_Text(pDX, IDC_EDIT2, m_b_input);
	DDV_MinMaxInt(pDX, m_b_input, 1, INT_MAX);
	DDX_Text(pDX, IDC_EDIT3, m_s_input);
	DDV_MinMaxInt(pDX, m_s_input, 1, INT_MAX);
}


BEGIN_MESSAGE_MAP(parameters, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &parameters::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &parameters::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &parameters::OnBnClickedButton2)
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
	CColorDialog color_dlg;
	if (color_dlg.DoModal() == IDOK) {
		COLORREF choosen_color = color_dlg.GetColor();
	}


}


void parameters::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CColorDialog color_dlg;
	color_dlg.m_cc.Flags |= CC_RGBINIT;
	color_dlg.m_cc.rgbResult = RGB(255, 255, 255);
	if (color_dlg.DoModal() == IDOK) {
		COLORREF chosen_color = color_dlg.GetColor();
	}
}
