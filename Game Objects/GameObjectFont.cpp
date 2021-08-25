#include "GameObjectFont.h"

namespace Azul
{
	GameObjectFont::GameObjectFont(GraphicsObject_Font* pGraphicsObject, GameObject::Type type)
		: GameObject(pGraphicsObject, type)
	{
		assert(pGraphicsObject);

		this->angle = 0.0f;
		this->posX = pGraphicsObject->origPosX;
		this->posY = pGraphicsObject->origPosY;
		this->scaleX = 1.0f;
		this->scaleY = 1.0f;

		this->pMessage = new char[MESSAGE_SIZE];
		this->glyphName = Glyph::Name::Uninitialized;
	}

	GameObjectFont::~GameObjectFont()
	{
		delete this->pMessage;
	}

	void GameObjectFont::Update(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix
		Matrix Scale(Matrix::Scale::XYZ, this->scaleX, this->scaleY, 1.0f);
		Matrix Rot(Matrix::Rot1::Z, this->angle);
		Matrix Trans(Matrix::Trans::XYZ, this->posX, this->posY, 0.0f);

		*this->poWorld = Scale * Rot * Trans;

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);


	}

	void GameObjectFont::Set(const char* const _pMessage, float xStart, float yStart)
	{
		this->privSetMessage(_pMessage);

		this->posX = xStart;
		this->posY = yStart;

	}

	void GameObjectFont::DrawFont()
	{
		float xTmp = this->posX;
		float yTmp = this->posY;

		float xEnd = this->posX;

		int count = strlen(this->pMessage);

		for (int i = 0; i < count; i++)
		{
			int key = (int)this->pMessage[i];

			Glyph* pGlyph = GlyphMan::Find(Glyph::Name::Consolas36pt, key);
			assert(pGlyph);

			xTmp = xEnd + pGlyph->GetRect()->width / 2;

			Rect screenRect(xTmp, yTmp, pGlyph->GetRect()->width, pGlyph->GetRect()->height);

			GraphicsObject_Font* pGraphicsObj = (GraphicsObject_Font*)this->poGraphicsObject;

			pGraphicsObj->Swap(pGlyph, screenRect);

			Matrix Scale(Matrix::Scale::XYZ, this->scaleX, this->scaleY, 1.0f);
			Matrix Rot(Matrix::Rot1::Z, this->angle);
			Matrix Trans(Matrix::Trans::XYZ, xTmp, yTmp, 0.0f);

			*this->poWorld = Scale * Rot * Trans;

			// push to graphics object
			pGraphicsObj->SetWorld(*this->poWorld);
			
			pGraphicsObj->Render();
			
			// move the starting to the next character
			xEnd = pGlyph->GetRect()->width / 2 + xTmp;

		}
	}

	void GameObjectFont::UpdateMessage(const char* const _pMessage)
	{
		this->privSetMessage(_pMessage);
	}


	void GameObjectFont::privSetMessage(const char* const input)
	{
		int i = 0;

		while (input[i] != '\0' && i < (int)strlen(input) + 1)
		{
			this->pMessage[i] = input[i];

			i++;
		}

		this->pMessage[i] = '\0';
	}
}