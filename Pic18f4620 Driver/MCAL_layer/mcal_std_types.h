/* 
 * File:   mcal_std_types.h
 * Author: Home?
 *
 * Created on July 28, 2023, 10:54 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
/*section: includes */
#include "std_libraries .h"
#include "compiler .h"


/*section : macro functions declarations*/
/*section : data types declarations */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int long sint32;

typedef uint8    Std_ReturnType;

/*section :macro declarations */
#define STD_high          0x01
#define STD_LOW           0x00

#define CONFIG_ENABLE      0x01
#define CONFIG_DISABLE     0x00


#define  STD_ON           0x01
#define  STD_OFF          0x00

#define  STD_ACTIVE       0x01
#define  STD_IDLE         0x00  


#define  E_OK             (Std_ReturnType)0x01
#define  E_NOK            (Std_ReturnType)0x00

#define ZERO_INIT         0

#define  _XTAL_FREQ 8000000UL 
 

/*section : function declarations */
#endif	/* MCAL_STD_TYPES_H */

