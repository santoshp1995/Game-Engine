#ifndef MODEL_MAN_H
#define MODEL_MAN_H

#include "Model.h"

namespace Azul
{
	class ModelMan
	{
	public:
		static void Add(Model* pModel);
		static void Create();
		static Model* Find(Model::ModelType modelType);
		static void Destroy();

	private:
		// methods
		static ModelMan* privGetInstance();
		ModelMan();

		void privAddToFront(Model* node, Model*& head);
		void privRemove(Model* node, Model*& head);

	private:
		// private data
		Model* pActive;
	};
}

#endif