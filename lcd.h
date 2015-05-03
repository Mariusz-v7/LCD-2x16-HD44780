#include <stdint.h>

#define HD44780_INTERFACE_MODE_8BIT                 0//set to 1 for 8bit interface. set to 0 for 4bit interface.

#define HD44780_ENABLE_PULSE_WIDTH                  1 //ms

#define HD44780_DB0                                 0x0001
#define HD44780_DB1                                 0x0002
#define HD44780_DB2                                 0x0004
#define HD44780_DB3                                 0x0008
#define HD44780_DB4                                 0x0010
#define HD44780_DB5                                 0x0020
#define HD44780_DB6                                 0x0040
#define HD44780_DB7                                 0x0080
#define HD44780_RS                                  0x0100
#define HD44780_RW                                  0x0200
#define HD44780_E                                   0x0400

#define HD44780_CMD_CLR_DISPLAY                     0x01
#define HD44780_CMD_RET_HOME                        0x02
#define HD44780_CMD_ENTRY_MODE                      0x04
#define HD44780_CMD_ENTRY_MODE_SHIFT_DISPLAY        0x01
#define HD44780_CMD_ENTRY_MODE_SHIFT_TO_THE_RIGHT   0x02
#define HD44780_CMD_DISPLAY_ONOFF                   0x08
#define HD44780_CMD_DISPLAY_ONOFF_ON                0x04
#define HD44780_CMD_DISPLAY_ONOFF_CURSOR_ON         0x02
#define HD44780_CMD_DISPLAY_ONOFF_CURSOR_BLINK      0x01
#define HD44780_CMD_FUNCTION_SET                    0x20
#define HD44780_CMD_FUNCTION_SET_8BIT               0x10
#define HD44780_CMD_FUNCTION_SET_DISPLAY_2_LINES    0x08
#define HD44780_CMD_FUNCTION_SET_BIG_FONT           0x04



void HD44780_init(void);
void HD44780_instr(uint8_t instruction);
void HD44780_write_char(uint8_t instruction);
void HD44780_gotoxy(uint8_t x, uint8_t y);
void HD44780_print(const char *string);
void HD44780_wait_for_not_busy(void);
void HD44780_start(void);
void HD44780_reset(void);
//Low level

void HD44780_delay(uint32_t miliseconds);
uint8_t HD44780_input_state(uint32_t pin);
void HD44780_set_output_state(uint32_t pin, uint8_t state);
void HD44780_set_pin_as_output(uint32_t pin);
void HD44780_set_pin_as_input(uint32_t pin);
uint8_t *HD44780_additional_characters();
