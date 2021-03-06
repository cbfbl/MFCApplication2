// BlurDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "BlurDialog.h"
#include "afxdialogex.h"


// BlurDialog dialog

IMPLEMENT_DYNAMIC(BlurDialog, CDialog)

BlurDialog::BlurDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BlurDialog, pParent)
{

}

BlurDialog::~BlurDialog()
{
}

void BlurDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_BLUR, blur);
    DDV_MinMaxDouble(pDX, blur, 0, 1);
}

double BlurDialog::getBlur() const
{
    return this->blur;
}
void BlurDialog::setBlur(double blur)
{
    this->blur = blur;
}


BEGIN_MESSAGE_MAP(BlurDialog, CDialog)
END_MESSAGE_MAP()


// BlurDialog message handlers
