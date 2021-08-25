#include "GraphicsObject_TextureLight.h"
#include "Model.h"
#include "Texture.h"
#include "CameraMan.h"
#include "ShaderObject.h"

namespace Azul
{
	GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model* _pModel, ShaderObject* _pShaderObj, TextureName _name, Vect& LightColor, Vect& LightPos)
		: GraphicsObject(_pModel, _pShaderObj), textName(_name)
	{
		this->poLightColor = new Vect(LightColor);
		this->poLightPos = new Vect(LightPos);
		assert(poLightColor);
		assert(poLightPos);
	}

	GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
	{
		delete this->poLightColor;
		delete this->poLightPos;
	}

	void GraphicsObject_TextureLight::SetState()
	{
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture
		GLuint textureID = Texture::FindID(this->textName);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	void GraphicsObject_TextureLight::SetDataGPU()
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

		Vect light = *this->poLightPos;
		Vect color = *this->poLightColor;
		glUniform3fv(this->pShaderObject->GetLocation("vLightPos"), 1, (float*)&light);
		glUniform4fv(this->pShaderObject->GetLocation("vColor"), 1, (float*)&color);
	}

	void GraphicsObject_TextureLight::Draw()
	{
		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_TextureLight::RestoreState()
	{
		// undo the states you corrupted
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}
}

