#ifndef GRAPHICS_OBJECT_TEXTURE_LIGHT_H
#define GRAPHICS_OBJECT_TEXTURE_LIGHT_H

#include "GraphicsObject.h"
#include "Texture.h"
#include "MathEngine.h"

namespace Azul
{
	class GraphicsObject_TextureLight : public GraphicsObject
	{
	public:
		GraphicsObject_TextureLight(Model* _pModel, ShaderObject* _pShaderObj, TextureName  _name, Vect& LightColor, Vect& LightPos);
		GraphicsObject_TextureLight() = delete;
		GraphicsObject_TextureLight(const GraphicsObject_TextureLight&) = delete;
		GraphicsObject_TextureLight& operator= (const GraphicsObject_TextureLight&) = delete;
		~GraphicsObject_TextureLight();

		// render material contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data : place uniforming instancing here
		TextureName textName;
		Vect* poLightColor;
		Vect* poLightPos;


	};
}


#endif