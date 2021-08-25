#include "Model.h"
#include "File.h"
#include "PackageHeader.h"
#include "Texture.h"


namespace Azul
{
	Model::Model()
		: numVerts(0),
		numTris(0),
		vao(0),
		vbo_verts(0),
		vbo_trilist(0),
		pRefSphere(new Sphere())
	{
	}


	bool Model::eat(const char* const inFileName, ChunkType _type, const char* const chunkName,
		unsigned char*& chunkBuff, unsigned int& chunkSize)
	{
		bool status = false;
		bool isFound = false;

		File::Handle fh;
		File::Error ferror;

		// unpack the package (Read Package HDR)
		PackageHeader packageHDR;

		ferror = File::Open(fh, inFileName, File::Mode::READ);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Read(fh, &packageHDR, sizeof(PackageHeader));
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Seek(fh, File::Location::BEGIN, sizeof(PackageHeader));
		assert(ferror == File::Error::SUCCESS);

		ChunkHeader chunkHDR;

		ferror = File::Read(fh, &chunkHDR, sizeof(ChunkHeader));
		assert(ferror == File::Error::SUCCESS);

		unsigned int index = 0;

		if (chunkHDR.type == _type && strcmp(chunkHDR.chunkName, chunkName) == 0)
		{
			isFound = true;
			status = true;
		}

		else
		{
			while (!isFound)
			{
				if (index >= packageHDR.numChunks) break;

				int offset = (int)(chunkHDR.chunkSize);

				ferror = File::Seek(fh, File::Location::CURRENT, offset);
				assert(ferror == File::Error::SUCCESS);

				File::Read(fh, &chunkHDR, sizeof(ChunkHeader));
				assert(ferror == File::Error::SUCCESS);

				index++;

				if (chunkHDR.type == _type && strcmp(chunkHDR.chunkName, chunkName) == 0)
				{
					isFound = true;
					status = true;
				}
			}
		}

		if (isFound)
		{
			chunkSize = chunkHDR.chunkSize;

			chunkBuff = new unsigned char[chunkSize];

			for (unsigned int i = 0; i < chunkSize; i++)
			{
				ferror = File::Read(fh, &chunkBuff[i], sizeof(char));
				assert(ferror == File::Error::SUCCESS);
			}

			ferror = File::Close(fh);
		}

		return status;
	}

	// use for tga file reading.
	bool Model::isFileInDirectory(const char* const pFileName)
	{
		bool status = false;

		WIN32_FIND_DATAA data;

		File::Handle fh;

		fh = FindFirstFileA(pFileName, &data);

		if (fh != INVALID_HANDLE_VALUE)
		{
			status = true;
		}

		return status;
	}

	void Model::SetModelType(Model::ModelType _type)
	{
		this->type = _type;
	}

	Model::ModelType Model::GetModelType() const
	{
		return this->type;
	}

	Model::~Model()
	{
		delete this->pRefSphere;
	}

}



