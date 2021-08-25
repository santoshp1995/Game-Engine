//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "Anim.h"

namespace Azul
{
	AnimController::AnimController(AnimTime delta, int boneCount, float boneWidth, const char* const pFileName,
		AnimController::ControllerType _type, SkinModel* pSkinModel)
	{

		Clip::ClipName name = Clip::ClipName::NOT_SET;

		this->privSetClipName(name, _type);

		assert(name != Clip::ClipName::NOT_SET);

		// Animation objects
		this->poAnim = new Anim(boneCount, boneWidth, pFileName, pSkinModel, name);
		assert(this->poAnim);


		// TimerControllers
		AnimTime maxTime1 = poAnim->FindMaxTime();
		AnimTime minTime1 = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl = new TimerController(delta, minTime1, maxTime1);
		assert(this->poTimerControl);

		this->controllerType = _type;
	}

	AnimController::~AnimController()
	{
		delete poAnim;
		delete poTimerControl;
	}

	void AnimController::CycleAnimation()
	{
		this->poAnim->CycleAnimation();

		AnimTime tCurr = AnimTime(AnimTime::Duration::ZERO);

		this->poTimerControl->SetCurrTime(tCurr);
	}

	void AnimController::Pause()
	{
		this->poTimerControl->SetPause(true);
	}

	Anim* AnimController::GetAnim() const
	{
		return this->poAnim;
	}

	void AnimController::privSetClipName(Clip::ClipName& name, AnimController::ControllerType _type)
	{
		switch (_type)
		{
		case AnimController::ControllerType::HUMANOID_A:
			name = Clip::ClipName::HUMAN_WALK;
			break;

		case AnimController::ControllerType::HUMANOID_B:
			name = Clip::ClipName::HUMAN_RUN;
			break;

		case AnimController::ControllerType::HUMANOID_C:
			name = Clip::ClipName::HUMAN_PUNCH;
			break;

		case AnimController::ControllerType::HUMANOID_D:
			name = Clip::ClipName::HUMAN_SHOT;
			break;

		case AnimController::ControllerType::TEDDY:
			name = Clip::ClipName::TEDDY_WALK;
			break;
		}
	}

	void AnimController::Update()
	{
		this->poTimerControl->Update();

		// interpolate all bones
		this->poAnim->Animate(this->poTimerControl->GetCurrTime());
	}

	AnimController::ControllerType AnimController::GetType() const
	{
		return this->controllerType;
	}
}