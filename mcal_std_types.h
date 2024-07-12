    /* 
 * File:   mcal_std_types.h
 * Author: En.Ahmed
 *
 * Created on March 4, 2024, 7:20 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/*  section  : includes  */
#include"std_libraries.h"
#include"compiler.h" 
 




/*section  : Macro function Declarations */

/*section  : Data Type Declarations  */
typedef  unsigned char    uint8;
typedef  unsigned short  uint16;
typedef  unsigned int    uint32;
typedef  signed char      sint8;
typedef  signed short    sint16;
typedef  signed int      sint32;



typedef  uint8    std_ReturnType;

#define _XTAL_FREQ  4000000UL


/*section  : Macro Declarations */

#define STD_HIGH      0X01
#define STD_LOW       0X00

#define STD_ON        0x01
#define Std_OFF       0x00

#define STD_ACTIVE    0x01
#define STD_IDLE      0x00

#define E_OK       (std_ReturnType)0x01
#define E_NOT_OK   (std_ReturnType)0x00 
 
#define ZERO_INIT    0

/*section  : function Declarations  */





#endif	/* MCAL_STD_TYPES_H */

