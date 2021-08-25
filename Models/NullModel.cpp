#include "NullModel.h"

namespace Azul
{
	NullModel::NullModel(const char* const pModelFileName)
		:Model()
	{
		AZUL_UNUSED_VAR(pModelFileName);
	}

	NullModel::~NullModel()
	{
	}

	void NullModel::CreateVAO(const char* const modelFileName)
	{
		AZUL_UNUSED_VAR(modelFileName);
	}
}





