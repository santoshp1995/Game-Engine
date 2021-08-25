#ifndef ANIM_CONTROLLER_MAN
#define ANIM_CONTROLLER_MAN

#include "AnimController.h"

namespace Azul
{
	class AnimControllerMan
	{
	public:
		static void Add(AnimController* pController);
		static void Create();
		static AnimController* Find(AnimController::ControllerType type);
		static void Destroy();
		static void Update();

	private:
		static AnimControllerMan* privGetInstance();
		AnimControllerMan();

		// store controllers in a a linked list format
		void privAddToFront(AnimController* node, AnimController*& head);
		void privRemove(AnimController* node, AnimController*& head);

	private:
		AnimController* pHead;

	};



}




#endif
