#ifndef ANIM_TRANSITION_CONTROLLER_LINK_H
#define ANIM_TRANSITION_CONTROLLER_LINK_H

namespace Azul
{
	class AnimTransitionControllerLink
	{
	public:

		AnimTransitionControllerLink()
		{
			this->next = nullptr;
			this->prev = nullptr;
		}

		virtual ~AnimTransitionControllerLink()
		{

		}

		AnimTransitionControllerLink* next;
		AnimTransitionControllerLink* prev;
	};

	
}



#endif