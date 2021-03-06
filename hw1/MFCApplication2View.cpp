
// MFCApplication2View.cpp : implementation of the CMFCApplication2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"
#include "parameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PARAMETERSINPUT_PARAMETERS, &CMFCApplication2View::OnParametersinputParameters)
    ON_COMMAND(ID_OPEN_PARAMS_DIALOG, &CMFCApplication2View::OnParametersinputParameters)
	ON_UPDATE_COMMAND_UI(ID_MODE_VALUES, &CMFCApplication2View::OnUpdateModeValues)
	ON_UPDATE_COMMAND_UI(ID_MODE_ZEROS, &CMFCApplication2View::OnUpdateModeZeros)
	ON_COMMAND(ID_MODE_VALUES, &CMFCApplication2View::OnModeValues)
	ON_COMMAND(ID_MODE_ZEROS, &CMFCApplication2View::OnModeZeros)
//        ON_WM_CREATE()
        END_MESSAGE_MAP()

// CMFCApplication2View construction/destruction

CMFCApplication2View::CMFCApplication2View() noexcept
{
	// TODO: add construction code here
}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View drawing

void CMFCApplication2View::OnDraw(CDC* pDC)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect clientRect;
	GetClientRect(clientRect);
	long width = clientRect.Width();
	long height = clientRect.Height();
	
	if (discrete_mode) {
		for (long cx = 0; cx < width; cx++) {
			for (long cy = 0; cy < height; cy++) {
				if (HomeworkFunction(cx, cy) > 0) {
					pDC->SetPixel(cx, cy, m_c1); // put c1
				}
				else {
					pDC->SetPixel(cx, cy, m_c2); // put c2
				}
			}
		}
	}
	else {
		for (long cx = 0; cx < width; cx++) {
			for (long cy = 0; cy < height; cy++) {
				double n_t = (HomeworkFunction(cx, cy) + 1) / 2;
				int new_red = int((GetRValue(m_c1)*(1 - n_t) + GetRValue(m_c2)*n_t)) % 256;
				int new_green = int((GetGValue(m_c1)*(1 - n_t) + GetGValue(m_c2)*n_t)) % 256;
				int new_blue = int((GetBValue(m_c1)*(1 - n_t) + GetBValue(m_c2)*n_t)) % 256;
				pDC->SetPixel(cx, cy, RGB(new_red,new_green,new_blue));
			}
		}
	}
	
}

void CMFCApplication2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication2View diagnostics

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View message handlers


void CMFCApplication2View::OnParametersinputParameters()
{
	// TODO: Add your command handler code here
	
	//TODO perhaps change the way m_s is recieved
	parameters params;
	INT_PTR nRet = -1;
	params.m_a_input = m_a;
	params.m_b_input = m_b;
	params.m_s_input = m_s;
	params.m_c1_input = m_c1;
	params.m_c2_input = m_c2;
	nRet = params.DoModal();
	switch(nRet)
	{
		case IDOK : 
		m_a = params.m_a_input;
		m_b = params.m_b_input;
		m_s = params.m_s_input;
		m_c1 = params.m_c1_input;
		m_c2 = params.m_c2_input;
		Invalidate();
		UpdateWindow();
		break;
		default :
			return;
	}
}


void CMFCApplication2View::OnUpdateModeValues(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(discrete_mode);
}


void CMFCApplication2View::OnUpdateModeZeros(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!discrete_mode);
}


void CMFCApplication2View::OnModeValues()
{
	// TODO: Add your command handler code here
	discrete_mode = true;
	Invalidate();
	UpdateWindow();
}


void CMFCApplication2View::OnModeZeros()
{
	
	// TODO: Add your command handler code here
	discrete_mode = false;
	Invalidate();
	UpdateWindow();
}

double CMFCApplication2View::HomeworkFunction(int x,int y)
{
	//TODO add real width and height
	CRect clientRect;
	GetClientRect(clientRect);
	long width = clientRect.Width();
	long height = clientRect.Height();
	double n_res = cos((pow((m_a*(x - (width / 2))),4) + pow((m_b*(y - (height / 2))),4)) / pow(m_s, 3));
	return n_res;
}


void CMFCApplication2View::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // Initialize draw parameters.

    CRect clientRect;
    GetClientRect(clientRect);
    long width = clientRect.Width();
    long height = clientRect.Height();

    m_a = 1;
    m_b = 1;
    m_s = width / 10;
    m_c1 = RGB(0, 0, 0);
    m_c2 = RGB(255, 255, 255);
}
