#pragma once
#include "draw.h"

namespace PicoGUI
{
    class Desktop
    {
    public:
        Desktop(Draw *draw, uint16_t textColor = TFT_BLACK, uint16_t backgroundColor = TFT_WHITE);
        ~Desktop();
        //
        void clear();
        void draw(const uint8_t *animationFrame, Vector animationSize, const uint16_t *palette = nullptr);
        //
        uint16_t getTextColor() const { return textColor; }
        uint16_t getBackgroundColor() const { return backgroundColor; }

    private:
        void drawHeader();
        Draw *display;
        uint16_t textColor;
        uint16_t backgroundColor;
        bool hasWiFi;
        const char *boardName;
    };
}