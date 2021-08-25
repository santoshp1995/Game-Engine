#ifndef MODEL_H
#define MODEL_H

#include "sb7.h"
#include "ModelLink.h"
#include "ChunkHeader.h"
#include "BoundingSphere.h"

namespace Azul
{
	class Model : public ModelLink
	{
	public:

		enum class ModelType
		{
			GENERIC,
			SPACE_FRIGATE,
			ASTROBOY,
			BUGGY,
			MILITARY_TRUCK,
			BEAR,
			SPHERE,
			CAMERA,
			SKINNED_TEDDY,
			SKINNED_HUMANOID,
			SKINNED_HUMANOID2,
			SKINNED_HUMANOID3,
			PYRAMID
		};

		Model();
		Model(const Model& copyModel) = delete;
		Model& operator=(const Model& copyModel) = delete;

		bool eat(const char* const inFileName,
			ChunkType type,
			const char* const chunkName,
			unsigned char*& chunkBuff,
			unsigned int& chunkSize);


		bool isFileInDirectory(const char* const pFileName);

		void SetModelType(Model::ModelType _type);
		Model::ModelType GetModelType() const;


		virtual ~Model();

		int numVerts;
		int numTris;

		GLuint vao;
		GLuint vbo_verts;   // xyzuvn
		GLuint vbo_trilist;   // trilist

		// Reference sphere... before any transformations are applied
		Sphere* pRefSphere;

		char* texture;
	protected:
		// load VAO
		virtual void CreateVAO(const char* const pModelFileName) = 0;
		



		Model::ModelType type;
		
	};
}



#endif
