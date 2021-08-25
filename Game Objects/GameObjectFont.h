#ifndef GAME_OBJECT_FONT_H
#define GAME_OBJECT_FONT_H

#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject_Font.h"


namespace Azul
{
	class GameObjectFont : public GameObject
	{

	public:
		GameObjectFont(GraphicsObject_Font* pGraphicsObject, GameObject::Type type);

		// big four
		GameObjectFont() = delete;
		GameObjectFont(const GameObjectFont&) = delete;
		GameObjectFont& operator= (const GameObjectFont&) = delete;
		virtual ~GameObjectFont() override; 
		virtual void Update(AnimTime currentTime) override;

		// Font stuff
		void Set(const char* const pMessage, float xStart, float yStart);

		void DrawFont();
		void UpdateMessage(const char* const pMessage);


	private:
		void privSetMessage(const char* const pMessage); // called in set, sets pMessage to the message


	private:
		static const unsigned int MESSAGE_SIZE = 120;

		float scaleX;
		float scaleY;
		float posX;
		float posY;
		float angle;

		char* pMessage;
		Glyph::Name glyphName;
	};


}



#endif
