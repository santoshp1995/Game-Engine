#ifndef GRAPHICS_OBJECT_COLOR_BY_POSITION_H
#define GRAPHICS_OBJECT_COLOR_BY_POSITION_H

#include "GraphicsObject.h"
namespace Azul
{
	class GraphicsObject_ColorByPosition : public GraphicsObject
	{

	public:
		GraphicsObject_ColorByPosition(const Model* const _pModel, const ShaderObject* const _pShaderObject);

		GraphicsObject_ColorByPosition() = delete;
		GraphicsObject_ColorByPosition(const GraphicsObject_ColorByPosition&) = delete;
		GraphicsObject_ColorByPosition& operator= (const GraphicsObject_ColorByPosition) = delete;
		~GraphicsObject_ColorByPosition() = default;

		// render material contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;
	};
}


#endif

