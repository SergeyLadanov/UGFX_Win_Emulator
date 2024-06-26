#ifndef __MAINPRESENTER_HPP_
#define __MAINPRESENTER_HPP_

#include "UGFX_PresenterBase.hpp"
#include "Model.hpp"
#include "IMainPresenter.hpp"

class MainScreen;


class MainPresenter : public UGFX_PresenterBase, public Model::Listener, public IMainPresenter
{
protected:
    MainScreen &View;
public:
    MainPresenter(MainScreen &view)
        :View(view)
    {
        
    }


    void TestInit(void) override
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