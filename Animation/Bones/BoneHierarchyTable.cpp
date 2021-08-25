#include "BoneHierarchyTable.h"

namespace Azul
{
	BoneHierarchyTable::BoneHierarchyTable()
	{
		memset(this->pBoneName, 0x0, 64);
		this->index = 0;
		this->parentIndex = 0;
	}
}