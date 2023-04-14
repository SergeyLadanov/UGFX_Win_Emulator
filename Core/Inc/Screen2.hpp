#ifndef __SCREEN2_HPP_
#define __SCREEN2_HPP_

#include "UGFX_ViewBase.hpp"
#include "GUI_App.hpp"
#include "Screen2Presenter.hpp"

class Screen2 : public UGFX_ViewBase<GUI_App, Screen2Presenter>
{
private:
    GHandle ghButton1;
    GHandle image1, image2;
public:
    Screen2()
    {
        Widget.g.show = true;

        // Apply the button parameters
        Widget.g.width = 100;
        Widget.g.height = 30;
        Widget.g.y = 10;
        Widget.g.x = 10;
        Widget.text = "Test 23";

        // Create the actual button
        ghButton1 = gwinButtonCreate(0, &Widget);


        Widget.g.show = true;

        // Apply the button parameters
        Widget.g.width = 32;
        Widget.g.height = 32;
        Widget.g.y = 50;
        Widget.g.x = 50;

        image1 = gwinImageCreate(0, &Widget.g);
        gwinImageOpenFile(image1, "menu_display.png");


        Widget.g.show = true;
        // Apply the button parameters
        Widget.g.width = 32;
        Widget.g.height = 32;
        Widget.g.y = 90;
        Widget.g.x = 40;

        image2 = gwinImageCreate(0, &Widget.g);
        gwinImageOpenFile(image2, "menu_display.png");

    }

    void HandleUgfxEvent(GEvent* pe) override
    {
        printf("Event from main screen...\r\n");
        //Application->GoToMainScreen();

        Application->GoToMainScreenAnimation();
    }

    void OnSetupScreen() override
    {
        printf("Setuping screen...\r\n");
    }

    void OnExitScreen() override
    {
        printf("Leaving screen...\r\n");
    }
};



#endif