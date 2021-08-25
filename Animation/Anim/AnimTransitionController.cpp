#include "AnimTransitionController.h"
#include "AnimationGPU.h"
#include "ClipMan.h"

namespace Azul
{
	AnimTransitionController::AnimTransitionController(Clip* pClipA, Clip* pClipB, SkinModel* _pSkinModel)
		:pSSBO_A(nullptr),
		pSSBO_B(nullptr),
		pSSBO_C(nullptr),
		pSSBO_D(nullptr),
		poSSBO_Result(nullptr),
		poBoneWorld_SSBO(nullptr),
		numBones(-1),
		tS(0.0f),
		StartEnable(false)
	{
		assert(pClipA);
		assert(pClipB);
		assert(_pSkinModel);

		this->pSkinModel = _pSkinModel;

		

		this->pSSBO_A = pClipA->GetResult();
		this->pSSBO_B = pClipB->GetResult();

		this->pClip = pClipA;

		assert(this->pSSBO_A);
		assert(this->pSSBO_A);

		assert(pClipA->GetNumBones() == pClipB->GetNumBones());

		this->numBones = pClipA->GetNumBones();

		this->poSSBO_Result = new SSBO();
		Bone* pBone = new Bone[(unsigned int)numBones]();
		this->poSSBO_Result->Set((unsigned int)numBones, sizeof(Bone), pBone);
		delete[] pBone;

		this->poBoneWorld_SSBO = new SSBO();
		Matrix* pResultMatrix = new Matrix[(unsigned int)numBones]();
		this->poBoneWorld_SSBO->Set((unsigned int)numBones, sizeof(Matrix), pResultMatrix);
		delete[] pResultMatrix;
	}

	AnimTransitionController::~AnimTransitionController()
	{
		delete this->poSSBO_Result;
		delete this->poBoneWorld_SSBO;
	}

	void AnimTransitionController::Update()
	{
		this->privTransitionTime();

		AnimationGPU::Blend_GPU(this->pSSBO_A, this->pSSBO_B, this->poSSBO_Result, this->tS, this->numBones);
		AnimationGPU::Local_To_World_GPU(this->poSSBO_Result, this->numBones);
	}

	void AnimTransitionController::StartTransition()
	{
		this->StartEnable = true;
	}

	void AnimTransitionController::StopTransition()
	{
		this->StartEnable = false;
	}

	void AnimTransitionController::SetNewTransition(Clip::ClipName name, Clip::ClipName name2)
	{
		Clip* pClipC = ClipMan::Find(name);
		Clip* pClipD = ClipMan::Find(name2);

		this->pSSBO_C = pClipC->GetResult();
		this->pSSBO_D = pClipD->GetResult();

		this->pSSBO_A = this->pSSBO_C;
		this->pSSBO_B = this->pSSBO_D;
	}

	void AnimTransitionController::privTransitionTime()
	{
		if (this->StartEnable)
		{
			float t_delta = 0.03f;
			float b = 1.0f;
			float a = 0.0f;
			static float t = 0.0f;
			t += t_delta;
			if (t > 1.0f)
			{
				t = 1.0f;
			}

			this->tS = a + t * (b - a);
		}
	}





}