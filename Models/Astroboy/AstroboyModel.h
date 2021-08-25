#ifndef ASTROBOY_MODEL_H
#define ASTROBOY_MODEL_H

#include "Model.h"


namespace Azul
{
	class AstroboyModel : public Model
	{
	public:
		AstroboyModel(const char* const pModelFileName, int index = -1);
		
		AstroboyModel() = delete;
		AstroboyModel(const AstroboyModel&) = delete;
		AstroboyModel& operator= (const AstroboyModel&) = delete;
		~AstroboyModel();

	private:
		virtual void CreateVAO(const char* const pModelFileName) override;
		void GetTextureName(const int index, char*& outTextName);
	};


}

#endif