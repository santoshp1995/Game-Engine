//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIMATION_GAME_OBJECT_H
#define ANIMATION_GAME_OBJECT_H

#include "GameObject.h"
#include "MathEngine.h"
#include "GraphicsObject.h"
#include "Bone.h"
#include "SkinModel.h"


namespace Azul
{
	class GameObjectAnim : public GameObject
	{
	public:
		GameObjectAnim(GraphicsObject* graphicsObject, Bone* pBoneResult, Type _type, SkinModel* pModel);

		// Big four
		GameObjectAnim() = delete;
		GameObjectAnim(const GameObjectAnim&) = delete;
		GameObjectAnim& operator=(GameObjectAnim&) = delete;
		virtual ~GameObjectAnim() override;

		virtual void Update(AnimTime currentTime);

		// Accessors
		Matrix GetBoneOrientation(void) const;
		void SetBoneOrientation(const Matrix&);
		void SetIndex(int val);

	private:
		void privUpdate(AnimTime currentTime);

	public:
		Vect* poScale;
		Vect* poPos;
		Vect* poDof;
		Vect* poUp;

		Matrix* poLocal;
		Matrix* poBoneOrientation;
		
		Bone* pBoneResult;
		
		SkinModel* pSkinModel;
		
		int    indexBoneArray;
	};

}

#endif

// --- End of File ---
