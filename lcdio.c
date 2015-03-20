#include "lcd.h"

    /* Low level function. You have to fill this functions with your code. */

void HD44780_delay(uint32_t miliseconds) {
    //put your delay function here
}
uint8_t HD44780_input_state(uint32_t pin) {
    //this function should check if passed pin is HI or LOW
    //example:
    //if (pin == HD44780_DB0) {
    //  GPIOx = OUTPUT;
    //}
}
void HD44780_set_output_state(uint32_t pin, uint8_t state) {
    //this function should set passed pin to HI or LOW depending on state value
}
void HD44780_set_pin_as_output(uint32_t pin) {
    //this function should set passed pin to output mode
}
void HD44780_set_pin_as_input(uint32_t pin) {
    //this function should set passed pin to input mode
}
uint8_t *HD44780_additional_characters() {
    //this array have to end with 0xFF
    static uint8_t chars[] = {
        //fill this array with special characters


        // leave 0xFF as last element
        0xFF
    };                     

    return chars;
}
