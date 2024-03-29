#include "sb7.h"
#include "SpriteModel.h"
#include "SpriteVBO.h"

namespace Azul
{
#define SPRITE_TRILIST_NUM_TRIANGLES (sizeof(SpriteTriList)/sizeof(Tri_index))

	Tri_index SpriteTriList[] =
	{
		{ 0, 1, 2 },
		{ 2, 3, 0 }
	};

#define SPRITE_DATA_NUM_VERTS (sizeof(SpriteData)/sizeof(Vert_xyzuv))

	Vert_xyzuv  SpriteData[] =
	{
		// Triangle 0
		{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f}, //0
		{  0.5f,  0.5f, 0.0f, 1.0f, 0.0f},// 1
		{  0.5f, -0.5f, 0.0f, 1.0f, 1.0f}, //2

		// Triangle 1
		{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  //3
	};

	void SpriteModel::CreateVAO(const char* const modelFileName)
	{
		// future proofing it for a file
		AZUL_UNUSED_VAR(modelFileName);

		this->numVerts = SPRITE_DATA_NUM_VERTS;
		this->numTris = SPRITE_TRILIST_NUM_TRIANGLES;

		// Create a VAO
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);
		glBindVertexArray(this->vao);

		// Create a VBO
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		glGenBuffers(1, &this->vbo_trilist);
		assert(this->vbo_trilist != 0);

		// Load the combined data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (int)sizeof(Vert_xyzuv) * this->numVerts, SpriteData, GL_STATIC_DRAW);

		// Vertext data in location 0
		void* offsetVert = (void*)((unsigned int)&SpriteData[0].x - (unsigned int)SpriteData);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuv), offsetVert);
		glEnableVertexAttribArray(0);

		// Texture data in location 1
		void* offsetTex = (void*)((unsigned int)&SpriteData[0].u - (unsigned int)SpriteData);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuv), offsetTex);
		glEnableVertexAttribArray(1);

		// Load the index data: ---------------------------------------------------------

		/* Bind our 2nd VBO as being the active buffer and storing index ) */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_trilist);

		/* Copy the index data to our buffer */
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int)sizeof(Tri_index) * this->numTris, SpriteTriList, GL_STATIC_DRAW);
	}


	SpriteModel::SpriteModel(const char* const modelFileName)
		: Model()
	{
		this->CreateVAO(modelFileName);
	}

	SpriteModel::~SpriteModel()
	{
	}
}