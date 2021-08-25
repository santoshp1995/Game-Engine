#ifndef SPRITE_MODEL_H
#define SPRITE_MODEL_H

#include "Model.h"

namespace Azul
{
	class SpriteModel : public Model
	{
	public:
		SpriteModel(const char* const pModelFileName);
		~SpriteModel();

		SpriteModel(const SpriteModel&) = delete;
		SpriteModel& operator= (const SpriteModel&) = delete;

	private:
		void CreateVAO(const char* const pModelFileName) override;
	};
}



#endif
