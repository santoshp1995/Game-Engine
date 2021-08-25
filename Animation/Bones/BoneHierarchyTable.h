#ifndef BONE_HIERARCHY_TABLE_H
#define BONE_HIERARCHY_TABLE_H

namespace Azul
{
	class BoneHierarchyTable
	{
	public:
		BoneHierarchyTable();
		BoneHierarchyTable(const BoneHierarchyTable&) = delete;
		BoneHierarchyTable& operator= (const BoneHierarchyTable&) = delete;
		~BoneHierarchyTable() = default;

	public:
		char pBoneName[64];
		int index;
		int parentIndex;
	};




}




#endif
