/* 
 * File:   hal_gpio.h
 * Author: En.Ahmed
 *
 * Created on March 4, 2024, 7:25 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H 

/*  section  : includes  */

#include"pic18f4620.h"
#include"../mcal_std_types.h"
#include"../device_config.h"
#include"hal_gpio_cfg.h"
/*section  : Macro Declarations */
#define BIT_MASK   (uint8)1

#define PORT_PIN_MAX_NUMBER    8
#define PORT_MAX_NUMBER        5

#define PORTC_MASK          0xFF
/*section  : Macro function Declarations */
#define HWREG8(_x)   (*((volatile uint8 *)(_x)))
#define SET_BIT(REG,BIT_POSN)       (REG |= (BIT_MASK<<BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)     (REG &=~ (BIT_MASK<<BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)    (REG ^= (BIT_MASK<<BIT_POSN))
#define READ_BIT(REG,BIT_POSN)      ((REG >> BIT_POSN) &BIT_MASK)

/*section  : Data Type Declarations  */
typedef enum{
    GPIO_LOW,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT=0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7  
}pin_index_t;

typedef enum{
    PORTA_INDEX=0,
    PORTB_INDEX,         
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}port_index_t;

typedef struct{
    uint8 port : 3;     /*@ref port_index_t */
    uint8 pin  : 3;     /* @ref pin_index_t*/
    uint8 direction : 1;/* @ref direction_t*/
    uint8 logic : 1;    /* @ref logic_t*/
}pin_config_t;
/*section  : function Declarations  */
std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config,direction_t *direction_status);
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic);
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic);
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);

std_ReturnType gpio_port_direction_initialize(port_index_t port,uint8 deirection);
std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 *direction_status);
std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic);
std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic);
std_ReturnType gpio_port_toggle_logic(port_index_t port);



#endif	/* HAL_GPIO_H */

