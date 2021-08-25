#include "GameObjectNull.h"

namespace Azul
{
	GameObjectNull::GameObjectNull(GraphicsObject_Null* pGraphicsObj)
		: GameObject(pGraphicsObj, GameObject::Type::NULL_TYPE)
	{
		assert(pGraphicsObj);
	}

	GameObjectNull::~GameObjectNull()
	{

	}

	void GameObjectNull::Update(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix
		Matrix Identity(Matrix::Special::Identity);
		*this->poWorld = Identity;

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}
}