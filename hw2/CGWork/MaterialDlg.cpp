// MaterialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "MaterialDlg.h"


// CMaterialDlg dialog

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialog)

CMaterialDlg::CMaterialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialDlg::IDD, pParent)
	, m_ambient(0)
	, m_diffuse(0)
	, m_shininess(0)
	, m_specular(0)
{

}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_MATERIAL_AMBIENT, m_ambient);
    DDV_MinMaxDouble(pDX, m_ambient, 0, 1);
    DDX_Text(pDX, IDC_MATERIAL_DIFFUSE, m_diffuse);
    DDV_MinMaxDouble(pDX, m_diffuse, 0, 1);
    DDX_Text(pDX, IDC_MATERIAL_SHININESS, m_shininess);
    DDV_MinMaxDouble(pDX, m_shininess, 0, 1);
    DDX_Text(pDX, IDC_MATERIAL_SPECULAR, m_specular);
}

void CMaterialDlg::SetDialogData(double ambient, double diffuse, double shininess, int specular)
{
    m_ambient = ambient;
    m_diffuse = diffuse;
    m_shininess = shininess;
    m_specular = specular;
}
double CMaterialDlg::getAmbient()
{
    return m_ambient;
}
double CMaterialDlg::getDiffuse()
{
    return m_diffuse;
}
double CMaterialDlg::getShininess()
{
    return m_shininess;
}
int CMaterialDlg::getSpecular()
{
    return m_specular;
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialog)
END_MESSAGE_MAP()


// CMaterialDlg message handlers
