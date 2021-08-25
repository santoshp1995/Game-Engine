
#ifndef GRAPHICS_OBJECT_FLAT_TEXTURE_H
#define GRAPHICS_OBJECT_FLAT_TEXTURE_H

#include "GraphicsObject.h"
#include "Texture.h"

namespace Azul
{
	class GraphicsObject_FlatTexture :public GraphicsObject
	{
	public:
		GraphicsObject_FlatTexture(const Model* const pModel, const ShaderObject* const pShaderObj, TextureName _name);

		GraphicsObject_FlatTexture() = delete;
		GraphicsObject_FlatTexture(const GraphicsObject_FlatTexture&) = delete;
		GraphicsObject_FlatTexture& operator= (const GraphicsObject_FlatTexture&) = delete;
		~GraphicsObject_FlatTexture() = default;

		// Render material contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data:  place uniform instancing here

		TextureName textName;

	};
}
#endif


