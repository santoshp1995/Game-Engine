#include "SkinModel.h"
#include "GenericData.h"


namespace Azul
{
	struct Vert_xyzuvn
	{
		int index;
		float x;
		float y;
		float z;
		float u;
		float v;
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

	struct Bone_weight_data
	{
		float a;
		float b;
		float c;
		float d;
	};

	struct Bone_index_data
	{
		unsigned int ia;
		unsigned int ib;
		unsigned int ic;
		unsigned int id;
	};

	struct Matrix_data
	{
		float m0;
		float m1;
		float m2;
		float m3;
		float m4;
		float m5;
		float m6;
		float m7;
		float m8;
		float m9;
		float m10;
		float m11;
		float m12;
		float m13;
		float m14;
		float m15;
	};

	void SkinModel::CreateVAO(const char* const modelFileName)
	{

		bool status;
		unsigned char* buff;
		unsigned int chunkSize;

		status = this->eat(modelFileName, ChunkType::DATA_TYPE, "genericData", buff, chunkSize);
		assert(status);

		GenericData* pGenericData = (GenericData*)buff;

		this->numVerts = pGenericData->numVerts;
		this->numTris = pGenericData->numTris;
		this->NumBones = pGenericData->numBones;

		this->pSSBO_inversePose = new SSBO();
		this->pSSBO_boneWorld = new SSBO();
		this->pSSBO_rigidWorld = new SSBO();
		this->poRigidWorld = new Matrix(Matrix::Special::Identity);

		delete buff;

		status = this->eat(modelFileName, ChunkType::VERTS_TYPE, "modelVerts", buff, chunkSize);
		assert(status);

		Vert_xyzuvn* pTmpVertsData = (Vert_xyzuvn*)buff;

		Vert_xyzuvn* pVertsData = new Vert_xyzuvn[(unsigned int)this->numVerts];
		assert(pVertsData);

		for (int i = 0; i < this->numVerts; i++)
		{
			pVertsData[i].index = pTmpVertsData[i].index;
			pVertsData[i].x = pTmpVertsData[i].x;
			pVertsData[i].y = pTmpVertsData[i].y;
			pVertsData[i].z = pTmpVertsData[i].z;

			if (pTmpVertsData[i].u < -1.f)
			{
				pVertsData[i].u = 0.0f;
				pVertsData[i].v = 0.0f;
			}

			else
			{
				pVertsData[i].u = pTmpVertsData[i].u;
				pVertsData[i].v = pTmpVertsData[i].v;
			}

			pVertsData[i].nx = pTmpVertsData[i].nx;
			pVertsData[i].ny = pTmpVertsData[i].ny;
			pVertsData[i].nz = pTmpVertsData[i].nz;
		}

		delete buff;

		status = this->eat(modelFileName, ChunkType::TRIS_TYPE, "modelTris", buff, chunkSize);
		assert(status);

		Tri_index_val* pTriIndex = new Tri_index_val[(unsigned int)this->numTris];
		Tri_index* pTmpData = (Tri_index*)buff;

		for (int i = 0; i < this->numTris; i++)
		{
			pTriIndex[i].v0 = (unsigned int)pTmpData[i].v0;
			pTriIndex[i].v1 = (unsigned int)pTmpData[i].v1;
			pTriIndex[i].v2 = (unsigned int)pTmpData[i].v2;
		}

		delete buff;

		status = this->eat(modelFileName, ChunkType::BONE_WEIGHT_TYPE, "weights", buff, chunkSize);
		assert(status);

		Bone_weight_data* pBoneWeightData = new Bone_weight_data[(unsigned int)this->numVerts];
		Bone_weight_data* pTmpBoneWeightsData = (Bone_weight_data*)buff;

		for (int i = 0; i < this->numVerts; i++)
		{
			pBoneWeightData[i].a = pTmpBoneWeightsData[i].a;
			pBoneWeightData[i].b = pTmpBoneWeightsData[i].b;
			pBoneWeightData[i].c = pTmpBoneWeightsData[i].c;
			pBoneWeightData[i].d = pTmpBoneWeightsData[i].d;
		}

		delete buff;

		status = this->eat(modelFileName, ChunkType::BONE_INDEX_TYPE, "boneIndex", buff, chunkSize);
		assert(status);

		Bone_index_data* pBoneIndexData = new Bone_index_data[(unsigned int)this->numVerts];
		Bone_index_data* pTmpBoneIndexData = (Bone_index_data*)buff;

		for (int i = 0; i < this->numVerts; i++)
		{
			pBoneIndexData[i].ia = pTmpBoneIndexData[i].ia;
			pBoneIndexData[i].ib = pTmpBoneIndexData[i].ib;
			pBoneIndexData[i].ic = pTmpBoneIndexData[i].ic;
			pBoneIndexData[i].id = pTmpBoneIndexData[i].id;
		}

		delete buff;

		status = this->eat(modelFileName, ChunkType::INVERSE_POSE_TYPE, "boneMatrix", buff, chunkSize);
		assert(status);

		Matrix_data* pMatrixData = new Matrix_data[(unsigned int)this->NumBones];
		Matrix_data* pTmpMatrixData = (Matrix_data*)buff;

		for (int i = 0; i < (int)this->NumBones; i++)
		{
			pMatrixData[i].m0 = pTmpMatrixData[i].m0;
			pMatrixData[i].m1 = pTmpMatrixData[i].m1;
			pMatrixData[i].m2 = pTmpMatrixData[i].m2;
			pMatrixData[i].m3 = pTmpMatrixData[i].m3;
			pMatrixData[i].m4 = pTmpMatrixData[i].m4;
			pMatrixData[i].m5 = pTmpMatrixData[i].m5;
			pMatrixData[i].m6 = pTmpMatrixData[i].m6;
			pMatrixData[i].m7 = pTmpMatrixData[i].m7;
			pMatrixData[i].m8 = pTmpMatrixData[i].m8;
			pMatrixData[i].m9 = pTmpMatrixData[i].m9;
			pMatrixData[i].m10 = pTmpMatrixData[i].m10;
			pMatrixData[i].m11 = pTmpMatrixData[i].m11;
			pMatrixData[i].m12 = pTmpMatrixData[i].m12;
			pMatrixData[i].m13 = pTmpMatrixData[i].m13;
			pMatrixData[i].m14 = pTmpMatrixData[i].m14;
			pMatrixData[i].m15 = pTmpMatrixData[i].m15;

		}

		delete buff;


		Matrix* pInvPose = new Matrix[this->NumBones];
		Matrix* poBoneWorld = new Matrix[this->NumBones];


		Matrix matIdentity(Matrix::Special::Identity);
		for (unsigned int i = 0; i < this->NumBones; i++)
		{
			pInvPose[i] = *(Matrix*)&pMatrixData[i];
		}

		this->pSSBO_inversePose->Set(this->NumBones, sizeof(Matrix), pInvPose);
		this->pSSBO_boneWorld->Set(this->NumBones, sizeof(Matrix), poBoneWorld);


		delete[] pInvPose;
		delete[] poBoneWorld;

		// Create a VAO
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);

		glBindVertexArray(this->vao);  //<---- active

		// Create a VBO
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		glGenBuffers(1, &this->vbo_trilist);
		assert(this->vbo_trilist != 0);

		glGenBuffers(1, &this->vbo_boneweight);
		assert(this->vbo_boneweight != 0);

		glGenBuffers(1, &this->vbo_boneindex);
		assert(this->vbo_boneindex != 0);

		// Load VERTS: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);
		
		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), pVertsData, GL_STATIC_DRAW);

		// Vertext data in location 0
		void* offsetVert = (void*)((unsigned int)&pVertsData[0].x - (unsigned int)pVertsData);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);
		glEnableVertexAttribArray(0);

		// Texture data in location 1
		void* offsetTex = (void*)((unsigned int)&pVertsData[0].u - (unsigned int)pVertsData);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
		glEnableVertexAttribArray(1);

		// Normal data in location 2
		void* offsetNorm = (void*)((unsigned int)&pVertsData[0].nx - (unsigned int)pVertsData);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
		glEnableVertexAttribArray(2);

		// Load BoneWeight: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_boneweight);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Bone_weight_data) * this->numVerts), pBoneWeightData, GL_STATIC_DRAW);

		// BoneWeight data in location 3
		offsetVert = (void*)((unsigned int)&pBoneWeightData[0].a - (unsigned int)pBoneWeightData);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Bone_weight_data), offsetVert);
		glEnableVertexAttribArray(3);

		// Load BoneIndex: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_boneindex);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Bone_index_data) * this->numVerts), pBoneIndexData, GL_STATIC_DRAW);

		// BoneIndex data in location 4
		offsetVert = (void*)((unsigned int)&pBoneIndexData[0].ia - (unsigned int)pBoneIndexData);
		glVertexAttribIPointer(4, 4, GL_UNSIGNED_INT, sizeof(Bone_index_data), offsetVert);
		glEnableVertexAttribArray(4);

		// Load TriList: ---------------------------------------------------------

		/* Bind our 2nd VBO as being the active buffer and storing index ) */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_trilist);

		/* Copy the index data to our buffer */
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index_val) * this->numTris), pTriIndex, GL_STATIC_DRAW);

		// clean up mem leaks
		delete pVertsData;
		delete pTriIndex;
		delete pBoneWeightData;
		delete pBoneIndexData;
		delete pMatrixData;
	}

	SkinModel::SkinModel(const char* const modelFileName)
		: Model(),
		vbo_boneweight(0),
		vbo_boneindex(0),
		NumBones(0),
		pSSBO_inversePose(nullptr),
		pSSBO_rigidWorld(nullptr),
		poRigidWorld(nullptr)
	{
		this->CreateVAO(modelFileName);

	}

	SkinModel::~SkinModel()
	{
		// remove anything dynamic here
		delete this->pSSBO_inversePose;
		delete this->pSSBO_boneWorld;
		delete this->pSSBO_rigidWorld;
		delete this->poRigidWorld;
	}
}