#ifndef CLIP_H
#define CLIP_H

#include "Bone.h"
#include "ClipLink.h"
#include "SSBO.h"
#include "AnimTime.h"

namespace Azul
{
	class Clip : public ClipLink
	{
	public:
		struct FrameBucket
		{
			FrameBucket();
			FrameBucket(const FrameBucket&) = default;
			FrameBucket& operator = (const FrameBucket&) = default;
			~FrameBucket();

			FrameBucket* nextBucket;
			FrameBucket* prevBucket;
			AnimTime        KeyTime;
			Bone* poBone;
			
			SSBO* pSSBO_KeyFrame;
		};

		enum class ClipName
		{
			HUMAN_RUN,
			HUMAN_PUNCH,
			HUMAN_SHOT,
			HERO_RUN_JUMP_ANIM, 
			HUMAN_WALK,
			TEDDY_WALK,
			TEDDY_IDLE,
			

			NOT_SET,
		};

		enum class ClipType
		{
			COMPRESSED,
			UNCOMPRESSED
		};

	public:
		Clip(int _numBones, Clip::ClipName _name, Clip::ClipType _type);

		Clip() = delete;
		Clip(const Clip&) = delete;
		Clip& operator = (const Clip&) = delete;
		~Clip();

		AnimTime GetTotalTime();
		void AnimateBones(AnimTime tCurr);

		Clip::ClipName GetClipName() const;

		void SetAnimationData(const char* const pFileName, const char* const pClipName, const char* const pKeyFrameName);

		SSBO* GetResult() const;
		int GetNumBones() const;

		FrameBucket* GetFrameBucketHead() const;
		int GetNumFrames() const;

	

	private:
		void privSetAnimationData(const char* const pFileName, const char* const pClipName, const char* const pKeyFrameName);
		AnimTime privFindMaxTime();
		int  privFindNumFrames();

	private:
		int          numBones;
		int          numFrames;
		AnimTime         TotalTime;
		FrameBucket* poHead;

		SSBO* pSSBO_bone1;
		SSBO* pSSBO_bone2;
		SSBO* pSSBO_MixerOutput;

		Clip::ClipName name;
		Clip::ClipType type;
		
	};
}

#endif
