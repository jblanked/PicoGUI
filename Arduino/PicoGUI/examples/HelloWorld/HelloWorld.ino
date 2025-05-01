#include "PicoGUI.h"
PicoGUI::Board board = VGMConfig; // VGMConfig, PicoCalcConfigPico, PicoCalcConfigPicoW, PicoCalcConfigPico2, PicoCalcConfigPico2W
Draw *draw;
TextBox *box;
uint32_t lineNumber;
static void clear() { draw->clear(Vector(0, 0), Vector(board.width, board.height), TFT_WHITE); }
static const PROGMEM char text[] = "Hello World.\n\nWelcome to the PicoGUI library.\n\nThis basic example is of the TextBox module.\n\nYou can test\nreally long texts.\n\nAnd they will draw as intended.\nPlus\nThere is a scroll bar\n\n\nTest\nand have fun creating gui\nwith PicoGUI\n\n:D\nStay tuned\nfor more GUI updates!\n\nList view, Deskstop, Waiting, and more..\n\nAnyways, thanks!\n\n";

void setup()
{
  draw = new Draw(board, false); // Initialize the Draw class in 16-bit mode
  box = new TextBox(
      draw,              // Draw
      0,                 // y
      draw->getSize().y, // height
      TFT_BLACK,         // Text Color
      TFT_WHITE          // Background Color
  );
  box->setText(text);                     // draw text on the screen
  lineNumber = box->getCurrentLine() - 1; // this is the index of the last line/where the cursor is - 1
  clear();
  // start at the top and scroll down
  for (int i = 0; i < box->getTotalLines() - 1; i++)
  {
    if (i > box->getLinesPerScreen())
    {
      clear();
    }
    box->setCurrentLine(i); // scroll down to the next line
    delay(500);
  }
}

void loop()
{
  // Scroll up
  for (int i = 1; i < 7; i++)
  {
    clear();
    box->setCurrentLine(lineNumber); // scroll up 1 line
    lineNumber--;
    delay(1000);
  }
  // Scroll down
  for (int i = 1; i < 7; i++)
  {
    clear();
    box->setCurrentLine(lineNumber); // scroll down 1 line
    lineNumber++;
    delay(1000);
  }
}