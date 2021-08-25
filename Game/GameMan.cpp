#include "Game.h"
#include "GameMan.h"

namespace Azul
{
	GameMan* GameMan::pInstance = nullptr;

	void GameMan::Create(const char* pWindowName, const int Width, const int Height)
	{
		GameMan::privCreate(pWindowName, Width, Height);
	}

	void GameMan::Destroy()
	{
		GameMan* pMan = GameMan::privInstance();
		assert(pMan);

		assert(pMan->poGame);
		delete pMan->poGame;
		pMan->poGame = nullptr;
	}

	Game* GameMan::GetGame()
	{
		GameMan* pMan = GameMan::privInstance();
		assert(pMan);
		assert(pMan->poGame);
		return pMan->poGame;
	}

	GameMan::~GameMan()
	{
		assert(this->poGame == nullptr);
	}

	void GameMan::privCreate(const char* pWindowName, const int Width, const int Height)
	{
		Game* poGame = new Game(pWindowName, Width, Height);

		// Storage
		static GameMan gameMan(poGame);
		GameMan::pInstance = &gameMan;
	}

	GameMan* GameMan::privInstance()
	{
		assert(GameMan::pInstance);
		return GameMan::pInstance;
	}
	
	GameMan::GameMan(Game* pGame)
	{
		assert(pGame);
		this->poGame = pGame;
	}
}