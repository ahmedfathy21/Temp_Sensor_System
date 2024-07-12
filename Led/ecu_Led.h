/* 
 * File:   ecu_Led.h
 * Author: En.Ahmed
 *
 * Created on March 4, 2024, 7:42 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*  section  : includes  */
#include"../../MCAL_Layer/Gpio/hal_gpio.h"
#include"ecu_led_cfg.h"


/*section  : Macro Declarations */



/*section  : Macro function Declarations */


/*section  : Data Type Declarations  */
typedef enum{
    LED_OFF,
    LED_ON        
}led_status_t;
typedef struct{
    uint8 port_name  : 4;
    uint8 pin        : 3;
    uint8 led_status : 1;
}led_t;

/*section  : function Declarations  */
std_ReturnType led_initialize(const led_t * led);     
std_ReturnType led_turn_on(const led_t * led);     
std_ReturnType led_turn_off(const led_t * led);     
std_ReturnType led_turn_toggle(const led_t * led);     

#endif	/* ECU_LED_H */

