/* 
 * File:   Application.c
 * Author: En.Ahmed
 *
 * Created on March 4, 2024, 6:40 PM
 */


#include"application.h"
#include"MCAL_Layer/EEPROM/hal_eeprom.h"
#include"MCAL_Layer/ADC/hal_adc.h"
uint16 LM35_res1,LM35_res2;
uint8 ADC_Flag;
uint16 LM35_res_1_txt[7],LM35_res_2_txt[7],LM35_res1_Celsius_mv,LM35_res2_Celsius_mv;
uint8 ADC_request = 0;
led_t Green_led = {.port_name= PORTB_INDEX , .pin = PIN6 , .led_status = LED_OFF};
led_t Red_led = {.port_name = PORTB_INDEX, .pin = PIN7, .led_status = LED_OFF};
dc_motor_t motor1 ={
  .dc_motor_pin[0].port = PORTD_INDEX,
  .dc_motor_pin[0].pin  = PIN0,
  .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[0].logic = GPIO_LOW,
  .dc_motor_pin[1].port = PORTD_INDEX,
  .dc_motor_pin[1].pin  = PIN1,
  .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[1].logic = GPIO_LOW,
   
};
dc_motor_t motor2 ={
  .dc_motor_pin[0].port = PORTD_INDEX,
  .dc_motor_pin[0].pin  = PIN2,
  .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[0].logic = GPIO_LOW,
  .dc_motor_pin[1].port = PORTD_INDEX,
  .dc_motor_pin[1].pin  = PIN3,
  .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[1].logic = GPIO_LOW,  
};

adc_conf_t adc1={
        .ADC_InterruptHandler=NULL,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED,
};
chr_lcd_4bit_t  lcd1 = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin  = PIN0 ,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin  = PIN1 ,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic = GPIO_LOW,
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].pin = PIN2,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].pin = PIN3,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].pin = PIN4,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].pin = PIN5,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOW,
};

int main() { 
    std_ReturnType ret = E_NOT_OK;
    
    application_initialize();
    ret = led_initialize(&Green_led);
    ret = led_initialize(&Red_led);
    ret = dc_motor_initialize(&motor1);
    ret = dc_motor_initialize(&motor2);
    ret = lcd_4bit_initialize(&lcd1);
    ret = lcd_4bit_send_string_pos(&lcd1,1,7,"LM35 Test");
    __delay_ms(2000);
    //ret = lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    ret = lcd_4bit_send_string_pos(&lcd1,2,1,"Temp1:");
    ret = lcd_4bit_send_string_pos(&lcd1,3,1,"Temp2:"); 
    while(1){
        ret =  ADC_GetConversion_Blocking(&adc1,ADC_CHANNEL_AN0,&LM35_res1);
        ret =  ADC_GetConversion_Blocking(&adc1,ADC_CHANNEL_AN1,&LM35_res2);
        
        
        LM35_res1_Celsius_mv = LM35_res1* 4.88f; /*5000mv / 2^10 = 4.88 */
        LM35_res2_Celsius_mv = LM35_res2* 4.88f;
        
        LM35_res1_Celsius_mv /=10;
        LM35_res2_Celsius_mv /=10;
        
        ret =  convert_uint16_to_string(LM35_res1_Celsius_mv,LM35_res_1_txt);
        ret =  convert_uint16_to_string(LM35_res2_Celsius_mv,LM35_res_2_txt);
      
        ret = lcd_4bit_send_string_pos(&lcd1,2,7,LM35_res_1_txt);
        ret = lcd_4bit_send_string_pos(&lcd1,3,7,LM35_res_2_txt);    
      
        if(LM35_res1_Celsius_mv > 25){
            ret = dc_motor_move_left(&motor1); 
            led_turn_on(&Green_led);
           
        }
        else{
            ret = dc_motor_stop(&motor1); 
            led_turn_off(&Green_led);
            
        }
         if(LM35_res2_Celsius_mv > 25){
            ret = dc_motor_move_left(&motor2); 
            led_turn_on(&Red_led);
        }
        else{
            ret = dc_motor_stop(&motor2);
             led_turn_off(&Red_led);
        }
    }       
    return (EXIT_SUCCESS);
}  


void application_initialize(void){ 
    std_ReturnType ret = E_NOT_OK;
      ret = ADC_Init(&adc1);
      ecu_layer_initialize();
     
}
