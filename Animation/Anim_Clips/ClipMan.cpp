#include "ClipMan.h"

namespace Azul
{
	ClipMan::ClipMan()
	{
		this->pHead = nullptr;
	}

	ClipMan* ClipMan::privGetInstance()
	{
		static ClipMan clipMan;
		return &clipMan;
	}

	void ClipMan::Create()
	{
		ClipMan* pClipMan = ClipMan::privGetInstance();
		assert(pClipMan);

		// shut up compiler warnings..
		AZUL_UNUSED_VAR(pClipMan);
	}

	void ClipMan::Add(Clip* pClip)
	{
		assert(pClip);

		ClipMan* pClipMan = ClipMan::privGetInstance();
		assert(pClipMan);

		pClipMan->privAddToFront(pClip, pClipMan->pHead);
	}

	Clip* ClipMan::Find(Clip::ClipName name)
	{
		ClipMan* pClipMan = ClipMan::privGetInstance();
		assert(pClipMan);

		Clip* pTmp = pClipMan->pHead;

		Clip* pReturn = nullptr;

		while (pTmp != nullptr)
		{
			if (pTmp->GetClipName() == name)
			{
				pReturn = pTmp;
				break;
			}

			pTmp = (Clip*)pTmp->next;
		}

		assert(pReturn);
		return pReturn;
	}

	void ClipMan::Destroy()
	{
		ClipMan* pClipMan = ClipMan::privGetInstance();
		assert(pClipMan);

		Clip* pLink = pClipMan->pHead;

		while (pLink != nullptr)
		{
			Clip* pTmp = pLink;
			pLink = (Clip*)pLink->next;
			pClipMan->privRemove(pTmp, pClipMan->pHead);
			delete pTmp;
		}
	}

	void ClipMan::privAddToFront(Clip* node, Clip*& head)
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

	void ClipMan::privRemove(Clip* pNode, Clip*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (Clip*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}
}