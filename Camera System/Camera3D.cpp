#include "Camera3D.h"

namespace Azul
{
	Camera3D::Camera3D(const Camera::Type _type)
		: Camera(_type)
	{

	}
	Camera3D::~Camera3D()
	{
	}

	// critical informational knobs for the perspective matrix
	// Field of View Y is in degrees (copying lame OpenGL)
	void Camera3D::setPerspective(const float Fovy, const float Aspect, const float NearDist, const float FarDist)
	{
		this->setAspectRatio(Aspect);
		this->setFieldOfView(Fovy);
		this->setNearDist(NearDist);
		this->setFarDist(FarDist);
	}

	void Camera3D::updateCamera(void)
	{
		// First find the near height/width, far height/width
		this->privCalcPlaneHeightWidth();

		// Find the frustum physical verts
		this->privCalcFrustumVerts();

		// find the frustum collision normals
		this->privCalcFrustumCollisionNormals();

		// update the projection matrix
		this->privUpdateProjectionMatrix();

		// update the view matrix
		this->privUpdateViewMatrix();
	}

	void Camera3D::privUpdateProjectionMatrix(void)
	{
		this->projMatrix[m0] = 2.0f * this->nearDist / this->near_width;
		this->projMatrix[m1] = 0.0f;
		this->projMatrix[m2] = 0.0f;
		this->projMatrix[m3] = 0.0f;

		this->projMatrix[m4] = 0.0f;
		this->projMatrix[m5] = 2.0f * this->nearDist / this->near_height;
		this->projMatrix[m6] = 0.0f;
		this->projMatrix[m7] = 0.0f;

		this->projMatrix[m8] = 0.0f;
		this->projMatrix[m9] = 0.0f;
		this->projMatrix[m10] = (this->farDist + this->nearDist) / (this->nearDist - this->farDist);
		this->projMatrix[m11] = -1.0f;

		this->projMatrix[m12] = 0.0f;
		this->projMatrix[m13] = 0.0f;
		this->projMatrix[m14] = (2.0f * this->farDist * this->nearDist) / (this->nearDist - this->farDist);
		this->projMatrix[m15] = 0.0f;
	}
}