#ifndef GAME_OBJECT_RIGID_H
#define GAME_OBJECT_RIGID_H

#include "GameObject.h"
#include "MathEngine.h"
#include "GraphicsObject.h"
#include "SkinModel.h"

namespace Azul
{
	// Keenan(33)
	class GameObjectRigid : public GameObject
	{
	public:
		GameObjectRigid(GraphicsObject* graphicsObject, SkinModel* _pSkinModel);

		// Big four
		GameObjectRigid() = delete;
		GameObjectRigid(const GameObjectRigid&) = delete;
		GameObjectRigid& operator=(GameObjectRigid&) = delete;
		virtual ~GameObjectRigid() override;



		virtual void Update(AnimTime currentTime);

		void SetPos(const float x, const float y, const float z);
		void SetScale(const float x, const float y, const float z);

	private:
		void privUpdate(AnimTime currentTime);

	public:
		Vect* pScale;
		Vect* pPos;
		SkinModel* pSkinModel;
		float angle;

		float deltaRotY;
		float deltaRotZ;
		float rotY;
		float rotZ;

		int flag;
	};
}

#endif