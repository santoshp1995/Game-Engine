#include "GraphicsObject_FlatTexture.h"
#include "Texture.h"
#include "Model.h"
#include "CameraMan.h"


namespace Azul
{
	GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(const Model* const _pModel, const ShaderObject* const _pShaderObj, TextureName _name)
		: GraphicsObject(_pModel, _pShaderObj), textName(_name)
	{
		assert(this->pModel);
		assert(this->pShaderObject);
		assert(this->pWorld);
	}

	void GraphicsObject_FlatTexture::SetState()
	{
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture
		GLuint textureID = Texture::FindID(this->textName);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	void GraphicsObject_FlatTexture::SetDataGPU()
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
		glUniformMatrix4fv(this->pShaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);;

		glUniform1i(this->pShaderObject->GetLocation("tex_object"), 0);
	}

	void GraphicsObject_FlatTexture::Draw()
	{
		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_FlatTexture::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}
}




