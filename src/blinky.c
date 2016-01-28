//
// STC15F204EA blinky example
// inspired by http://jjmz.free.fr/?p=179 http://jjmz.free.fr/?p=191
// and stc15f204ea datasheet
//

#include <stc12.h>
#include <stdint.h>
#include <stdio.h>
#include "ds1302.h"

/* ------------------------------------------------------------------------- */
/* Printing functions */
/* ------------------------------------------------------------------------- */

#include "./soft_serial/serial.h"
#define printf printf_fast     // see sdcc user guide

// P0.1 called P5.5 on my board?
#define LED P1_6     

/* ------------------------------------------------------------------------- */

// counter
int temp = 0;

struct ds1302_rtc rtc;

void _delay_ms(unsigned char ms)
{	
    // i,j selected for fosc 11.0592MHz, using oscilloscope
    // the stc-isp tool gives inaccurate values (perhaps for C51 vs sdcc?)
    // max 255 ms
    unsigned char i, j;
    do {
    	i = 4;
    	j = 200;
    	do
    	{
    		while (--j);
    	} while (--i);
    } while (--ms);
}

const char* startstring = "\nSTC15F204EA starting up...\n";
uint8_t i, b;

struct ram_config config;

//struct ram_config config;

int main()
{
    /* init the software uart */
    UART_INIT();

    /* simple greeting message */
    printf("%s", startstring);
    
    LED = 1;
    

    ds_init();
    
    // intentionally corrupt magic bytes to test initialization
    // ds_writebyte(DS_CMD_RAM >> 1 | 0x01, 0x22);
    
    ds_ram_config_init((uint8_t *) &config);    
    
    /*
    // setup some test values
    config.temp_F_C = 1;
    config.temp_cal = 4;
    config.alarm_on = 1;
    config.chime_hour_start = 10;
    config.chime_hour_stop = 20;
    */
    
    while(1)
    {                
        LED = 0;
		_delay_ms(250);
        
        //LED = 1;
        //_delay_ms(100);
        //LED = 0;
        //_delay_ms(100);
        
        LED = 1;        
        _delay_ms(250);
        _delay_ms(250);
        _delay_ms(250);
        
        ds_readburst((uint8_t *) &rtc); // read rtc        
                
        printf("counter: %d \n", temp);
        printf("yy mm dd hh mm ss am/pm 24/12 ww \n%d%d %d%d %d%d %d%d %d%d %d%d     %d     %d  %d\n",
            rtc.tenyear, rtc.year, rtc.tenmonth, rtc.month, rtc.tenday, rtc.day, rtc.h12.tenhour, rtc.h12.hour, 
            rtc.tenminutes, rtc.minutes, rtc.tenseconds, rtc.seconds, rtc.h12.pm, rtc.h12.hour_12_24, rtc.weekday);
        printf("ram: ");
        for (i=0; i<8; i++) {
            printf("%02x ", ds_readbyte( DS_CMD_RAM >> 1 | i));
        } 
  
        config.hour_12_24 = rtc.h12.hour_12_24;
        
        printf("\nconfig: hour_12_24=%d, temp_F_C=%d, alarm_on=%d, alarm_hour=%d, alarm_minute=%d\n", 
                config.hour_12_24, config.temp_F_C, config.alarm_on, config.alarm_hour, config.alarm_minute);
        printf("chime_on=%d, chime_hour_start=%d, chime_hour_stop=%d, temp_cal=%d\n\n",
                config.chime_on, config.chime_hour_start, config.chime_hour_stop, config.temp_cal);
        
        ds_ram_config_write((uint8_t *) &config);
        _delay_ms(250);
        _delay_ms(250);        
        temp++;
        WDT_CONTR |= 1 << 4; // clear wdt
    }
}
/* ------------------------------------------------------------------------- */
