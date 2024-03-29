#ifndef GRAPHICS_OBJECT_SPRITE_H
#define GRAPHICS_OBJECT_SPRITE_H

#include "Texture.h"
#include "Image.h"
#include "GraphicsObject.h"
#include "ShaderObject.h"

namespace Azul
{
	class GraphicsObject_Sprite : public GraphicsObject
	{
	public:
		GraphicsObject_Sprite(Model* pModel, ShaderObject* pShaderObj, Image* pImage, Rect rect);
		virtual ~GraphicsObject_Sprite();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data:  place uniform instancing here

			//GLuint textureID;
		Image* pImage;
		Matrix* poMatrix_uv;
		Matrix* poMatrix_orig;

		float origWidth;
		float origHeight;

		float origPosX;
		float origPosY;
	};
	
}


#endif
