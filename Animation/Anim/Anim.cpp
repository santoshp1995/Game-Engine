#include "Anim.h"
#include "Constants.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "Mixer.h"
#include "PCSTreeForwardIterator.h"
#include "GameObjectMan.h"
#include "Clip.h"
#include "ClipMan.h"

namespace Azul
{
	Anim::Anim(int boneCount, float _boneWidth, const char* const pFileName, SkinModel* pSkinModel, Clip::ClipName name)
	{
		this->pClip = nullptr;

		this->numBones = boneCount;
		this->boneWidth = _boneWidth;

		this->poSkeleton = new Skeleton(numBones, pFileName, pSkinModel);

		this->pClip = ClipMan::Find(name);

		assert(pClip);
	}

	Anim::~Anim()
	{
		delete poSkeleton;
	}

	AnimTime Anim::FindMaxTime()
	{
		assert(pClip);
		return this->pClip->GetTotalTime();
	}

	void Anim::CycleAnimation()
	{
		assert(pClip);

		if (this->pClip->GetClipName() == Clip::ClipName::HUMAN_RUN)
		{
			this->pClip = ClipMan::Find(Clip::ClipName::HUMAN_WALK);
		}

		else
		{
			this->pClip = ClipMan::Find(Clip::ClipName::HUMAN_RUN);
		}
	}

	Skeleton* Anim::GetSkeleton() const
	{
		return this->poSkeleton;
	}

	Clip* Anim::GetClip() const
	{
		assert(this->pClip);
		return this->pClip;
	}

	void Anim::SetNext(Anim* pAnim)
	{
		this->pNext = pAnim;
	}

	Anim* Anim::GetNext() const
	{
		return this->pNext;
	}

	void Anim::Animate(AnimTime tCurr)
	{
		this->pClip->AnimateBones(tCurr);
	}

	
}
