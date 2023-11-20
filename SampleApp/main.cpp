#include <OccViewerQt/OccViewer/OccViewer.h>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierSurface.hxx>
#include <AIS_ColoredShape.hxx>
#include <AIS_Point.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <GC_MakeSegment.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TopoDS_Wire.hxx>
#include <BRepFill_Filling.hxx>
#include <BRepBuilderAPI_NurbsConvert.hxx>
#include <BRepLib_FindSurface.hxx>
#include <GeomConvert.hxx>

#include <OccEasyDrawing/EasyDrawing.hpp>

#include "OccViewerQt/OccViewerQt.hpp"

int main(int argc, char* argv[])
{
    OccViewerQt::OccViewerHelper::GlobalInit(argc, argv);

    /*
    // Define a 4x4 grid of points for BSpline surface.
    TColgp_Array2OfPnt aBSplinePnts(1, 4, 1, 4);
    for (Standard_Integer i = 1; i <= 4; ++i)
    {
        gp_Pnt aPnt;
        aPnt.SetX(5.0 * i);
        for (Standard_Integer j = 1; j <= 4; ++j)
        {
            aPnt.SetY(5.0 * j);
            if (1 < i && i < 4 && 1 < j && j < 4)
            {
                aPnt.SetZ(5.0);
            }
            else
            {
                aPnt.SetZ(0.0);
            }
            aBSplinePnts.SetValue(i, j, aPnt);
        }
    }

    // Define a 4x4 grid of points for Bezier surface.
    TColgp_Array2OfPnt aBezierPnts(1, 4, 1, 4);
    for (Standard_Integer i = 1; i <= 4; ++i)
    {
        gp_Pnt aPnt;
        aPnt.SetX(20.0 + 5.0 * i);
        for (Standard_Integer j = 1; j <= 4; ++j)
        {
            aPnt.SetY(20.0 + 5.0 * j);
            if (1 < i && i < 4 && 1 < j && j < 4)
            {
                aPnt.SetZ(5.0);
            }
            else
            {
                aPnt.SetZ(0.0);
            }
            aBezierPnts.SetValue(i, j, aPnt);
        }
    }

    // Define BSpline weights.
    TColStd_Array2OfReal aBSplineWeights(1, 4, 1, 4);
    for (Standard_Integer i = 1; i <= 4; ++i)
    {
        for (Standard_Integer j = 1; j <= 4; ++j)
        {
            if (1 < i && i < 4 && 1 < j && j < 4)
            {
                aBSplineWeights.SetValue(i, j, 0.5);
            }
            else
            {
                aBSplineWeights.SetValue(i, j, 1.0);
            }
        }
    }

    // Define knots.
    TColStd_Array1OfReal aUKnots(1, 2), aVKnots(1, 2);
    aUKnots.SetValue(1, 0.0);
    aUKnots.SetValue(2, 1.0);
    aVKnots.SetValue(1, 0.0);
    aVKnots.SetValue(2, 1.0);

    // Define multiplicities.
    TColStd_Array1OfInteger aUMults(1, 2), aVMults(1, 2);
    aUMults.SetValue(1, 4);
    aUMults.SetValue(2, 4);
    aVMults.SetValue(1, 4);
    aVMults.SetValue(2, 4);

    // Define BSpline degree and periodicity.
    Standard_Integer aUDegree = 3;
    Standard_Integer aVDegree = 3;
    Standard_Boolean aUPeriodic = Standard_False;
    Standard_Boolean aVPeriodic = Standard_False;

    // Create a BSpline surface.
    Handle(Geom_BSplineSurface) aBSplineSurf = new Geom_BSplineSurface(
            aBSplinePnts, aBSplineWeights, aUKnots, aVKnots,
            aUMults, aVMults, aUDegree, aVDegree, aUPeriodic, aVPeriodic);


    // Define BSpline weights.
    TColStd_Array2OfReal aBezierWeights(1, 4, 1, 4);
    for (Standard_Integer i = 1; i <= 4; ++i)
    {
        for (Standard_Integer j = 1; j <= 4; ++j)
        {
            if (1 < i && i < 4 && 1 < j && j < 4)
            {
                aBezierWeights.SetValue(i, j, 1.5);
            }
            else
            {
                aBezierWeights.SetValue(i, j, 0.5);
            }
        }
    }

    // Create a Bezier surface.
    Handle(Geom_BezierSurface) aBezierSurf = new Geom_BezierSurface(aBezierPnts, aBezierWeights);


    Handle(AIS_ColoredShape) anAisBSplineSurf = new AIS_ColoredShape(
            BRepBuilderAPI_MakeFace(aBSplineSurf, Precision::Confusion()).Shape());
    Handle(AIS_ColoredShape) anAisBezierSurf = new AIS_ColoredShape(
            BRepBuilderAPI_MakeFace(aBezierSurf, Precision::Confusion()).Shape());
    anAisBSplineSurf->SetColor(Quantity_Color(Quantity_NOC_RED));
    anAisBezierSurf->SetColor(Quantity_Color(Quantity_NOC_GREEN));


    std::vector<Handle(AIS_InteractiveObject) > objs;

    objs.push_back(anAisBSplineSurf);
    objs.push_back(anAisBezierSurf);
    for (TColgp_Array2OfPnt::Iterator anIt(aBSplinePnts); anIt.More(); anIt.Next())
    {
        objs.push_back(new AIS_Point(new Geom_CartesianPoint(anIt.Value())));
    }
    for (TColgp_Array2OfPnt::Iterator anIt(aBezierPnts); anIt.More(); anIt.Next())
    {
        objs.push_back(new AIS_Point(new Geom_CartesianPoint(anIt.Value())));
    }

*/


    // Define points.
    gp_Pnt aPnt1(0.0, 0.0, 0.0);
    gp_Pnt aPnt2(5.0, 5.0, 0.0);
    gp_Pnt aPnt3(10.0, 5.0, 0.0);
    gp_Pnt aPnt4(15.0, 0.0, 0.0);

    gp_Pnt aPnt5(0.0, 0.0, 20.0);
    gp_Pnt aPnt6(4.0, 7.0, 20.0);
    gp_Pnt aPnt7(13.0, 8.0, 20.0);
    gp_Pnt aPnt8(15.0, 0.0, 20.0);

    // Add points to the curve poles array.
    TColgp_Array1OfPnt aPoles1(1, 4);
    aPoles1.SetValue(1, aPnt1);
    aPoles1.SetValue(2, aPnt2);
    aPoles1.SetValue(3, aPnt3);
    aPoles1.SetValue(4, aPnt4);

    TColgp_Array1OfPnt aPoles2(1, 4);
    aPoles2.SetValue(1, aPnt5);
    aPoles2.SetValue(2, aPnt6);
    aPoles2.SetValue(3, aPnt7);
    aPoles2.SetValue(4, aPnt8);

    // Define BSpline weights.
    TColStd_Array1OfReal aBSplineWeights(1, 4);
    aBSplineWeights.SetValue(1, 1.0);
    aBSplineWeights.SetValue(2, 0.5);
    aBSplineWeights.SetValue(3, 0.5);
    aBSplineWeights.SetValue(4, 1.0);

    // Define knots.
    TColStd_Array1OfReal aKnots(1, 2);
    aKnots.SetValue(1, 0.0);
    aKnots.SetValue(2, 1.0);

    // Define multiplicities.
    TColStd_Array1OfInteger aMults(1, 2);
    aMults.SetValue(1, 4);
    aMults.SetValue(2, 4);

    // Define BSpline degree and periodicity.
    Standard_Integer aDegree = 3;
    Standard_Boolean aPeriodic = Standard_False;

    // Create a BSpline curve.
    Handle(Geom_BSplineCurve) aBSplineCurve1 = new Geom_BSplineCurve(
        aPoles1, aBSplineWeights, aKnots, aMults, aDegree, aPeriodic);
    Handle(Geom_BSplineCurve) aBSplineCurve2 = new Geom_BSplineCurve(
        aPoles2, aBSplineWeights, aKnots, aMults, aDegree, aPeriodic);


    auto edge1 = BRepBuilderAPI_MakeEdge(aBSplineCurve1);
    auto edge2 = BRepBuilderAPI_MakeEdge(aBSplineCurve2);
    auto seg1 = BRepBuilderAPI_MakeEdge(GC_MakeSegment(aPnt1, aPnt5).Value());
    auto seg2 = BRepBuilderAPI_MakeEdge(GC_MakeSegment(aPnt4, aPnt8).Value());


    OccEasyDrawing::AISObjects objs;


    auto make_wire = BRepBuilderAPI_MakeWire(edge1.Edge(),seg1.Edge(), edge2.Edge(), seg2.Edge());

    if(!make_wire.IsDone())
    {
        std::cout << "make_wire not done" << std::endl;
    }
    else
    {
        objs.push_back(new AIS_ColoredShape(make_wire.Shape()));
    }

    BRepFill_Filling filling;
    filling.Add(edge1.Edge(), GeomAbs_C0);
    filling.Add(seg1.Edge(), GeomAbs_C0);
    filling.Add(edge2.Edge(), GeomAbs_C0);
    filling.Add(seg2.Edge(), GeomAbs_C0);

    filling.Build();
    if(!filling.IsDone())
    {
        std::cout << "filling not done" << std::endl;
    }
    else
    {
         objs.push_back(new AIS_ColoredShape(filling.Face()));
    }

    BRepBuilderAPI_NurbsConvert nurbs(filling.Face());
    Handle(Geom_Surface) geom_Extrusion = BRepLib_FindSurface(nurbs.Shape()).Surface();
    Handle(Geom_BSplineSurface) geombspline_Extrusion = GeomConvert::SurfaceToBSplineSurface(geom_Extrusion);
    objs.push_back(new AIS_ColoredShape(BRepBuilderAPI_MakeFace(geombspline_Extrusion, Precision::Confusion()).Shape()));
    // print bspline surface info
    std::cout << "bspline surface info:" << std::endl;
    std::cout << "  nbUPoles: " << geombspline_Extrusion->NbUPoles() << std::endl;
    std::cout << "  nbVPoles: " << geombspline_Extrusion->NbVPoles() << std::endl;
    std::cout << "  nbUKnots: " << geombspline_Extrusion->NbUKnots() << std::endl;
    std::cout << "  nbVKnots: " << geombspline_Extrusion->NbVKnots() << std::endl;
    std::cout << "  uDegree: " << geombspline_Extrusion->UDegree() << std::endl;
    std::cout << "  vDegree: " << geombspline_Extrusion->VDegree() << std::endl;
    std::cout << "  uPeriodic: " << geombspline_Extrusion->IsUPeriodic() << std::endl;
    std::cout << "  vPeriodic: " << geombspline_Extrusion->IsVPeriodic() << std::endl;
    std::cout << "  uClosed: " << geombspline_Extrusion->IsUClosed() << std::endl;
    std::cout << "  vClosed: " << geombspline_Extrusion->IsVClosed() << std::endl;

    // TODO: GeomPlate_BuildPlateSurface


    OccViewerQt::OccViewerHelper helper;
    OccViewerQt::OccViewer& viewer = helper.GetViewer();
    OccEasyDrawing::ViewerHandles handles{viewer.GetV3dView(), viewer.GetAISContext()};
    OccEasyDrawing::DisplayObject(handles, objs);

    viewer.GetViewWidget()->Shading();
    viewer.GetViewWidget()->FitAll();

    helper.ShowViewerDialog();
    return 0;
}
