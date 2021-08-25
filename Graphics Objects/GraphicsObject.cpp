#include "GraphicsObject.h"
#include "MathEngine.h"
#include "Model.h"


namespace Azul
{
	GraphicsObject::GraphicsObject(const Model* const _pModel, const ShaderObject* const _pShaderObject)
		:pModel(_pModel),
		pShaderObject(_pShaderObject)
	{

		this->pWorld = new Matrix(Matrix::Special::Identity);
		this->pCurrSphere = new Sphere();
		assert(this->pCurrSphere);
		assert(this->pModel);
		assert(_pModel);
		assert(_pShaderObject);
	}

	GraphicsObject::~GraphicsObject()
	{
		delete this->pWorld;
		delete this->pCurrSphere;
	}

	void GraphicsObject::Render()
	{
		this->SetState();
		this->SetDataGPU();
		this->Draw();
		this->RestoreState();
	}

	void GraphicsObject::SetWorld(Matrix& world)
	{
		*this->pWorld = world;
	}

	const Model* GraphicsObject::GetModel() const
	{
		return this->pModel;
	}

	Matrix& GraphicsObject::GetWorld()
	{
		return *this->pWorld;
	}
}

