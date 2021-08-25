#ifndef FONT_LINK_H
#define FONT_LINK_H

namespace Azul
{
	class FontLink
	{
	public:
		FontLink()
		{
			next = nullptr;
			prev = nullptr;
		}

		virtual ~FontLink()
		{

		}

		FontLink* next;
		FontLink* prev;

	};
}



#endif
