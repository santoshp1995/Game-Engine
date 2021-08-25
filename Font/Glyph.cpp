#include "Glyph.h"
#include "Texture.h"


namespace Azul
{
	Glyph::Glyph()
	{
		this->name = Glyph::Name::Uninitialized;
		this->key = 0;
		this->pTextNode = nullptr;
		this->pRect = new Rect();
	}

	Glyph::~Glyph()
	{
		delete this->pRect;
	}

	void Glyph::Set(const Glyph::Name _name, const int _key, const TextureName textName, const float x, const float y, 
		const float width, const float height)
	{
		assert(this->pRect);
		this->name = _name;

		Texture::FindNode(textName, this->pTextNode);
		assert(this->pTextNode);

		this->pRect->x = x;
		this->pRect->y = y;
		this->pRect->height = height;
		this->pRect->width = width;

		this->key = _key;
	}

	Glyph::Name Glyph::GetName() const
	{
		return this->name;
	}

	int Glyph::GetKey() const
	{
		return this->key;
	}

	Rect* Glyph::GetRect() const
	{
		return this->pRect;
	}

	TextureNode* Glyph::GetTextNode() const
	{
		return this->pTextNode;
	}


}