/* 
 * File:   ECU_DC_MOTOR.h
 * Author: En.Ahmed
 *
 * Created on April 13, 2024, 6:09 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/*  section  : includes  */
#include"ECU_DC_MOTOR_CFG.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

/*section  : Macro Declarations */
#define DC_MOTOR_ON_STATUS    0x01U
#define DC_MOTOR_OFF_STATUS   0x00U


#define DC_MOTOR_PIN1  0x00U
#define DC_MOTOR_PIN2  0x01U

/*section  : Macro function Declarations */



/*section  : Data Type Declarations  */
typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/*section  : function Declarations  */
std_ReturnType  dc_motor_initialize(const dc_motor_t * dc_motor);
std_ReturnType  dc_motor_move_right(const dc_motor_t * dc_motor);
std_ReturnType  dc_motor_move_left(const dc_motor_t * dc_motor);
std_ReturnType  dc_motor_stop(const dc_motor_t * dc_motor);

#endif	/* ECU_DC_MOTOR_H */

