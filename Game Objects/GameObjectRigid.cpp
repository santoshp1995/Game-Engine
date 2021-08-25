#include "MathEngine.h"
#include "GameObjectRigid.h"
#include "GraphicsObject.h"
#include "ModelMan.h"

namespace Azul
{
	GameObjectRigid::GameObjectRigid(GraphicsObject* pGraphicsObject, SkinModel* _pSkinModel)
		: GameObject(pGraphicsObject, GameObject::Type::GAME_OBJECT)
	{
		assert(pGraphicsObject != 0);
		assert(_pSkinModel);

		this->pScale = new Vect(1.0f, 1.0f, 1.0f);
		assert(this->pScale);

		this->pPos = new Vect(0.0f, 0.0f, 0.0f);
		assert(this->pPos);

		this->angle = 0.0f;

		this->rotY = 0.0f;
		this->rotZ = 0.0f;
		this->deltaRotZ = 0.0f;
		this->deltaRotY = 0.0f;

		this->pSkinModel = _pSkinModel;
	}

	GameObjectRigid::~GameObjectRigid()
	{
		delete this->pPos;
		delete this->pScale;
	}

	void GameObjectRigid::privUpdate(AnimTime)
	{
		this->rotY += deltaRotY;
		this->rotZ += deltaRotZ;

		Matrix Scale(Matrix::Scale::XYZ, *this->pScale);
		Matrix TransA(Matrix::Trans::XYZ, *this->pPos);
		Matrix RotY(Matrix::Rot1::Y, this->rotY);
		Matrix RotZ(Matrix::Rot1::Z, this->rotZ);

		*this->poWorld = Scale * RotY * RotZ * TransA;

		*this->pSkinModel->poRigidWorld = *this->poWorld;
		this->pSkinModel->pSSBO_rigidWorld->Set(this->pSkinModel->NumBones, sizeof(Matrix), this->pSkinModel->poRigidWorld);
	}

	void GameObjectRigid::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}
	void GameObjectRigid::SetPos(const float x, const float y, const float z)
	{
		this->pPos->set(x, y, z);
	}
	void GameObjectRigid::SetScale(const float x, const float y, const float z)
	{
		this->pScale->set(x, y, z);
	}
}

// --- End of File ---