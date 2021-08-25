#ifndef GLYPH_H
#define GLYPH_H

#include "GlyphLink.h"
#include "Rect.h"
#include "TextureNode.h"

namespace Azul
{
	class Glyph : public GlyphLink
	{
	public:
		enum class Name
		{
			Consolas36pt,
			Uninitialized
		};

	public:
		Glyph();
		Glyph(const Glyph&) = delete;
		Glyph& operator= (const Glyph&) = delete;
		~Glyph();

		void Set(const Glyph::Name _name, const int key, const TextureName textName, const float x, const float y,
			const float width, const float height);

		// accessors
		Glyph::Name GetName() const;
		int GetKey() const;
		Rect* GetRect() const;
		TextureNode* GetTextNode() const;


	private:
		Glyph::Name name;
		int key;
		Rect* pRect;
		TextureNode* pTextNode;


	};
}






#endif
