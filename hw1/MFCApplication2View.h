
// MFCApplication2View.h : interface of the CMFCApplication2View class
//

#pragma once


class CMFCApplication2View : public CView
{
protected: // create from serialization only
	CMFCApplication2View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication2View)

// Attributes
public:
	CMFCApplication2Doc* GetDocument() const;

// Operations
public:
	double CMFCApplication2View::HomeworkFunction(int x,int y);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCApplication2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnParametersinputParameters();
	afx_msg void OnUpdateModeValues(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeZeros(CCmdUI *pCmdUI);
//    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    private :
	bool discrete_mode{ true };
public:
	afx_msg void OnModeValues();
	afx_msg void OnModeZeros();
	int m_a;
	int m_b;
	int m_s;
	COLORREF m_c1;
	COLORREF m_c2;
    virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in MFCApplication2View.cpp
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

