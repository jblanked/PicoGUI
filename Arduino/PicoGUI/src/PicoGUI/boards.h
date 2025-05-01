#pragma once
#include <Arduino.h>

/* Pico Calc
#define PicoGUI_SCK 10  //
#define PicoGUI_MOSI 11 // TX
#define PicoGUI_MISO 12 // RX
#define PicoGUI_CS 13   //
#define PicoGUI_DC 14
#define PicoGUI_RST 15
*/

/* VGM
#define PicoGUI_SCK 8
#define PicoGUI_MOSI 11
#define PicoGUI_MISO 12
#define PicoGUI_CS 13
#define PicoGUI_DC 14
#define PicoGUI_RST 15

static const struct dvi_serialiser_cfg picodvi_dvi_cfg = {
    .pio = DVI_DEFAULT_PIO_INST,
    .sm_tmds = {0, 1, 2},
    .pins_tmds = {10, 12, 14},
    .pins_clk = 8,
    .invert_diffpairs = true
};

*/

namespace PicoGUI
{
    typedef enum
    {
        BOARD_TYPE_PICO_CALC = 0,
        BOARD_TYPE_VGM = 1
    } BoardType;

    typedef enum
    {
        PICO_TYPE_PICO = 0,    // Raspberry Pi Pico
        PICO_TYPE_PICO_W = 1,  // Raspberry Pi Pico W
        PICO_TYPE_PICO_2 = 2,  // Raspberry Pi Pico 2
        PICO_TYPE_PICO_2_W = 3 // Raspberry Pi Pico 2 W
    } PicoType;

    typedef struct
    {
        uint8_t sck;
        uint8_t mosi;
        uint8_t miso;
        uint8_t cs;
        uint8_t dc;
        uint8_t rst;
    } BoardPins;

    typedef struct
    {
        BoardType boardType;
        PicoType picoType;
        BoardPins pins;
        uint16_t width;
        uint16_t height;
        uint8_t rotation;
    } Board;

    static const Board VGMConfig = {
        .boardType = BOARD_TYPE_VGM,
        .picoType = PICO_TYPE_PICO,
        .pins = {
            .sck = 8,
            .mosi = 11,
            .miso = 12,
            .cs = 13,
            .dc = 14,
            .rst = 15},
        .width = 320,
        .height = 240,
        .rotation = 0};

    static const Board PicoCalcConfigPico = {
        .boardType = BOARD_TYPE_PICO_CALC,
        .picoType = PICO_TYPE_PICO,
        .pins = {
            .sck = 10,
            .mosi = 11,
            .miso = 12,
            .cs = 13,
            .dc = 14,
            .rst = 15},
        .width = 320,
        .height = 320,
        .rotation = 0};

    static const Board PicoCalcConfigPicoW = {
        .boardType = BOARD_TYPE_PICO_CALC,
        .picoType = PICO_TYPE_PICO_W,
        .pins = {
            .sck = 10,
            .mosi = 11,
            .miso = 12,
            .cs = 13,
            .dc = 14,
            .rst = 15},
        .width = 320,
        .height = 320,
        .rotation = 0};

    static const Board PicoCalcConfigPico2 = {
        .boardType = BOARD_TYPE_PICO_CALC,
        .picoType = PICO_TYPE_PICO_2,
        .pins = {
            .sck = 10,
            .mosi = 11,
            .miso = 12,
            .cs = 13,
            .dc = 14,
            .rst = 15},
        .width = 320,
        .height = 320,
        .rotation = 0};

    static const Board PicoCalcConfigPico2W = {
        .boardType = BOARD_TYPE_PICO_CALC,
        .picoType = PICO_TYPE_PICO_2_W,
        .pins = {
            .sck = 10,
            .mosi = 11,
            .miso = 12,
            .cs = 13,
            .dc = 14,
            .rst = 15},
        .width = 320,
        .height = 320,
        .rotation = 0};

};
