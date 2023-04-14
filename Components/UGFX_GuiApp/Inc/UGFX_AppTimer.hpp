#ifndef __UGFX_APPTIMER_HPP_
#define __UGFX_APPTIMER_HPP_


#include "gfx.h"


class UGFX_AppTimer : private GTimer
{
private:
    uint32_t TimerTicks = 0;
    GTimerFunction TickCallBack = 0;
    GTimerFunction EndCallBack = 0;
    void *Arg = nullptr;
public:

    UGFX_AppTimer()
    {
        // printf("Timer constructor\r\n");
        param = this;
        fn = [](void *arg)
        {
            UGFX_AppTimer *obj = (UGFX_AppTimer *) arg;

            if (obj->TickCallBack)
            {
                obj->TickCallBack(obj->Arg);
            }

            if (obj->TimerTicks < 0xFFFFFFFF)
            {
                if (obj->TimerTicks != 0)
                {
                    obj->TimerTicks--;

                    if (!obj->TimerTicks)
                    {
                        if (obj->EndCallBack)
                        {
                            obj->EndCallBack(obj->Arg);
                        }
                        gtimerStop(obj);
                    }
                }

            }
        };
    }


    void SetTickCallBack(GTimerFunction callback)
    {
        TickCallBack = callback;
    }

    void SetEndCallBack(GTimerFunction callback)
    {
        EndCallBack = callback;
    }

    void SetArg(void *arg)
    {
        Arg = arg;
    }

    void Start(uint32_t period, uint32_t nTicks = 0xFFFFFFFF)
    {
        bool autoreload = true;
        TimerTicks = nTicks;

        Stop();

        if (nTicks == 0)
        {
            autoreload = false;
        }

        gtimerStart(this, fn, param, autoreload, period); 
    }


    void Stop(void)
    {
        if (gtimerIsActive(this))
        {
            gtimerStop(this);
        }
    }

    ~UGFX_AppTimer()
    {

    }
};



#endif