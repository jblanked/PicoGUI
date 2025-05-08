#include "PicoGUI.h"
PicoGUI::Board board = VGMConfig; // VGMConfig, PicoCalcConfigPico, PicoCalcConfigPicoW, PicoCalcConfigPico2, PicoCalcConfigPico2W
Draw *draw;
Menu *menu;
void setup()
{
    draw = new Draw(
        board, // Board configuration
        true,  // Use 8-bit?
        true   // Use double buffering?
    );
    menu = new Menu(
        draw,         // draw instance
        "Menu",       // title
        0,            // y
        board.height, // height
        TFT_BLACK,    // text color
        TFT_WHITE,    // background color
        TFT_BLUE,     // selected color
        TFT_BLACK,    // border/separator color
        2             // border/separator width
    );
    menu->addItem("Hello");
    menu->addItem("World");
    menu->addItem("Welcome to the PicoGUI library.");
    menu->addItem("This is a simple menu example.");
    menu->addItem("You can add items to the menu.");
    menu->addItem("You can remove items from the menu.");
    menu->addItem("You can scroll through the menu.");
    menu->addItem("You can select items in the menu.");
    menu->addItem("Item 1");
    menu->addItem("Item 2");
    menu->addItem("Item 3");
    menu->addItem("Item 4");
    menu->addItem("Item 5");
    menu->addItem("Item 6");
    menu->addItem("Item 7");
    menu->addItem("Item 8");
    menu->addItem("Item 9");
    menu->addItem("Item 10");
    menu->draw();
}

void loop()
{
    for (int i = 0; i < 18; i++)
    {
        menu->setSelected(i);
        delay(1000);
    }
    for (int i = 16; i > 0; i--)
    {
        menu->setSelected(i);
        delay(1000);
    }
}