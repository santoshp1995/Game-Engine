#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "MathEngine.h"

namespace Azul
{
	class Sphere : public Align16
	{
	public:
		Sphere();
		Sphere(const Sphere&) = default;
		Sphere& operator = (const Sphere&) = default;
		~Sphere() = default;

		void RitterSphere(Vect* pt, int numPts);

		// Data: ---------------------------------
		Vect cntr;
		float rad;
		float pad[3];

	private:

		void privMostSeparatedPointsOnAABB(int& min, int& max, Vect* pt, int numPts);
		void privSphereFromDistantPoints(Vect* pt, int numPts);
		void privSphereOfSphereAndPt(Vect& p);

	};
}

#endif
