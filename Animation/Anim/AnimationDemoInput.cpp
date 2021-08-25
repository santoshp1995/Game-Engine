#include "AnimationDemoInput.h"
#include "InputMan.h"
#include "Keyboard.h"
#include "AnimControllerMan.h"
#include "AnimTransitionController.h"


namespace Azul
{
	bool keyAPressed = false;
	bool keySPressed = false;
	bool keyDPressed = false;

	void AnimationDemoInput()
	{
		Keyboard* key = InputMan::GetKeyboard();

		if (key->GetKeyState(Keyboard::KEY_A))
		{
			if (!keyAPressed)
			{
				keyAPressed = true;
				keySPressed = false;
				keyDPressed = false;

				

				
				

				//AnimController* pController = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID);
				//assert(pController);

				//pController->CycleAnimation();
			}
		}

		if (key->GetKeyState(Keyboard::KEY_S))
		{
			if (!keySPressed)
			{
				keyAPressed = false;
				keySPressed = true;
				keyDPressed = false;

				AnimController* pController = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID_A);
				assert(pController);

				pController->CycleAnimation();
			}
		}

		if (key->GetKeyState(Keyboard::KEY_D))
		{
			if (!keyDPressed)
			{
				keyAPressed = false;
				keySPressed = false;
				keyDPressed = true;

				AnimController* pController = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID_A);
				assert(pController);

				pController->CycleAnimation();
			}
		}
	}
}