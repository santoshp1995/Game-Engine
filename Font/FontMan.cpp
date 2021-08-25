#include "FontMan.h"

namespace Azul
{
	FontMan::FontMan()
	{
		this->pActive = nullptr;
	}

	FontMan* FontMan::privGetInstance()
	{
		static FontMan fontMan;
		return &fontMan;
	}

	void FontMan::Create()
	{
		FontMan* pMan = FontMan::privGetInstance();
		assert(pMan);

		AZUL_UNUSED_VAR(pMan);
	}

	void FontMan::Add(Font::Name name, GraphicsObject_Font* pGraphicsObj, 
		const char* const pMessageString, float xStart, float yStart)
	{
		FontMan* pMan = FontMan::privGetInstance();
		assert(pMan);

		Font* pNode = new Font(name, pGraphicsObj);



		pNode->Set(pMessageString, xStart, yStart);

		// add node to the list
		pMan->privAddToFront(pNode, pMan->pActive);
	}

	Font* FontMan::Find(Font::Name name)
	{
		FontMan* pMan = FontMan::privGetInstance();
		assert(pMan);

		Font* pTmp = pMan->pActive;
		Font* pReturn = nullptr;

		while (pTmp != nullptr)
		{
			if (pTmp->GetName() == name)
			{
				pReturn = pTmp;
				break;
			}

			pTmp = (Font*)pTmp->next;
		}

		return pReturn;
	}

	void FontMan::Destroy()
	{
		FontMan* pMan = FontMan::privGetInstance();
		assert(pMan);

		Font* pLink = pMan->pActive;

		while (pLink != nullptr)
		{
			Font* pTmp = pLink;
			pLink = (Font*)pLink->next;
			pMan->privRemove(pTmp, pMan->pActive);
			delete pTmp;
		}
	}

	void FontMan::privAddToFront(Font* node, Font*& head)
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

	void FontMan::privRemove(Font* pNode, Font*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (Font*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}
}