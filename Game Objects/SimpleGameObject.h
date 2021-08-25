#ifndef SIMPLE_GAME_OBJECT_H
#define SIMPLE_GAME_OBJECT_H

#include "GameObject.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"

namespace Azul
{
	class SimpleGameObject : public GameObject
	{
	public:
		enum MoveDir
		{
			MOVE_X,
			MOVE_Y,
			MOVE_Z,
			MOVE_NONE
		};

	public:
		SimpleGameObject(GraphicsObject* pGraphicsObj, Type type);

		// big four
		SimpleGameObject() = delete;
		SimpleGameObject(const SimpleGameObject&) = delete;
		SimpleGameObject& operator= (const SimpleGameObject&) = delete;
		virtual ~SimpleGameObject();

		virtual void Update(AnimTime t);

		void SetScale(float sx, float sy, float sz);
		void SetPos(float x, float y, float z);
		void SetMove(SimpleGameObject::MoveDir dir);


	private:
		void privUpdate(AnimTime t);
	
	public:   // add accessors later
		Vect* poScale;
		Vect* poTrans;

		float deltaRotY;
		float deltaRotZ;
		float rotY;
		float rotZ;

		SimpleGameObject::MoveDir dir;
	};
}



#endif
