#ifndef SPACE_FRIGATE_MODEL_H
#define SPACE_FRIGATE_MODEL_H

#include "Model.h"

namespace Azul
{
	class SpaceFrigateModel : public Model
	{
	public:
		SpaceFrigateModel(const char* const pFileName, int index = -1);

		SpaceFrigateModel() = delete;
		SpaceFrigateModel(const SpaceFrigateModel&) = delete;
		SpaceFrigateModel& operator= (const SpaceFrigateModel&) = delete;
		~SpaceFrigateModel();

	private:
		virtual void CreateVAO(const char* const pModelFileName) override;
		void GetTextureName(const int index, char*& outTextName);
		


	};
}


#endif