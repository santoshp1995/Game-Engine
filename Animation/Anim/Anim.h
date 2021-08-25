#ifndef ANIM_H
#define ANIM_H

#include "AnimTimer.h"
#include "AnimationGameObject.h"
#include "Clip.h"
#include "Skeleton.h"
#include "SkinModel.h"
#include "SSBO.h"

namespace Azul
{
	class Anim
	{
	public:
		Anim(int boneCount, float boneWidth, const char* const pFileName, SkinModel* pSkinModel, Clip::ClipName name);

		Anim() = delete;
		Anim(const Anim&) = delete;
		Anim& operator = (const Anim&) = delete;
		~Anim();

		void Animate(AnimTime tCurr);
		
		AnimTime FindMaxTime();

		// change clips
		void CycleAnimation();

		Skeleton* GetSkeleton() const;

		Clip* GetClip() const;


		void SetNext(Anim* pAnim);
		Anim* GetNext() const;
		
	private:
		Clip* pClip;
		Skeleton* poSkeleton;
	
		Anim* pNext;
		Anim* pPrev;

		int   numBones;
		float boneWidth;
	};


}

#endif

