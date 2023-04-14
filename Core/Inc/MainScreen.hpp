#ifndef __MAINSCREEN_HPP_
#define __MAINSCREEN_HPP_

#include "UGFX_ViewBase.hpp"
#include "GUI_App.hpp"
#include "MainPresenter.hpp"

class MainScreen : public UGFX_ViewBase<GUI_App, MainPresenter>
{
private:
    GHandle ghButton1;
    GHandle image1, image2, image3, image4;
    UGFX_AppTimer TestTim;
public:
    MainScreen()
    {
        Widget.g.show = true;

        // Apply the button parameters
        Widget.g.width = 100;
        Widget.g.height = 30;
        Widget.g.y = 10;
        Widget.g.x = 10;
        Widget.text = "Test";

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
        Widget.g.y = 40;
        Widget.g.x = 40;

        image2 = gwinImageCreate(0, &Widget.g);
        gwinImageOpenFile(image2, "menu_display.png");


        Widget.g.show = true;
        // Apply the button parameters
        Widget.g.width = 32;
        Widget.g.height = 32;
        Widget.g.y = 90;
        Widget.g.x = 40;

        image3 = gwinImageCreate(0, &Widget.g);
        gwinImageOpenFile(image3, "menu_display.png");
        


        Widget.g.show = true;
        // Apply the button parameters
        Widget.g.width = 32;
        Widget.g.height = 32;
        Widget.g.y = 130;
        Widget.g.x = 40;

        image4 = gwinImageCreate(0, &Widget.g);
        gwinImageOpenFile(image4, "menu_display.png");

        gwinImageCache(image1);
	    gwinImageCache(image2);
        gwinImageCache(image3);
        gwinImageCache(image4);

    }

    void HandleUgfxEvent(GEvent* pe) override
    {
        printf("Event from main screen...\r\n");
        Application->GoToScreen2Animation();
        //Application->GoToScreen2();
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