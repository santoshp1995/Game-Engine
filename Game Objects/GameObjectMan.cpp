#include "NullModel.h"
#include "GraphicsObject_Null.h"
#include "GameObject.h"
#include "GameObjectRigid.h"
#include "GameObjectMan.h"
#include "ModelMan.h"
#include "ShaderMan.h"
#include "PCSTreeForwardIterator.h"
#include "GameObjectNull.h"
#include "SimpleGameObject.h"
#include "AnimationGameObject.h"
#include "GameObjectFont.h"


namespace Azul
{
	GameObjectMan::GameObjectMan()
	{
		NullModel* pModel = new NullModel(nullptr);
		assert(pModel);
		ModelMan::Add(pModel);

		ShaderObject* pShaderObj = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObj);
		ShaderMan::Add(pShaderObj);

		GraphicsObject_Null* pGraphicsObject = new GraphicsObject_Null(pModel, pShaderObj);

		GameObjectNull* pGameRoot = new GameObjectNull(pGraphicsObject);
		pGameRoot->SetName("GameObjectNull_Root");

		// create the tree
		this->pRootTree = new PCSTree();
		assert(this->pRootTree);

		// attach the root node
		this->pRootTree->Insert(pGameRoot, this->pRootTree->GetRoot());
	}

	GameObjectMan* GameObjectMan::privGetInstance()
	{
		// This is where its actually stored (BSS section)
		static GameObjectMan gom;
		return &gom;
	}

	void GameObjectMan::Add(GameObject* pObj)
	{
		assert(pObj != 0);

		// Get Singleton
		GameObjectMan* pMan = GameObjectMan::privGetInstance();

		// get root node
		PCSNode* pRootNode = pMan->pRootTree->GetRoot();

		// insert object to root
		pMan->pRootTree->Insert(pObj, pRootNode);
	}

	void GameObjectMan::Add(GameObject* pObj, GameObject* pParent)
	{
		assert(pObj != nullptr);
		assert(pParent != nullptr);

		// Get singleton
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();

		// insert object to root
		pGOM->pRootTree->Insert(pObj, pParent);
	}

	void GameObjectMan::Draw(void)
	{
		GameObjectMan* pMan = GameObjectMan::privGetInstance();
		assert(pMan);

		PCSNode* pRootNode = pMan->pRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForIter(pRootNode);

		PCSNode* pNode = pForIter.First();

		GameObject* pGameObj = nullptr;

		while (!pForIter.IsDone())
		{
			assert(pNode);

			pGameObj = (GameObject*)pNode;

			pGameObj->Draw();

			if (pGameObj->GetType() == GameObject::Type::FONT)
			{
				GameObjectFont* pFontObj = (GameObjectFont*)pGameObj;

				pFontObj->DrawFont();
			}


			pNode = pForIter.Next();
		}
	}

	void GameObjectMan::Update(AnimTime currentTime)
	{
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode* pRootNode = pGOM->pRootTree->GetRoot();
		assert(pRootNode);

		if (pRootNode->GetChild() != nullptr)
		{
			//Trace::out("%p\n", pRootNode->GetChild());

			PCSTreeForwardIterator pIter(pRootNode);

			PCSNode* pNode = pIter.First();

			GameObject* pGameObj = 0;

			while (!pIter.IsDone())
			{
				assert(pNode);
				// Update the game object
				pGameObj = (GameObject*)pNode;

				//if (pGameObj->GetType() == GameObject::Type::ANIM_TYPE)
				//{
					pGameObj->Update(currentTime);
				//}

				pNode = pIter.Next();
			}
		}
	}

	GameObject* GameObjectMan::GetRoot(void)
	{
		// Get singleton
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		GameObject* pGameObj = (GameObject*)pGOM->pRootTree->GetRoot();
		assert(pGameObj);

		return pGameObj;
	}

	PCSTree* GameObjectMan::GetPCSTree()
	{
		// Get singleton
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		// Get root node
		return pGOM->pRootTree;
	}

	void GameObjectMan::Destroy()
	{
		// Get singleton
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSTree* pTree = pGOM->pRootTree;
		PCSNode* pNode = nullptr;

		PCSTreeForwardIterator pForIter(pTree->GetRoot());
		pNode = pForIter.First();
		PCSNode* pTmp = nullptr;
		while (!pForIter.IsDone())
		{
			pTmp = pForIter.CurrentItem();

			pNode = pForIter.Next();
			delete pTmp;
			pTmp = nullptr;
		}


	}

	void GameObjectMan::ToggleBoundingSpheresOff()
	{
		GameObjectMan* pMan = GameObjectMan::privGetInstance();
		assert(pMan);

		PCSNode* pRootNode = pMan->pRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForIter(pRootNode);

		PCSNode* pNode = pForIter.First();

		GameObject* pGameObj = nullptr;

		while (!pForIter.IsDone())
		{
			assert(pNode);

			pGameObj = (GameObject*)pNode;

			if (pGameObj->GetType() == GameObject::Type::BOUNDING_OBJECT)
			{
				// turn rendering off
				pGameObj->SetRender(false);
			}

			pNode = pForIter.Next();
		}
	}

	void GameObjectMan::ToggleBoundingSpheresOn()
	{
		GameObjectMan* pMan = GameObjectMan::privGetInstance();
		assert(pMan);

		PCSNode* pRootNode = pMan->pRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForIter(pRootNode);

		PCSNode* pNode = pForIter.First();

		GameObject* pGameObj = nullptr;

		while (!pForIter.IsDone())
		{
			assert(pNode);

			pGameObj = (GameObject*)pNode;

			if (pGameObj->GetType() == GameObject::Type::BOUNDING_OBJECT)
			{
				// turn rendering on
				pGameObj->SetRender(true);
			}

			pNode = pForIter.Next();
		}
	}

	GameObject* GameObjectMan::Find(const char* const inName)
	{
		GameObjectMan* pMan = GameObjectMan::privGetInstance();
		assert(pMan);

		PCSNode* pRootNode = pMan->pRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForIter(pRootNode);

		PCSNode* pNode = pForIter.First();

		GameObject* pGameObj = nullptr;

		char buff[PCSNode::NAME_SIZE];


		while (!pForIter.IsDone())
		{
			assert(pNode);

			pNode->GetName(buff, PCSNode::NAME_SIZE);

			if (strcmp(buff, inName) == 0)
			{
				// found it
				pGameObj = (GameObject*)pNode;
				break;
			}

			pNode = pForIter.Next();
		}
		assert(pGameObj);

		return pGameObj;
	}

	GameObject* GameObjectMan::FindObjectByIndex(const int index)
	{
		GameObjectMan* pMan = GameObjectMan::privGetInstance();
		assert(pMan);

		PCSNode* pRootNode = pMan->pRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForIter(pRootNode);

		PCSNode* pNode = pForIter.First();

		GameObjectAnim* pGameObj = nullptr;

		while (!pForIter.IsDone())
		{
			assert(pNode);

			pGameObj = (GameObjectAnim*)pNode;

			if (pGameObj->indexBoneArray == index)
			{
				// found it
				break;
			}

			pNode = pForIter.Next();
		}

		return (GameObject*)pGameObj;
	}

	GameObjectMan::~GameObjectMan()
	{
		delete this->pRootTree;
	}



}