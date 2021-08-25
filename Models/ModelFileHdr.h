#ifndef MODEL_FILE_HDR_H
#define MODEL_FILE_HDR_H

namespace Azul
{
	struct ModelFileHdr
	{
	public:
		static const unsigned int OBJECT_NAME_SIZE = 32;
		static const unsigned int TEXTURE_NAME_SIZE = 32;

	public:
		ModelFileHdr();
		ModelFileHdr(const ModelFileHdr&) = delete;
		ModelFileHdr& operator= (const ModelFileHdr&) = delete;
		~ModelFileHdr() = default;

	public:
		// Data -----------------

		// object name
		char	objName[OBJECT_NAME_SIZE];

		// vertex buffer
		int		numVerts;
		DWORD	vertBufferOffset;

		// trilist index 
		int		numTriList;
		DWORD	triListBufferOffset;


	};
}


#endif