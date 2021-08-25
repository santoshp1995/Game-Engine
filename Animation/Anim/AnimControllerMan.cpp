#include "AnimControllerMan.h"

namespace Azul
{
	AnimControllerMan::AnimControllerMan()
	{
		this->pHead = nullptr;
	}

	AnimControllerMan* AnimControllerMan::privGetInstance()
	{		
		static AnimControllerMan animControllerMan;
		return &animControllerMan;
	}

	void AnimControllerMan::Create()
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan);

		AZUL_UNUSED_VAR(pMan);
	}

	AnimController* AnimControllerMan::Find(AnimController::ControllerType type)
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan);


		AnimController* pTmp = pMan->pHead;

		AnimController* pReturn = nullptr;

		while (pTmp != nullptr)
		{
			if (pTmp->GetType() == type)
			{
				pReturn = pTmp;
				break;
			}

			pTmp = (AnimController*)pTmp->next;
		}

		assert(pReturn);
		return pReturn;
	}

	void AnimControllerMan::Destroy()
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan);

		AnimController* pLink = pMan->pHead;

		while (pLink != nullptr)
		{
			AnimController* pTmp = pLink;
			pLink = (AnimController*)pLink->next;
			pMan->privRemove(pTmp, pMan->pHead);
			delete pTmp;
		}
	}

	void AnimControllerMan::Update()
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan);

		AnimController* pTmp = pMan->pHead;

		while (pTmp != nullptr)
		{
			pTmp->Update();

			pTmp = (AnimController*)pTmp->next;
		}
	}

	
	void AnimControllerMan::Add(AnimController* pController)
	{
		AnimControllerMan* pMan = AnimControllerMan::privGetInstance();
		assert(pMan);

		assert(pController);

		pMan->privAddToFront(pController, pMan->pHead);
	}

	void AnimControllerMan::privAddToFront(AnimController* node, AnimController*& head)
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

	void AnimControllerMan::privRemove(AnimController* pNode, AnimController*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (AnimController*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}
}