// CGWorkView.h : interface of the CCGWorkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGWORKVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_)
#define AFX_CGWORKVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "CGWork.h"
#include "stdafx.h"
#include "CGWorkDoc.h"
#include <iostream>
using std::cout;
using std::endl;
#include "BlurDialog.h"
#include "FineNessDialog.h"
#include "FogFactorDialog.h"
#include "LightDialog.h"
#include "MainFrm.h"
#include "Mat4.h"
#include "MaterialDlg.h"
#include "MouseSensitivityDialog.h"
#include "PerspectiveCtrlDLG.h"
#include "PngRenderDialog.h"
#include "TransparencyDialog.h"
#include "iritSkel.h"
#include "Light.h"
#include <algorithm>
#include <tuple>
#include <vector>
#include <set>
using std::tuple;
using std::vector;
#include "AliasFilter.h"
#include "GraphicModel.h"
#include "PngWrapper.h"

#include "gl\gl.h" // Include the standard CGWork  headers
#include "gl\glu.h" // Add the utility library



class CCGWorkView : public CView {
protected: // create from serialization only
    CCGWorkView();
    DECLARE_DYNCREATE(CCGWorkView)

    // Attributes
public:
    CCGWorkDoc* GetDocument();

    // Operations
public:
private:
    int m_nAxis; // Axis of Action, X, Y, Z or XY
    int m_nAction; // Rotate, Translate, Scale
    int m_nView; // Orthographic, perspective
    bool m_bIsPerspective; // is the view perspective

    CString m_strItdFileName; // file name of IRIT data

    int m_nLightShading; // shading: Flat, Gouraud.

    double m_lMaterialAmbient; // The Ambient in the scene
    double m_lMaterialDiffuse; // The Diffuse in the scene
    double m_lMaterialSpecular; // The Specular in the scene
    int m_nMaterialCosineFactor; // The cosine factor for the specular

    LightParams m_lights[MAX_LIGHT]; //configurable lights array
    LightParams m_ambientLight; //ambient light (only RGB is used)

    bool drawBoundingBox;
    bool drawSilhouette;
    int drawNormals;
    CPoint lastCursorLocation;
    Mat4 screen;
	Mat4 screen_inverse;
    vector<GraphicModel> models;
    double projection_d;
    COLORREF normalsColor;
    bool useCustomNormalsColor;
    COLORREF backgroundColor;
    COLORREF silhouetteColor;
    int mouseSensitivity;
    bool object;
    int modelIdx;
    double d;
    double a;
    bool invertNormals;
    bool renderScreen;
    bool cullBackfaces;
    bool bgStretch;
    bool useCalculateNormals;
    bool bonusBackfaceCulling;
    vector<vector<double>> zbuffer;
    vector<vector<COLORREF>> cbuffer;
    vector<vector<COLORREF>> bgbuffer;

    bool enableFog;
    COLORREF fogColor;
    double fogStart; // Z (depth) values, closest to the viewer.
    double fogEnd; // Z (depth) values, farthest away from the viewer.

    int antiAliasing;
    AliasFilter filterSinc3, filterSinc5;
    AliasFilter filterBox3, filterBox5;
    AliasFilter filterHat3, filterHat5;
    AliasFilter filterGaussian3, filterGaussian5;

    bool animationIsRecording;
    bool animationIsPlaying;
    int animationCurrentKeyFrame;
    int animationInterpolVar;
    int animationFramesBetweenKeyFrames;
    const int ANIMATION_FRAMES_STEP = 5;

    double blur;
    bool blurDone;
    vector<vector<COLORREF>> cbufferBlur;

    double transparency;
    bool transparencyEnabled;

    void Transform(CPoint diff);
    void Transform(GraphicModel& model, double dx, double dy);
    void drawLine(Vec4& start, Vec4& end, COLORREF color);
    Edge getNormalToPolygon(GraphicPolygon& p, Mat4& t, bool calculated);
    Edge getNormalToVertex(Vec4& v, Mat4& t, bool calculated);
    COLORREF getColorAfterShading(Edge& ne, COLORREF objectColor, Mat4& t);
    COLORREF getBgValue(int x, int y, int width, int height);
    void renderSceneToFile(int width, int height, CString& pngPath);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCGWorkView)
public:
    virtual void OnDraw(CDC* pDC); // overridden to draw this view
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

    virtual void RenderScene(int width, int height);

    HGLRC m_hRC; // holds the Rendering Context
    CDC* m_pDC; // holds the Device Context
    int m_WindowWidth; // hold the windows width
    int m_WindowHeight; // hold the windows height
    double m_AspectRatio; // hold the fixed Aspect Ration

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
    afx_msg void OnFileClear();
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
    afx_msg void OnLightShadingPhong();
    afx_msg void OnUpdateLightShadingPhong(CCmdUI* pCmdUI);
    afx_msg void OnLightConstants();
    afx_msg void OnMaterialConstants();
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
    afx_msg void OnUpdateViewSilhouette(CCmdUI* pCmdUI);
    afx_msg void OnViewSilhouette();
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
    afx_msg void OnUpdateInvertedNormals(CCmdUI* pCmdUI);
    afx_msg void OnInvertedNormals();
    afx_msg void OnUpdateRenderWireframe(CCmdUI* pCmdUI);
    afx_msg void OnRenderWireframe();
    afx_msg void OnUpdateRenderScreen(CCmdUI* pCmdUI);
    afx_msg void OnRenderScreen();
    afx_msg void OnUpdateRenderFile(CCmdUI* pCmdUI);
    afx_msg void OnRenderFile();
    afx_msg void OnUpdateBackfaceCulling(CCmdUI* pCmdUI);
    afx_msg void OnBackfaceCulling();
    afx_msg void OnUpdateBonusBackfaceCulling(CCmdUI* pCmdUI);
    afx_msg void OnBonusBackfaceCulling();
    afx_msg void OnUpdateBgStretch(CCmdUI* pCmdUI);
    afx_msg void OnBgStretch();
    afx_msg void OnUpdateBgRepeat(CCmdUI* pCmdUI);
    afx_msg void OnBgRepeat();
    afx_msg void OnBgLoad();
    afx_msg void OnBgClear();

    afx_msg void OnOptionsWireframecolor();
    afx_msg void OnOptionsSilhouettecolor();
    afx_msg void OnOptionsNormalscolor();
    afx_msg void OnOptionsBackgroundcolor();
    afx_msg void OnUpdateActionView(CCmdUI* pCmdUI);
    afx_msg void OnUpdateActionObject(CCmdUI* pCmdUI);
    afx_msg void OnActionView();
    afx_msg void OnActionObject();
    afx_msg void OnOptionsFineness();
    afx_msg void OnOptionsPerspectivecontrol32824();
    afx_msg void OnUpdateUseCalculatedNormals(CCmdUI* pCmdUI);
    afx_msg void OnUseCalculatedNormals();
    afx_msg void OnFogEnable();
    afx_msg void OnUpdateFogEnable(CCmdUI* pCmdUI);
    afx_msg void OnFogColor();
    afx_msg void OnFogFactor();
    afx_msg void OnAntiAliasingNone();
    afx_msg void OnUpdateAntiAliasingNone(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingSinc3();
    afx_msg void OnUpdateAntiAliasingSinc3(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingSinc5();
    afx_msg void OnUpdateAntiAliasingSinc5(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingBox3();
    afx_msg void OnUpdateAntiAliasingBox3(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingBox5();
    afx_msg void OnUpdateAntiAliasingBox5(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingHat3();
    afx_msg void OnUpdateAntiAliasingHat3(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingHat5();
    afx_msg void OnUpdateAntiAliasingHat5(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingGaussian3();
    afx_msg void OnUpdateAntiAliasingGaussian3(CCmdUI* pCmdUI);
    afx_msg void OnAntiAliasingGaussian5();
    afx_msg void OnUpdateAntiAliasingGaussian5(CCmdUI* pCmdUI);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnAnimationRecordStart();
    afx_msg void OnAnimationRecordStop();
    afx_msg void OnAnimationPlay();
    afx_msg void OnAnimationFaster();
    afx_msg void OnAnimationSlower();
    afx_msg void OnAnimationToFile();
    afx_msg void OnAnimationRenderBlur();
    afx_msg void OnAnimationBlur();
    afx_msg void OnTransparency();
    afx_msg void OnTransparencyEnabled();
    afx_msg void OnUpdateTransparencyEnabled(CCmdUI* pCmdUI);
    afx_msg void OnUpdateModelSelect(CCmdUI* pCmdUI);
    afx_msg void OnModelSelect(UINT nID);
};

#ifndef _DEBUG // debug version in CGWorkView.cpp
inline CCGWorkDoc* CCGWorkView::GetDocument()
{
    return (CCGWorkDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGWORKVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_)
