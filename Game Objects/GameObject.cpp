#include "MathEngine.h"
#include "GameObject.h"
#include "Game.h"
#include "GraphicsObject.h"
#include "Model.h"

namespace Azul
{
	GameObject::GameObject(GraphicsObject* pGraphicsObject, Type type)
		: poGraphicsObject(pGraphicsObject)
	{
		this->poWorld = new Matrix(Matrix::Special::Identity);
		assert(poWorld);

		this->objectType = type;
		this->isRendering = true;

		assert(pGraphicsObject != 0);
	}

	GameObject::~GameObject()
	{

		delete this->poWorld;
		delete this->poGraphicsObject;
	}

	void GameObject::baseUpdateBoundingSphere()
	{
		// Get the ref Sphere
		Sphere* pRefSphere = poGraphicsObject->GetModel()->pRefSphere;
		assert(pRefSphere);

		// Get the curr Sphere
		Sphere* pCurrSphere = poGraphicsObject->pCurrSphere;
		assert(pCurrSphere);

		// Update... cntr process through the world
		// Assuming a uniform scaling
		Vect A = pRefSphere->cntr;
		Vect radius(1.0f, 0.0f, 0.0f);
		Vect B = A + radius;
		Vect A_out = A * (*this->poWorld);
		Vect B_out = B * (*this->poWorld);

		pCurrSphere->rad = (B_out[x] - A_out[x]) * pRefSphere->rad;
		pCurrSphere->cntr = A_out;
	}

	Matrix* GameObject::GetWorld()
	{
		return this->poWorld;
	}

	GraphicsObject* GameObject::GetGraphicsObject()
	{
		return this->poGraphicsObject;
	}

	void GameObject::SetWorld(Matrix* _pWorld)
	{
		assert(_pWorld);
		*this->poWorld = *_pWorld;
	}

	GameObject::Type GameObject::GetType() const
	{
		return this->objectType;
	}

	void GameObject::SetRender(bool b)
	{
		this->isRendering = b;
	}

	void GameObject::Draw()
	{
		GraphicsObject* pGraphicsObj = this->GetGraphicsObject();
		assert(pGraphicsObj);

		if (this->isRendering)
		{
			pGraphicsObj->Render();
		}


	}

}


