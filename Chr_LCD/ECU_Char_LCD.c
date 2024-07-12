/* 
 * File:   ECU_Char_LCD.c
 * Author: En.Ahmed
 *
 * Created on April 19, 2024, 12:16 AM
 */

#include"ECU_Char_LCD.h"
static std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command);
static std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 coulmn);
static std_ReturnType  lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 coulmn);
/**
 * 
 * @param lcd
 * @return 
 */
std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
    std_ReturnType ret = E_OK ;
    uint8 l_data_pins_counter=0;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {      
        ret = gpio_pin_initialize(&lcd->lcd_rs);
        ret = gpio_pin_initialize(&lcd->lcd_en);
        for(l_data_pins_counter=0;l_data_pins_counter<4;l_data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
           } 
       __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
        }
    
    return ret;
 
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command){
    std_ReturnType ret = E_OK ;
    
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        ret = lcd_send_4bits(lcd,command >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd,command);
        ret = lcd_4bit_send_enable_signal(lcd);
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data){
    std_ReturnType ret = E_OK ;
    
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        ret = lcd_send_4bits(lcd,data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd,data);
        ret = lcd_4bit_send_enable_signal(lcd);
            
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param data
 * @return 
 */
std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 coulmn,uint8 data){
    
    std_ReturnType ret = E_OK ;
    
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = lcd_4bit_set_cursor(lcd,row,coulmn);
        ret = lcd_4bit_send_char_data(lcd,data);
            
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str){
    std_ReturnType ret = E_OK ;
    
    if((lcd == NULL)||(str== NULL)){
        ret = E_NOT_OK;
    }
    else 
    {
         while(*str){
            ret = lcd_4bit_send_char_data(lcd,*str++);
        }
            
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param str
 * @return 
 */
std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 coulmn,uint8 *str){
     std_ReturnType ret = E_OK ;
    
    if((lcd == NULL)||(str== NULL)){
        ret = E_NOT_OK;
    }
    else 
    {
       ret = lcd_4bit_set_cursor(lcd,row,coulmn);
             while(*str){
            ret = lcd_4bit_send_char_data(lcd,*str++);
        }
            
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param chr
 * @param mem_pos
 * @return 
 */
std_ReturnType lcd_4bit_send_custome_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 coulmn,const uint8 chr[],uint8 mem_pos){
     std_ReturnType ret = E_OK ;
     uint8 lcd_counter = ZERO_INIT;
             
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
         ret = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = 0;lcd_counter<8;lcd_counter++){
           ret = lcd_4bit_send_char_data(lcd,chr[lcd_counter]);
          }
        ret = lcd_4bit_send_char_data_pos(lcd,row,coulmn,mem_pos);
            
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @return 
 */
std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
     std_ReturnType ret = E_OK ;
     uint8 l_data_pins_counter =0;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_initialize(&lcd->lcd_rs);
        ret = gpio_pin_initialize(&lcd->lcd_en);
        for(l_data_pins_counter=0;l_data_pins_counter<8;l_data_pins_counter++){
            ret = gpio_pin_initialize(&lcd->lcd_data[l_data_pins_counter]);
           }   
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
        }
    
    return ret;
}


/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command){
     std_ReturnType ret = E_OK ;
     uint8 l_pins_counter =ZERO_INIT;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_write_logic(&lcd->lcd_rs,GPIO_LOW);
        for(l_pins_counter=ZERO_INIT;l_pins_counter<8;l_pins_counter++){
            ret =gpio_pin_write_logic(&(lcd->lcd_data[l_pins_counter]),(command >> l_pins_counter)&(uint8)0x01);
        }
            ret = lcd_8bit_send_enable_signal(lcd);
        }
    
    return ret;
}


/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data){
     std_ReturnType ret = E_OK ;
    uint8 l_pins_counter =ZERO_INIT;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
          ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
             for(l_pins_counter=ZERO_INIT;l_pins_counter<8;l_pins_counter++){
            ret =gpio_pin_write_logic(&(lcd->lcd_data[l_pins_counter]),(data >> l_pins_counter)&(uint8)0x01);
        }
            ret = lcd_8bit_send_enable_signal(lcd);
        }
        
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param data
 * @return 
 */
std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 coulmn,uint8 data){
     std_ReturnType ret = E_OK ;
    
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = lcd_8bit_set_cursor(lcd,row,coulmn);
          ret = lcd_8bit_send_char_data(lcd,data);
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str){
      std_ReturnType ret = E_OK ;
    
    if((lcd == NULL)||(str== NULL)){
        ret = E_NOT_OK;
    }
    else 
    {
        while(*str){
            ret = lcd_8bit_send_char_data(lcd,*str++);
        }
            
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param str
 * @return 
 */
std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 coulmn,uint8 *str){
     std_ReturnType ret = E_OK ;
    
    if((lcd == NULL)||(str== NULL)){
        ret = E_NOT_OK;
    }
    else 
    {
           ret = lcd_8bit_set_cursor(lcd,row,coulmn);
             while(*str){
            ret = lcd_8bit_send_char_data(lcd,*str++);
        }
        }
    
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @param chr
 * @param mem_pos
 * @return 
 */
std_ReturnType lcd_8bit_send_custome_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 coulmn,const uint8 chr[],uint8 mem_pos){
     std_ReturnType ret = E_OK ;
     uint8 lcd_counter = ZERO_INIT;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = lcd_8bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = 0;lcd_counter<8;lcd_counter++){
           ret = lcd_8bit_send_char_data(lcd,chr[lcd_counter]);
          }
        ret = lcd_8bit_send_char_data_pos(lcd,row,coulmn,mem_pos);
        }
    
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
std_ReturnType convert_uint8_to_string(uint8 value,uint8 *str){
     std_ReturnType ret = E_OK ;
    
    if(str== NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        memset(str,'\0',4);
        sprintf(str,"%i",value);    
        }
     return ret;
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
std_ReturnType convert_uint16_to_string(uint16 value,uint8 *str){
     std_ReturnType ret = E_OK ;
     uint8 Temp_String[6] = {0};
     uint8 DataCounter = 0;
    if(str== NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        memset(str,' ',6);
        str[5] = '\0';
        sprintf((char *)Temp_String,"%i",value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
            
        }
     return ret; 
}
/**
 * 
 * @param value
 * @param str
 */
std_ReturnType convert_uint32_to_string(uint32 value,uint8 *str){
     std_ReturnType ret = E_OK ;
    
    if(str== NULL){
        ret = E_NOT_OK;
    }
    else 
    {
       memset(str,'\0',11);
        sprintf(str,"%i",value);   
            
        }
      return ret; 
}
static std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command){
    std_ReturnType ret = E_OK ;
    ret =gpio_pin_write_logic(&(lcd->lcd_data[0]),(_data_command >> 0)&(uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[1]),(_data_command >> 1)&(uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[2]),(_data_command >> 2)&(uint8)0x01);
    ret =gpio_pin_write_logic(&(lcd->lcd_data[3]),(_data_command >> 3)&(uint8)0x01);
    return ret; 
}
static std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    std_ReturnType ret = E_OK ;
    ret =gpio_pin_write_logic(&lcd->lcd_en,GPIO_HIGH);
    __delay_ms(5);
    ret =gpio_pin_write_logic(&lcd->lcd_en,GPIO_LOW);
    
    return ret;
}

static std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    std_ReturnType ret = E_OK ;
   ret =gpio_pin_write_logic(&lcd->lcd_en,GPIO_HIGH);
    __delay_ms(5);
    ret =gpio_pin_write_logic(&lcd->lcd_en,GPIO_LOW);
    
    return ret;
}
static std_ReturnType  lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 coulmn){
    std_ReturnType ret = E_OK ;
    coulmn--;
    switch(row){
        case ROW1 : ret = ret = lcd_8bit_send_command(lcd, (0x80+coulmn));break;
        case ROW2 : ret = ret = lcd_8bit_send_command(lcd, (0xC0+coulmn));break;
        case ROW3 : ret = ret = lcd_8bit_send_command(lcd, (0x94+coulmn));break;
        case ROW4 : ret = ret = lcd_8bit_send_command(lcd, (0xd4+coulmn));break;
    }
    
    return ret;
}
static std_ReturnType  lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 coulmn){
    std_ReturnType ret = E_OK ;
    coulmn--;
    switch(row){
        case ROW1 : ret = ret = lcd_4bit_send_command(lcd, (0x80+coulmn));break;
        case ROW2 : ret = ret = lcd_4bit_send_command(lcd, (0xC0+coulmn));break;
        case ROW3 : ret = ret = lcd_4bit_send_command(lcd, (0x94+coulmn));break;
        case ROW4 : ret = ret = lcd_4bit_send_command(lcd, (0xd4+coulmn));break;
    }
    
    return ret;
}