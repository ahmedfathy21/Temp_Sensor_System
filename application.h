/* 
 * File:   application.h
 * Author: En.Ahmed
 *
 * Created on March 4, 2024, 7:46 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/*  section  : includes  */
#include"ECU_Layer/ECU_layer_init.h"
#include"MCAL_Layer/interrupt/mcal_external_interrupt.h"
#include"MCAL_Layer/EEPROM/hal_eeprom.h"
#include"MCAL_Layer/ADC/hal_adc.h"
#include"MCAL_Layer/Timer0/hal_timer0.h"
#include"MCAL_Layer/Timer1/hal_timer1.h"
#include"MCAL_Layer/Timer2/hal_timer2.h"
#include"MCAL_Layer/Timer3/hal_timer3.h"
#include"MCAL_Layer/CCP1/hal_ccp1.h"
#include"MCAL_Layer/usart/hal_usart.h"
#include"MCAL_Layer/SPI/HAL_SPI.h"
#include"MCAL_Layer/I2C/HAL_I2C.h"
/*section  : Macro Declarations */
//#define _XTAL_FREQ  8000000UL

/*section  : Macro function Declarations */


/*section  : Data Type Declarations  */
extern led_t led1; 
extern led_t led2; 
extern led_t led3; 
extern led_t led4; 
extern led_t led5; 
extern led_t led6; 
extern led_t led7; 
extern led_t led8; 
extern  button_t button1;
extern  button_t button2;

/*section  : function Declarations  */
void application_initialize(void);
void Int0_APP_ISR(void);

#endif	/* APPLICATION_H */

