#ifndef __UGFX_PRESENTERBASE_HPP_
#define __UGFX_PRESENTERBASE_HPP_

#include <cstdint>

class UGFX_PresenterBase
{
public:
	UGFX_PresenterBase()
	{
	}

	virtual void Activate(void)
	{
	}

	virtual void DeActivate(void)
	{
	}

	virtual ~UGFX_PresenterBase()
	{
		printf("UGFX_PresenterBase::~UGFX_PresenterBase()\n");
	}
};

#endif