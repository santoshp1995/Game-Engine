#include "AstroboyModel.h"
#include "File.h"
#include "ModelData.h"
#include "TextureWrapper.h"
#include "Texture.h"

namespace Azul
{

	struct Vert_xyzuvn
	{
		float x;
		float y;
		float z;
		float s; // u
		float t; // v
		float nx;
		float ny;
		float nz;
	};

	struct Tri_index
	{
		unsigned short v0;
		unsigned short v1;
		unsigned short v2;
	};

	struct Tri_index_val
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};


	AstroboyModel::AstroboyModel(const char* const pModelFileName, int index)
		: Model()
	{
		assert(pModelFileName);

		this->GetTextureName(index, this->texture);
		assert(this->texture);

		this->CreateVAO(pModelFileName);
	}
	
	AstroboyModel::~AstroboyModel()
	{

	}

	void AstroboyModel::CreateVAO(const char* const pModelFileName)
	{
		// chunk shit
		bool status;
		unsigned char* buff;
		unsigned int chunkSize;

		status = this->eat(pModelFileName, ChunkType::VERTS_TYPE, "modelVerts", buff, chunkSize);
		assert(status == true);

		unsigned int vertsSize = (unsigned int)sizeof(Vert_xyzuvn);
		this->numVerts = (int)(chunkSize / vertsSize);

		Vert_xyzuvn* pTmpVertsData = (Vert_xyzuvn*)buff;
		Vert_xyzuvn* pVertsData = new Vert_xyzuvn[(unsigned int)this->numVerts];
		assert(pVertsData);

		for (int i = 0; i < this->numVerts; i++)
		{
			pVertsData[i].x = pTmpVertsData[i].x;
			pVertsData[i].y = pTmpVertsData[i].y;
			pVertsData[i].z = pTmpVertsData[i].z;
			pVertsData[i].s = pTmpVertsData[i].s;
			pVertsData[i].t = pTmpVertsData[i].t;
			pVertsData[i].nx = pTmpVertsData[i].nx;
			pVertsData[i].ny = pTmpVertsData[i].ny;
			pVertsData[i].nz = pTmpVertsData[i].nz;
		}

		delete buff;

		status = this->eat(pModelFileName, ChunkType::TRIS_TYPE, "modelTris", buff, chunkSize);
		assert(status == true);

		unsigned int trisSize = (unsigned int)sizeof(Tri_index);

		this->numTris = (int)(chunkSize / trisSize);

		Tri_index_val* pTriIndex = new Tri_index_val[(unsigned int)this->numTris];

		Tri_index* pTmpData = (Tri_index*)buff;

		for (int i = 0; i < this->numTris; i++)
		{
			pTriIndex[i].v0 = (unsigned int)pTmpData[i].v0;
			pTriIndex[i].v1 = (unsigned int)pTmpData[i].v1;
			pTriIndex[i].v2 = (unsigned int)pTmpData[i].v2;
		}

		delete buff;

		// Data is in RAM...
		// Configure and send data to GPU

		// Create a VAO
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);
		glBindVertexArray(this->vao);

		// Create a VBO
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		glGenBuffers(1, &this->vbo_trilist);
		assert(this->vbo_trilist != 0);

		bool foundTextfile = this->isFileInDirectory(pModelFileName);

		if (!foundTextfile)
		{
			status = this->eat(pModelFileName, ChunkType::TEXTURE_TYPE, "modelTex", buff, chunkSize);
			assert(status == true);

			File::Handle fh;
			File::Error ferror;

			ferror = File::Open(fh, this->texture, File::Mode::WRITE);
			assert(ferror == File::Error::SUCCESS);

			ferror = File::Write(fh, buff, chunkSize);
			assert(ferror == File::Error::SUCCESS);

			ferror = File::Close(fh);
			assert(ferror == File::Error::SUCCESS);

			delete buff;
		}

		if (strcmp(this->texture, "astroboy.tga") == 0)
		{
			Texture::Add(this->texture, TextureName::ASTROBOY);
		}
		

		// Find Bounding Volume - quick hack
	// MOVE this to converter!!!!!
		Vect* pVerts = new Vect[(unsigned int)this->numVerts];
		for (int i = 0; i < this->numVerts; i++)
		{
			pVerts[i].set(pVertsData[i].x, pVertsData[i].y, pVertsData[i].z);
			Trace::out("%d:  %f %f %f\n", i, pVerts[i][x], pVerts[i][y], pVerts[i][z]);
		}

		assert(this->pRefSphere);
		this->pRefSphere->RitterSphere(pVerts, this->numVerts);
		Trace::out("Ritter: cntr:%f %f %f  rad: %f ", this->pRefSphere->cntr[x], this->pRefSphere->cntr[y], this->pRefSphere->cntr[z], this->pRefSphere->rad);

		delete[] pVerts;


		// Load the combined data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), pVertsData, GL_STATIC_DRAW);

		// Define an array of generic vertex attribute data

		// todo make a table or enum - locations needs enums...

		// Vert data is location: 0  (used in vertex shader)
		void* offsetVert = (void*)((unsigned int)&pVertsData[0].x - (unsigned int)pVertsData);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);
		glEnableVertexAttribArray(0);

		// Texture data is location: 1  (used in vertex shader)
		void* offsetTex = (void*)((unsigned int)&pVertsData[0].s - (unsigned int)pVertsData);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
		glEnableVertexAttribArray(1);

		// normals data in location 2 (used in vertex shader
		void* offsetNorm = (void*)((unsigned int)&pVertsData[0].nx - (unsigned int)pVertsData);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
		glEnableVertexAttribArray(2);

		delete pVertsData;

		// Load the index data: ---------------------------------------------------------

			/* Bind our 2nd VBO as being the active buffer and storing index ) */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_trilist);

		/* Copy the index data to our buffer */
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index_val) * this->numTris), pTriIndex, GL_STATIC_DRAW);
		delete pTriIndex;
	}

	void AstroboyModel::GetTextureName(const int index, char*& outTextName)
	{
		switch (index)
		{
		case -1:
			outTextName = "HotPink.tga";
			break;

		case 0:
			outTextName = "astroboy.tga";
			break;

		default:
			break;
		}
	}
}