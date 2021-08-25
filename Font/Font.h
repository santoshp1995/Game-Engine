#ifndef FONT_H
#define FONT_H

#include "FontLink.h"
#include "GameObjectFont.h"
#include "Glyph.h"
#include <string>

using namespace std;

namespace Azul
{
	class Font : public FontLink
	{
	public:
		enum class Name
		{
			StaticString,
			DynamicString
		};


	public:
		Font(Font::Name _name, GraphicsObject_Font* pGraphicsObj);
		Font(const Font&) = delete;
		Font& operator= (const Font&) = delete;
		~Font();

		// accessors
		Font::Name GetName() const;

		void Set(const char* const pMessage, float xStart, float yStart);

		void UpdateMessage(const char* const pMessage);

	private:
		Font::Name name;
		GameObjectFont* pFontObj;


	};
}


#endif