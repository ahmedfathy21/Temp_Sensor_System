/* 
 * File:   ECU_DC_MOTOR.h
 * Author: En.Ahmed
 *
 * Created on April 13, 2024, 6:09 PM
 */


#include"ECU_DC_MOTOR.h"


/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType  dc_motor_initialize(const dc_motor_t * dc_motor){
     std_ReturnType ret = E_OK ;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
     gpio_pin_initialize(&(dc_motor->dc_motor_pin[0]));
     gpio_pin_initialize(&(dc_motor->dc_motor_pin[1]));
    
    }                     
   return ret; 
}
/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType  dc_motor_move_right(const dc_motor_t * dc_motor){
      std_ReturnType ret = E_OK ;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]),GPIO_HIGH);
      gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]),GPIO_LOW);
    }
       return ret; 
    }                     
  
    

/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType  dc_motor_move_left(const dc_motor_t * dc_motor){
      std_ReturnType ret = E_OK ;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
         gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]),GPIO_LOW);
         gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]),GPIO_HIGH);
        
    }                     
   return ret; 
    
    
}
/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType  dc_motor_stop(const dc_motor_t * dc_motor){
      std_ReturnType ret = E_OK ;
    if(dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
         gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]),GPIO_LOW);
         gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]),GPIO_LOW);
    }                     
   return ret; 
}