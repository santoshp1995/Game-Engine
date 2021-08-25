#ifndef ANIMATION_GPU_H
#define ANIMATION_GPU_H

#include "SSBO.h"
#include "Bone.h"


namespace Azul
{
	class AnimationGPU
	{
	public:
		static void Blend_GPU(SSBO* pKey_A, SSBO* PKey_B, SSBO* pResult_GPU, const float tS, const int numBones);
		static void Local_To_World_GPU(SSBO* mixerOutput, int numBones);


	};



}








#endif
