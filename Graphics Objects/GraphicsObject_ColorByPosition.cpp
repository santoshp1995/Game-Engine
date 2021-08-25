//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject_ColorByPosition.h"
#include "CameraMan.h"

// ToDo fix this...


namespace Azul
{
	GraphicsObject_ColorByPosition::GraphicsObject_ColorByPosition(const Model* const model, const ShaderObject* const pShaderObj)
		: GraphicsObject(model, pShaderObj)
	{
		assert(pModel);
		assert(pShaderObj);
		assert(pWorld);
	}

	void GraphicsObject_ColorByPosition::SetState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	void GraphicsObject_ColorByPosition::SetDataGPU()
	{
		// use this shader
		this->pShaderObject->SetActive();

		// set the vao
		glBindVertexArray(this->GetModel()->vao);

		Matrix world = this->GetWorld();
		Matrix view = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->getViewMatrix();
		Matrix proj = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->getProjMatrix();

		glUniformMatrix4fv(this->pShaderObject->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
	}

	void GraphicsObject_ColorByPosition::Draw()
	{
		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_ColorByPosition::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

}

// ---  End of File ---








