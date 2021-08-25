#ifndef FONT_MAN_H
#define FONT_MAN_H

#include "Font.h"


using namespace std;

namespace Azul
{
	class FontMan
	{
	public:
		static void Create();
		static void Add(Font::Name name, GraphicsObject_Font* pGraphicsObj, const char* const pMessageString, 
			float xStart, float yStart);
		static Font* Find(Font::Name name);
		static void Destroy();

	private:
		FontMan();
		static FontMan* privGetInstance();

		void privAddToFront(Font* node, Font*& head);
		void privRemove(Font* pNode, Font*& poHead);

	private:
		Font* pActive;
	};
}


#endif