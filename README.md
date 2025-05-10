# PicoGUI
Easy-to-use GUI for Raspberry Pi Pico Devices

## Features
- List
- Menu
- Loading
- TextBox
- Scrollbar
- Images
- Desktop (with WiFi icon + animation)

## How To Use
**Arduino IDE Installation**
1. Install the Arduino IDE from https://www.arduino.cc/en/software.
2. Download this repository as a .zip file (available here: https://github.com/jblanked/PicoGUI/archive/refs/heads/main.zip).
3. Within the `ArduinoIDE` folder, right-click the `PicoGUI` folder and select `Copy`.
4. Navigate to your Arduino libraries folder (usually at `../../Documents/Arduino/libraries`) and paste the folder there.
5. Open the Arduino IDE you downloaded earlier, go to Preferences/Settings, and add the following URL to the `Additional Boards Manager URLs` field: `https://github.com/earlephilhower/arduino-pico/releases/download/4.5.3/package_rp2040_index.json`. Click `OK`.
6. In `Boards Manager`, search for `rp2040` and install the `Raspberry Pi Pico/RP2040/RP2350` package.
7. In `Library Manager`, search for `TFT_eSPI` and install the `TFT_eSPI` library by `Bodmer`. Then search for `PicoDVI` and install the `PicoDVI - Adafruit Fork` by `Luke Wren (Wren6991)`.
8. Restart your Arduino IDE.
9. Hold the `BOOT` button while connecting your USB data cable.
10. Select the serial port to which your Pico is connected and choose your specific Pico type (e.g., `Raspberry Pi Pico`) as your board.
11. Click `File` in the menu, then `Examples/PicoGUI`, and choose one of the examples.
12. In line 2, change the board configuration (e.g., `VGMConfig, PicoCalcConfigPico, etc.`) to your specific configuration.
13. Lastly, click `Sketch` in the menu, then select `Upload`.

**CircuitPython Installation**
1. Download and install Thonny IDE (https://thonny.org).
2. Download this repository as a .zip file (available here: https://github.com/jblanked/PicoGUI/archive/refs/heads/main.zip).
3. Press and hold the `BOOT` button on your device for 2 seconds.
4. While holding the `BOOT` button, connect the device to your computer using a USB cable.
5. Open Thonny, and in the bottom right corner, select `Install CircuitPython`.
6. Change the settings to your specific Raspberry Pi Pico type and proceed with the installation.
7. Once finished, close the window and hit the red `Stop/Restart` button.
8. Afterwards, open the .zip file downloaded earlier and navigate to the `CircuitPython/src` folder. Copy and paste all of the contents within that folder into your `lib` folder in your `CIRCUITPY` drive that appeared after CircuitPython finished installing.
9. Inside the .zip file (in the `CircuitPython/examples` folder), there are examples that you can copy and paste into your `CIRCUITPY` drive. These should be in your root directory (or optionally the `sd` directory).
10. In Thonny, hit the `Stop/Restart` button again, then double-click the example you added to your `CIRCUITPY` drive and click the green `Start/Run` button.