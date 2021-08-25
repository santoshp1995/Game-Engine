#include "Clip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "AnimationGPU.h"
#include "ExtractData.h"
#include "Keyframe.h"
#include "AnimationGPU.h"
#include "AnimTime.h"


namespace Azul
{
	Clip::FrameBucket::FrameBucket()
		:nextBucket(nullptr),
		prevBucket(nullptr),
		KeyTime(),
		poBone(nullptr),
		pSSBO_KeyFrame(nullptr)
	{
	}

	Clip::FrameBucket::~FrameBucket()
	{
		delete[] poBone;
		delete pSSBO_KeyFrame;
	}


	Clip::Clip(int _numBones, Clip::ClipName _name, Clip::ClipType _type)
		: numBones(_numBones),
		numFrames(0),
		TotalTime(AnimTime::Duration::ZERO),
		poHead(nullptr),
		pSSBO_bone1(nullptr),
		pSSBO_bone2(nullptr),
		pSSBO_MixerOutput(nullptr),
		name(_name),
		type(_type)
	{
		this->pSSBO_MixerOutput = new SSBO();

		Bone* poBone = new Bone[(unsigned int)numBones];
		assert(poBone);

		this->pSSBO_MixerOutput->Set((unsigned int)numBones, sizeof(Bone), poBone);

		delete[] poBone;
	}

	Clip::~Clip()
	{
		FrameBucket* pTmp = poHead;

		while (pTmp != nullptr)
		{
			FrameBucket* pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}

		delete this->pSSBO_MixerOutput;
	}

	void Clip::AnimateBones(AnimTime tCurr)
	{
		// First one 
		FrameBucket* pTmp = this->poHead;

		// Find which key frames
		while (tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket* pA = pTmp->prevBucket;
		FrameBucket* pB = pTmp;

		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		AnimationGPU::Blend_GPU(pA->pSSBO_KeyFrame, pB->pSSBO_KeyFrame, this->pSSBO_MixerOutput, tS, this->numBones);

		
		AnimationGPU::Local_To_World_GPU(this->pSSBO_MixerOutput, numBones);
	}

	Clip::ClipName Clip::GetClipName() const
	{
		return this->name;
	}

	void Clip::SetAnimationData(const char* const pFileName, const char* const pClipName, const char* const pKeyFrameName)
	{
		this->privSetAnimationData(pFileName, pClipName, pKeyFrameName);
		this->TotalTime = this->privFindMaxTime();
		this->numFrames = this->privFindNumFrames();
	}

	SSBO* Clip::GetResult() const
	{
		return this->pSSBO_MixerOutput;
	}

	int Clip::GetNumBones() const
	{
		return this->numBones;
	}

	Clip::FrameBucket* Clip::GetFrameBucketHead() const
	{
		assert(this->poHead);
		return this->poHead;
	}

	int Clip::GetNumFrames() const
	{
		return this->numFrames;
	}

	int Clip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket* pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime Clip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket* pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime Clip::GetTotalTime()
	{
		return this->TotalTime;
	}

	void Clip::privSetAnimationData(const char* const pFileName, const char* const pClipName, const char* const pKeyFrameName)
	{
		bool status;
		unsigned char* buff;
		unsigned int chunkSize;

		// extract the key frame data
		status = ExtractData::eat(pFileName, ChunkType::ANIM_TYPE, pKeyFrameName, buff, chunkSize);
		assert(status);

		Keyframe* pKeyFrame = (Keyframe*)buff;

		int numKeyFrames = pKeyFrame->numKeyFrames;

		delete buff;

		status = ExtractData::eat(pFileName, ChunkType::ANIM_TYPE, pClipName, buff, chunkSize);
		assert(status);

		BoneData* pBoneData = (BoneData*)buff;
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = new FrameBucket();
		pTmp->prevBucket = nullptr;
		pTmp->nextBucket = nullptr;
		pTmp->KeyTime = 0 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
		pTmp->poBone = new Bone[(unsigned int)this->numBones];
		poHead = pTmp;

		pTmp->pSSBO_KeyFrame = new SSBO();
		assert(pTmp->pSSBO_KeyFrame);

		int k = 0;

		for (int i = 0; i < numKeyFrames; i++)
		{
			if (i > 0)
			{
				FrameBucket* pTmp2 = new FrameBucket();
				pTmp2->prevBucket = pTmp;
				pTmp2->nextBucket = nullptr;
				pTmp2->KeyTime = i * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
				pTmp2->poBone = new Bone[(unsigned int)this->numBones];
				pTmp->nextBucket = pTmp2;

				pTmp = pTmp2;

				pTmp->pSSBO_KeyFrame = new SSBO();
				assert(pTmp->pSSBO_KeyFrame);
			}

			for (int j = 0; j < this->numBones; j++)
			{
				pTmp->poBone[j].T = Vect(pBoneData[k].tx, pBoneData[k].ty, pBoneData[k].tz);
				pTmp->poBone[j].Q = Quat(Quat::Rot3::XYZ, pBoneData[k].rx, pBoneData[k].ry, pBoneData[k].rz);
				pTmp->poBone[j].S = Vect(pBoneData[k].sx, pBoneData[k].sy, pBoneData[k].sz);

				k++;
			}

			pTmp->pSSBO_KeyFrame->Set((unsigned int)numBones, sizeof(Bone), &pTmp->poBone[0]);
		}
		delete buff;

	}
}

// --- End of File ---