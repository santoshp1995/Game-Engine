#include "DynamicFontDemo.h"

namespace Azul
{
	void FontDemo(char*& pChar, const int num)
	{
		switch (num)
		{
		case 0:
			strcpy_s(pChar, 100, "0 ");
			break;

		case 20:
			strcpy_s(pChar, 100, "1 ");
			break;

		case 40:
			strcpy_s(pChar, 100, "2 ");
			break;

		case 60:
			strcpy_s(pChar, 100, "3 ");
			break;

		case 80:
			strcpy_s(pChar, 100, "4 ");
			break;

		case 100:
			strcpy_s(pChar, 100, "5 ");
			break;

		case 120:
			strcpy_s(pChar, 100, "6 ");
			break;

		case 140:
			strcpy_s(pChar, 100, "7 ");
			break;

		case 160:
			strcpy_s(pChar, 100, "8 ");
			break;

		case 180:
			strcpy_s(pChar, 100, "9 ");
			break;

		default:
			break;
		}
	}

}
