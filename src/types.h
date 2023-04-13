#pragma once

// чип
enum M_chip {
    LED_WS2811,    // GBR
    LED_WS2812,    // GRB
    LED_WS2813,    // GRB
    LED_WS2815,    // GRB
    LED_WS2818,    // RGB
    LED_WS6812,    // BGR
    LED_APA102,    // BGR
    LED_APA102_SPI,    // BGR
};

enum M_order {
    // порядок цвета: r-00, g-01, b-10
    ORDER_RGB = 0b000110,
    ORDER_RBG = 0b001001,
    ORDER_BRG = 0b100001,
    ORDER_BGR = 0b100100,
    ORDER_GRB = 0b010010,
    ORDER_GBR = 0b011000,
};

enum M_ISR {
    CLI_OFF,
    CLI_LOW,
    CLI_AVER,
    CLI_HIGH,
};

// ========== ПОДКЛЮЧЕНИЕ МАТРИЦЫ ==========
enum M_type {
    ZIGZAG,
    PARALLEL,
};
enum M_connection {
    LEFT_BOTTOM,
    LEFT_TOP,
    RIGHT_TOP,
    RIGHT_BOTTOM,
};
enum M_dir {
    DIR_RIGHT,
    DIR_UP,
    DIR_LEFT,
    DIR_DOWN,
};