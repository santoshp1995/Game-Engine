//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"


namespace Azul
{
	class GameObject : public PCSNode
	{
	public:
		enum class Type
		{
			GAME_OBJECT,
			BONE,
			BOUNDING_OBJECT,
			CAMERA_OBJECT,
			ANIM_TYPE,
			SKELETON,
			GAME_OBJECT_2D,
			FONT,
			NULL_TYPE
		};

	public:
		GameObject(GraphicsObject* graphicsObject, Type type);

		// Big four
		GameObject() = delete;
		GameObject(const GameObject&) = delete;
		GameObject& operator=(GameObject&) = delete;
		virtual ~GameObject();

		virtual void Draw();
		virtual void Update(AnimTime t) = 0;

		GraphicsObject* GetGraphicsObject();
		Matrix* GetWorld();

		void SetWorld(Matrix* _pWorld);

		GameObject::Type GetType() const;
		void SetRender(bool b);

	protected:
		Matrix* poWorld;
		void baseUpdateBoundingSphere();

	protected:
		Sphere* pSphere;
		GraphicsObject* poGraphicsObject;
		Type objectType;
		bool isRendering;
	};
}



#endif


// --- End of File ---
