#ifndef ANIM_TRANSITION_H
#define ANIM_TRANSITION_H

#include "TimerController.h"
#include "AnimationGameObject.h"
#include "AnimTransitionControllerLink.h"
#include "Anim.h"

namespace Azul
{
	class AnimTransitionController : public AnimTransitionControllerLink
	{
	public:
		AnimTransitionController(Clip* pClipA, Clip* pClipB, SkinModel* pSkinModel);
		AnimTransitionController(const AnimTransitionController&) = delete;
		AnimTransitionController& operator= (const AnimTransitionController&) = delete;
		~AnimTransitionController();

		void Update();

		void StartTransition();

		void StopTransition();

		void SetNewTransition(Clip::ClipName name, Clip::ClipName name2);

	private:
		void privTransitionTime();

	public:
		SSBO* pSSBO_A;
		SSBO* pSSBO_B;
		SSBO* pSSBO_C;
		SSBO* pSSBO_D;

		SSBO* poSSBO_Result;
		SSBO* poBoneWorld_SSBO;

		SkinModel* pSkinModel;

		Clip* pClip;

		int numBones;
		int tag;
		float tS;

		bool StartEnable;
	};
}





#endif
