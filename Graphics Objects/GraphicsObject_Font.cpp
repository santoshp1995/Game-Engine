#include "GraphicsObject_Font.h"
#include "Model.h"
#include "Camera.h"
#include "CameraMan.h"

namespace Azul
{
	GraphicsObject_Font::GraphicsObject_Font(Model* pModel, ShaderObject* pShaderObj, Glyph* pGlyph)
		: GraphicsObject(pModel, pShaderObj)
	{
		assert(pGlyph);

		Rect* pRect = pGlyph->GetRect();
		this->pTextNode = pGlyph->GetTextNode();


		this->origWidth = pRect->width;
		this->origHeight = pRect->height;

		this->origPosX = pRect->x;
		this->origPosY = pRect->y;

		// Create the UV matrix
		this->poMatrix_uv = new Matrix();

		float w = pRect->width / (float)this->pTextNode->width;
		float h = pRect->height / (float)this->pTextNode->height;
		float u = pRect->x / (float)this->pTextNode->width;
		float v = pRect->y / (float)this->pTextNode->height;
		Matrix ScaleUV(Matrix::Scale::XYZ, w, h, 1.0f);
		Matrix TransUV(Matrix::Trans::XYZ, u, v, 0.0f);
		*this->poMatrix_uv = ScaleUV * TransUV;

		// Create the orig Matrix 
		// The initial sprite setup, after this point standard world will adjust
		this->poMatrix_orig = new Matrix();

		Matrix Scale(Matrix::Scale::XYZ, this->origWidth, this->origHeight, 1.0f);
		*this->poMatrix_orig = Scale;
	}

	GraphicsObject_Font::~GraphicsObject_Font()
	{
		delete this->poMatrix_uv;
		delete this->poMatrix_orig;
	}

	void GraphicsObject_Font::SetState()
	{
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture
		GLuint textureID = this->pTextNode->textureID;
		glBindTexture(GL_TEXTURE_2D, textureID);

		// comment out one
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CW);

		// Blends for sprites
		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	}

	void GraphicsObject_Font::SetDataGPU()
	{
		// Get camera
		Camera* pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);

		// set the vao
		glBindVertexArray(this->GetModel()->vao);

		// use this shader
		this->pShaderObject->SetActive();

		// World matrix ----------------------------
		Matrix TransToOriginLowerLeft(Matrix::Trans::XYZ, (float)-pCam->getScreenWidth() / 2.0f, (float)-pCam->getScreenHeight() / 2.0f, 0.0f);
		Matrix tmpMatrix = *this->poMatrix_orig * this->GetWorld() * TransToOriginLowerLeft;

		glUniformMatrix4fv(this->pShaderObject->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&pCam->getProjMatrix());
		glUniformMatrix4fv(this->pShaderObject->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&pCam->getViewMatrix());
		glUniformMatrix4fv(this->pShaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&tmpMatrix);
		glUniformMatrix4fv(this->pShaderObject->GetLocation("uv_matrix"), 1, GL_FALSE, (float*)this->poMatrix_uv);

	}

	void GraphicsObject_Font::Draw()
	{
		// draw
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);   //The starting point of the IBO
	}

	void GraphicsObject_Font::RestoreState()
	{
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	void GraphicsObject_Font::Swap(Glyph* pGlyph, Rect r)
	{
		assert(pGlyph);

		this->origWidth = r.width;
		this->origHeight = r.height;

		this->origPosX = r.x;
		this->origPosY = r.y;

		float w = pGlyph->GetRect()->width / pGlyph->GetTextNode()->width;
		float h = pGlyph->GetRect()->height / pGlyph->GetTextNode()->height;
		float u = pGlyph->GetRect()->x / pGlyph->GetTextNode()->width;
		float v = pGlyph->GetRect()->y / pGlyph->GetTextNode()->height;

		Matrix ScaleUV(Matrix::Scale::XYZ, w, h, 1.0f);
		Matrix TransUV(Matrix::Trans::XYZ, u, v, 0.0f);
		*this->poMatrix_uv = ScaleUV * TransUV;

		Matrix Scale(Matrix::Scale::XYZ, this->origWidth, this->origHeight, 1.0f);
		*this->poMatrix_orig = Scale;

	}
}