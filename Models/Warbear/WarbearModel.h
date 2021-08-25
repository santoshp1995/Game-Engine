#ifndef WARBEAR_MODEL_H
#define WARBEAR_MODEL_H

#include "Model.h"

namespace Azul
{
	class WarbearModel : public Model
	{
	public:
		WarbearModel(const char* const pModelFileName, const int index = -1);

		WarbearModel() = delete;
		WarbearModel(const WarbearModel&) = delete;
		WarbearModel& operator= (const WarbearModel&) = delete;
		~WarbearModel();

	private:
		virtual void CreateVAO(const char* const pModelFileName) override;
		void GetTextureName(const int index, char*& outTextName);
	};
}




#endif
