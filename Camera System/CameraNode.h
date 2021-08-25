#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "Camera.h"
#include "CameraLink.h"



namespace Azul
{
	class Camera;

	class CameraNode : public CameraLink
	{
	public:
		CameraNode();
		~CameraNode();
		void set(Camera* pCamera);

	public:
		Camera* pCamera;
	};


}


#endif