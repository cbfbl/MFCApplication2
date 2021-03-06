// FogFactorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "FogFactorDialog.h"
#include "afxdialogex.h"


// FogFactorDialog dialog

IMPLEMENT_DYNAMIC(FogFactorDialog, CDialog)

FogFactorDialog::FogFactorDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FogFactorDialog, pParent)
{

}

FogFactorDialog::~FogFactorDialog()
{
}

void FogFactorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_START, fogStart);
    DDX_Text(pDX, IDC_EDIT_END, fogEnd);
}

void FogFactorDialog::SetDialogData(double fogStart, double fogEnd)
{
    this->fogStart = fogStart;
    this->fogEnd = fogEnd;
}
double FogFactorDialog::getFogStart()
{
    return fogStart;
}
double FogFactorDialog::getFogEnd()
{
    return fogEnd;
}


BEGIN_MESSAGE_MAP(FogFactorDialog, CDialog)
END_MESSAGE_MAP()


// FogFactorDialog message handlers
