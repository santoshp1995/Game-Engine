//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CameraDemoInput.h"
#include "InputMan.h"
#include "Keyboard.h"
#include "CameraMan.h"

namespace Azul
{
	void CameraDemoInput()
	{
		Vect obj(0.0f, 0.0f, 0.0f);


		Keyboard* key = InputMan::GetKeyboard();

		if (key->GetKeyState(Keyboard::KEY_ARROW_UP))
		{
			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			tar = obj;

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);
			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, rightNorm, -0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->SetHelper(up, tar, pos);
		}

		if (key->GetKeyState(Keyboard::KEY_ARROW_RIGHT))
		{

			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			tar = obj;

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);

			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, upNorm, +0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->SetHelper(up, tar, pos);
		}

		if (key->GetKeyState(Keyboard::KEY_ARROW_LEFT))
		{

			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm

			tar = obj;

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);

			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, upNorm, -0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->SetHelper(up, tar, pos);
		}

		if (key->GetKeyState(Keyboard::KEY_ARROW_DOWN))
		{
			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			tar = obj;

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);
			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, rightNorm, 0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D)->SetHelper(up, tar, pos);
		}

	}
}

// --- End of File ---