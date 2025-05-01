#include "menu.h"

namespace PicoGUI
{
    Menu::Menu(
        Draw *draw,
        const char *title,
        uint16_t y,
        uint16_t height,
        uint16_t textColor,
        uint16_t backgroundColor,
        uint16_t selectedColor,
        uint16_t borderColor,
        uint16_t borderWidth)
    {
        this->display = draw;
        this->textColor = textColor;
        this->backgroundColor = backgroundColor;
        list = new List(draw, y + 20, height - 20, textColor, backgroundColor, selectedColor, borderColor, borderWidth);
        this->position = Vector(0, y);
        this->size = Vector(draw->getSize().x, height);
        this->display->clear(position, size, TFT_WHITE);
        this->display->swap();
    }

    Menu::~Menu()
    {
        delete list;
    }

    void Menu::clear()
    {
        list->clear();
    }

    void Menu::draw()
    {
        display->clear(position, size, TFT_WHITE);
        drawTitle();
        list->draw();
    }

    void Menu::drawTitle()
    {
        display->clear(Vector(0, 20), Vector(display->getSize().x, 20), backgroundColor);
        display->text(Vector(2, 2), "Menu", textColor, 4);
    }

    void Menu::scrollDown()
    {
        drawTitle();
        list->scrollDown();
    }

    void Menu::scrollUp()
    {
        drawTitle();
        list->scrollUp();
    }

    void Menu::setSelected(uint16_t index)
    {
        drawTitle();
        list->setSelected(index);
    }
}