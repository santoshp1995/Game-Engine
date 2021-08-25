#ifndef CAMERA_LINK_H
#define CAMERA_LINK_H

namespace Azul
{
	class CameraLink
	{
	public:
		CameraLink()
		{
			this->next = nullptr;
			this->prev = nullptr;
		}

		virtual ~CameraLink() = default;

		CameraLink* next;
		CameraLink* prev;
	};
}


#endif