#include "Camera.h"
#include "CameraNode.h"
#include "CameraMan.h"

namespace Azul
{
	CameraMan::CameraMan()
	{
		this->poActive = nullptr;

		// w1(3)
		this->pCamPerspective = nullptr;
		this->pCamOrthographic = nullptr;
	}

	CameraMan* CameraMan::privGetInstance()
	{
		// This is where its actually stored (BSS section)
		static CameraMan cameraMan;
		return &cameraMan;
	}

	void CameraMan::Create()
	{
		// Get the instance to the manager
		CameraMan* pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);
		AZUL_UNUSED_VAR(pCameraMan);
	}

	void CameraMan::Destroy()
	{
		// Get the instance to the manager
		CameraMan* pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);

		CameraLink* pTmp = pCameraMan->poActive;
		while (pTmp != nullptr)
		{
			CameraLink* pDeleteMe = pTmp;
			pTmp = pTmp->next;
			delete pDeleteMe;
		}

	}

	void CameraMan::Add(Camera::Name name, Camera* pCamera)
	{
		// Get the instance to the manager
		CameraMan* pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);

		// Create a TextureNode
		CameraNode* pNode = new CameraNode();
		assert(pNode);

		// initialize it
		assert(pCamera);
		pCamera->setName(name);
		pNode->set(pCamera);

		// Now add it to the manager
		pCameraMan->privAddToFront(pNode, pCameraMan->poActive);
	}

	// w1(3)
	Camera* CameraMan::Find(Camera::Name _name)
	{
		// Get the instance to the manager
		CameraMan* pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);

		CameraNode* pNode = (CameraNode*)pCameraMan->poActive;
		while (pNode != nullptr)
		{
			if (pNode->pCamera->getName() == _name)
			{
				// found it
				break;
			}

			pNode = (CameraNode*)pNode->next;
		}
		assert(pNode);
		return pNode->pCamera;
	}

	// w1(3)
	void CameraMan::SetCurrent(const Camera::Name name, Camera::Type type)
	{
		CameraMan* pCamMan = CameraMan::privGetInstance();
		assert(pCamMan);

		Camera* pCam = CameraMan::Find(name);
		assert(pCam);

		switch (type)
		{
		case Camera::Type::PERSPECTIVE_3D:
			assert(pCam->getType() == Camera::Type::PERSPECTIVE_3D);
			pCamMan->pCamPerspective = pCam;
			break;

		case Camera::Type::ORTHOGRAPHIC_2D:
			assert(pCam->getType() == Camera::Type::ORTHOGRAPHIC_2D);
			pCamMan->pCamOrthographic = pCam;
			break;

		default:
			assert(false);
			break;
		}

	}

	Camera* CameraMan::GetCurrent(Camera::Type type)
	{
		Camera* pCam = 0;
		switch (type)
		{
		case Camera::Type::PERSPECTIVE_3D:
			pCam = CameraMan::privGetInstance()->pCamPerspective;
			break;

		case Camera::Type::ORTHOGRAPHIC_2D:
			pCam = CameraMan::privGetInstance()->pCamOrthographic;
			break;

		default:
			assert(false);
			break;
		}

		assert(pCam != 0);
		return pCam;
	}

	void CameraMan::privAddToFront(CameraLink* node, CameraLink*& head)
	{
		assert(node != nullptr);

		if (head == nullptr)
		{
			head = node;
			node->next = nullptr;
			node->prev = nullptr;
		}
		else
		{
			node->next = head;
			head->prev = node;
			head = node;
		}
	}

	void CameraMan::privRemove(CameraLink* pNode, CameraLink*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (CameraLink*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}

}

// --- End of File ---