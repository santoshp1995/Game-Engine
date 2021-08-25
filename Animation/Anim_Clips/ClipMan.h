#ifndef CLIP_MAN_H
#define CLIP_MAN_H

#include "Clip.h"

namespace Azul
{
	class ClipMan
	{
	public:
		static void Create();
		static void Add(Clip* pClip);
		static Clip* Find(Clip::ClipName name);
		static void Destroy();
		//static Clip* GetActiveClip();


	private:
		static ClipMan* privGetInstance();
		ClipMan();

		void privAddToFront(Clip* node, Clip*& head);
		void privRemove(Clip* node, Clip*& head);

	private:
		Clip* pHead;
		//Clip* pActive;
	};
}

#endif