#include <string.h>
#include "ModelFileHdr.h"

namespace Azul
{
	ModelFileHdr::ModelFileHdr()
	{
		memset(this, 0x0, sizeof(ModelFileHdr));
	}

}