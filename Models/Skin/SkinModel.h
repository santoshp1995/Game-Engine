#ifndef SKIN_MODEL_H
#define SKIN_MODEL_H

#include "Model.h"
#include "SSBO.h"

namespace Azul
{
	class SkinModel : public Model
	{
	public:
		SkinModel(const char* const pModelFileName);
		virtual ~SkinModel();

		SkinModel() = delete;
		SkinModel(const SkinModel&) = delete;
		SkinModel& operator= (const SkinModel&) = delete;

	private:
		virtual void CreateVAO(const char* const pModelFileName);

	public:
		// data
		GLuint vbo_boneweight;   // Bone_weight
		GLuint vbo_boneindex;   // Bone_index

		unsigned int NumBones;
		SSBO* pSSBO_inversePose;
		SSBO* pSSBO_boneWorld;
		SSBO* pSSBO_rigidWorld;
		Matrix* poRigidWorld;
	};
}






#endif
