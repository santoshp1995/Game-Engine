#include "AnimTransitionControllerMan.h"

namespace Azul
{
	AnimTransitionControllerMan::AnimTransitionControllerMan()
	{
		this->pHead = nullptr;
	}

	void AnimTransitionControllerMan::privAddToFront(AnimTransitionController* node, AnimTransitionController*& head)
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

	void AnimTransitionControllerMan::privRemove(AnimTransitionController* pNode, AnimTransitionController*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (AnimTransitionController*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}

	AnimTransitionControllerMan* AnimTransitionControllerMan::privGetInstance()
	{
		static AnimTransitionControllerMan animTransitionControllerMan;
		return &animTransitionControllerMan;
	}

	void AnimTransitionControllerMan::Add(AnimTransitionController* pTransition)
	{
		AnimTransitionControllerMan* pMan = AnimTransitionControllerMan::privGetInstance();
		assert(pMan);

		assert(pTransition);

		pMan->privAddToFront(pTransition, pMan->pHead);
	}

	void AnimTransitionControllerMan::Create()
	{
		AnimTransitionControllerMan* pMan = AnimTransitionControllerMan::privGetInstance();
		assert(pMan);

		AZUL_UNUSED_VAR(pMan);
	}

	void AnimTransitionControllerMan::Destroy()
	{
		AnimTransitionControllerMan* pMan = AnimTransitionControllerMan::privGetInstance();
		assert(pMan);

		AnimTransitionController* pLink = pMan->pHead;

		while (pLink != nullptr)
		{
			AnimTransitionController* pTmp = pLink;
			pLink = (AnimTransitionController*)pLink->next;
			pMan->privRemove(pTmp, pMan->pHead);
			delete pTmp;
		}
	}

	void AnimTransitionControllerMan::Update()
	{
		AnimTransitionControllerMan* pMan = AnimTransitionControllerMan::privGetInstance();
		assert(pMan);

		AnimTransitionController* pTmp = pMan->pHead;

		while (pTmp != nullptr)
		{
			pTmp->Update();

			pTmp = (AnimTransitionController*)pTmp->next;
		}

	}

	void AnimTransitionControllerMan::StartTransition()
	{
		AnimTransitionControllerMan* pMan = AnimTransitionControllerMan::privGetInstance();
		assert(pMan);

		AnimTransitionController* pTmp = pMan->pHead;

		while (pTmp != nullptr)
		{
			pTmp->StartTransition();

			pTmp = (AnimTransitionController*)pTmp->next;
		}
	}


}