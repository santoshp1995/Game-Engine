#include "Game.h"
#include "MathEngine.h"
#include "SimpleGameObject.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Model.h"


namespace Azul
{
	SimpleGameObject::SimpleGameObject(GraphicsObject* pGraphicsObj, Type type)
		: GameObject(pGraphicsObj, type)
	{
		assert(pGraphicsObj);

		this->poTrans = new Vect(0.0f, 0.0f, 0.0f);
		this->poScale = new Vect(1.0f, 1.0f, 1.0f);
		assert(this->poTrans);
		assert(this->poScale);

		this->rotY = 0.0f;
		this->rotZ = 0.0f;
		this->deltaRotZ = 0.0f;
		this->deltaRotY = 0.0f;
	}

	SimpleGameObject::~SimpleGameObject()
	{
		delete this->poTrans;
		delete this->poScale;
	}

	void SimpleGameObject::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);


	}

	void SimpleGameObject::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void SimpleGameObject::SetPos(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void SimpleGameObject::SetMove(SimpleGameObject::MoveDir _dir)
	{
		this->dir = _dir;
	}

	void SimpleGameObject::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		float delta = 0.01f;

		static float dirX = 1.0f;
		static float dirY = 1.0f;
		static float dirZ = 1.0f;

		switch (this->dir)
		{
		case MOVE_X:
			this->poTrans->x() += (delta * dirX);
			if (this->poTrans->x() > 6.0f || this->poTrans->x() < -6.0f)
			{
				dirX *= -1.0f;
			}
			break;

		case MOVE_Y:
			this->poTrans->y() += (delta * dirY);
			if (this->poTrans->y() > 4.0f || this->poTrans->y() < -4.0f)
			{
				dirY *= -1.0f;
			}
			break;

		case MOVE_Z:
			this->poTrans->z() += (delta * dirZ);
			if (this->poTrans->z() > 7.0f || this->poTrans->z() < -5.0f)
			{
				dirZ *= -1.0f;
			}
			break;

		case MOVE_NONE:
		default:
			break;
		}

		// Goal: update the world matrix

		this->rotY += deltaRotY;
		this->rotZ += deltaRotZ;

		Matrix Scale(Matrix::Scale::XYZ, *this->poScale);
		Matrix TransA(Matrix::Trans::XYZ, *this->poTrans);
		Matrix RotY(Matrix::Rot1::Y, this->rotY);
		Matrix RotZ(Matrix::Rot1::Z, this->rotZ);

		// world matrix
		*this->poWorld = Scale * RotY * RotZ * TransA;


	}
}


