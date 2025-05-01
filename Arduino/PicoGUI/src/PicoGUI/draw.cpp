#include "draw.h"
namespace PicoGUI
{
    DisplayAdapter::DisplayAdapter(Board board, bool use_8bit)
    {
        this->picoBoard = board;
        if (board.boardType == BOARD_TYPE_VGM)
        {
            if (use_8bit)
            {
                this->display8 = new DVIGFX8(DVI_RES_320x240p60, true, picodvi_dvi_cfg);
                this->display16 = nullptr;
            }
            else
            {
                this->display16 = new DVIGFX16(DVI_RES_320x240p60, picodvi_dvi_cfg);
                this->display8 = nullptr;
            }
        }
        else if (board.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->display8 = nullptr;
            this->display16 = nullptr;
            this->displayTFT = new TFT_eSPI();
        }
        else
        {
            this->display8 = nullptr;
            this->display16 = nullptr;
            this->displayTFT = nullptr;
        }
    }

    DisplayAdapter::~DisplayAdapter()
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                delete this->display8;
            }
            else
            {
                delete this->display16;
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            delete this->displayTFT;
        }
    }

    bool DisplayAdapter::begin()
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                return this->display8->begin();
            }
            else
            {
                return this->display16->begin();
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->init();
            this->displayTFT->setRotation(picoBoard.rotation);
            return true;
        }
        return false;
    }

    void DisplayAdapter::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawBitmap(x, y, bitmap, w, h, color);
            }
            else
            {
                this->display16->drawBitmap(x, y, bitmap, w, h, color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->drawBitmap(x, y, bitmap, w, h, color);
        }
    }

    void DisplayAdapter::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawCircle(x0, y0, r, color);
            }
            else
            {
                this->display16->drawCircle(x0, y0, r, color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->drawCircle(x0, y0, r, color);
        }
    }

    void DisplayAdapter::drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawGrayscaleBitmap(x, y, bitmap, w, h);
            }
            else
            {
                this->display16->drawGrayscaleBitmap(x, y, bitmap, w, h);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->drawBitmap(x, y, bitmap, w, h, color);
        }
    }

    void DisplayAdapter::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawLine(x0, y0, x1, y1, color);
            }
            else
            {
                this->display16->drawLine(x0, y0, x1, y1, color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->drawLine(x0, y0, x1, y1, color);
        }
    }

    void DisplayAdapter::drawPixel(int16_t x, int16_t y, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawPixel(x, y, color);
            }
            else
            {
                this->display16->drawPixel(x, y, color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->drawPixel(x, y, color);
        }
    }

    void DisplayAdapter::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawRect(x, y, w, h, color);
            }
            else
            {
                this->display16->drawRect(x, y, w, h, color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->drawRect(x, y, w, h, color);
        }
    }

    void DisplayAdapter::drawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawRGBBitmap(x, y, bitmap, w, h);
            }
            else
            {
                this->display16->drawRGBBitmap(x, y, bitmap, w, h);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->pushImage((int32_t)x, (int32_t)y, (int32_t)w, (int32_t)h, bitmap);
        }
    }

    void DisplayAdapter::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->drawRoundRect(x, y, w, h, r, color);
            }
            else
            {
                this->display16->drawRoundRect(x, y, w, h, r, color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->drawRoundRect(x, y, w, h, r, color);
        }
    }

    void DisplayAdapter::fillScreen(uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->fillScreen(color);
            }
            else
            {
                this->display16->fillScreen(color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->fillScreen(color);
        }
    }

    void DisplayAdapter::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->fillRect(x, y, w, h, color);
            }
            else
            {
                this->display16->fillRect(x, y, w, h, color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->fillRect(x, y, w, h, color);
        }
    }

    uint16_t *DisplayAdapter::getPalette()
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                return this->display8->getPalette();
            }
            else
            {
                // does not exist
                return nullptr;
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            // does not exist
            return nullptr;
        }
        return nullptr;
    }

    Vector DisplayAdapter::getCursor()
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                return Vector(this->display8->getCursorX(), this->display8->getCursorY());
            }
            else
            {
                return Vector(this->display16->getCursorX(), this->display16->getCursorY());
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            return Vector(this->displayTFT->getCursorX(), this->displayTFT->getCursorY());
        }
        return Vector(0, 0);
    }

    void DisplayAdapter::print(char text)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->print(text);
            }
            else
            {
                this->display16->print(text);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->print(text);
        }
    }

    void DisplayAdapter::print(const char *text)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->print(text);
            }
            else
            {
                this->display16->print(text);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->print(text);
        }
    }

    void DisplayAdapter::setPalette(const uint16_t *palette)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                memcpy(this->display8->getPalette(), palette, sizeof palette);
            }
            else
            {
                // does not exist
                return;
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            // does not exist
            return;
        }
    }

    void DisplayAdapter::setColor(uint8_t idx, uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->setColor(idx, color);
            }
            else
            {
                // does not exist
                return;
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->setTextColor(color);
        }
    }

    void DisplayAdapter::setCursor(int16_t x, int16_t y)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->setCursor(x, y);
            }
            else
            {
                this->display16->setCursor(x, y);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->setCursor(x, y);
        }
    }

    void DisplayAdapter::setFont(int font)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            // fonts from the TFT_eSPI library (NULL for now)
            if (this->display8 != nullptr)
            {
                this->display8->setFont(NULL);
            }
            else
            {
                this->display16->setFont(NULL);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->setTextFont(font);
        }
    }

    void DisplayAdapter::setTextSize(uint8_t size)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->setTextSize(size);
            }
            else
            {
                this->display16->setTextSize(size);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->setTextSize(size);
        }
    }

    void DisplayAdapter::setTextColor(uint16_t color)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->setTextColor(color);
            }
            else
            {
                this->display16->setTextColor(color);
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            this->displayTFT->setTextColor(color);
        }
    }

    void DisplayAdapter::swap(bool copy_framebuffer, bool copy_palette)
    {
        if (picoBoard.boardType == BOARD_TYPE_VGM)
        {
            if (this->display8 != nullptr)
            {
                this->display8->swap(copy_framebuffer, copy_palette);
            }
            else
            {
                // does not exist
                return;
            }
        }
        else if (picoBoard.boardType == BOARD_TYPE_PICO_CALC)
        {
            // does not exist
            return;
        }
    }

    Draw::Draw(Board board, bool use_8bit) : is_8bit(use_8bit)
    {
        this->size = Vector(board.width, board.height);
        this->display = new DisplayAdapter(board, use_8bit);
        if (this->display == nullptr)
            return;

        if (!this->display->begin())
            return;

        this->display->setFont();
        this->display->setTextSize(1);
        this->picoBoard = board;
    }

    Draw::~Draw()
    {
        delete this->display;
    }

    void Draw::background(uint16_t color)
    {
        this->display->fillScreen(color);
    }

    void Draw::clear(Vector position, Vector size, uint16_t color)
    {
        // Calculate the clipping boundaries
        int x = position.x;
        int y = position.y;
        int width = size.x;
        int height = size.y;

        // Adjust for left and top boundaries
        if (x < 0)
        {
            width += x; // Reduce width by the negative offset
            x = 0;
        }
        if (y < 0)
        {
            height += y; // Reduce height by the negative offset
            y = 0;
        }

        // Adjust for right and bottom boundaries
        if (x + width > this->size.x)
        {
            width = this->size.x - x;
        }
        if (y + height > this->size.y)
        {
            height = this->size.y - y;
        }

        // Ensure width and height are positive before drawing
        if (width > 0 && height > 0)
        {
            this->display->fillRect(x, y, width, height, color);
        }
    }

    void Draw::color(uint16_t color)
    {
        this->display->setTextColor(color);
    }

    void Draw::drawLine(Vector position, Vector size, uint16_t color)
    {
        this->display->drawLine(position.x, position.y, size.x, size.y, color);
    }

    void Draw::drawRect(Vector position, Vector size, uint16_t color)
    {
        this->display->drawRect(position.x, position.y, size.x, size.y, color);
    }

    void Draw::fillRect(Vector position, Vector size, uint16_t color)
    {
        this->display->fillRect(position.x, position.y, size.x, size.y, color);
    }

    Vector Draw::getCursor()
    {
        return this->display->getCursor();
    }

    void Draw::image(Vector position, const uint8_t *bitmap, Vector size)
    {
        if (bitmap != nullptr &&
            position.x < this->size.x &&
            position.y < this->size.y &&
            size.x > 0 &&
            size.y > 0)
        {
            if (this->is_8bit)
            {
                this->display->drawGrayscaleBitmap(position.x, position.y, bitmap, size.x, size.y);
            }
            else
            {
                this->display->drawRGBBitmap(position.x, position.y, (const uint16_t *)bitmap, size.x, size.y);
            }
        }
    }

    void Draw::setFont(int font)
    {
        this->display->setFont(font);
    }

    void Draw::text(Vector position, const char text)
    {
        this->display->setCursor(position.x, position.y);
        this->display->print(text);
    }

    void Draw::text(Vector position, const char text, uint16_t color)
    {
        this->display->setCursor(position.x, position.y);
        this->display->setTextColor(color);
        this->display->print(text);
    }

    void Draw::text(Vector position, const char *text)
    {
        this->display->setCursor(position.x, position.y);
        this->display->print(text);
    }

    void Draw::text(Vector position, const char *text, uint16_t color, int font)
    {
        this->display->setCursor(position.x, position.y);
        this->display->setFont(font);
        this->display->setTextColor(color);
        this->display->print(text);
    }
}