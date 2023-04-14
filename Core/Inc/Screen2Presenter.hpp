#ifndef __SCREEN2PRESENTER_HPP_
#define __SCREEN2PRESENTER_HPP_

#include "UGFX_PresenterBase.hpp"
#include "Model.hpp"


class Screen2;

class Screen2Presenter : public UGFX_PresenterBase, public Model::Listener
{
protected:
    Screen2 &View;
public:
    Screen2Presenter(Screen2 &view)
        :View(view)
    {
        
    }

    void Activate() override
    {
        printf("Presener activate...\r\n");
    }


    void DeActivate() override
    {
        printf("Presener deactivate...\r\n");
    }
};


#endif