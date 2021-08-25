#include "AnimationGPU.h"
#include "ShaderMan.h"
#include "AnimControllerMan.h"
#include "SkinModel.h"
#include "ModelMan.h"

namespace Azul
{
	void AnimationGPU::Blend_GPU(SSBO* pKey_A, SSBO* pKey_B, SSBO* pResult_GPU, const float tS, const int numBones)
	{
		assert(pKey_A != nullptr);
		assert(pKey_B != nullptr);
		assert(pResult_GPU != nullptr);

		ShaderObject* pMixerShader = ShaderMan::Find(ShaderObject::Name::COMPUTE_MIXER);

		pMixerShader->SetActive();

		pKey_A->Bind(0);
		pKey_B->Bind(1);
		pResult_GPU->Bind(2);

		glUniform1f(pMixerShader->GetLocation("ts"), tS);
		glUniform1i(pMixerShader->GetLocation("boneCount"), numBones);

		unsigned int count = (unsigned int)numBones / 20;

		// Dispatch
		pMixerShader->Dispatch(count, 1, 1);

		// Block Waiting for stages to complete
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}

	void AnimationGPU::Local_To_World_GPU(SSBO* mixerOutput, int numBones)
	{
		ShaderObject* pComputeWorld = ShaderMan::Find(ShaderObject::Name::COMPUTE_WORLD);

		pComputeWorld->SetActive();

		SSBO* pBoneLocal = mixerOutput;
		pBoneLocal->Bind(0);

		AnimController* pController = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID_A);

		pController->GetAnim()->GetSkeleton()->pSSBO_hierarchy->Bind(1);
		pController->GetAnim()->GetSkeleton()->GetSkinModel()->pSSBO_boneWorld->Bind(2);
		pController->GetAnim()->GetSkeleton()->GetSkinModel()->pSSBO_rigidWorld->Bind(3);

		glUniform1i(pComputeWorld->GetLocation("tableDepth"), numBones);
		glUniform1i(pComputeWorld->GetLocation("boneCount"), numBones);

		unsigned int count = (unsigned int)(numBones / 20);

		// dispatch
		pComputeWorld->Dispatch(count, 1, 1);

		// wait for stages to complete
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}
}
