#ifndef GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H
#define GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H

#include "GraphicsObject.h"

namespace Azul
{
	class GraphicsObjectWireframeConstantColor : public GraphicsObject
	{
	public:
		GraphicsObjectWireframeConstantColor() = delete;
		GraphicsObjectWireframeConstantColor(const GraphicsObjectWireframeConstantColor&) = delete;
		GraphicsObjectWireframeConstantColor& operator= (const GraphicsObjectWireframeConstantColor&) = delete;
		~GraphicsObjectWireframeConstantColor();

		GraphicsObjectWireframeConstantColor(Model* pModel, ShaderObject* pShaderObj, Vect& wireColor);

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

	public:
		// data:  place uniform instancing here
		Vect* pWireColor;
	};
}





#endif
