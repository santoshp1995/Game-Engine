#ifndef GLYPH_MAN_H
#define GLYPH_MAN_H

#include "Glyph.h"
#include <string>

using namespace std;

namespace Azul
{
	class GlyphMan
	{
	public:
		static void Create();
		static void Add(Glyph::Name name, int key, TextureName textName, float x, float y, float width, float height);
		static void AddXml(Glyph::Name glyphName, string assetName, TextureName textName);
		static Glyph* Find(Glyph::Name name, int key);
		static void Destroy();

	private:
		static GlyphMan* privGetInstance();
		GlyphMan();

		void privAddToFront(Glyph* node, Glyph*& head);
		void privRemove(Glyph* pNode, Glyph*& poHead);

		Glyph* pActive;
	};
}

#endif
