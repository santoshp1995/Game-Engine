#include "GraphicsObject_Null.h"

namespace Azul
{

	GraphicsObject_Null::GraphicsObject_Null(const Model* const _pModel, const ShaderObject* const pShaderObj)
		:GraphicsObject(_pModel, pShaderObj)
	{
	}

	void GraphicsObject_Null::SetState()
	{
	}

	void GraphicsObject_Null::SetDataGPU()
	{
	}

	void GraphicsObject_Null::Draw()
	{
	}

	void GraphicsObject_Null::RestoreState()
	{
	}
}
