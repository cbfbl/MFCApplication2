// CGWorkView.cpp : implementation of the CCGWorkView class
//
#include "CGWork.h"
#include "stdafx.h"

#include "CGWorkDoc.h"
#include "CGWorkView.h"

#include <iostream>
using std::cout;
using std::endl;
#include "FineNessDialog.h"
#include "LightDialog.h"
#include "MaterialDlg.h"
#include "MouseSensitivityDialog.h"
#include "ObjectSelectionDialog.h"
#include "PerspectiveCtrlDLG.h"
#include "PngRenderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
ON_COMMAND(ID_SHADING_PHONG, OnLightShadingPhong)
ON_UPDATE_COMMAND_UI(ID_SHADING_PHONG, OnUpdateLightShadingPhong)
ON_COMMAND(ID_LIGHT_CONSTANTS, OnLightConstants)
ON_COMMAND(ID_LIGHT_MATERIAL, OnMaterialConstants)
ON_COMMAND(ID_OPTIONS_MOUSESENSITIVITY, OnOptionsMousesensitivity)
ON_UPDATE_COMMAND_UI(ID_VIEW_BOUNDINGBOX, OnUpdateViewBoundingbox)
ON_COMMAND(ID_VIEW_BOUNDINGBOX, OnViewBoundingbox)
ON_UPDATE_COMMAND_UI(ID_VIEW_SILHOUETTE, OnUpdateViewSilhouette)
ON_COMMAND(ID_VIEW_SILHOUETTE, OnViewSilhouette)
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
ON_COMMAND(ID_OPTIONS_SILHOUETTE_COLOR, OnOptionsSilhouettecolor)
ON_COMMAND(ID_OPTIONS_NORMALSCOLOR, OnOptionsNormalscolor)
ON_COMMAND(ID_OPTIONS_BACKGROUNDCOLOR, OnOptionsBackgroundcolor)
ON_UPDATE_COMMAND_UI(ID_ACTION_VIEW, OnUpdateActionView)
ON_UPDATE_COMMAND_UI(ID_ACTION_OBJECT, OnUpdateActionObject)
ON_COMMAND(ID_ACTION_VIEW, OnActionView)
ON_COMMAND(ID_ACTION_OBJECT, OnActionObject)
ON_UPDATE_COMMAND_UI(ID_OPTIONS_USECALCULATEDNORMALS, OnUpdateUseCalculatedNormals)
ON_COMMAND(ID_OPTIONS_USECALCULATEDNORMALS, OnUseCalculatedNormals)
ON_COMMAND(ID_ACTION_SELECTEDOBJECT, OnActionSelectedobject)
ON_COMMAND(ID_OPTIONS_FINENESS, OnOptionsFineness)
ON_COMMAND(ID_OPTIONS_PERSPECTIVECONTROL32824, OnOptionsPerspectivecontrol32824)
ON_COMMAND(ID_RENDER_WIREFRAME, OnRenderWireframe)
ON_UPDATE_COMMAND_UI(ID_RENDER_WIREFRAME, OnUpdateRenderWireframe)
ON_COMMAND(ID_RENDER_SCREEN, OnRenderScreen)
ON_UPDATE_COMMAND_UI(ID_RENDER_SCREEN, OnUpdateRenderScreen)
ON_COMMAND(ID_RENDER_FILE, OnRenderFile)
ON_UPDATE_COMMAND_UI(ID_RENDER_FILE, OnUpdateRenderFile)
ON_COMMAND(ID_RENDER_BACKFACECULLING, OnBackfaceCulling)
ON_UPDATE_COMMAND_UI(ID_RENDER_BACKFACECULLING, OnUpdateBackfaceCulling)
ON_COMMAND(ID_RENDER_BONUSBACKFACECULLING, OnBonusBackfaceCulling)
ON_UPDATE_COMMAND_UI(ID_RENDER_BONUSBACKFACECULLING, OnUpdateBonusBackfaceCulling)
ON_COMMAND(ID_BG_LOAD, OnBgLoad)
ON_COMMAND(ID_BG_CLEAR, OnBgClear)
ON_COMMAND(ID_BG_STRETCH, OnBgStretch)
ON_UPDATE_COMMAND_UI(ID_BG_STRETCH, OnUpdateBgStretch)
ON_COMMAND(ID_BG_REPEAT, OnBgRepeat)
ON_UPDATE_COMMAND_UI(ID_BG_REPEAT, OnUpdateBgRepeat)
ON_COMMAND(ID_FOG_COLOR, OnFogColor)
ON_COMMAND(ID_FOG_ENABLE, OnFogEnable)
ON_UPDATE_COMMAND_UI(ID_FOG_ENABLE, OnUpdateFogEnable)
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
    m_lights[LIGHT_ID_1].type = LIGHT_TYPE_POINT;
    m_pDbBitMap = NULL;
    m_pDbDC = NULL;

    mouseSensitivity = 5;
    drawBoundingBox = false;
    drawSilhouette = false;
    lastCursorLocation = CPoint();
    modelIdx = 0;
    normalsColor = RGB(0, 0, 0);
    useCustomNormalsColor = false;
    backgroundColor = RGB(255, 255, 255);
    silhouetteColor = RGB(255, 255, 0);
    object = false;
    d = 2.71828;
    a = 1;
    invertNormals = false;
    renderScreen = false;
    cullBackfaces = false;
    bonusBackfaceCulling = false;
    bgStretch = true;
    useCalculateNormals = true;
    enableFog = false;
    fogColor = RGB(220, 220, 220);
    //bgbuffer = vector<vector<COLORREF>>(0);
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
    RenderScene(m_WindowWidth, m_WindowHeight);
    for (size_t i = 0; i < m_WindowWidth; i++) {
        for (size_t j = 0; j < m_WindowHeight; j++) {
            if (cbuffer[i][j] != backgroundColor) {
                pDCToUse->SetPixel(i, j, cbuffer[i][j]);
            } else if (!bgbuffer.empty()) {
                pDCToUse->SetPixel(i, j, getBgValue(i, j, m_WindowWidth, m_WindowHeight));
            }
        }
    }

    if (pDCToUse != m_pDC) {
        m_pDC->BitBlt(r.left, r.top, r.Width(), r.Height(), pDCToUse, r.left, r.top, SRCCOPY);
    }
}

void CCGWorkView::RenderScene(int width, int height)
{
    zbuffer = vector<vector<double>>(width);
    for (size_t i = 0; i < width; i++) {
        zbuffer[i] = vector<double>(height);
        for (size_t j = 0; j < height; j++) {
            zbuffer[i][j] = DBL_MAX;
        }
    }
    cbuffer = vector<vector<COLORREF>>(width);
    for (size_t i = 0; i < width; i++) {
        cbuffer[i] = vector<COLORREF>(height);
        for (size_t j = 0; j < height; j++) {
            cbuffer[i][j] = backgroundColor;
        }
    }

    for (size_t i = 0; i < models.size(); i++) {
        GraphicModel model = models[i];
        Mat4 rotateX = Mat4(
            Vec4(1, 0, 0, 0),
            Vec4(0, cos(model.thetaX), -sin(model.thetaX), 0),
            Vec4(0, sin(model.thetaX), cos(model.thetaX), 0),
            Vec4(0, 0, 0, 1));
        Mat4 rotateY = Mat4(
            Vec4(cos(model.thetaY), 0, sin(model.thetaY), 0),
            Vec4(0, 1, 0, 0),
            Vec4(-sin(model.thetaY), 0, cos(model.thetaY), 0),
            Vec4(0, 0, 0, 1));
        Mat4 rotateZ = Mat4(
            Vec4(cos(model.thetaZ), -sin(model.thetaZ), 0, 0),
            Vec4(sin(model.thetaZ), cos(model.thetaZ), 0, 0),
            Vec4(0, 0, 1, 0),
            Vec4(0, 0, 0, 1));
        Mat4 scale = Mat4(
            Vec4(model.scaleX, 0, 0, 0),
            Vec4(0, model.scaleY, 0, 0),
            Vec4(0, 0, model.scaleZ, 0),
            Vec4(0, 0, 0, 1));
        Mat4 translate = Mat4(
            Vec4(1, 0, 0, model.translateX),
            Vec4(0, 1, 0, model.translateY),
            Vec4(0, 0, 1, model.translateZ),
            Vec4(0, 0, 0, 1));
        Mat4 perspective = Mat4(
            Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0),
            Vec4(0, 0, d / (d - a), -a * d / (d - a)),
            Vec4(0, 0, 1 / d, 0));
        Mat4 translateZinit = Mat4(
            Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0),
            Vec4(0, 0, 1, 3.14),
            Vec4(0, 0, 0, 1));
        Mat4 t, tp;
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
            tp = screen * translateZinit * translate * rotateZ * rotateY * rotateX * scale;
        } else {
            t = screen * perspective * translateZinit * translate * rotateX * rotateY * rotateZ * scale;
            tp = screen * translateZinit * translate * rotateX * rotateY * rotateZ * scale;
        }
        for (GraphicObject o : model.objects) {
            COLORREF objectColor = model.useCustomWireframeColor ? model.wireframeColor : RGB(o.red, o.green, o.blue);
            COLORREF normalColor = useCustomNormalsColor ? normalsColor : RGB(o.red, o.green, o.blue);
            for (GraphicPolygon p : o.polygons) {
                // Draw the normals of the polygon:
                Edge ne;
                switch (drawNormals) {
                case ID_NORMAL_POLYGONS_CALCULATED:
                    ne = getNormalToPolygon(p, t, true);
                    drawLine(ne.start, ne.end, normalColor);
                    break;
                case ID_NORMAL_POLYGONS_GIVEN:
                    ne = getNormalToPolygon(p, t, false);
                    drawLine(ne.start, ne.end, normalColor);
                    break;
                case ID_NORMAL_VERTICES_CALCULATED:
                    for (Edge e : p.edges) {
                        ne = getNormalToVertex(e.start, t, true);
                        drawLine(ne.start, ne.end, normalColor);
                    }
                    break;
                case ID_NORMAL_VERTICES_GIVEN:
                    for (Edge e : p.edges) {
                        if (!(e.start.normalX == 0 && e.start.normalY == 0 && e.start.normalZ == 0)) {
                            ne = getNormalToVertex(e.start, t, false);
                            drawLine(ne.start, ne.end, normalColor);
                        }
                    }
                    break;
                default:
                    break;
                }
                // Draw the silhouette of the object:
                if (drawSilhouette) {
                    for (Edge e : p.edges) {
                        vector<int> hashStart;
                        hashStart.push_back((int)(e.start.x * HASH_PRECISION));
                        hashStart.push_back((int)(e.start.y * HASH_PRECISION));
                        hashStart.push_back((int)(e.start.z * HASH_PRECISION));
                        vector<int> hashEnd;
                        hashEnd.push_back((int)(e.end.x * HASH_PRECISION));
                        hashEnd.push_back((int)(e.end.y * HASH_PRECISION));
                        hashEnd.push_back((int)(e.end.z * HASH_PRECISION));
                        vector<Vec4> polyNormalsAdjToStart = vertexAdjPolygonNormals[hashStart];
                        vector<Vec4> polyNormalsAdjToEnd = vertexAdjPolygonNormals[hashEnd];
                        Vec4 polyNormal1, polyNormal2;
                        int pns = 0;
                        for (Vec4 polyNormalStart : polyNormalsAdjToStart) {
                            if (pns == 2) {
                                break;
                            }
                            for (Vec4 polyNormalEnd : polyNormalsAdjToEnd) {
                                if (polyNormalEnd == polyNormalStart) {
                                    if (pns == 0) {
                                        polyNormal1 = t * polyNormalStart;
                                        pns++;
                                        break;
                                    } else if (polyNormal1 != polyNormalStart) {
                                        polyNormal2 = t * polyNormalStart;
                                        pns++;
                                        break;
                                    }
                                }
                            }
                        }
                        if (pns == 2) {
                            double dot = polyNormal1.z * polyNormal2.z;
                            if (dot < 0) {
                                // Edge is silhouette, draw it:
                                Vec4 start = t * e.start;
                                start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
                                Vec4 start2 = Vec4(start.x / start.w, start.y + 1 / start.w, start.z / start.w, 1);
                                Vec4 start3 = Vec4(start.x / start.w, start.y - 1 / start.w, start.z / start.w, 1);
                                Vec4 start4 = Vec4(start.x / start.w, start.y + 2 / start.w, start.z / start.w, 1);
                                Vec4 start5 = Vec4(start.x / start.w, start.y - 2 / start.w, start.z / start.w, 1);
                                Vec4 end = t * e.end;
                                end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
                                Vec4 end2 = Vec4(end.x / end.w, end.y + 1 / end.w, end.z / end.w, 1);
                                Vec4 end3 = Vec4(end.x / end.w, end.y - 1 / end.w, end.z / end.w, 1);
                                Vec4 end4 = Vec4(end.x / end.w, end.y + 2 / end.w, end.z / end.w, 1);
                                Vec4 end5 = Vec4(end.x / end.w, end.y - 2 / end.w, end.z / end.w, 1);
                                drawLine(start, end, silhouetteColor);
                                drawLine(start2, end2, silhouetteColor);
                                drawLine(start3, end3, silhouetteColor);
                                drawLine(start4, end4, silhouetteColor);
                                drawLine(start5, end5, silhouetteColor);
                            }
                        }
                    }
                }
            }
            // Draw the bounding box of the object:
            if (drawBoundingBox) {
                for (Edge e : o.boundingBox) {
                    Vec4 start = t * e.start;
                    start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
                    Vec4 end = t * e.end;
                    end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
                    drawLine(start, end, objectColor);
                }
            }
            // Draw the edges of the polygon in wireframe mode:
            if (!renderScreen) {
                for (GraphicPolygon p : o.polygons) {
                    if (bonusBackfaceCulling) {
                        Vec4 normal = t * p.normal;
                        if (normal.z < 0) {
                            continue;
                        }
                    }
                    for (Edge e : p.edges) {
                        Vec4 start = t * e.start;
                        start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
                        Vec4 end = t * e.end;
                        end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
                        drawLine(start, end, objectColor);
                    }
                }
            }
            for (GraphicPolygon p : o.polygons) {
                COLORREF flatShadingColor;
                if (m_nLightShading == ID_LIGHT_SHADING_FLAT) {
                    Edge ne = getNormalToPolygon(p, t, useCalculateNormals);
                    flatShadingColor = getColorAfterShading(ne, objectColor, t);
                }

                vector<Edge> projectedEdges;
                size_t y_min = UINT_MAX;
                size_t y_max = 0;
                for (Edge e : p.edges) {
                    Vec4 start = t * e.start;
                    start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
                    Vec4 end = t * e.end;
                    end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
                    y_min = (min(start.y, end.y)) < y_min ? (min(start.y, end.y)) : y_min;
                    y_max = (max(start.y, end.y)) > y_max ? (max(start.y, end.y)) : y_max;

                    if (m_nLightShading == ID_LIGHT_SHADING_GOURAUD) {
                        Edge neStart = getNormalToVertex(e.start, t, useCalculateNormals);
                        COLORREF cStart = getColorAfterShading(neStart, objectColor, t);
                        start.r = GetRValue(cStart);
                        start.g = GetGValue(cStart);
                        start.b = GetBValue(cStart);
                        Edge neEnd = getNormalToVertex(e.end, t, useCalculateNormals);
                        COLORREF cEnd = getColorAfterShading(neEnd, objectColor, t);
                        end.r = GetRValue(cEnd);
                        end.g = GetGValue(cEnd);
                        end.b = GetBValue(cEnd);
                    } else if (m_nLightShading == ID_SHADING_PHONG) {
                        Edge ne_start = getNormalToVertex(e.start, t, useCalculateNormals);
                        Vec4 start_dir = (ne_start.end - ne_start.start).normalize();
                        start.dirX = start_dir.x;
                        start.dirY = start_dir.y;
                        start.dirZ = start_dir.z;
                        Edge ne_end = getNormalToVertex(e.end, t, useCalculateNormals);
                        Vec4 end_dir = (ne_end.end - ne_end.start).normalize();
                        end.dirX = end_dir.x;
                        end.dirY = end_dir.y;
                        end.dirZ = end_dir.z;
                    }
                    projectedEdges.push_back(Edge(start, end));
                }
                for (size_t y = y_min; y <= y_max; y++) {
                    vector<std::pair<double, Edge>> edge_intersections;
                    for (Edge e : projectedEdges) {
                        if ((e.start.y <= y && y < e.end.y) || (e.end.y <= y && y < e.start.y)) {
                            if (e.end.x == e.start.x) {
                                edge_intersections.push_back(std::pair<double, Edge>(e.start.x, e));
                            } else {
                                double x = ((y - e.start.y) / (e.end.y - e.start.y)) * (e.end.x - e.start.x) + e.start.x;
                                edge_intersections.push_back(std::pair<double, Edge>(x, e));
                            }
                        }
                    }

                    std::sort(edge_intersections.begin(), edge_intersections.end(),
                        [](std::pair<double, Edge> p1, std::pair<double, Edge> p2) { return p1.first < p2.first; });

                    for (int k = 0; k < edge_intersections.size(); k += 2) {
                        double l_x = edge_intersections[k].first;
                        double r_x = edge_intersections[k + 1].first;
                        Edge l_edge = edge_intersections[k].second;
                        Edge r_edge = edge_intersections[k + 1].second;
                        double l_z = l_edge.getZ(l_x, y);
                        double r_z = r_edge.getZ(r_x, y);
                        Edge scan_edge(Vec4(l_x, y, l_z, 1), Vec4(r_x, y, r_z, 1));

                        if (m_nLightShading == ID_LIGHT_SHADING_GOURAUD) {
                            COLORREF l_color = l_edge.getColor(l_x, y);
                            scan_edge.start.r = GetRValue(l_color);
                            scan_edge.start.g = GetGValue(l_color);
                            scan_edge.start.b = GetBValue(l_color);
                            COLORREF r_color = r_edge.getColor(r_x, y);
                            scan_edge.end.r = GetRValue(r_color);
                            scan_edge.end.g = GetGValue(r_color);
                            scan_edge.end.b = GetBValue(r_color);
                        } else if (m_nLightShading == ID_SHADING_PHONG) {
                            Vec4 l_p_n_dir = l_edge.getPhongNormal(l_x, y);
                            scan_edge.start.dirX = l_p_n_dir.x;
                            scan_edge.start.dirY = l_p_n_dir.y;
                            scan_edge.start.dirZ = l_p_n_dir.z;
                            Vec4 r_p_n_dir = r_edge.getPhongNormal(r_x, y);
                            scan_edge.end.dirX = r_p_n_dir.x;
                            scan_edge.end.dirY = r_p_n_dir.y;
                            scan_edge.end.dirZ = r_p_n_dir.z;
                        }

                        for (double current_x = scan_edge.start.x; current_x <= scan_edge.end.x; current_x++) {
                            double current_z = scan_edge.getZ(current_x, y);
                            if ((current_x < zbuffer.size() && current_x >= 0 && y >= 0 && y < zbuffer[0].size()) && current_z < zbuffer[current_x][y]) {
                                if (cullBackfaces) {
                                    zbuffer[current_x][y] = current_z;
                                    if (renderScreen) {
                                        if (m_nLightShading == ID_LIGHT_SHADING_FLAT) {
                                            cbuffer[current_x][y] = flatShadingColor;
                                        } else if (m_nLightShading == ID_LIGHT_SHADING_GOURAUD) {
                                            COLORREF gouraudShadingColor = scan_edge.getColor(current_x, y);
                                            cbuffer[current_x][y] = gouraudShadingColor;
                                        } else if (m_nLightShading == ID_SHADING_PHONG) {
                                            Vec4 p_n_dir = scan_edge.getPhongNormal(current_x, y);
                                            Vec4 p_ne_start(current_x, y, current_z, 1);
                                            Vec4 p_ne_end = p_ne_start + p_n_dir;
                                            p_ne_end.w = 1;
                                            Edge p_ne(p_ne_start, p_ne_end);
                                            COLORREF phongShadingColor = getColorAfterShading(p_ne, objectColor, t);
                                            cbuffer[current_x][y] = phongShadingColor;
                                        }
                                    } else {
                                        cbuffer[current_x][y] = backgroundColor;
                                    }
                                } else if (renderScreen) {
                                    if (m_nLightShading == ID_LIGHT_SHADING_FLAT) {
                                        cbuffer[current_x][y] = flatShadingColor;
                                    } else if (m_nLightShading == ID_LIGHT_SHADING_GOURAUD) {
                                        COLORREF gouraudShadingColor = scan_edge.getColor(current_x, y);
                                        cbuffer[current_x][y] = gouraudShadingColor;
                                    } else if (m_nLightShading == ID_SHADING_PHONG) {
                                        Vec4 p_n_dir = scan_edge.getPhongNormal(current_x, y);
                                        Vec4 p_ne_start(current_x, y, current_z, 1);
                                        Vec4 p_ne_end = p_ne_start + p_n_dir;
                                        p_ne_end.w = 1;
                                        Edge p_ne(p_ne_start, p_ne_end);
                                        COLORREF phongShadingColor = getColorAfterShading(p_ne, objectColor, t);
                                        cbuffer[current_x][y] = phongShadingColor;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CCGWorkView::drawLine(Vec4& start, Vec4& end, COLORREF color)
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
    Edge scanned_edge = Edge(start, end);
    if (x >= zbuffer.size() || y >= zbuffer[0].size() || y < 0 || x < 0) {
        return;
    }
    if (scanned_edge.getZ(x, y) < zbuffer[x][y]) {
        zbuffer[x][y] = scanned_edge.getZ(x, y);
        cbuffer[x][y] = color;
    }
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
        if (x >= zbuffer.size() || y >= zbuffer[0].size() || y < 0 || x < 0) {
            return;
        }
        if (scanned_edge.getZ(x, y) < zbuffer[x][y]) {
            zbuffer[x][y] = scanned_edge.getZ(x, y);
            cbuffer[x][y] = color;
        }
    }
}

Edge CCGWorkView::getNormalToVertex(Vec4& v, Mat4& t, bool calculated)
{
    Vec4 normal, start, end;
    if (calculated) {
        vector<int> hashVertex;
        hashVertex.push_back((int)(v.x * HASH_PRECISION));
        hashVertex.push_back((int)(v.y * HASH_PRECISION));
        hashVertex.push_back((int)(v.z * HASH_PRECISION));
        normal = vertexNormals[hashVertex];
        if (invertNormals) {
            normal = -normal;
        }
        start = t * v;
        end = start - (t * normal);
        start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
        end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
        return Edge(start, end);
    } else {
        normal = Vec4(v.normalX, v.normalY, v.normalZ, 0);
        if (invertNormals) {
            normal = -normal;
        }
        start = t * v;
        end = start + (t * normal);
        start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
        end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
        return Edge(start, end);
    }
}
Edge CCGWorkView::getNormalToPolygon(GraphicPolygon& p, Mat4& t, bool calculated)
{
    Vec4 normal, v0, v1, start, end, direction;
    if (calculated) {
        v0 = p.edges[0].end - p.edges[0].start;
        v1 = p.edges[1].end - p.edges[1].start;
        normal = -v0.cross(v1).normalize();
        if (invertNormals) {
            normal = -normal;
        }
        start = t * p.center;
        end = t * (p.center - normal);
        start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
        end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
        return Edge(start, end);
    } else {
        normal = p.normal;
        if (invertNormals) {
            normal = -normal;
        }
        start = t * p.center;
        end = t * (p.center - normal);
        start = Vec4(start.x / start.w, start.y / start.w, start.z / start.w, 1);
        end = Vec4(end.x / end.w, end.y / end.w, end.z / end.w, 1);
        return Edge(start, end);
    }
}

COLORREF CCGWorkView::getColorAfterShading(Edge& ne, COLORREF objectColor, Mat4& t)
{
    double A = m_lMaterialAmbient;
    double D = m_lMaterialDiffuse;
    double S = m_lMaterialSpecular;
    double C = m_nMaterialCosineFactor;

    double I[3] = { 0 };
    double Ia = 0.7;
    double Id = 0.4;
    double Is = 0.4;

    // Ambient light:
    double objectColorR = GetRValue(objectColor) / 255.0;
    double objectColorG = GetGValue(objectColor) / 255.0;
    double objectColorB = GetBValue(objectColor) / 255.0;
    double ambientColorR = m_ambientLight.colorR / 255.0;
    double ambientColorG = m_ambientLight.colorG / 255.0;
    double ambientColorB = m_ambientLight.colorB / 255.0;
    I[0] = Ia * (A * ambientColorR);
    I[1] = Ia * (A * ambientColorG);
    I[2] = Ia * (A * ambientColorB);

    int lightsCount = 0;
    for (LightParams light : m_lights) {
        if (light.enabled) {
            lightsCount++;
        }
    }

    for (LightParams light : m_lights) {
        if (light.enabled) {
            // Diffuse light:
            Vec4 N = (ne.end - ne.start);
            if (N.x == 0 && N.y == 0 && N.z == 0) {
                continue;
            }
            N = N.normalize();
            Vec4 L;
            if (light.type == LIGHT_TYPE_DIRECTIONAL) {
                // Minus dirY because Y+ is in the down direction on the screen, and we are in image space at this stage.
                // Same deal for dirZ.
                // Same deal for dirX.
                L = Vec4(-light.dirX, -light.dirY, -light.dirZ, 1);
            } else if (light.type == LIGHT_TYPE_POINT) {
                // Minus posY because Y+ is in the down direction on the screen, and we are in image space at this stage.
                // Same deal for posZ.
                L = Vec4(light.posX - ne.start.x, -light.posY - ne.start.y, -light.posZ - ne.start.z, 1);
            } else {
                continue;
            }
            if (L.x == 0 && L.y == 0 && L.z == 0) {
                continue;
            }
            L = L.normalize();
            double NL = N * L;
            if (NL < 0) {
                continue;
            }
            // MAYBE: (1-D) * NL * lightColorR  + D * objectColorR
            // MAYBE: (1-D) * NL * lightColorR
            // MAYBE: D * NL * lightColorR
            double lightColorR = light.colorR / 255.0;
            double lightColorG = light.colorG / 255.0;
            double lightColorB = light.colorB / 255.0;
            I[0] += Id * (D * NL * lightColorR) / lightsCount;
            I[1] += Id * (D * NL * lightColorG) / lightsCount;
            I[2] += Id * (D * NL * lightColorB) / lightsCount;
            /////////////////

            // Specular light:
            // MAYBE: Calculate V = (0,0,1) - ne.start
            Vec4 R = ((N * 2) * NL - L);
            if (R.x == 0 && R.y == 0 && R.z == 0) {
                continue;
            }
            R = R.normalize();
            Vec4 V = Vec4(0, 0, 1, 1);
            double RV = R * V;
            double RVn = pow(RV, C);
            I[0] += Is * (S * RVn * lightColorR) / lightsCount;
            I[1] += Is * (S * RVn * lightColorG) / lightsCount;
            I[2] += Is * (S * RVn * lightColorB) / lightsCount;
            /////////////////
        }
    }

    double fogFactor = 0;
    double fogColorR = GetRValue(fogColor) / 255.0;
    double fogColorG = GetGValue(fogColor) / 255.0;
    double fogColorB = GetBValue(fogColor) / 255.0;
    if (enableFog) {
        double fogStart = 2; // Z (depth) values, closest to the viewer.
        double fogEnd = 1; // Z (depth) values, farthest away from the viewer.
        fogFactor = (fogEnd - ne.start.z) / (fogEnd - fogStart);
        fogFactor = max(0, min(1, fogFactor));
    }

    I[0] = min(1, (1 - fogFactor) * objectColorR * I[0] + fogFactor * fogColorR);
    I[1] = min(1, (1 - fogFactor) * objectColorG * I[1] + fogFactor * fogColorG);
    I[2] = min(1, (1 - fogFactor) * objectColorB * I[2] + fogFactor * fogColorB);

    return RGB(
        (int)(255 * I[0]),
        (int)(255 * I[1]),
        (int)(255 * I[2]));
}

COLORREF CCGWorkView::getBgValue(int x, int y, int width, int height)
{
    if (bgStretch) {
        // Stretch:
        return bgbuffer[x * bgbuffer.size() / width][y * bgbuffer[0].size() / height];
    } else {
        // Repeat:
        return bgbuffer[x % bgbuffer.size()][y % bgbuffer[0].size()];
    }
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CCGWorkView::OnFileLoad()
{
    TCHAR szFilters[] = _T ("IRIT Data Files (*.itd)|*.itd|All Files (*.*)|*.*||");

    CFileDialog dlg(TRUE, _T("itd"), _T("*.itd"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

    if (dlg.DoModal() == IDOK) {
        m_strItdFileName = dlg.GetPathName(); // Full path and filename
        graphicObjects.clear();
        CGSkelProcessIritDataFiles(m_strItdFileName, 1);
        // Open the file and read it.
        models.push_back(GraphicModel(dlg.GetFileName(), graphicObjects));

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
    Invalidate();
}

void CCGWorkView::OnUpdateLightShadingFlat(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_FLAT);
}

void CCGWorkView::OnLightShadingGouraud()
{
    m_nLightShading = ID_LIGHT_SHADING_GOURAUD;
    Invalidate();
}

void CCGWorkView::OnUpdateLightShadingGouraud(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_GOURAUD);
}
void CCGWorkView::OnLightShadingPhong()
{
    m_nLightShading = ID_SHADING_PHONG;
    Invalidate();
}

void CCGWorkView::OnUpdateLightShadingPhong(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nLightShading == ID_SHADING_PHONG);
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
void CCGWorkView::OnMaterialConstants()
{
    CMaterialDlg dlg;

    dlg.SetDialogData(m_lMaterialAmbient, m_lMaterialDiffuse, m_lMaterialSpecular, m_nMaterialCosineFactor);

    if (dlg.DoModal() == IDOK) {
        m_lMaterialAmbient = dlg.getAmbient();
        m_lMaterialDiffuse = dlg.getDiffuse();
        m_lMaterialSpecular = dlg.getShininess();
        m_nMaterialCosineFactor = dlg.getSpecular();
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

    if (modelIdx == models.size()) {
        // Transform all models.
        for (int i = 0; i < modelIdx; i++) {
            Transform(models[i], dx, dy);
        }
    } else {
        Transform(models[modelIdx], dx, dy);
    }
    Invalidate();
}

// i == the index of the object to transform.
void CCGWorkView::Transform(GraphicModel& model, double dx, double dy)
{
    switch (m_nAxis) {
    case ID_AXIS_X:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            model.thetaX += dx;
            break;
        case ID_ACTION_SCALE:
            model.scaleX = max(0.1, model.scaleX + dx);
            break;
        case ID_ACTION_TRANSLATE:
            model.translateX += dx;
            break;
        }
        break;
    case ID_AXIS_Y:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            model.thetaY += dx;
            break;
        case ID_ACTION_SCALE:
            model.scaleY = max(0.1, model.scaleY + dx);
            break;
        case ID_ACTION_TRANSLATE:
            model.translateY += dx;
            break;
        }
        break;
    case ID_AXIS_Z:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            model.thetaZ += dx;
            break;
        case ID_ACTION_SCALE:
            model.scaleZ = max(0.1, model.scaleZ + dx);
            break;
        case ID_ACTION_TRANSLATE:
            model.translateZ += dx;
            break;
        }
        break;
    case ID_AXIS_XY:
        switch (m_nAction) {
        case ID_ACTION_ROTATE:
            model.thetaX += dy;
            model.thetaY += dx;
            break;
        case ID_ACTION_SCALE:
            model.scaleX = max(0.1, model.scaleX + dx);
            model.scaleY = max(0.1, model.scaleY + dy);
            break;
        case ID_ACTION_TRANSLATE:
            model.translateX += dx;
            model.translateY += dy;
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
}

void CCGWorkView::OnViewBoundingbox()
{
    drawBoundingBox = !drawBoundingBox;
    Invalidate();
}

void CCGWorkView::OnUpdateViewSilhouette(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawSilhouette);
}

void CCGWorkView::OnViewSilhouette()
{
    drawSilhouette = !drawSilhouette;
    Invalidate();
}

void CCGWorkView::OnUpdateNormalPolygonsCalculated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_POLYGONS_CALCULATED);
}

void CCGWorkView::OnNormalPolygonsCalculated()
{
    drawNormals = ID_NORMAL_POLYGONS_CALCULATED;
    Invalidate();
}

void CCGWorkView::OnUpdateNormalPolygonsGiven(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_POLYGONS_GIVEN);
}

void CCGWorkView::OnNormalPolygonsGiven()
{
    drawNormals = ID_NORMAL_POLYGONS_GIVEN;
    Invalidate();
}

void CCGWorkView::OnUpdateNormalVerticesCalculated(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_VERTICES_CALCULATED);
}

void CCGWorkView::OnNormalVerticesCalculated()
{
    drawNormals = ID_NORMAL_VERTICES_CALCULATED;
    Invalidate();
}

void CCGWorkView::OnUpdateNormalVerticesGiven(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMAL_VERTICES_GIVEN);
}

void CCGWorkView::OnNormalVerticesGiven()
{
    drawNormals = ID_NORMAL_VERTICES_GIVEN;
    Invalidate();
}
void CCGWorkView::OnUpdateNormalNone(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(drawNormals == ID_NORMALS_NONE);
}

void CCGWorkView::OnNormalNone()
{
    drawNormals = ID_NORMALS_NONE;
    Invalidate();
}

void CCGWorkView::OnOptionsWireframecolor()
{
    CColorDialog colorDialog;
    colorDialog.m_cc.Flags |= CC_RGBINIT;
    if (modelIdx == models.size()) {
        colorDialog.m_cc.rgbResult = models[0].wireframeColor;
    } else {
        colorDialog.m_cc.rgbResult = models[modelIdx].wireframeColor;
    }
    if (colorDialog.DoModal() == IDOK) {
        if (modelIdx == models.size()) {
            for (int i = 0; i < modelIdx; i++) {
                models[i].wireframeColor = colorDialog.GetColor();
                models[i].useCustomWireframeColor = true;
            }
        } else {
            models[modelIdx].wireframeColor = colorDialog.GetColor();
            models[modelIdx].useCustomWireframeColor = true;
        }
        Invalidate();
    }
}

void CCGWorkView::OnOptionsSilhouettecolor()
{
    CColorDialog colorDialog;
    colorDialog.m_cc.Flags |= CC_RGBINIT;
    colorDialog.m_cc.rgbResult = silhouetteColor;
    if (colorDialog.DoModal() == IDOK) {
        silhouetteColor = colorDialog.GetColor();
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
    dlg.setModels(models);
    dlg.setIndex(modelIdx);
    dlg.setMaxIndex(models.size());
    if (dlg.DoModal() == IDOK) {
        modelIdx = dlg.getIndex();
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
}

void CCGWorkView::OnInvertedNormals()
{
    invertNormals = !invertNormals;
    Invalidate();
}

void CCGWorkView::OnUpdateRenderWireframe(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(!renderScreen);
}

void CCGWorkView::OnRenderWireframe()
{
    renderScreen = false;
    Invalidate();
}

void CCGWorkView::OnUpdateRenderScreen(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(renderScreen);
}

void CCGWorkView::OnRenderScreen()
{
    renderScreen = true;
    Invalidate();
}

void CCGWorkView::OnUpdateRenderFile(CCmdUI* pCmdUI)
{
}

void CCGWorkView::OnRenderFile()
{
    PngRenderDialog dialog;
    dialog.SetDialogData(m_WindowWidth, m_WindowHeight);
    if (dialog.DoModal() == IDOK) {
        int width = dialog.getWidth();
        int height = dialog.getHeight();
        CFileDialog fileDialog(FALSE, _T("png"), _T("*.png"), OFN_OVERWRITEPROMPT, _T ("PNG (*.png)|*.png|All Files (*.*)|*.*||"));
        if (fileDialog.DoModal() == IDOK) {
            double half_w = width / 2;
            double half_h = height / 2;
            Mat4 oldScreen = Mat4(screen);
            screen = Mat4(
                Vec4(half_h, 0, 0, half_w),
                Vec4(0, -half_h, 0, half_h),
                Vec4(0, 0, 1, 0),
                Vec4(0, 0, 0, 1));

            CStringA pngPath = CStringA(fileDialog.GetPathName());
            PngWrapper png(pngPath, width, height);
            png.InitWritePng();
            int bg = SET_RGB(GetRValue(backgroundColor), GetGValue(backgroundColor), GetBValue(backgroundColor));
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    png.SetValue(x, y, bg);
                }
            }
            RenderScene(width, height);
            for (size_t i = 0; i < width; i++) {
                for (size_t j = 0; j < height; j++) {
                    if (cbuffer[i][j] != backgroundColor) {
                        COLORREF c = cbuffer[i][j];
                        png.SetValue(i, j, SET_RGB(GetRValue(c), GetGValue(c), GetBValue(c)));
                    } else if (!bgbuffer.empty()) {
                        COLORREF c = getBgValue(i, j, width, height);
                        png.SetValue(i, j, SET_RGB(GetRValue(c), GetGValue(c), GetBValue(c)));
                    }
                }
            }
            png.WritePng();
            screen = Mat4(oldScreen);
        }
    }
}

void CCGWorkView::OnUpdateBackfaceCulling(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(cullBackfaces);
}
void CCGWorkView::OnBackfaceCulling()
{
    cullBackfaces = !cullBackfaces;
    bonusBackfaceCulling = false;
    Invalidate();
}

void CCGWorkView::OnUpdateBonusBackfaceCulling(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(bonusBackfaceCulling);
}
void CCGWorkView::OnBonusBackfaceCulling()
{
    bonusBackfaceCulling = !bonusBackfaceCulling;
    cullBackfaces = false;
    Invalidate();
}

void CCGWorkView::OnUpdateBgStretch(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(bgStretch);
}
void CCGWorkView::OnBgStretch()
{
    bgStretch = true;
    Invalidate();
}
void CCGWorkView::OnUpdateBgRepeat(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(!bgStretch);
}
void CCGWorkView::OnBgRepeat()
{
    bgStretch = false;
    Invalidate();
}

void CCGWorkView::OnBgLoad()
{
    CFileDialog fileDialog(TRUE, _T("png"), _T("*.png"), OFN_OVERWRITEPROMPT, _T ("PNG (*.png)|*.png|All Files (*.*)|*.*||"));
    if (fileDialog.DoModal() == IDOK) {
        CStringA pngPath = CStringA(fileDialog.GetPathName());
        PngWrapper png(pngPath);
        png.ReadPng();
        bool isGrayscale = png.GetNumChannels() == 1;
        int width = png.GetWidth();
        int height = png.GetHeight();

        bgbuffer = vector<vector<COLORREF>>(width);
        for (int x = 0; x < width; x++) {
            bgbuffer[x] = vector<COLORREF>(height);
            for (int y = 0; y < height; y++) {
                int c = png.GetValue(x, y);
                if (isGrayscale) {
                    bgbuffer[x][y] = c;
                } else {
                    bgbuffer[x][y] = RGB(GET_R(c), GET_G(c), GET_B(c));
                }
            }
        }
        Invalidate();
    }
}

void CCGWorkView::OnBgClear()
{
    bgbuffer.clear();
    Invalidate();
}

void CCGWorkView::OnUpdateUseCalculatedNormals(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(useCalculateNormals);
}
void CCGWorkView::OnUseCalculatedNormals()
{
    useCalculateNormals = !useCalculateNormals;
    Invalidate();
}

void CCGWorkView::OnFogColor()
{
    CColorDialog colorDialog;
    colorDialog.m_cc.Flags |= CC_RGBINIT;
    colorDialog.m_cc.rgbResult = fogColor;
    if (colorDialog.DoModal() == IDOK) {
        fogColor = colorDialog.GetColor();
        Invalidate();
    }
}

void CCGWorkView::OnUpdateFogEnable(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(enableFog);
}
void CCGWorkView::OnFogEnable()
{
    enableFog = !enableFog;
    Invalidate();
}