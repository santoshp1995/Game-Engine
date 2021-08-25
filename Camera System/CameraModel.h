#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "Model.h"

namespace Azul
{
	class CameraModel : public Model
	{
	public:
		CameraModel(const char* const pModelFileName);
		~CameraModel();

		void update();

		CameraModel(const CameraModel&) = delete;
		CameraModel& operator= (const CameraModel&) = delete;

	private:
		virtual void CreateVAO(const char* const pModelFileName) override;
	};



}



#endif

