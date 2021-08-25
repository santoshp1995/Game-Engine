#ifndef GRAPHICS_OBJECT_FONT_H
#define GRAPHICS_OBECT_FONT_H

#include "Texture.h"
#include "GraphicsObject.h"
#include "ShaderObject.h"
#include "GlyphMan.h"

namespace Azul
{
	class GraphicsObject_Font : public GraphicsObject
	{
	public:
		GraphicsObject_Font(Model* pModel, ShaderObject* pShaderObj, Glyph* pGlyph);
		virtual ~GraphicsObject_Font();


		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		void Swap(Glyph* pGlyph, Rect r);


		Matrix* poMatrix_uv;
		Matrix* poMatrix_orig;

		TextureNode* pTextNode;

		float origWidth;
		float origHeight;

		float origPosX;
		float origPosY;


	};
}


#endif
