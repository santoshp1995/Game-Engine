#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "AnimControllerLink.h"
#include "TimerController.h"
#include "AnimationGameObject.h"
#include "Anim.h"
#include "SkinModel.h"


namespace Azul
{
	class AnimController : public AnimControllerLink
	{
	public:
		enum class ControllerType
		{
			HUMANOID_A,
			HUMANOID_B,
			HUMANOID_C,
			HUMANOID_D,
			TEDDY
		};

	public:
		AnimController(AnimTime delta, int boneCount, float boneWidth, const char* const pFileName,
			AnimController::ControllerType type, SkinModel* pSkinModel);
		AnimController(const AnimController&) = delete;
		AnimController& operator = (const AnimController&) = delete;
		~AnimController();

		void Update();

		AnimController::ControllerType GetType() const;
		

		// Controller Functions
		void CycleAnimation();
		void Pause();

		Anim* GetAnim() const;

	private:
		void privSetClipName(Clip::ClipName& name, AnimController::ControllerType _type);

	private:
		TimerController* poTimerControl;
		Anim* poAnim;
		

		AnimController::ControllerType controllerType;
	};
}

#endif