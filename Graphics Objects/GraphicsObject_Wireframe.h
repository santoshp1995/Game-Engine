#ifndef GRAPHICS_OBJECT_WIREFRAME_H
#define GRAPHICS_OBJECT_WIREFRAME_H

#include "GraphicsObject.h"

namespace Azul
{
	class GraphicsObject_Wireframe : public GraphicsObject
	{
	public:
		GraphicsObject_Wireframe(const Model* const _pModel, const ShaderObject* const _pShaderObject);

		GraphicsObject_Wireframe() = delete;
		GraphicsObject_Wireframe(const GraphicsObject_Wireframe&) = delete;
		GraphicsObject_Wireframe& operator= (const GraphicsObject_Wireframe&) = delete;
		~GraphicsObject_Wireframe() = default;

		// Render material contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;
	};
}

#endif