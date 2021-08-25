#ifndef MILITARY_TRUCK_H
#define MILITARY_TRUCK_H

#include "Model.h"

namespace Azul
{
	class MilitaryTruckModel : public Model
	{
	public:
		MilitaryTruckModel(const char* const pModelFileName, const int index = -1);

		MilitaryTruckModel() = delete;
		MilitaryTruckModel(const MilitaryTruckModel&) = delete;
		MilitaryTruckModel& operator= (const MilitaryTruckModel&) = delete;
		~MilitaryTruckModel();

	private:
		virtual void CreateVAO(const char* const pModelFileName) override;
		void GetTextureName(const int index, char*& outTextName);
	};
}


#endif
