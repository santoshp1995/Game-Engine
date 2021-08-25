#ifndef GRAPHICS_OBJECT_SKIN_TEXTURE_H
#define GRAPHICS_OBJECT_SKIN_TEXTURE_H

#include "GraphicsObject.h"
#include "Texture.h"

namespace Azul
{

	class GraphicsObject_SkinTexture : public GraphicsObject
	{
	public:
		GraphicsObject_SkinTexture(const Model* pModel, const ShaderObject* pShaderObj, TextureName name);

		GraphicsObject_SkinTexture() = delete;
		GraphicsObject_SkinTexture(const GraphicsObject_SkinTexture&) = delete;
		GraphicsObject_SkinTexture& operator = (const GraphicsObject_SkinTexture&) = delete;
		~GraphicsObject_SkinTexture() = default;

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		//data -- place uniform instancing here
		TextureName textName;
	};

}







#endif
