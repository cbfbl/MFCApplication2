// CGWorkView.cpp : implementation of the CCGWorkView class
//
#include "CGWork.h"
#include "stdafx.h"

#include "CGWorkDoc.h"
#include "CGWorkView.h"

#include <iostream>
using std::cout;
using std::endl;
#include "LightDialog.h"
#include "MaterialDlg.h"
#include "MouseSensitivityDialog.h"
#include "ObjectSelectionDialog.h"
#include "FineNessDialog.h"
#include "PerspectiveCtrlDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "PngWrapper.h"

// For Status Bar access
#include "MainFrm.h"

#include "Mat4.h"

// Use this macro to display text messages in the status bar.
#define STATUS_BAR_TEXT(str) (((CMainFrame*)GetParentFrame())->getStatusBar().SetWindowText(str))

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView

IMPLEMENT_DYNCREATE(CCGWorkView, CView)

BEGIN_MESSAGE_MAP(CCGWorkView, CView)
//{{AFX_MSG_MAP(CCGWorkView)
ON_WM_ERASEBKGND()
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_SIZE()
ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
ON_COMMAND(ID_VIEW_ORTHOGRAPHIC, OnViewOrthographic)
ON_UPDATE_COMMAND_UI(ID_VIEW_ORTHOGRAPHIC, OnUpdateViewOrthographic)
ON_COMMAND(ID_VIEW_PERSPECTIVE, OnViewPerspective)
ON_UPDATE_COMMAND_UI(ID_VIEW_PERSPECTIVE, OnUpdateViewPerspective)
ON_COMMAND(ID_ACTION_ROTATE, OnActionRotate)
ON_UPDATE_COMMAND_UI(ID_ACTION_ROTATE, OnUpdateActionRotate)
ON_COMMAND(ID_ACTION_SCALE, OnActionScale)
ON_UPDATE_COMMAND_UI(ID_ACTION_SCALE, OnUpdateActionScale)
ON_COMMAND(ID_ACTION_TRANSLATE, OnActionTranslate)
ON_UPDATE_COMMAND_UI(ID_ACTION_TRANSLATE, OnUpdateActionTranslate)
ON_COMMAND(ID_AXIS_X, OnAxisX)
ON_UPDATE_COMMAND_UI(ID_AXIS_X, OnUpdateAxisX)
ON_COMMAND(ID_AXIS_Y, OnAxisY)
ON_UPDATE_COMMAND_UI(ID_AXIS_Y, OnUpdateAxisY)
ON_COMMAND(ID_AXIS_Z, OnAxisZ)
ON_UPDATE_COMMAND_UI(ID_AXIS_Z, OnUpdateAxisZ)
ON_COMMAND(ID_AXIS_XY, OnAxisXy)
ON_UPDATE_COMMAND_UI(ID_AXIS_XY, OnUpdateAxisXy)
ON_COMMAND(ID_LIGHT_SHADING_FLAT, OnLightShadingFlat)
ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_FLAT, OnUpdateLightShadingFlat)
ON_COMMAND(ID_LIGHT_SHADING_GOURAUD, OnLightShadingGouraud)
ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_GOURAUD, OnUpdateLightShadingGouraud)
ON_COMMAND(ID_LIGHT_CONSTANTS, OnLightConstants)
ON_COMMAND(ID_OPTIONS_MOUSESENSITIVITY, OnOptionsMousesensitivity)
ON_UPDATE_COMMAND_UI(ID_VIEW_BOUNDINGBOX, OnUpdateViewBoundingbox)
ON_COMMAND(ID_VIEW_BOUNDINGBOX, OnViewBoundingbox)
ON_COMMAND(ID_NORMAL_POLYGONS_CALCULATED, OnNormalPolygonsCalculated)
ON_UPDATE_COMMAND_UI(ID_NORMAL_POLYGONS_CALCULATED, OnUpdateNormalPolygonsCalculated)
ON_COMMAND(ID_NORMAL_POLYGONS_GIVEN, OnNormalPolygonsGiven)
ON_UPDATE_COMMAND_UI(ID_NORMAL_POLYGONS_GIVEN, OnUpdateNormalPolygonsGiven)
ON_COMMAND(ID_NORMAL_VERTICES_CALCULATED, OnNormalVerticesCalculated)
ON_UPDATE_COMMAND_UI(ID_NORMAL_VERTICES_CALCULATED, OnUpdateNormalVerticesCalculated)
ON_COMMAND(ID_NORMAL_VERTICES_GIVEN, OnNormalVerticesGiven)
ON_UPDATE_COMMAND_UI(ID_NORMAL_VERTICES_GIVEN, OnUpdateNormalVerticesGiven)
ON_COMMAND(ID_NORMALS_NONE, OnNormalNone)
ON_UPDATE_COMMAND_UI(ID_NORMALS_NONE, OnUpdateNormalNone)
ON_COMMAND(ID_VIEW_INVERTEDNORMALS, OnInvertedNormals)
ON_UPDATE_COMMAND_UI(ID_VIEW_INVERTEDNORMALS, OnUpdateInvertedNormals)
ON_COMMAND(ID_OPTIONS_WIREFRAMECOLOR, OnOptionsWireframecolor)
ON_COMMAND(ID_OPTIONS_NORMALSCOLOR, OnOptionsNormalscolor)
ON_COMMAND(ID_OPTIONS_BACKGROUNDCOLOR, OnOptionsBackgroundcolor)
ON_UPDATE_COMMAND_UI(ID_ACTION_VIEW, OnUpdateActionView)
ON_UPDATE_COMMAND_UI(ID_ACTION_OBJECT, OnUpdateActionObject)
ON_COMMAND(ID_ACTION_VIEW, OnActionView)
ON_COMMAND(ID_ACTION_OBJECT, OnActionObject)
ON_COMMAND(ID_ACTION_SELECTEDOBJECT, OnActionSelectedobject)
ON_COMMAND(ID_OPTIONS_FINENESS, OnOptionsFineness)
ON_COMMAND(ID_OPTIONS_PERSPECTIVECONTROL32824, OnOptionsPerspectivecontrol32824)
//}}AFX_MSG_MAP
ON_WM_TIMER()
ON_WM_KEYUP()
ON_WM_KEYDOWN()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// A patch to fix GLaux disappearance from VS2005 to VS2008
void auxSolidCone(GLdouble radius, GLdouble height)
{
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluCylinder(quad, radius, 0.0, height, 20, 20);
    gluDeleteQuadric(quad);
}

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView construction/destruction

CCGWorkView::CCGWorkView()
{
    // Set default values
    m_nAxis = ID_AXIS_X;
    m_nAction = ID_ACTION_ROTATE;
    m_nView = ID_VIEW_ORTHOGRAPHIC;
    m_bIsPerspective = false;

    m_nLightShading = ID_LIGHT_SHADING_FLAT;

    m_lMaterialAmbient = 0.2;
    m_lMaterialDiffuse = 0.8;
    m_lMaterialSpecular = 1.0;
    m_nMaterialCosineFactor = 32;

    //init the first light to be enabled
    m_lights[LIGHT_ID_1].enabled = true;
    m_pDbBitMap = NULL;
    m_pDbDC = NULL;

    mouseSensitivity = 5;
    drawBoundingBox = false;
    lastCursorLocation = CPoint();
    objIdx = 0;
    thetaX.push_back(0);
    thetaY.push_back(0);
    thetaZ.push_back(0);
    scaleX.push_back(0.14);
    scaleY.push_back(0.14);
    scaleZ.push_back(0.14);
    translateX.push_back(0);
    translateY.push_back(0);
    translateZ.push_back(0);
    wireframeColor = RGB(0, 0, 0);
    useCustomWireframeColor = false;
    normalsColor = RGB(0, 0, 0);
    useCustomNormalsColor = false;
    backgroundColor = RGB(255, 255, 255);
    object = false;
	d = 2.71828;
	a = 1;
    invertNormals = false;
}

CCGWorkView::~CCGWorkView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView diagnostics

#ifdef _DEBUG
void CCGWorkView::AssertValid() const
{
    CView::AssertValid();
}

void CCGWorkView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CCGWorkDoc* CCGWorkView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGWorkDoc)));
    return (CCGWorkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView Window Creation - Linkage of windows to CGWork

BOOL CCGWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    // An CGWork window must be created with the following
    // flags and must NOT include CS_PARENTDC for the
    // class style.

    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    return CView::PreCreateWindow(cs);
}

int CCGWorkView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    InitializeCGWork();

    return 0;
}

// This method initialized the CGWork system.
BOOL CCGWorkView::InitializeCGWork()
{
    m_pDC = new CClientDC(this);

    if (NULL == m_pDC) { // failure to get DC
        ::AfxMessageBox(CString("Couldn't get a valid DC."));
        return FALSE;
    }

    CRect r;
    GetClientRect(&r);
    m_pDbDC = new CDC();
    m_pDbDC->CreateCompatibleDC(m_pDC);
    SetTimer(1, 1, NULL);
    m_pDbBitMap = CreateCompatibleBitmap(m_pDC->m_hDC, r.right, r.bottom);
    m_pDbDC->SelectObject(m_pDbBitMap);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView message handlers

void CCGWorkView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    if (0 >= cx || 0 >= cy) {
        return;
    }

    // save the width and height of the current window
    m_WindowWidth = cx;
    m_WindowHeight = cy;

    // compute the aspect ratio
    // this will keep all dimension scales equal
    m_AspectRatio = (GLdouble)m_WindowWidth / (GLdouble)m_WindowHeight;

    CRect r;
    GetClientRect(&r);
    DeleteObject(m_pDbBitMap);
    m_pDbBitMap = CreateCompatibleBitmap(m_pDC->m_hDC, r.right, r.bottom);
    m_pDbDC->SelectObject(m_pDbBitMap);

    double half_w = r.Width() / 2;
    double half_h = r.Height() / 2;

    screen = Mat4(
        Vec4(half_h, 0, 0, half_w),
        Vec4(0, -half_h, 0, half_h),
        Vec4(0, 0, 1, 0),
        Vec4(0, 0, 0, 1));
}

BOOL CCGWorkView::SetupViewingFrustum(void)
{
    return TRUE;
}

// This viewing projection gives us a constant aspect ration. This is done by
// increasing the corresponding size of the ortho cube.
BOOL CCGWorkView::SetupViewingOrthoConstAspect(void)
{
    return TRUE;
}

BOOL CCGWorkView::OnEraseBkgnd(CDC* pDC)
{
    // Windows will clear the window with the background color every time your window
    // is redrawn, and then CGWork will clear the viewport with its own background color.

    return true;
}

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView drawing
/////////////////////////////////////////////////////////////////////////////

void CCGWorkView::OnDraw(CDC* pDC)
{
    CCGWorkDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    CRect r;

    GetClientRect(&r);
    CDC* pDCToUse = /*m_pDC*/ m_pDbDC;

    pDCToUse->FillSolidRect(&r, backgroundColor);

    for (size_t i = 0; i < graphicObjects.size(); i++) {
        Mat4 rotateX = Mat4(
            Vec4(1, 0, 0, 0),
            Vec4(0, cos(thetaX[i]), -sin(thetaX[i]), 0),
            Vec4(0, sin(thetaX[i]), cos(thetaX[i]), 0),
            Vec4(0, 0, 0, 1));
        Mat4 rotateY = Mat4(
            Vec4(cos(thetaY[i]), 0, sin(thetaY[i]), 0),
            Vec4(0, 1, 0, 0),
            Vec4(-sin(thetaY[i]), 0, cos(thetaY[i]), 0),
            Vec4(0, 0, 0, 1));
        Mat4 rotateZ = Mat4(
            Vec4(cos(thetaZ[i]), -sin(thetaZ[i]), 0, 0),
            Vec4(sin(thetaZ[i]), cos(thetaZ[i]), 0, 0),
            Vec4(0, 0, 1, 0),
            Vec4(0, 0, 0, 1));
        Mat4 scale = Mat4(
            Vec4(scaleX[i], 0, 0, 0),
            Vec4(0, scaleY[i], 0, 0),
            Vec4(0, 0, scaleZ[i], 0),
            Vec4(0, 0, 0, 1));
        Mat4 translate = Mat4(
            Vec4(1, 0, 0, translateX[i]),
            Vec4(0, 1, 0, translateY[i]),
            Vec4(0, 0, 1, translateZ[i]),
            Vec4(0, 0, 0, 1));
		Mat4 perspective = Mat4(
			Vec4(1, 0, 0, 0),
			Vec4(0, 1, 0, 0),
			Vec4(0, 0, d/(d-a), -a*d/(d-a)),
			Vec4(0, 0, 1 / d, 0));
		Mat4 translateZinit = Mat4(
			Vec4(1, 0, 0, 0),
			Vec4(0, 1, 0, 0),
			Vec4(0, 0, 1, 3.14),
			Vec4(0, 0, 0, 1));
		Mat4 t;
		if (!m_bIsPerspective) {
			perspective = Mat4(
				Vec4(1, 0, 0, 0),
				Vec4(0, 1, 0, 0),
				Vec4(0, 0, 1, 0),
				Vec4(0, 0, 0, 1));
			translateZinit = Mat4(
				Vec4(1, 0, 0, 0),
				Vec4(0, 1, 0, 0),
				Vec4(0, 0, 1, 0),
				Vec4(0, 0, 0, 1));
		}
		if (object) {
			t = screen * perspective * translateZinit * translate * rotateZ * rotateY * rotateX * scale;
		}
		else {
			t = screen * perspective * translateZinit * translate * rotateX * rotateY * rotateZ * scale;
		}
		GraphicObject o = graphicObjects[i];

		COLORREF objectColor = useCustomWireframeColor ? wireframeColor : RGB(o.red, o.green, o.blue);
		COLORREF normalColor = useCustomNormalsColor ? normalsColor : RGB(o.red, o.green, o.blue);

		for (GraphicPolygon p : o.polygons) {
			// Draw the edges of the polygon:
			for (Edge e : p.edges) {
				Vec4 start = t * e.start;
				start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
				Vec4 end = t * e.end;
				end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
				drawLine(start, end, objectColor, pDCToUse);
			}

            // Draw the normals of the polygon:
            Vec4 normal, v0, v1, start, end, direction;
            switch (drawNormals) {
            case ID_NORMAL_POLYGONS_CALCULATED:
                v0 = p.edges[0].end - p.edges[0].start;
                v1 = p.edges[1].end - p.edges[1].start;
                normal = v0.cross(v1).normalize();
                if (invertNormals) {
                    normal = -normal;
                }
                start = t * p.center;
                end = t * (p.center - normal);
                drawLine(start, end, normalColor, pDCToUse);
                break;
            case ID_NORMAL_POLYGONS_GIVEN:
                normal = p.normal;
                if (invertNormals) {
                    normal = -normal;
                }
                start = t * p.center;
                end = t * (p.center - normal);
                drawLine(start, end, normalColor, pDCToUse);
                break;
            case ID_NORMAL_VERTICES_CALCULATED:
                for (Edge e : p.edges) {
                    vector<int> hashVertex;
                    hashVertex.push_back((int)(e.start.x * HASH_PRECISION));
                    hashVertex.push_back((int)(e.start.y * HASH_PRECISION));
                    hashVertex.push_back((int)(e.start.z * HASH_PRECISION));
                    normal = vertexNormals[hashVertex];
                    if (invertNormals) {
                        normal = -normal;
                    }
                    start = t * e.start;
                    end = start - (t * normal);
                    drawLine(start, end, normalColor, pDCToUse);
                }
                break;
            case ID_NORMAL_VERTICES_GIVEN:
                for (Edge e : p.edges) {
                    if (!(e.start.normalX == 0 && e.start.normalY == 0 && e.start.normalZ == 0)) {
                        normal = Vec4(e.start.normalX, e.start.normalY, e.start.normalZ, 0);
                        if (invertNormals) {
                            normal = -normal;
                        }
                        start = t * e.start;
                        end = start + (t * normal);
                        drawLine(start, end, normalColor, pDCToUse);   
                    }
                }
                break;
            default:
                break;
            }
        }

        // Draw the bounding box of the object:
        if (drawBoundingBox) {
            for (Edge e : o.boundingBox) {
                Vec4 start = t * e.start;
                Vec4 end = t * e.end;
                drawLine(start, end, objectColor, pDCToUse);
            }
        }
    }

    if (pDCToUse != m_pDC) {
        m_pDC->BitBlt(r.left, r.top, r.Width(), r.Height(), pDCToUse, r.left, r.top, SRCCOPY);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView CGWork Finishing and clearing...

void CCGWorkView::OnDestroy()
{
    CView::OnDestroy();

    // delete the DC
    if (m_pDC) {
        delete m_pDC;
    }

    if (m_pDbDC) {
        delete m_pDbDC;
    }
}

/////////////////////////////////////////////////////////////////////////////
// User Defined Functions

void CCGWorkView::RenderScene()
{
    // do nothing. This is supposed to be overriden...

    return;
}

void CCGWorkView::OnFileLoad()
{
    TCHAR szFilters[] = _T ("IRIT Data Files (*.itd)|*.itd|All Files (*.*)|*.*||");

    CFileDialog dlg(TRUE, _T("itd"), _T("*.itd"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

    if (dlg.DoModal() == IDOK) {
        m_strItdFileName = dlg.GetPathName(); // Full path and filename
        PngWrapper p;
        graphicObjects.clear();
        CGSkelProcessIritDataFiles(m_strItdFileName, 1);
        // Open the file and read it.
        // Your code here...

        thetaX.clear();
        thetaY.clear();
        thetaZ.clear();
        scaleX.clear();
        scaleY.clear();
        scaleZ.clear();
        translateX.clear();
        translateY.clear();
        translateZ.clear();
        for (GraphicObject o : graphicObjects) {
            thetaX.push_back(0);
            thetaY.push_back(0);
            thetaZ.push_back(0);
            scaleX.push_back(0.14);
            scaleY.push_back(0.14);
            scaleZ.push_back(0.14);
            translateX.push_back(0);
            translateY.push_back(0);
            translateZ.push_back(0);
        }
        objIdx = graphicObjects.size(); // Default to selecting all objects.

        Invalidate(); // force a WM_PAINT for drawing.
    }
}

// VIEW HANDLERS ///////////////////////////////////////////

// Note: that all the following Message Handlers act in a similar way.
// Each control or command has two functions associated with it.

void CCGWorkView::OnViewOrthographic()
{
    m_nView = ID_VIEW_ORTHOGRAPHIC;
    m_bIsPerspective = false;
    Invalidate(); // redraw using the new view.
}

void CCGWorkView::OnUpdateViewOrthographic(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nView == ID_VIEW_ORTHOGRAPHIC);
}

void CCGWorkView::OnViewPerspective()
{
    m_nView = ID_VIEW_PERSPECTIVE;
    m_bIsPerspective = true;
    Invalidate();
}

void CCGWorkView::OnUpdateViewPerspective(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nView == ID_VIEW_PERSPECTIVE);
}

// ACTION HANDLERS ///////////////////////////////////////////

void CCGWorkView::OnActionRotate()
{
    m_nAction = ID_ACTION_ROTATE;
}

void CCGWorkView::OnUpdateActionRotate(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nAction == ID_ACTION_ROTATE);
}

void CCGWorkView::OnActionTranslate()
{
    m_nAction = ID_ACTION_TRANSLATE;
}

void CCGWorkView::OnUpdateActionTranslate(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nAction == ID_ACTION_TRANSLATE);
}

void CCGWorkView::OnActionScale()
{
    m_nAction = ID_ACTION_SCALE;
}

void CCGWorkView::OnUpdateActionScale(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nAction == ID_ACTION_SCALE);
}

// AXIS HANDLERS ///////////////////////////////////////////

// Gets calles when the X button is pressed or when the Axis->X menu is selected.
// The only thing we do here is set the ChildView member variable m_nAxis to the
// selected axis.
void CCGWorkView::OnAxisX()
{
    m_nAxis = ID_AXIS_X;
}

// Gets called when windows has to repaint either the X button or the Axis pop up menu.
// The control is responsible for its redrawing.
// It sets itself disabled when the action is a Scale action.
// It sets itself Checked if the current axis is the X axis.
void CCGWorkView::OnUpdateAxisX(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nAxis == ID_AXIS_X);
}

void CCGWorkView::OnAxisY()
{
    m_nAxis = ID_AXIS_Y;
}

void CCGWorkView::OnUpdateAxisY(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nAxis == ID_AXIS_Y);
}

void CCGWorkView::OnAxisZ()
{
    m_nAxis = ID_AXIS_Z;
}

void CCGWorkView::OnUpdateAxisZ(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nAxis == ID_AXIS_Z);
}

void CCGWorkView::OnAxisXy()
{
    m_nAxis = ID_AXIS_XY;
}

void CCGWorkView::OnUpdateAxisXy(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nAxis == ID_AXIS_XY);
}

// OPTIONS HANDLERS ///////////////////////////////////////////

// LIGHT SHADING HANDLERS ///////////////////////////////////////////

void CCGWorkView::OnLightShadingFlat()
{
    m_nLightShading = ID_LIGHT_SHADING_FLAT;
}

void CCGWorkView::OnUpdateLightShadingFlat(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_FLAT);
}

void CCGWorkView::OnLightShadingGouraud()
{
    m_nLightShading = ID_LIGHT_SHADING_GOURAUD;
}

void CCGWorkView::OnUpdateLightShadingGouraud(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_GOURAUD);
}

// LIGHT SETUP HANDLER ///////////////////////////////////////////

void CCGWorkView::OnLightConstants()
{
    CLightDialog dlg;

    for (int id = LIGHT_ID_1; id < MAX_LIGHT; id++) {
        dlg.SetDialogData((LightID)id, m_lights[id]);
    }
    dlg.SetDialogData(LIGHT_ID_AMBIENT, m_ambientLight);

    if (dlg.DoModal() == IDOK) {
        for (int id = LIGHT_ID_1; id < MAX_LIGHT; id++) {
            m_lights[id] = dlg.GetDialogData((LightID)id);
        }
        m_ambientLight = dlg.GetDialogData(LIGHT_ID_AMBIENT);
    }
    Invalidate();
}

void CCGWorkView::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    //CView::OnTimer(nIDEvent);
    //if (nIDEvent == 1)
    //Invalidate();
}

void CCGWorkView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: Add your message handler code here and/or call default
    CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCGWorkView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: Add your message handler code here and/or call default

    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCGWorkView::OnMouseMove(UINT nFlags, CPoint point)
{
    CView::OnMouseMove(nFlags, point);

    if (nFlags & MK_LBUTTON) {
        CPoint diff = point - lastCursorLocation;
        //TRACE("%d, %d\n", diff.x, diff.y);
        Transform(diff);
    }
    lastCursorLocation.SetPoint(point.x, point.y);
}

void CCGWorkView::Transform(CPoint diff)
{
    double dx = double(diff.x * mouseSensitivity) / 1000;
    double dy = double(-diff.y * mouseSensitivity) / 1000;

    if (objIdx == graphicObjects.size()) {
        // Transform all objects.
        for (int i = 0; i < objIdx; i++) {
            Transform(i, dx, dy);
        }
    } else {
        Transform(objIdx, dx, dy);
    }
    Invalidate();
}


// i == the index of the object to transform.
void CCGWorkView::Transform(int i, double dx, double dy) {
    switch (m_nAxis) {
    case ID_AXIS_X:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            thetaX[i] += dx;
            break;
        case ID_ACTION_SCALE:
            scaleX[i] = max(0.1, scaleX[i] + dx);
            break;
        case ID_ACTION_TRANSLATE:
            translateX[i] += dx;
            break;
        }
        break;
    case ID_AXIS_Y:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            thetaY[i] += dx;
            break;
        case ID_ACTION_SCALE:
            scaleY[i] = max(0.1, scaleY[i] + dx);
            break;
        case ID_ACTION_TRANSLATE:
            translateY[i] += dx;
            break;
        }
        break;
    case ID_AXIS_Z:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            thetaZ[i] += dx;
            break;
        case ID_ACTION_SCALE:
            scaleZ[i] = max(0.1, scaleZ[i] + dx);
            break;
        case ID_ACTION_TRANSLATE:
            translateZ[i] += dx;
            break;
        }
        break;
    case ID_AXIS_XY:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            thetaX[i] += dy;
            thetaY[i] += dx;
            break;
        case ID_ACTION_SCALE:
            scaleX[i] = max(0.1, scaleX[i] + dx);
            scaleY[i] = max(0.1, scaleY[i] + dy);
            break;
        case ID_ACTION_TRANSLATE:
            translateX[i] += dx;
            translateY[i] += dy;
            break;
        }
        break;
    }
}

void CCGWorkView::OnOptionsMousesensitivity()
{
    MouseSensitivityDialog dlg;
    dlg.setSensitivity(mouseSensitivity);
    if (dlg.DoModal() == IDOK) {
        mouseSensitivity = dlg.getSensitivity();
    }
}

void CCGWorkView::OnUpdateViewBoundingbox(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawBoundingBox);
    Invalidate();
}

void CCGWorkView::OnViewBoundingbox()
{
    drawBoundingBox = !drawBoundingBox;
}

void CCGWorkView::OnUpdateNormalPolygonsCalculated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_POLYGONS_CALCULATED);
    Invalidate();
}

void CCGWorkView::OnNormalPolygonsCalculated()
{
    drawNormals = ID_NORMAL_POLYGONS_CALCULATED;
}

void CCGWorkView::OnUpdateNormalPolygonsGiven(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_POLYGONS_GIVEN);
    Invalidate();
}

void CCGWorkView::OnNormalPolygonsGiven()
{
    drawNormals = ID_NORMAL_POLYGONS_GIVEN;
}

void CCGWorkView::OnUpdateNormalVerticesCalculated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_VERTICES_CALCULATED);
    Invalidate();
}

void CCGWorkView::OnNormalVerticesCalculated()
{
    drawNormals = ID_NORMAL_VERTICES_CALCULATED;
}

void CCGWorkView::OnUpdateNormalVerticesGiven(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_VERTICES_GIVEN);
    Invalidate();
}

void CCGWorkView::OnNormalVerticesGiven()
{
    drawNormals = ID_NORMAL_VERTICES_GIVEN;
}
void CCGWorkView::OnUpdateNormalNone(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMALS_NONE);
    Invalidate();
}

void CCGWorkView::OnNormalNone()
{
    drawNormals = ID_NORMALS_NONE;
}

void CCGWorkView::drawLine(Vec4& start, Vec4& end, COLORREF color, CDC* dc)
{
    int x1 = start.x;
    int y1 = start.y;
    int x2 = end.x;
    int y2 = end.y;
    int x = x1;
    int y = y1;
    int dx = x2 - x1 > 0 ? x2 - x1 : x1 - x2;
    int dy = y2 - y1 > 0 ? y2 - y1 : y1 - y2;
    int s1 = x2 > x1 ? 1 : -1;
    int s2 = y2 > y1 ? 1 : -1;
    int change = 0;
    if (dy > dx) {
        int tmp = dx;
        dx = dy;
        dy = tmp;
        change = 1;
    } else {
        change = 0;
    }
    int ne = 2 * dy - dx;
    int a = 2 * dy;
    int b = 2 * dy - 2 * dx;
    dc->SetPixel(x, y, color);
    for (int i = 1; i <= dx; i++) {
        if (ne < 0) {
            if (change == 1) {
                y = y + s2;
            } else {
                x = x + s1;
            }
            ne = ne + a;
        } else {
            y = y + s2;
            x = x + s1;
            ne = ne + b;
        }
        dc->SetPixel(x, y, color);
    }
}

void CCGWorkView::OnOptionsWireframecolor()
{
    CColorDialog colorDialog;
    colorDialog.m_cc.Flags |= CC_RGBINIT;
    colorDialog.m_cc.rgbResult = wireframeColor;
    if (colorDialog.DoModal() == IDOK) {
        wireframeColor = colorDialog.GetColor();
        useCustomWireframeColor = true;
        Invalidate();
    }
}

void CCGWorkView::OnOptionsNormalscolor()
{
    CColorDialog colorDialog;
    colorDialog.m_cc.Flags |= CC_RGBINIT;
    colorDialog.m_cc.rgbResult = normalsColor;
    if (colorDialog.DoModal() == IDOK) {
        normalsColor = colorDialog.GetColor();
        useCustomNormalsColor = true;
        Invalidate();
    }
}

void CCGWorkView::OnOptionsBackgroundcolor()
{
    CColorDialog colorDialog;
    colorDialog.m_cc.Flags |= CC_RGBINIT;
    colorDialog.m_cc.rgbResult = backgroundColor;
    if (colorDialog.DoModal() == IDOK) {
        backgroundColor = colorDialog.GetColor();
        Invalidate();
    }
}

void CCGWorkView::OnUpdateActionView(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(!object);
}

void CCGWorkView::OnUpdateActionObject(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(object);
}

void CCGWorkView::OnActionView()
{
    // TODO: Add your command handler code here
    object = false;
}

void CCGWorkView::OnActionObject()
{
    // TODO: Add your command handler code here
    object = true;
}

void CCGWorkView::OnActionSelectedobject()
{
    ObjectSelectionDialog dlg;
    dlg.setIndex(objIdx);
    dlg.setMaxIndex(graphicObjects.size());
    if (dlg.DoModal() == IDOK) {
        objIdx = dlg.getIndex();
    }
}

void CCGWorkView::OnOptionsFineness()
{
    FineNessDialog dlg;
    dlg.setFineNess(getFineNess());
    if (dlg.DoModal() == IDOK) {
        setFineNess(dlg.getFineNess());
        graphicObjects.clear();
        CGSkelProcessIritDataFiles(m_strItdFileName, 1);
        Invalidate();
    }
}


void CCGWorkView::OnOptionsPerspectivecontrol32824()
{
	// TODO: Add your command handler code here
	PerspectiveCtrlDLG dlg;
	dlg.m_a = a;
	dlg.m_d = d;
	if (dlg.DoModal() == IDOK) {
		d = dlg.getDValue();
		a = dlg.getAValue();
		Invalidate();
	}

}

void CCGWorkView::OnUpdateInvertedNormals(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(invertNormals);
    Invalidate();
}

void CCGWorkView::OnInvertedNormals()
{
    invertNormals = !invertNormals;
}
