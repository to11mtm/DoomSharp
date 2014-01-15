#ifndef __P_TICK_HPP__
#define __P_TICK_HPP__

using namespace System;
using namespace System::Collections::Generic;

#include <vcclr.h>
#include <stdlib.h>

extern gcroot<List<Thinker^>^> thinkers;

ref class LegacyThinker : Thinker
{
public:
	thinker_t *ptr;

	LegacyThinker(size_t size)
	{
		ptr = (thinker_t *)malloc(size + 256);
		if (!ptr)
			throw gcnew ApplicationException();
	}

	virtual bool Tick() override
	{
		if (ptr->function.acp1 == (actionf_p1)-1)
		{
			return true;
		}
		if (ptr->function.acp1)
		{
			ptr->function.acp1(ptr);
		}
		return false;
	}

	~LegacyThinker()
	{
		this->!LegacyThinker();
	}

	!LegacyThinker()
	{
		free(ptr);
	}
};

#endif