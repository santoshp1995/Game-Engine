//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Model.h"
#include "GraphicsObject_Wireframe.h"
#include "ShaderObject.h"
#include "CameraMan.h"

namespace Azul
{

	GraphicsObject_Wireframe::GraphicsObject_Wireframe(const Model* const _pModel, const ShaderObject* const _pShaderObj)
		: GraphicsObject(_pModel, _pShaderObj)
	{
		assert(pModel);
		assert(pShaderObject);
		assert(pWorld);
	}

	void GraphicsObject_Wireframe::SetState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	void GraphicsObject_Wireframe::SetDataGPU()
	{
		// use this shader
		this->pShaderObject->SetActive();

		// Draw Me: -----------------------------------------

		// set the vao
		glBindVertexArray(this->GetModel()->vao);

		// Set state
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);

		Matrix world = this->GetWorld();
		Matrix view = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->getViewMatrix();
		Matrix proj = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->getProjMatrix();

		glUniformMatrix4fv(this->pShaderObject->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
	}

	void GraphicsObject_Wireframe::Draw()
	{
		// draw
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_Wireframe::RestoreState()
	{
		// Restore state
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}

// ---  End of File ---






