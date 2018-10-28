
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
	ON_UPDATE_COMMAND_UI(ID_MODE_VALUES, &CMFCApplication2View::OnUpdateModeValues)
	ON_UPDATE_COMMAND_UI(ID_MODE_ZEROS, &CMFCApplication2View::OnUpdateModeZeros)
	ON_COMMAND(ID_MODE_VALUES, &CMFCApplication2View::OnModeValues)
	ON_COMMAND(ID_MODE_ZEROS, &CMFCApplication2View::OnModeZeros)
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

void CMFCApplication2View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	/*
	GetClientRect();
	SetPixel();
	if (discrete_mode) {
		draw with discrete;
	}
	else {
		draw real;
	}
	*/
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
	parameters params;
	params.DoModal();

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
}


void CMFCApplication2View::OnModeZeros()
{
	discrete_mode = false;
	// TODO: Add your command handler code here
}
