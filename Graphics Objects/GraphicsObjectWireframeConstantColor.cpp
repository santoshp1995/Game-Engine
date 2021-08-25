#include "GraphicsObjectWireframeConstantColor.h"
#include "CameraMan.h"

namespace Azul
{
	GraphicsObjectWireframeConstantColor::~GraphicsObjectWireframeConstantColor()
	{
		delete this->pWireColor;
	}

	GraphicsObjectWireframeConstantColor::GraphicsObjectWireframeConstantColor(Model* pModel, ShaderObject* pShaderObj, Vect& wireColor)
		: GraphicsObject(pModel, pShaderObj)
	{

		assert(pModel);
		assert(pShaderObj);

		this->pWireColor = new Vect(wireColor);
	}

	void GraphicsObjectWireframeConstantColor::SetState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	void GraphicsObjectWireframeConstantColor::SetDataGPU()
	{
		// Draw Me: -----------------------------------------

		// set the vao
		glBindVertexArray(this->GetModel()->vao);

		// Set state
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);

		// use this shader
		this->pShaderObject->SetActive();

		Camera* pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);

		Matrix world = this->GetWorld();
		Matrix view = pCam->getViewMatrix();
		Matrix proj = pCam->getProjMatrix();

		glUniformMatrix4fv(this->pShaderObject->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);

		glUniform4fv(this->pShaderObject->GetLocation("wire_color"), 1, (float*)this->pWireColor);
	}

	void GraphicsObjectWireframeConstantColor::Draw()
	{
		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObjectWireframeConstantColor::RestoreState()
	{
		// Restore state
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}





}
