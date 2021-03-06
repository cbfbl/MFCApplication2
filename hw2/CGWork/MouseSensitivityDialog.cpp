// MouseSensitivityDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "MouseSensitivityDialog.h"
#include "afxdialogex.h"


// MouseSensitivityDialog dialog

IMPLEMENT_DYNAMIC(MouseSensitivityDialog, CDialog)

MouseSensitivityDialog::MouseSensitivityDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MouseSensitivityDialog, pParent)
{
    sensitivity = 1;
}

MouseSensitivityDialog::~MouseSensitivityDialog()
{
}

void MouseSensitivityDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER1, sliderMouseSensitivity);
    DDX_Control(pDX, IDC_STATIC_MOUSE_SENSITIVITY, textMouseSensitivity);
}


BEGIN_MESSAGE_MAP(MouseSensitivityDialog, CDialog)
ON_WM_HSCROLL()
END_MESSAGE_MAP()


// MouseSensitivityDialog message handlers

void MouseSensitivityDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* slider = (CSliderCtrl*)pScrollBar;
    int nID = slider->GetDlgCtrlID();
    int pos = ((CSliderCtrl*)pScrollBar)->GetPos();
    CWnd* wnd = GetDlgItem(nID);

    switch (nID) {
    default:
        break;
    case IDC_SLIDER1:
        sensitivity = pos;
        updateStaticText();
        UpdateData(FALSE);
        break;
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

int MouseSensitivityDialog::getSensitivity() const
{
    return sensitivity;
}

void MouseSensitivityDialog::setSensitivity(int newValue)
{
    sensitivity = newValue;
}

BOOL MouseSensitivityDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    sliderMouseSensitivity.SetRange(1, 100);
    sliderMouseSensitivity.SetTicFreq(1);
    sliderMouseSensitivity.SetPos(sensitivity);
    updateStaticText();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void MouseSensitivityDialog::updateStaticText()
{
    CString str;
    str.Format(_T("%d"), sensitivity);
    textMouseSensitivity.SetWindowTextW(str);
}
