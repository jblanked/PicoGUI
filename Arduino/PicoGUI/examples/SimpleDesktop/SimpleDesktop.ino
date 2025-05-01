#include "PicoGUI.h"
#include "frames.h"
PicoGUI::Board board = PicoCalcConfigPicoW; // VGMConfig, PicoCalcConfigPico, PicoCalcConfigPicoW, PicoCalcConfigPico2, PicoCalcConfigPico2W
Draw *draw;
Desktop *desktop;
int next_frame = 1;
int max_frame = 4;
int direction = 1;
const PROGMEM uint8_t *frame_data(uint8_t index)
{
    return index == 1 ? frame_1 : index == 2 ? frame_2
                              : index == 3   ? frame_3
                                             : frame_4;
}
void setup()
{
    draw = new Draw(
        board, // Board configuration
        true,  // Use 8-bit?
        true   // Use double buffering?
    );
    desktop = new Desktop(draw);
}
void loop()
{
    desktop->draw(frame_data(next_frame), Vector(320, 240));
    next_frame += direction;
    if (next_frame == max_frame)
    {
        direction = -1;
    }
    if (next_frame == 1)
    {
        direction = 1;
    }
}