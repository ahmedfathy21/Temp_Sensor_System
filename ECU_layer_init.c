/* 
 * File:   ECU_layer_init.c
 * Author: En.Ahmed
 *
 * Created on April 17, 2024, 12:35 AM
 */
#include"ECU_layer_init.h"
led_t led1 = {.port_name = PORTC_INDEX, .pin = PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = PIN1, .led_status = GPIO_LOW};
led_t led3 = {.port_name = PORTC_INDEX, .pin = PIN2, .led_status = GPIO_LOW};
led_t led4 = {.port_name = PORTC_INDEX, .pin = PIN3, .led_status = GPIO_LOW};
led_t led5 = {.port_name = PORTC_INDEX, .pin = PIN4, .led_status = GPIO_LOW};
led_t led6 = {.port_name = PORTC_INDEX, .pin = PIN5, .led_status = GPIO_LOW};
led_t led7 = {.port_name = PORTC_INDEX, .pin = PIN6, .led_status = GPIO_LOW};
led_t led8 = {.port_name = PORTC_INDEX, .pin = PIN7, .led_status = GPIO_LOW};
button_t button1={.button_pin.port=PORTD_INDEX,.button_pin.pin=PIN0,.button_pin.direction=GPIO_DIRECTION_INPUT,
.button_pin.logic=GPIO_LOW,.button_connection=BUTTON_ACTIVE_LOW,.button_state=BUTTON_RELEASED};
button_t button2={.button_pin.port=PORTD_INDEX,.button_pin.pin=PIN1,.button_pin.direction=GPIO_DIRECTION_INPUT,
.button_pin.logic=GPIO_LOW,.button_connection=BUTTON_ACTIVE_LOW,.button_state=BUTTON_RELEASED};
void ecu_layer_initialize(void){ 
    std_ReturnType ret = E_NOT_OK;
    ret = button_initialize(&button1);
    ret = button_initialize(&button2);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    ret = led_initialize(&led4);
    ret = led_initialize(&led5);
    ret = led_initialize(&led6);
    ret = led_initialize(&led7);
    ret = led_initialize(&led8);  
}