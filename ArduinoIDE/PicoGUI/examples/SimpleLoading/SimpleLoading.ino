#include "PicoGUI.h"
PicoGUI::Board board = VGMConfig; // VGMConfig, PicoCalcConfigPico, PicoCalcConfigPicoW, PicoCalcConfigPico2, PicoCalcConfigPico2W
Draw *draw;
Loading *loading;
void setup()
{
    draw = new Draw(
        board, // Board configuration
        true,  // Use 8-bit?
        true   // Use double buffering?
    );
    loading = new Loading(
        draw,      // draw instance
        TFT_BLACK, // spinner color
        TFT_WHITE  // background color
    );
    loading->setText("Loading..."); // Set the text to be displayed
}
void loop()
{
    for (int i = 0; i < 500; i++)
    {
        loading->animate(); // Animate the loading spinner
        delay(10);          // Delay for a short period
    }
    loading->stop(); // Stop the loading spinner
    delay(2000);
}