 /* 
 * File:   Application.c
 * Author: En.Ahmed
 *
 * Created on March 4, 2024, 6:40 PM
 */
                 

#include"ecu_Led.h"
/**
 * @brief initialize the assigned pin to be OUTPUT and turn the led off
 * @param led : pointer to the led module configurations
 * @return status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
std_ReturnType led_initialize(const led_t * led){
    std_ReturnType ret = E_OK;
     
    if (NULL == led ){
                 ret = E_NOT_OK;   
     
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name,.pin=led->pin,
                              .direction=GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
     gpio_pin_initialize(&pin_obj);     
    }  
    return ret;
} 
/**
 * @brief turn the led on
 * @param led : pointer to the led module configurations
 * @return status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
std_ReturnType led_turn_on(const led_t * led){
     std_ReturnType ret = E_OK;
     
    if (NULL == led ){
                 ret = E_NOT_OK;   

    }
    else{
         pin_config_t pin_obj = {.port = led->port_name,.pin=led->pin,
                                 .direction=GPIO_DIRECTION_OUTPUT,.logic = led->led_status}; 
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
    
    return ret;
    
}  
/**
 * @brief turn the led off
 * @param led : pointer to the led module configurations
 * @return status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
std_ReturnType led_turn_off(const led_t * led){
     std_ReturnType ret = E_OK;
    if (NULL == led ){
                 ret = E_NOT_OK;   

    }
    else{
         pin_config_t pin_obj = {.port = led->port_name,.pin=led->pin,
                                 .direction=GPIO_DIRECTION_OUTPUT,.logic = led->led_status}; 
        gpio_pin_write_logic(&pin_obj,GPIO_LOW);
        
    }
    
    return ret;
    
}  
/**
 * @brief toggle the led
 * @param led : pointer to the led module configurations
 * @return status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
std_ReturnType led_turn_toggle(const led_t * led){
     std_ReturnType ret = E_OK;
    if (NULL == led ){
                 ret = E_NOT_OK;   
     
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name,.pin=led->pin,
                                 .direction=GPIO_DIRECTION_OUTPUT,.logic = led->led_status}; 
        gpio_pin_toggle_logic(&pin_obj);
    }  
    return ret;
     
}