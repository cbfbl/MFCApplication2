// TransparencyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "TransparencyDialog.h"
#include "afxdialogex.h"


// TransparencyDialog dialog

IMPLEMENT_DYNAMIC(TransparencyDialog, CDialog)

TransparencyDialog::TransparencyDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TransparencyDialog, pParent)
{

}

TransparencyDialog::~TransparencyDialog()
{
}

void TransparencyDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_TRANSPARENCY, transparency);
    DDV_MinMaxDouble(pDX, transparency, 0, 1);
}

double TransparencyDialog::getTransparency() const
{
    return this->transparency;
}
void TransparencyDialog::setTransparency(double transparency)
{
    this->transparency = transparency;
}



BEGIN_MESSAGE_MAP(TransparencyDialog, CDialog)
END_MESSAGE_MAP()


// TransparencyDialog message handlers
