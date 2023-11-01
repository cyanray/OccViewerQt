#pragma once

#include <Standard_Handle.hxx>
#include <NCollection_Vector.hxx>
#include <V3d_View.hxx>
#include <AIS_InteractiveObject.hxx>

#include <tuple>
#include <vector>

namespace OccEasyDrawing
{
	using AISObjects = std::vector<Handle(AIS_InteractiveObject)>;

	struct ViewerHandles
	{
		Handle(V3d_View) View;
		Handle(AIS_InteractiveContext) Context;
	};
}