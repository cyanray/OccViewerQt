#include "OccEasyDrawing/EasyDrawing.hpp"

#include <gp_Pnt.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <AIS_Point.hxx>
#include <AIS_ColoredShape.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_CartesianPoint.hxx>

#include <stdexcept>


namespace OccEasyDrawing
{
	void DisplayObject(const ViewerHandles& handles, const AISObjects& objs)
	{
		for (const auto& obj : objs)
		{
			handles.Context->Display(obj, Standard_False);
		}
		handles.View->Redraw();
		handles.View->FitAll();
	}

	void DisplayObject(const ViewerHandles& handles, const Handle(AIS_InteractiveObject)& obj)
	{
		handles.Context->Display(obj, Standard_False);
		handles.View->Redraw();
		handles.View->FitAll();
	}

	void ApplyShapeRenderStyle(Handle(AIS_ColoredShape)& shape, const ShapeRenderStyle& style)
	{
		shape->SetColor(style.Color);
		shape->SetMaterial(style.Material);
		shape->SetTransparency(style.Transparency);
	}

	Handle(AIS_ColoredShape) MakePolygonPlane(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3)
	{
		TopoDS_Wire wire = BRepBuilderAPI_MakePolygon(p1, p2, p3, Standard_True);
		Handle(AIS_ColoredShape) aisFace = new AIS_ColoredShape(BRepBuilderAPI_MakeFace(wire, Standard_True).Shape());
		ApplyShapeRenderStyle(aisFace, DefaultShapeRenderStyle);
		return aisFace;
	}

	Handle(AIS_ColoredShape) MakePolygonPlane(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3, const gp_Pnt& p4)
	{
		TopoDS_Wire wire = BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True);
		Handle(AIS_ColoredShape) aisFace = new AIS_ColoredShape(BRepBuilderAPI_MakeFace(wire, Standard_True).Shape());
		ApplyShapeRenderStyle(aisFace, DefaultShapeRenderStyle);
		return aisFace;
	}

	Handle(AIS_ColoredShape) MakePolygonBSplineSurface(const std::vector<gp_Pnt>& vertex)
	{
		if (vertex.size() > 4)
		{
			throw std::runtime_error("vertex size must be less than 4");
		}
		TColgp_Array2OfPnt Array(1, 2, 1, 2);
		Array.SetValue(1, 1, vertex[0]);
		Array.SetValue(1, 2, vertex[1]);
		Array.SetValue(2, 2, vertex[2]);
		if (vertex.size() == 4)
		{
			Array.SetValue(2, 1, vertex[3]);
		}

		Handle(Geom_BSplineSurface) pSurface = GeomAPI_PointsToBSplineSurface(Array);
		auto gsurf = typename Handle(Geom_Surface){static_cast<Geom_Surface*>(pSurface.get())};

		auto tmp = BRepBuilderAPI_MakeFace(gsurf, 1e-6);
		Handle(AIS_ColoredShape) aisFace = new AIS_ColoredShape(tmp.Shape());
		ApplyShapeRenderStyle(aisFace, DefaultShapeRenderStyle);
		return aisFace;
	}

    Handle(AIS_InteractiveObject) MakePoint(const gp_Pnt& pt)
    {
        return new AIS_Point(new Geom_CartesianPoint(pt));
    }
}