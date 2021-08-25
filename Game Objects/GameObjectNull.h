#ifndef GAME_OBJECT_NULL_H
#define GAME_OBJECT_NULL_H

#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject_Null.h"

namespace Azul
{
	class GameObjectNull : public GameObject
	{
	public:
		GameObjectNull(GraphicsObject_Null* pGraphicsObj);

		// big four
		GameObjectNull() = delete;
		GameObjectNull(const GameObjectNull&) = delete;
		GameObjectNull& operator= (const GameObjectNull&) = delete;
		virtual ~GameObjectNull() override;

		virtual void Update(AnimTime currentTime) override;


	};
}



#endif
