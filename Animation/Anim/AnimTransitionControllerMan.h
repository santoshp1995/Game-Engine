#ifndef ANIM_TRANSITION_CONTROLLER_MAN_H
#define ANIM_TRANSITION_CONTROLLER_MAN_H

#include "AnimTransitionController.h"

namespace Azul
{
	class AnimTransitionControllerMan
	{
	public:
		static void Add(AnimTransitionController* pTransition);
		static void Create();
		static void Destroy();
		static void Update();
		static void StartTransition();

	private:
		static AnimTransitionControllerMan* privGetInstance();
		AnimTransitionControllerMan();

		void privAddToFront(AnimTransitionController* node, AnimTransitionController*& pHead);
		void privRemove(AnimTransitionController* node, AnimTransitionController*& pHead);

	private:
		AnimTransitionController* pHead;
	};
}



#endif
