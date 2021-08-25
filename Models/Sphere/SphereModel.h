
#ifndef SPHERE_MODEL_H
#define SPHERE_MODEL_H

#include "Model.h"

namespace Azul
{
	class SphereModel : public Model
	{
	public:
		SphereModel(const char* const pModelFileName);
		~SphereModel();

		// tells the compiler do not create or allow it to be used, c++11
		SphereModel(const SphereModel&) = delete;
		SphereModel& operator=(const SphereModel& other) = delete;

	private:
		virtual void CreateVAO(const char* const pModelFileName) override;
	};
}



#endif
