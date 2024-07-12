/* 
 * File:   Application.c
 * Author: En.Ahmed
 *
 * Created on March 4, 2024, 6:40 PM
 */
#include"hal_gpio.h"
volatile uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
/**
 * @brief initialize the direction of a specific pin @ref  direction_t
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @return status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1 ){
         ret = E_NOT_OK;   
    }
            switch(_pin_config->direction){
           case GPIO_DIRECTION_OUTPUT:
               CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
               break;
           case GPIO_DIRECTION_INPUT:
               SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
               
               
               break;
               default : ret = E_NOT_OK;
    }
    
   
    
   return ret; 
}
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @param direction_status
 * @return status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config,direction_t *direction_status){
    std_ReturnType ret = E_OK;
    if ((NULL == _pin_config)||(NULL == direction_status) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1)){
         ret = E_NOT_OK;   
    }
    else{
       *direction_status = READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
        
        
    }
     
    
    
    return ret;
}
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @param logic
 * @return status of the function
 *            E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic){
     std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;   
    }
    switch (logic){
        case GPIO_LOW  :
            CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
            break;
        case GPIO_HIGH :
            SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
            break;
        default : ret = E_NOT_OK;
        
    }
    
    
    return ret;
    
}
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @param logic
 * @return status of the function
 *            E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic){
     std_ReturnType ret = E_OK;
   if ((NULL == _pin_config)||(NULL == logic) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1)){
         ret = E_NOT_OK;   
    }
   else{
       *logic = READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
   }
     
    
    
    
    return ret;
    
}
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @return status of the function
 *            E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
     std_ReturnType ret = E_OK;
     if (NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;   
    }   
     else{
         TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
     }
    
    
    return ret;
    
}
#endif
/**
 * 
 * @param port
 * @param deirection
 * @return status of the function
 *            E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
     if (NULL == _pin_config){
         ret = E_NOT_OK;   
    }   
     else{
        ret =  gpio_pin_direction_initialize(_pin_config);
        ret =  gpio_pin_write_logic(_pin_config,_pin_config->logic);
     }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param deirection
 * @return  status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */


#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_port_direction_initialize(port_index_t port,uint8 deirection){
     std_ReturnType ret = E_OK;
     if(port>PORT_MAX_NUMBER-1){
         ret = E_NOT_OK;
     }
     else{
         *tris_registers[port]= deirection;
     }
    return ret;
    
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return  status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 *direction_status){
     std_ReturnType ret = E_OK;
     if ((NULL == direction_status) || (port > PORT_MAX_NUMBER-1) ){
         ret = E_NOT_OK;   
    }
     else{
         *direction_status = *tris_registers[port];
     }
    
    
    return ret;
    
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return  status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic){
     std_ReturnType ret = E_OK;
     if(port > PORT_MAX_NUMBER-1){
         ret = E_NOT_OK;
     }
     else{
         *lat_registers[port] = logic;
     }
    
    
    
    return ret;
    
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return  status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic){
     std_ReturnType ret = E_OK;
      if ((NULL == logic) || (port > PORT_MAX_NUMBER-1)){
         ret = E_NOT_OK;   
    }
      else{
          *logic= *lat_registers[port];
      }
    
    
    
    return ret;
    
}
#endif
/**
 * 
 * @param port
 * @return  status of the function
 *           E_OK  : function done successfully 
 *         E_NOT_OK : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
std_ReturnType gpio_port_toggle_logic(port_index_t port){
     std_ReturnType ret = E_OK;
     if (port > PORT_MAX_NUMBER-1){
         ret = E_NOT_OK;   
    }
     else{
         *lat_registers[port] ^=PORTC_MASK;
     }
    
    
    return ret;
    
}
#endif