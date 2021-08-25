#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "Camera.h"

namespace Azul
{
	class Camera3D final : public Camera
	{
	public:
		Camera3D(Camera::Type type);


		Camera3D() = delete;
		Camera3D(const Camera3D&) = delete;
		Camera3D& operator= (const Camera3D&) = delete;
		~Camera3D();

		void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);

		virtual void updateCamera(void) override;

	private:
		void privUpdateProjectionMatrix(void);

	};
}



#endif
