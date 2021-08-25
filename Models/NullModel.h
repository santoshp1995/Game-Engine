#ifndef NULL_MODEL_H
#define NULL_MODEL_H

#include "Model.h"

namespace Azul
{
	class NullModel : public Model
	{
	public:
		NullModel(const char* const pModelFileName);
		~NullModel();

		// tells the model do not create or allow for use, c++ 11
		NullModel(const NullModel&) = delete;
		NullModel& operator=(const NullModel& other) = delete;

	private:
		virtual void CreateVAO(const char* const modelFileName) override;
	};

}





#endif
