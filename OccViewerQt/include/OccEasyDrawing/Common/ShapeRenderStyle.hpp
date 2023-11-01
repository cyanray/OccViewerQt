#pragma once
#include <Quantity_Color.hxx>
#include <Graphic3d_MaterialAspect.hxx>

namespace OccEasyDrawing
{
	struct ShapeRenderStyle
	{
		Quantity_Color Color = Quantity_NOC_DEEPSKYBLUE2;
		Graphic3d_MaterialAspect Material = Graphic3d_NOM_STEEL;
		double Transparency = 0.3;
	};
}