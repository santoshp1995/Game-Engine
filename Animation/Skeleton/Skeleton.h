#ifndef SKELETON_H
#define SKELETON_H

#include "AnimationGameObject.h"
#include "BoneHierarchyTable.h"
#include "Bone.h"
#include "SkinModel.h"
#include "SSBO.h"

namespace Azul
{
	class Skeleton
	{
	public:
		Skeleton(int numBones, const char* const pFileName, SkinModel* pSkinModel);

		Skeleton() = delete;
		Skeleton(const Skeleton&) = delete;
		Skeleton& operator = (const Skeleton&) = delete;
		~Skeleton();

		//GameObjectAnim* GetFirstBone();

		SSBO* pSSBO_hierarchy;
		SSBO* pSSBO_resultMatrix;
		
		int GetFlag();

		SkinModel* GetSkinModel() const;


		//GameObjectAnim* FindBoneByIndex(int index);
	private:
		void privExtractTableData(const char* const pFileName);
		void privSetAnimationHierarchy();
		void privSetMatrixData();
		

	private:
		//GameObjectAnim* pFirstBone;
		BoneHierarchyTable* pTable;
		SkinModel* pSkinModel;
		
		int* pMatData;
		int             numBones;
		int flag;
	};
}




#endif

// --- End of File ---
