// PngRenderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "PngRenderDialog.h"
#include "afxdialogex.h"


// PngRenderDialog dialog

IMPLEMENT_DYNAMIC(PngRenderDialog, CDialog)

PngRenderDialog::PngRenderDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PngRenderDialog, pParent)
{

}

PngRenderDialog::~PngRenderDialog()
{
}

void PngRenderDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
    DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
}

void PngRenderDialog::SetDialogData(int width, int height)
{
    m_width = width;
    m_height = height;
}
int PngRenderDialog::getWidth()
{
    return m_width;
}
int PngRenderDialog::getHeight()
{
    return m_height;
}

BEGIN_MESSAGE_MAP(PngRenderDialog, CDialog)
END_MESSAGE_MAP()


// PngRenderDialog message handlers
