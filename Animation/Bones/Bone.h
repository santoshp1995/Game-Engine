#ifndef BONE_H
#define BONE_H

#include "MathEngine.h"

namespace Azul
{
	struct Bone : public Align16
	{
		Bone();
		Vect  T;
		Quat  Q;
		Vect  S;
	};
}

#endif




