#ifndef BUGGY_MODEL_H
#define BUGGY_MODEL_H

#include "Model.h"

namespace Azul
{
	class BuggyModel : public Model
	{
	public:
		BuggyModel(const char* const pModelFileName, int index = -1);
		
		BuggyModel() = delete;
		BuggyModel(const BuggyModel&) = delete;
		BuggyModel& operator= (const BuggyModel&) = delete;
		~BuggyModel();

	private:
		virtual void CreateVAO(const char* const pModelFileName) override;
		void GetTextureName(const int index, char*& outTextName);

	};
}


#endif
