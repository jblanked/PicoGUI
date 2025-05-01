#include "PicoGUI.h"
PicoGUI::Board board = VGMConfig; // VGMConfig, PicoCalcConfigPico, PicoCalcConfigPicoW, PicoCalcConfigPico2, PicoCalcConfigPico2W
Draw *draw;
List *list;
static void clear() { draw->clear(Vector(0, 0), Vector(board.width, board.height), TFT_WHITE); }
void setup()
{
    draw = new Draw(board, false); // Initialize the Draw class in 16-bit mode
    list = new List(
        draw,         // draw instance
        0,            // y
        board.height, // height
        TFT_BLACK,    // text color
        TFT_WHITE,    // background color
        TFT_BLUE,     // selected color
        TFT_BLACK,    // border/separator color
        2             // border/separator width
    );
    list->addItem("Hello");
    list->addItem("World");
    list->addItem("Welcome to the PicoGUI library.");
    list->addItem("This is a simple list example.");
    list->addItem("You can add items to the list.");
    list->addItem("You can remove items from the list.");
    list->addItem("You can scroll through the list.");
    list->addItem("You can select items in the list.");
    list->addItem("Item 1");
    list->addItem("Item 2");
    list->addItem("Item 3");
    list->addItem("Item 4");
    list->addItem("Item 5");
    list->addItem("Item 6");
    list->addItem("Item 7");
    list->addItem("Item 8");
    list->addItem("Item 9");
    list->addItem("Item 10");
    list->draw();
}

void loop()
{
    for (int i = 0; i < 18; i++)
    {
        clear();
        list->setSelected(i);
        delay(1000);
    }
    for (int i = 16; i > 0; i--)
    {
        clear();
        list->setSelected(i);
        delay(1000);
    }
}