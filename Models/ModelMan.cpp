#include "ModelMan.h"

namespace Azul
{
	ModelMan::ModelMan()
	{
		this->pActive = nullptr;
	}

	ModelMan* ModelMan::privGetInstance()
	{
		// This is where its actually stored (BSS section)
		static ModelMan modelMan;
		return &modelMan;
	}

	void ModelMan::Create()
	{
		ModelMan* pModelMan = ModelMan::privGetInstance();
		assert(pModelMan);

		AZUL_UNUSED_VAR(pModelMan);
	}

	Model* ModelMan::Find(Model::ModelType modelType)
	{
		ModelMan* pModelMan = ModelMan::privGetInstance();
		assert(pModelMan);

		Model* pTmp = pModelMan->pActive;

		Model* pReturn = nullptr;


		while (pTmp != nullptr)
		{
			if (pTmp->GetModelType() == modelType)
			{
				pReturn = pTmp;
				break;
			}

			pTmp = (Model*)pTmp->next;
		}

		assert(pReturn);
		return pReturn;
	}

	void ModelMan::Destroy()
	{
		ModelMan* pModelMan = ModelMan::privGetInstance();
		assert(pModelMan);

		Model* pLink = pModelMan->pActive;

		while (pLink != nullptr)
		{
			Model* pTmp = pLink;
			pLink = (Model*)pLink->next;
			pModelMan->privRemove(pTmp, pModelMan->pActive);
			delete pTmp;
		}
	}

	void ModelMan::Add(Model* pModel)
	{
		ModelMan* pModelMan = ModelMan::privGetInstance();
		assert(pModelMan);

		assert(pModel);

		// now add it to manager
		pModelMan->privAddToFront(pModel, pModelMan->pActive);
	}


	void ModelMan::privAddToFront(Model* node, Model*& head)
	{
		assert(node != 0);

		if (head == 0)
		{
			head = node;
			node->next = 0;
			node->prev = 0;
		}
		else
		{
			node->next = head;
			head->prev = node;
			head = node;
		}
	}

	void ModelMan::privRemove(Model* pNode, Model*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (Model*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}

}