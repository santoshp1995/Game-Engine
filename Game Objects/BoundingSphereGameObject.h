#ifndef BOUNDING_SPHERE_GAME_OBJECT_H
#define BOUNDING_SPHERE_GAME_OBJECT_H

#include "MathEngine.h"
#include "GameObject.h"


namespace Azul
{
	class BoundingSphereGameObject : public GameObject
	{
	public:
		BoundingSphereGameObject() = delete;
		BoundingSphereGameObject(const BoundingSphereGameObject&) = delete;
		BoundingSphereGameObject& operator= (const BoundingSphereGameObject&) = delete;
		virtual ~BoundingSphereGameObject();

		BoundingSphereGameObject(GraphicsObject* pGraphicsObj, Type type);

		void SetBoundingSphereReference(GameObject* pGameObj);

		virtual void Update(AnimTime t) override;

	private:
		void privUpdate(AnimTime t);
		void privUpdateBoundingSphereReference(AnimTime currentTime);

		// data
		GameObject* pRefGameObj;
		
	public:
		Vect* pScale;
		Vect* pTrans;
	};
}



#endif