// FineNessDialog.cpp : implementation file
//

#include "CGWork.h"
#include "FineNessDialog.h"
#include "afxdialogex.h"
#include "stdafx.h"

// FineNessDialog dialog

IMPLEMENT_DYNAMIC(FineNessDialog, CDialog)

FineNessDialog::FineNessDialog(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_FineNessDialog, pParent)
{
    fineNess = 20;
}

FineNessDialog::~FineNessDialog()
{
}

void FineNessDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_FINENESS, sliderFineNess);
    DDX_Control(pDX, IDC_STATIC_FINENESS, textFineNess);
}

BEGIN_MESSAGE_MAP(FineNessDialog, CDialog)
ON_WM_HSCROLL()
END_MESSAGE_MAP()

// FineNessDialog message handlers

void FineNessDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* slider = (CSliderCtrl*)pScrollBar;
    int nID = slider->GetDlgCtrlID();
    int pos = ((CSliderCtrl*)pScrollBar)->GetPos();
    CWnd* wnd = GetDlgItem(nID);

    switch (nID) {
    default:
        break;
    case IDC_SLIDER_FINENESS:
        fineNess = pos;
        updateStaticText();
        UpdateData(FALSE);
        break;
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

int FineNessDialog::getFineNess() const
{
    return fineNess;
}

void FineNessDialog::setFineNess(int newFineNess)
{
    fineNess = newFineNess;
}

BOOL FineNessDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    sliderFineNess.SetRange(2, 20);
    sliderFineNess.SetTicFreq(1);
    sliderFineNess.SetPos(fineNess);
    updateStaticText();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void FineNessDialog::updateStaticText()
{
    CString str;
    str.Format(_T("%d"), fineNess);
    textFineNess.SetWindowTextW(str);
}
