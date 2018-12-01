// CGWorkView.h : interface of the CCGWorkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGWORKVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_)
#define AFX_CGWORKVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "gl\gl.h"    // Include the standard CGWork  headers
#include "gl\glu.h"   // Add the utility library

#include "Mat4.h"

#include "Light.h"
#include <vector>
using std::vector;


class CCGWorkView : public CView
{
protected: // create from serialization only
	CCGWorkView();
	DECLARE_DYNCREATE(CCGWorkView)

// Attributes
public:
	CCGWorkDoc* GetDocument();

// Operations
public:

private:
	int m_nAxis;				// Axis of Action, X, Y, Z or XY
	int m_nAction;				// Rotate, Translate, Scale
	int m_nView;				// Orthographic, perspective
	bool m_bIsPerspective;			// is the view perspective
	
	CString m_strItdFileName;		// file name of IRIT data

	int m_nLightShading;			// shading: Flat, Gouraud.

	double m_lMaterialAmbient;		// The Ambient in the scene
	double m_lMaterialDiffuse;		// The Diffuse in the scene
	double m_lMaterialSpecular;		// The Specular in the scene
	int m_nMaterialCosineFactor;		// The cosine factor for the specular

	LightParams m_lights[MAX_LIGHT];	//configurable lights array
	LightParams m_ambientLight;		//ambient light (only RGB is used)

    bool drawBoundingBox;
    int drawNormals;
    CPoint lastCursorLocation;
    Mat4 screen;
    vector<double> thetaX;
    vector<double> thetaY;
    vector<double> thetaZ;
    vector<double> scaleX;
    vector<double> scaleY;
    vector<double> scaleZ;
    vector<double> translateX;
    vector<double> translateY;
    vector<double> translateZ;
    double projection_d;
    COLORREF wireframeColor;
    bool useCustomWireframeColor;
    COLORREF normalsColor;
    bool useCustomNormalsColor;
    COLORREF backgroundColor;
    int mouseSensitivity;
	bool object;
    int objIdx;

    void Transform(CPoint diff);
    void Transform(int i, double dx, double dy);
    void drawLine(Vec4& start, Vec4& end, COLORREF color, CDC* dc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGWorkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGWorkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL InitializeCGWork();
	BOOL SetupViewingFrustum(void);
	BOOL SetupViewingOrthoConstAspect(void);

	virtual void RenderScene();


	HGLRC    m_hRC;			// holds the Rendering Context
	CDC*     m_pDC;			// holds the Device Context
	int m_WindowWidth;		// hold the windows width
	int m_WindowHeight;		// hold the windows height
	double m_AspectRatio;		// hold the fixed Aspect Ration

	HBITMAP m_pDbBitMap;
	CDC* m_pDbDC;

// Generated message map functions
protected:
	//{{AFX_MSG(CCGWorkView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileLoad();
	afx_msg void OnViewOrthographic();
	afx_msg void OnUpdateViewOrthographic(CCmdUI* pCmdUI);
	afx_msg void OnViewPerspective();
	afx_msg void OnUpdateViewPerspective(CCmdUI* pCmdUI);
	afx_msg void OnActionRotate();
	afx_msg void OnUpdateActionRotate(CCmdUI* pCmdUI);
	afx_msg void OnActionScale();
	afx_msg void OnUpdateActionScale(CCmdUI* pCmdUI);
	afx_msg void OnActionTranslate();
	afx_msg void OnUpdateActionTranslate(CCmdUI* pCmdUI);
	afx_msg void OnAxisX();
	afx_msg void OnUpdateAxisX(CCmdUI* pCmdUI);
	afx_msg void OnAxisY();
	afx_msg void OnUpdateAxisY(CCmdUI* pCmdUI);
	afx_msg void OnAxisZ();
	afx_msg void OnUpdateAxisZ(CCmdUI* pCmdUI);
	afx_msg void OnLightShadingFlat();
	afx_msg void OnUpdateLightShadingFlat(CCmdUI* pCmdUI);
	afx_msg void OnLightShadingGouraud();
	afx_msg void OnUpdateLightShadingGouraud(CCmdUI* pCmdUI);
	afx_msg void OnLightConstants();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnOptionsMousesensitivity();
    afx_msg void OnAxisXy();
    afx_msg void OnUpdateAxisXy(CCmdUI* pCmdUI);
    afx_msg void OnUpdateViewBoundingbox(CCmdUI* pCmdUI);
    afx_msg void OnViewBoundingbox();
    afx_msg void OnNormalPolygonsCalculated();
    afx_msg void OnUpdateNormalPolygonsCalculated(CCmdUI* pCmdUI);
    afx_msg void OnNormalPolygonsGiven();
    afx_msg void OnUpdateNormalPolygonsGiven(CCmdUI* pCmdUI);
    afx_msg void OnNormalVerticesCalculated();
    afx_msg void OnUpdateNormalVerticesCalculated(CCmdUI* pCmdUI);
    afx_msg void OnNormalVerticesGiven();
    afx_msg void OnUpdateNormalVerticesGiven(CCmdUI* pCmdUI);
    afx_msg void OnNormalNone();
    afx_msg void OnUpdateNormalNone(CCmdUI* pCmdUI);

    afx_msg void OnOptionsWireframecolor();
    afx_msg void OnOptionsNormalscolor();
    afx_msg void OnOptionsBackgroundcolor();
	afx_msg void OnUpdateActionView(CCmdUI *pCmdUI);
	afx_msg void OnUpdateActionObject(CCmdUI *pCmdUI);
	afx_msg void OnActionView();
	afx_msg void OnActionObject();
        afx_msg void OnActionSelectedobject();
        afx_msg void OnOptionsFineness();
};

#ifndef _DEBUG  // debug version in CGWorkView.cpp
inline CCGWorkDoc* CCGWorkView::GetDocument()
   { return (CCGWorkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGWORKVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_)
