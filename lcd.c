#include "lcd.h"

uint8_t HD44780_busycheck_enabled = 0;
/////
void HD44780_output_mode(uint32_t pins) {
    uint32_t bit = HD44780_DB0, i, pin = 0;
    if (!HD44780_INTERFACE_MODE_8BIT) bit = HD44780_DB4;

    for (i = 0; bit <= HD44780_E; ++i) {
        pin = pins & bit;
        if (pin) HD44780_set_pin_as_output(pin);
        bit = bit << 1;
    }
}
void HD44780_input_mode(uint32_t pins) {
    uint32_t bit = HD44780_DB0, i, pin = 0;
    if (!HD44780_INTERFACE_MODE_8BIT) bit = HD44780_DB4;

    for (i = 0; bit <= HD44780_E; ++i) {
        pin = pins & bit;
        if (pin) HD44780_set_pin_as_input(pin);
        bit = bit << 1;
    }
}
void HD44780_output(uint32_t pins, uint8_t state) {
    uint32_t bit = HD44780_DB0, i, pin = 0;
    if (!HD44780_INTERFACE_MODE_8BIT) bit = HD44780_DB4;

    for (i = 0; bit <= HD44780_E; ++i) {
        pin = pins & bit;
        if (pin) HD44780_set_output_state(pin, state);
        bit = bit << 1;
    }
}

void HD44780_init() {
    //gnd | vcc | vo | rs | rw | e | db0 | ... | db7 | a (vcc) | k (gnd)
    HD44780_output_mode(HD44780_RS | HD44780_RW | HD44780_E);
    HD44780_output_mode(HD44780_DB0 | HD44780_DB1 | HD44780_DB2 | HD44780_DB3 | HD44780_DB4 | HD44780_DB5 | HD44780_DB6 | HD44780_DB7);
}
void HD44780_write_4bits(uint8_t bits) {
    //for 4 bit interface
    bits &= 0x0F;
    bits = bits << 4;

    HD44780_output((uint32_t) bits & 0xFF, 1);
    HD44780_output((uint32_t) (~bits) & 0xFF, 0);

    HD44780_output(HD44780_E, 1);
    HD44780_delay(HD44780_ENABLE_PULSE_WIDTH);
    HD44780_output(HD44780_E, 0);
}

void HD44780_instr(uint8_t instruction){
    if (HD44780_busycheck_enabled) HD44780_wait_for_not_busy();
    HD44780_output(HD44780_RS | HD44780_RW, 0);

    if (HD44780_INTERFACE_MODE_8BIT) {
        HD44780_output((uint32_t) instruction & 0xFF, 1);
        HD44780_output((uint32_t) (~instruction) & 0xFF, 0);

        HD44780_output(HD44780_E, 1);
        HD44780_delay(HD44780_ENABLE_PULSE_WIDTH);
        HD44780_output(HD44780_E, 0);
    } else {
        HD44780_write_4bits(instruction >> 4);
        HD44780_write_4bits(instruction);
    }
}

void HD44780_write_char(uint8_t instruction){
    HD44780_wait_for_not_busy();
    HD44780_output(HD44780_RS, 1);
    HD44780_output(HD44780_RW, 0);

    if (HD44780_INTERFACE_MODE_8BIT) {
        HD44780_output((uint32_t) instruction & 0xFF, 1);
        HD44780_output((uint32_t) (~instruction) & 0xFF, 0);

        HD44780_output(HD44780_E, 1);
        HD44780_delay(HD44780_ENABLE_PULSE_WIDTH);
        HD44780_output(HD44780_E, 0);
    } else {
        HD44780_write_4bits(instruction >> 4);
        HD44780_write_4bits(instruction);
    }
}
void HD44780_gotoxy(uint8_t x, uint8_t y) { //ustalanie "pozycji kursora" na LCD
    uint8_t xy;
    xy = 0x41;
	
    xy = x + y * 0x40;
	 
    HD44780_instr(xy | 0x80);
}
void HD44780_print(const char *str){
    HD44780_instr(HD44780_CMD_RET_HOME);
    while (*str != '\0') {
        if (*str == '\n') HD44780_gotoxy(0, 1);
        else HD44780_write_char(*str);
        ++str;
    }
}
void HD44780_wait_for_not_busy() {
    HD44780_input_mode(HD44780_DB0 | HD44780_DB1 | HD44780_DB2 | HD44780_DB3 | HD44780_DB4 | HD44780_DB5 | HD44780_DB6 | HD44780_DB7);

    HD44780_output(HD44780_RW, 1);
    HD44780_output(HD44780_RS, 0);
    HD44780_output(HD44780_E, 1);

    while(HD44780_input_state(HD44780_DB7));

    HD44780_output(HD44780_E, 0);
    HD44780_output(HD44780_RW, 0);
    HD44780_output_mode(HD44780_DB0 | HD44780_DB1 | HD44780_DB2 | HD44780_DB3 | HD44780_DB4 | HD44780_DB5 | HD44780_DB6 | HD44780_DB7);
}

void HD44780_start() {
    HD44780_init();
    HD44780_delay(50);//>30ms

    HD44780_output(HD44780_RS | HD44780_RW | HD44780_E, 0);
    //
    if (HD44780_INTERFACE_MODE_8BIT) HD44780_instr(HD44780_CMD_FUNCTION_SET | HD44780_CMD_FUNCTION_SET_8BIT | HD44780_CMD_FUNCTION_SET_DISPLAY_2_LINES);
    else {
        HD44780_write_4bits(0x02);
        HD44780_instr(HD44780_CMD_FUNCTION_SET | HD44780_CMD_FUNCTION_SET_DISPLAY_2_LINES);
    }

    HD44780_busycheck_enabled = 1;
    HD44780_instr(HD44780_CMD_DISPLAY_ONOFF | HD44780_CMD_DISPLAY_ONOFF_ON); 
    HD44780_instr(HD44780_CMD_CLR_DISPLAY);
    HD44780_instr(HD44780_CMD_ENTRY_MODE | HD44780_CMD_ENTRY_MODE_SHIFT_TO_THE_RIGHT);
    HD44780_instr(HD44780_CMD_RET_HOME);
}

