#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"
#include "AnimTime.h"


namespace Azul
{
	class GameObjectMan
	{
	public:
		static void Add(GameObject* pObj);
		static void Add(GameObject* pObj, GameObject* pParent);
		static void Draw(void);
		static void Update(AnimTime currentTime);
		static GameObject* GetRoot(void);
		static PCSTree* GetPCSTree();
		static void Destroy();
		static void ToggleBoundingSpheresOff();
		static void ToggleBoundingSpheresOn();
		static GameObject* Find(const char* const inName);
		static GameObject* FindObjectByIndex(const int index);

		~GameObjectMan();

	private:
		GameObjectMan();

		static GameObjectMan* privGetInstance();

		// data
		PCSTree* pRootTree;

	};
}

#endif