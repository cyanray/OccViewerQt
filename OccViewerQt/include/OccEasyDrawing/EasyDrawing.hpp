#pragma once
#include "OccEasyDrawing/Common/Common.hpp"
#include "OccEasyDrawing/Common/ShapeRenderStyle.hpp"
#include <gp_Pnt.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_ColoredShape.hxx>

#include <vector>

namespace OccEasyDrawing
{
	const static ShapeRenderStyle DefaultShapeRenderStyle{};

	inline void ClearView(const ViewerHandles& handles)
	{
		handles.Context->RemoveAll(Standard_True);
	}

	void DisplayObject(const ViewerHandles& handles, const AISObjects& objs);

	void DisplayObject(const ViewerHandles& handles, const Handle(AIS_InteractiveObject)& obj);

	void ApplyShapeRenderStyle(Handle(AIS_ColoredShape)& shape, const ShapeRenderStyle& style);

    Handle(AIS_InteractiveObject) MakePoint(const gp_Pnt& pt);

	Handle(AIS_ColoredShape) MakePolygonPlane(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3);

	Handle(AIS_ColoredShape) MakePolygonPlane(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3, const gp_Pnt& p4);

	Handle(AIS_ColoredShape) MakePolygonBSplineSurface(const std::vector<gp_Pnt>& vertex);

    Handle(AIS_InteractiveObject) MakeLine(const gp_Pnt& pt1, const gp_Pnt& pt2);

}