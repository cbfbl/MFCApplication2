#include "iritSkel.h"
#include "stdafx.h"
/*****************************************************************************
* Skeleton for an interface to a parser to read IRIT data files.			 *
******************************************************************************
* (C) Gershon Elber, Technion, Israel Institute of Technology                *
******************************************************************************
* Written by:  Gershon Elber				Ver 1.0, Feb 2002				 *
* Minimal changes made by Amit Mano			November 2008					 *
******************************************************************************/

IPFreeformConvStateStruct CGSkelFFCState = {
    FALSE, /* Talkative */
    FALSE, /* DumpObjsAsPolylines */
    TRUE, /* DrawFFGeom */
    FALSE, /* DrawFFMesh */
    { 10, 10, 10 }, /* 10 isocurves peru/v/w direction. */
    100, /* 100 point samples along a curve. */
    SYMB_CRV_APPROX_UNIFORM, /* CrvApproxMethod */
    FALSE, /* ShowIntrnal */
    FALSE, /* CubicCrvsAprox */
    20, /* Polygonal FineNess */
    FALSE, /* ComputeUV */
    TRUE, /* ComputeNrml */
    FALSE, /* FourPerFlat */
    0, /* OptimalPolygons */
    FALSE, /* BBoxGrid */
    TRUE, /* LinearOnePolyFlag */
    FALSE
};

//CGSkelProcessIritDataFiles(argv + 1, argc - 1);

vector<GraphicObject> graphicObjects;
map<vector<int>, vector<Vec4>> vertexAdjPolygonNormals;
map<vector<int>, Vec4> vertexNormals;

void setFineNess(int fineNess)
{
    CGSkelFFCState.FineNess = fineNess;
}

int getFineNess()
{
    return CGSkelFFCState.FineNess;
}

/*****************************************************************************
* DESCRIPTION:                                                               *
* Main module of skeleton - Read command line and do what is needed...	     *
*                                                                            *
* PARAMETERS:                                                                *
*   FileNames:  Files to open and read, as a vector of strings.              *
*   NumFiles:   Length of the FileNames vector.								 *
*                                                                            *
* RETURN VALUE:                                                              *
*   bool:		false - fail, true - success.                                *
*****************************************************************************/
bool CGSkelProcessIritDataFiles(CString& FileNames, int NumFiles)
{
    IPObjectStruct* PObjects;
    IrtHmgnMatType CrntViewMat;
    vertexAdjPolygonNormals.clear();
    /* Get the data files: */
    IPSetFlattenObjects(FALSE);
    CStringA CStr(FileNames);
    if ((PObjects = IPGetDataFiles((const char* const*)&CStr, 1 /*NumFiles*/, TRUE, FALSE)) == NULL)
        return false;
    PObjects = IPResolveInstances(PObjects);

    if (IPWasPrspMat)
        MatMultTwo4by4(CrntViewMat, IPViewMat, IPPrspMat);
    else
        IRIT_GEN_COPY(CrntViewMat, IPViewMat, sizeof(IrtHmgnMatType));

    /* Here some useful parameters to play with in tesselating freeforms: */
    //CGSkelFFCState.FineNess = 20;   /* Res. of tesselation, larger is finer. */
    CGSkelFFCState.ComputeUV = TRUE; /* Wants UV coordinates for textures. */
    CGSkelFFCState.FourPerFlat = TRUE; /* 4 poly per ~flat patch, 2 otherwise.*/
    CGSkelFFCState.LinearOnePolyFlag = TRUE; /* Linear srf gen. one poly. */

    /* Traverse ALL the parsed data, recursively. */
    IPTraverseObjListHierarchy(PObjects, CrntViewMat,
        CGSkelDumpOneTraversedObject);
    return true;
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Call back function of IPTraverseObjListHierarchy. Called on every non    *
* list object found in hierarchy.                                            *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:       Non list object to handle.                                   *
*   Mat:        Transformation matrix to apply to this object.               *
*   Data:       Additional data.                                             *
*                                                                            *
* RETURN VALUE:                                                              *
*   void									                                 *
*****************************************************************************/
void CGSkelDumpOneTraversedObject(IPObjectStruct* PObj,
    IrtHmgnMatType Mat,
    void* Data)
{
    IPObjectStruct* PObjs;

    if (IP_IS_FFGEOM_OBJ(PObj))
        PObjs = IPConvertFreeForm(PObj, &CGSkelFFCState);
    else
        PObjs = PObj;

    for (PObj = PObjs; PObj != NULL; PObj = PObj->Pnext)
        if (!CGSkelStoreData(PObj))
            exit(1);
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Prints the data from given geometry object.								 *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:       Object to print.                                             *
*   Indent:     Column of indentation.                                       *
*                                                                            *
* RETURN VALUE:                                                              *
*   bool:		false - fail, true - success.                                *
*****************************************************************************/
bool CGSkelStoreData(IPObjectStruct* PObj)
{
    int i;
    const char* Str;
    double RGB[3], Transp;
    IPPolygonStruct* PPolygon;
    IPVertexStruct* PVertex;
    const IPAttributeStruct* Attrs = AttrTraceAttributes(PObj->Attr, PObj->Attr);

    if (PObj->ObjType != IP_OBJ_POLY) {
        AfxMessageBox(_T("Non polygonal object detected and ignored"));
        return true;
    }

    /* You can use IP_IS_POLYGON_OBJ(PObj) and IP_IS_POINTLIST_OBJ(PObj) 
	   to identify the type of the object*/

    if (CGSkelGetObjectColor(PObj, RGB)) {
        /* color code */
    }
    if (CGSkelGetObjectTransp(PObj, &Transp)) {
        /* transparency code */
    }
    if ((Str = CGSkelGetObjectTexture(PObj)) != NULL) {
        /* volumetric texture code */
    }
    if ((Str = CGSkelGetObjectPTexture(PObj)) != NULL) {
        /* parametric texture code */
    }
    if (Attrs != NULL) {
        printf("[OBJECT\n");
        while (Attrs) {
            /* attributes code */
            Attrs = AttrTraceAttributes(Attrs, NULL);
        }
    }

    GraphicObject graphicObject(RGB);

    double minX = DBL_MAX;
    double minY = DBL_MAX;
    double minZ = DBL_MAX;
    double maxX = DBL_MIN;
    double maxY = DBL_MIN;
    double maxZ = DBL_MIN;

    for (PPolygon = PObj->U.Pl; PPolygon != NULL; PPolygon = PPolygon->Pnext) {
        GraphicPolygon poly;
        double sumX = 0;
        double sumY = 0;
        double sumZ = 0;
        int vertexCount = 0;

        if (PPolygon->PVertex == NULL) {
            AfxMessageBox(_T("Dump: Attemp to dump empty polygon"));
            return false;
        }

        Vec4 start, end;
        double vsize;

        PVertex = PPolygon->PVertex;
        while (1) {
            if (PVertex == NULL)
                break;

            vsize = 1;
            start = Vec4(
                PVertex->Coord[0] / vsize,
                PVertex->Coord[1] / vsize,
                PVertex->Coord[2] / vsize,
                1);

            if (IP_HAS_NORMAL_VRTX(PVertex)) {
                start.normalX = PVertex->Normal[0];
                start.normalY = PVertex->Normal[1];
                start.normalZ = PVertex->Normal[2];
            }

            vector<int> hashVertex;
            hashVertex.push_back((int)(start.x * HASH_PRECISION));
            hashVertex.push_back((int)(start.y * HASH_PRECISION));
            hashVertex.push_back((int)(start.z * HASH_PRECISION));
            Vec4 hashPolygonNormal = Vec4(
                PPolygon->Plane[0],
                PPolygon->Plane[1],
                PPolygon->Plane[2],
                0);
            vertexAdjPolygonNormals[hashVertex].push_back(hashPolygonNormal);

            PVertex = PVertex->Pnext;
            if (PVertex == NULL) {
                // We connect the last vertex with the first vertex in order to close the polygon.
                PVertex = PPolygon->PVertex; // The first vertex.
                vsize = 1;
                end = Vec4(
                    PVertex->Coord[0] / vsize,
                    PVertex->Coord[1] / vsize,
                    PVertex->Coord[2] / vsize,
                    1);

                poly.edges.push_back(Edge(start, end));
                break;
            }

            vsize = 1;
            end = Vec4(
                PVertex->Coord[0] / vsize,
                PVertex->Coord[1] / vsize,
                PVertex->Coord[2] / vsize,
                1);

            poly.edges.push_back(Edge(start, end));

            if (start.x > maxX) {
                maxX = start.x;
            }
            if (start.y > maxY) {
                maxY = start.y;
            }
            if (start.z > maxZ) {
                maxZ = start.z;
            }

            if (start.x < minX) {
                minX = start.x;
            }
            if (start.y < minY) {
                minY = start.y;
            }
            if (start.z < minZ) {
                minZ = start.z;
            }

            sumX += start.x;
            sumY += start.y;
            sumZ += start.z;
            vertexCount++;
        }

        poly.center = Vec4(sumX / vertexCount, sumY / vertexCount, sumZ / vertexCount, 1);

        if (IP_HAS_PLANE_POLY(PPolygon) != 0) {
            poly.normal = -Vec4(
                PPolygon->Plane[0],
                PPolygon->Plane[1],
                PPolygon->Plane[2],
                0);
        }
        /* Close the polygon. */
        graphicObject.polygons.push_back(poly);
    }

    // For silhouettes:
    for (int i = 0; i < graphicObject.polygons.size(); i++) {
        for (Edge polyEdge : graphicObject.polygons[i].edges) {
            vector<int> hashEdgeStart;
            hashEdgeStart.push_back((int)(polyEdge.start.x * HASH_PRECISION));
            hashEdgeStart.push_back((int)(polyEdge.start.y * HASH_PRECISION));
            hashEdgeStart.push_back((int)(polyEdge.start.z * HASH_PRECISION));
            vector<int> hashEdgeEnd;
            hashEdgeEnd.push_back((int)(polyEdge.end.x * HASH_PRECISION));
            hashEdgeEnd.push_back((int)(polyEdge.end.y * HASH_PRECISION));
            hashEdgeEnd.push_back((int)(polyEdge.end.z * HASH_PRECISION));
            auto e = make_pair(hashEdgeStart, hashEdgeEnd);
            if (graphicObject.edgePolygons.count(e) == 1) {
                graphicObject.edgePolygons[e] = std::make_pair(graphicObject.edgePolygons[e].first, i);
            } else {
                auto re = make_pair(hashEdgeEnd, hashEdgeStart);
                if (graphicObject.edgePolygons.count(re) == 1) {
                    graphicObject.edgePolygons[re] = std::make_pair(graphicObject.edgePolygons[re].first, i);
                } else {
                    graphicObject.edgePolygons[e] = std::make_pair(i, -1);
                }
            }
        }   
    }

    // Calculate bounding box edges:
    graphicObject.boundingBox.push_back(Edge(Vec4(minX, minY, minZ, 1), Vec4(maxX, minY, minZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(minX, minY, minZ, 1), Vec4(minX, maxY, minZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(maxX, minY, minZ, 1), Vec4(maxX, maxY, minZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(minX, maxY, minZ, 1), Vec4(maxX, maxY, minZ, 1)));

    graphicObject.boundingBox.push_back(Edge(Vec4(minX, minY, maxZ, 1), Vec4(maxX, minY, maxZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(minX, minY, maxZ, 1), Vec4(minX, maxY, maxZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(maxX, minY, maxZ, 1), Vec4(maxX, maxY, maxZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(minX, maxY, maxZ, 1), Vec4(maxX, maxY, maxZ, 1)));

    graphicObject.boundingBox.push_back(Edge(Vec4(minX, minY, minZ, 1), Vec4(minX, minY, maxZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(maxX, minY, minZ, 1), Vec4(maxX, minY, maxZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(minX, maxY, minZ, 1), Vec4(minX, maxY, maxZ, 1)));
    graphicObject.boundingBox.push_back(Edge(Vec4(maxX, maxY, minZ, 1), Vec4(maxX, maxY, maxZ, 1)));

    graphicObjects.push_back(graphicObject);

    map<vector<int>, vector<Vec4>>::iterator it;
    for (it = vertexAdjPolygonNormals.begin(); it != vertexAdjPolygonNormals.end(); it++) {
        Vec4 vnorm = Vec4(0, 0, 0, 0);
        for (Vec4 v : it->second) {
            vnorm = vnorm + v;
        }
        vnorm = vnorm * (1.0 / it->second.size());
        vertexNormals[it->first] = -vnorm;
    }

    /* Close the object. */
    return true;
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the color of an object.                                          *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its color.                                         *
*   RGB:    as 3 floats in the domain [0, 1].                                *
*                                                                            *
* RETURN VALUE:                                                              *
*   int:    TRUE if object has color, FALSE otherwise.                       *
*****************************************************************************/
int CGSkelGetObjectColor(IPObjectStruct* PObj, double RGB[3])
{
    static int TransColorTable[][4] = {
        { /* BLACK	*/ 0, 0, 0, 0 },
        { /* BLUE	*/ 1, 0, 0, 255 },
        { /* GREEN	*/ 2, 0, 255, 0 },
        { /* CYAN	*/ 3, 0, 255, 255 },
        { /* RED	*/ 4, 255, 0, 0 },
        { /* MAGENTA 	*/ 5, 255, 0, 255 },
        { /* BROWN	*/ 6, 50, 0, 0 },
        { /* LIGHTGRAY	*/ 7, 127, 127, 127 },
        { /* DARKGRAY	*/ 8, 63, 63, 63 },
        { /* LIGHTBLUE	*/ 9, 0, 0, 255 },
        { /* LIGHTGREEN	*/ 10, 0, 255, 0 },
        { /* LIGHTCYAN	*/ 11, 0, 255, 255 },
        { /* LIGHTRED	*/ 12, 255, 0, 0 },
        { /* LIGHTMAGENTA */ 13, 255, 0, 255 },
        { /* YELLOW	*/ 14, 255, 255, 0 },
        { /* WHITE	*/ 15, 255, 255, 255 },
        { /* BROWN	*/ 20, 50, 0, 0 },
        { /* DARKGRAY	*/ 56, 63, 63, 63 },
        { /* LIGHTBLUE	*/ 57, 0, 0, 255 },
        { /* LIGHTGREEN	*/ 58, 0, 255, 0 },
        { /* LIGHTCYAN	*/ 59, 0, 255, 255 },
        { /* LIGHTRED	*/ 60, 255, 0, 0 },
        { /* LIGHTMAGENTA */ 61, 255, 0, 255 },
        { /* YELLOW	*/ 62, 255, 255, 0 },
        { /* WHITE	*/ 63, 255, 255, 255 },
        { -1, 0, 0, 0 }
    };
    int i, j, Color, RGBIColor[3];

    if (AttrGetObjectRGBColor(PObj,
            &RGBIColor[0], &RGBIColor[1], &RGBIColor[2])) {
        for (i = 0; i < 3; i++)
            RGB[i] = RGBIColor[i] / 255.0;

        return TRUE;
    } else if ((Color = AttrGetObjectColor(PObj)) != IP_ATTR_NO_COLOR) {
        for (i = 0; TransColorTable[i][0] >= 0; i++) {
            if (TransColorTable[i][0] == Color) {
                for (j = 0; j < 3; j++)
                    RGB[j] = TransColorTable[i][j + 1] / 255.0;
                return TRUE;
            }
        }
    }

    return FALSE;
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the volumetric texture of an object, if any.                     *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its volumetric texture.                            *
*                                                                            *
* RETURN VALUE:                                                              *
*   char *:    Name of volumetric texture map to apply, NULL if none.        *
*****************************************************************************/
const char* CGSkelGetObjectTexture(IPObjectStruct* PObj)
{
    return AttrGetObjectStrAttrib(PObj, "texture");
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the parametric texture of an object, if any.                     *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its parametric texture.                            *
*                                                                            *
* RETURN VALUE:                                                              *
*   char *:    Name of parametric texture map to apply, NULL if none.        *
*****************************************************************************/
const char* CGSkelGetObjectPTexture(IPObjectStruct* PObj)
{
    return AttrGetObjectStrAttrib(PObj, "ptexture");
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the transparency level of an object, if any.                     *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its volumetric texture.                            *
*   Transp: Transparency level between zero and one.                         *
*                                                                            *
* RETURN VALUE:                                                              *
*   int:    TRUE if object has transparency, FALSE otherwise.                *
*****************************************************************************/
int CGSkelGetObjectTransp(IPObjectStruct* PObj, double* Transp)
{
    *Transp = AttrGetObjectRealAttrib(PObj, "transp");

    return !IP_ATTR_IS_BAD_REAL(*Transp);
}
