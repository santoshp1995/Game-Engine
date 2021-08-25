#include "CameraNode.h"

Azul::CameraNode::CameraNode()
{
	this->pCamera = nullptr;
}

Azul::CameraNode::~CameraNode()
{
	delete this->pCamera;
}

void Azul::CameraNode::set(Camera* _pCamera)
{
	this->pCamera = _pCamera;
}




