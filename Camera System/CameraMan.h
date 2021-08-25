#ifndef CAMERA_MAN_H
#define CAMERA_MAN_H

#include "Camera.h"
#include "CameraNode.h"

namespace Azul
{
	// Singleton
	class CameraMan
	{
	public:
		static void Add(Camera::Name name, Camera* pCamera);
		static Camera* Find(Camera::Name name);

		static void SetCurrent(Camera::Name name, Camera::Type type);
		static Camera* GetCurrent(Camera::Type type);

		static void Create();
		static void Destroy();

	private:  // methods

		static CameraMan* privGetInstance();
		CameraMan();
		void privAddToFront(CameraLink* node, CameraLink*& head);
		void privRemove(CameraLink* pNode, CameraLink*& poHead);

	private:  // add

		CameraLink* poActive;

		// Data 
		// w1(3)
		Camera* pCamOrthographic;
		Camera* pCamPerspective;

	};

}

#endif