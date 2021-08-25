//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "PyramidModel.h"
#include "GraphicsObject_TextureLight.h"
#include "GameObjectMan.h"
#include "ModelMan.h"
#include "ShaderMan.h"
#include "GameObjectRigid.h"
#include "GraphicsObject_Null.h"
#include "NullModel.h"
#include "Skeleton.h"
#include "PCSTreeForwardIterator.h"
#include "GameObjectMan.h"
#include "ExtractData.h"
#include <vector>

namespace Azul
{
	Skeleton::Skeleton(int _numBones, const char* const pFileName, SkinModel* _pSkinModel)
		:
		numBones(_numBones)
	{
		assert(_pSkinModel);

		if (strcmp(pFileName, "humanoid.azul") == 0)
		{
			this->flag = 0;
		}

		else
		{
			this->flag = 1;
		}

		this->pSkinModel = _pSkinModel;

		this->pSSBO_hierarchy = new SSBO();
		this->pSSBO_resultMatrix = new SSBO();
		

		this->pTable = new BoneHierarchyTable[(unsigned int)this->numBones];
		this->privExtractTableData(pFileName);
		this->privSetAnimationHierarchy();
	
		this->pMatData = nullptr;
	}


	Skeleton::~Skeleton()
	{
		delete this->pTable;
		
		delete this->pSSBO_hierarchy;

		delete this->pSSBO_resultMatrix;
	}

	int Skeleton::GetFlag()
	{
		return this->flag;
	}

	SkinModel* Skeleton::GetSkinModel() const
	{
		return this->pSkinModel;
	}

	
	void Skeleton::privExtractTableData(const char* const pFileName)
	{
		bool status;
		unsigned char* buff;
		unsigned int chunkSize;

		status = ExtractData::eat(pFileName, ChunkType::ANIM_TYPE, "boneTree", buff, chunkSize);
		assert(status);

		BoneHierarchyTable* pTmpData = (BoneHierarchyTable*)buff;

		for (int i = 0; i < this->numBones; i++)
		{
			strcpy_s(this->pTable[i].pBoneName, pTmpData[i].pBoneName);
			this->pTable[i].index = pTmpData[i].index;
			this->pTable[i].parentIndex = pTmpData[i].parentIndex;
		}

		//Bone* pBoneLocal = new Bone[this->numBones]();
		Matrix* pResultMatrix = new Matrix[this->numBones]();

		this->pMatData = new int[this->numBones * this->numBones];
		this->privSetMatrixData();

		this->pSSBO_hierarchy->Set(this->numBones * this->numBones, sizeof(int), &this->pMatData[0]);
		this->pSSBO_resultMatrix->Set(this->numBones, sizeof(Matrix), pResultMatrix);

		delete[] this->pMatData;
		delete[] pResultMatrix;

		delete buff;
	}

	void Skeleton::privSetAnimationHierarchy()
	{
		// Load the model
		PyramidModel* pPyramidModel = new PyramidModel("pyramidModel.azul");
		assert(pPyramidModel);
		ModelMan::Add(pPyramidModel);

		// Create/Load Shader 
		ShaderObject* pShaderObject_textureLight = new ShaderObject(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_textureLight);
		ShaderMan::Add(pShaderObject_textureLight);

		ShaderObject* pShaderObject_null = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_null);
		ShaderMan::Add(pShaderObject_null);

		// Create GameObject
		Vect color;
		Vect pos(1, 1, 1);
	}

	void Skeleton::privSetMatrixData()
	{
		std::vector<std::vector<int>> _matrix(numBones, std::vector<int>(numBones, numBones));


		for (int i = 0; i < numBones; i++)
		{
			_matrix[i][0] = 0;

			int j = i;

			while (j > 0)
			{
				_matrix[i][j] = j;
				j = pTable[j].parentIndex;
			}
		}

		for (int i = 0; i < numBones; i++)
		{
			for (int j = 0; j < numBones; j++)
			{
				Trace::out("%2d ", _matrix[i][j]);

				this->pMatData[i * numBones + j] = _matrix[i][j];
			}

			Trace::out("\n");
		}
	}
}

// --- End of File ---