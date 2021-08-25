#include "GraphicsObject_SkinTexture.h"
#include "CameraMan.h"
#include "SkinModel.h"


namespace Azul
{
	GraphicsObject_SkinTexture::GraphicsObject_SkinTexture(const Model* pModel, const ShaderObject* pShaderObj, TextureName name) : GraphicsObject(pModel, pShaderObj), textName(name)
	{
		// check the base class
		assert(this->pModel);
		assert(this->pShaderObject);
		assert(this->pWorld);
	}

	void GraphicsObject_SkinTexture::SetState()
	{
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture
		GLuint textureID = Texture::FindID(this->textName);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}

	void GraphicsObject_SkinTexture::SetDataGPU()
	{
		// use this shader
		this->pShaderObject->SetActive();

		// set the vao
		glBindVertexArray(this->GetModel()->vao);

		Camera* pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		assert(pCam);

		Matrix view = pCam->getViewMatrix();
		Matrix proj = pCam->getProjMatrix();

		SkinModel* pSkinModel = (SkinModel*)this->GetModel();

		pSkinModel->pSSBO_inversePose->Bind(0);
		pSkinModel->pSSBO_boneWorld->Bind(1);

		// Send over Uniforms
		glUniformMatrix4fv(this->pShaderObject->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	}

	void GraphicsObject_SkinTexture::Draw()
	{
		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_SkinTexture::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}
}
