#include "Font.h"
#include "GameObjectMan.h"

namespace Azul
{
	Font::Font(Font::Name _name, GraphicsObject_Font* pGraphicsObj)
	{
		this->name = _name;

		this->pFontObj = new GameObjectFont(pGraphicsObj, GameObject::Type::FONT);

		GameObjectMan::Add(pFontObj);
	}

	Font::~Font()
	{
		
	}

	Font::Name Font::GetName() const
	{
		return this->name;
	}

	void Font::Set(const char* const pMessage, float xStart, float yStart)
	{
		this->pFontObj->Set(pMessage, xStart, yStart);
	}

	void Font::UpdateMessage(const char* const pMessage)
	{
		this->pFontObj->UpdateMessage(pMessage);
	}
}