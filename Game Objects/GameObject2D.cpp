#include "MathEngine.h"
#include "GameObject2D.h"
#include "GraphicsObject.h"

namespace Azul
{
	GameObject2D::GameObject2D(GraphicsObject_Sprite* pGraphicsObj)
		: GameObject(pGraphicsObj, GameObject::Type::GAME_OBJECT_2D)
	{
		assert(pGraphicsObj != nullptr);

		this->angle = 0.0f;
		this->posX = pGraphicsObj->origPosX;
		this->posY = pGraphicsObj->origPosY;
		this->scaleX = 1.0f;
		this->scaleY = 1.0f;
	}

	GameObject2D::~GameObject2D()
	{
	}

	void GameObject2D::Update(AnimTime currentTime)
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


}