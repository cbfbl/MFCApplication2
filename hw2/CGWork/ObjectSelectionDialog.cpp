// ObjectSelectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "ObjectSelectionDialog.h"
#include "afxdialogex.h"


// ObjectSelectionDialog dialog

IMPLEMENT_DYNAMIC(ObjectSelectionDialog, CDialog)

ObjectSelectionDialog::ObjectSelectionDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ObjectSelectionDialog, pParent)
{
    objIdx = 0;
}

ObjectSelectionDialog::~ObjectSelectionDialog()
{
}

BOOL ObjectSelectionDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    for (int i = 0; i < maxObjIdx; i++) {
        CString str;
        str.Format(_T("Model #%00d - %s"), i+1, models[i].name);
        comboObjIdx.AddString(str);
    }
    comboObjIdx.AddString(L"zz All zz");
    comboObjIdx.SetCurSel(objIdx);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void ObjectSelectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, comboObjIdx);
}


BEGIN_MESSAGE_MAP(ObjectSelectionDialog, CDialog)
ON_CBN_SELCHANGE(IDC_COMBO1, &ObjectSelectionDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// ObjectSelectionDialog message handlers
int ObjectSelectionDialog::getIndex() const
{
    return objIdx;
}

/*
    Set newMaxObjIdx if you want to select all objects.
*/
void ObjectSelectionDialog::setIndex(int newObjIdx)
{
    objIdx = newObjIdx;
}

void ObjectSelectionDialog::setModels(vector<GraphicModel>& models)
{
    this->models = models;
}
void ObjectSelectionDialog::setMaxIndex(int newMaxObjIdx)
{
    maxObjIdx = newMaxObjIdx;
}

void ObjectSelectionDialog::OnCbnSelchangeCombo1()
{
    setIndex(comboObjIdx.GetCurSel());
}
