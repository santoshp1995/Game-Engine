#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "Camera.h"

namespace Azul
{
	class Camera2D final : public Camera
	{
	public:
		Camera2D(const Camera::Type type);

		Camera2D() = delete;
		Camera2D(const Camera2D&) = delete;
		Camera2D& operator= (const Camera2D&) = delete;
		~Camera2D();


		void setOrthographic(const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax);
		
		virtual void updateCamera(void) override;

	private:
		void privUpdateProjectionMatrix(void);

	};
}



#endif
