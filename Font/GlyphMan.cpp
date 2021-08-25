#include "GlyphMan.h"
#include "pugixml.hpp"
#include "Parser.h"


namespace Azul
{
	GlyphMan::GlyphMan()
	{
		this->pActive = nullptr;
	}

	void GlyphMan::privAddToFront(Glyph* node, Glyph*& head)
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

	void GlyphMan::privRemove(Glyph* pNode, Glyph*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (Glyph*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}

	GlyphMan* GlyphMan::privGetInstance()
	{
		static GlyphMan glyphMan;
		return &glyphMan;
	}

	void GlyphMan::Create()
	{
		GlyphMan* pMan = GlyphMan::privGetInstance();
		assert(pMan);

		AZUL_UNUSED_VAR(pMan);

	}

	void GlyphMan::Add(Glyph::Name name, int key, TextureName textName, float x, float y, float width, float height)
	{
		GlyphMan* pMan = GlyphMan::privGetInstance();
		assert(pMan);

		Glyph* pNode = new Glyph();

		// set values
		pNode->Set(name, key, textName, x, y, width, height);

		// add it to the list
		pMan->privAddToFront(pNode, pMan->pActive);
	}

	void GlyphMan::AddXml(Glyph::Name glyphName, string assetName, TextureName textName)
	{
		pugi::xml_document doc;

		pugi::xml_parse_result result = doc.load_file(assetName.c_str());

		// should never hit here
		if (!result)
		{
			assert(false);
		}

		pugi::xml_node root = doc.child("fontMetrics");

		pugi::xml_node tmp;

		int key = -1;
		int x = -1;
		int y = -1;
		int width = -1;
		int height = -1;

		for (pugi::xml_node currentNode = root.first_child(); currentNode; currentNode = currentNode.next_sibling())
		{
			key = std::atoi(currentNode.first_attribute().value());

			tmp = currentNode.first_child();

			Parser::ParseValues(key, x, y, width, height);

			// Add glyph to manager
			GlyphMan::Add(glyphName, key, textName, (float)x, (float)y, (float)width, (float)height);

		}
		
	}

	Glyph* GlyphMan::Find(Glyph::Name name, int key)
	{
		GlyphMan* pMan = GlyphMan::privGetInstance();
		assert(pMan);

		Glyph* pTmp = pMan->pActive;
		Glyph* pReturn = nullptr;


		while (pTmp != nullptr)
		{
			if (pTmp->GetName() == name && pTmp->GetKey() == key)
			{
				pReturn = pTmp;
				break;
			}

			pTmp = (Glyph*)pTmp->next;
		}

		assert(pReturn);
		return pReturn;
	}

	void GlyphMan::Destroy()
	{
		GlyphMan* pMan = GlyphMan::privGetInstance();
		assert(pMan);

		Glyph* pLink = pMan->pActive;

		while (pLink != nullptr)
		{
			Glyph* pTmp = pLink;
			pLink = (Glyph*)pLink->next;
			pMan->privRemove(pTmp, pMan->pActive);
			delete pTmp;
		}
	}


}