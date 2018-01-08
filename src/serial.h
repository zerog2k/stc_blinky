/*--------------------------------------------------------------------------------*/
/* --- STC MCU International Limited -----------------------------------*/
/* --- STC 15 Series I/O simulate serial port ----------------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the */
/* article, please specify in which data and procedures from STC */
/*-------------------------------------------------------------------------------*/

void UART_INIT(void);
void _tm1() __interrupt 3 __using 1;
#ifndef PLATFORMIO
void putchar(unsigned char);
#endif
#define uart_put_char putchar
#define _putchar putchar
