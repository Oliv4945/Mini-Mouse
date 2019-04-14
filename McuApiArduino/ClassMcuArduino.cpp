/*
 __  __ _       _                                 
 |  \/  (_)     (_)                                
 | \  / |_ _ __  _ _ __ ___   ___  _   _ ___  ___  
 | |\/| | | '_ \| | '_ ` _ \ / _ \| | | / __|/ _ \
 | |  | | | | | | | | | | | | (_) | |_| \__ \  __/ 
 |_|  |_|_|_| |_|_|_| |_| |_|\___/ \__,_|___/\___| 
                                                   
                                                   
Description       : Flash Api.  


License           : Revised BSD License, see LICENSE.TXT file include in the project

Maintainer        : Fabien Holin (SEMTECH)
*/
#include "Arduino.h"
#include "SPI.h"
#include "ClassMcuArduino.h"
#include "stdint.h"
#include "ApiMcu.h"
#include "time.h"
#include "UserDefine.h"
#include "Define.h"

#if DEBUG_TRACE == 1
    #include <stdarg.h>
    #include <string.h>
#endif

// TODO: Arduino
#define WATCH_DOG_PERIOD_RELEASE 30 // this period have to be lower than the Watch Dog period of 32 seconds







/********************************************************************/
/*                    SystemClock_Config functions                  */
/********************************************************************/


/********************************************************************/
/*                           Flash local functions                  */
/********************************************************************/
// TODO: Arduino


uint32_t FLASH_If_Erase(uint32_t bank_active)
{
    // TODO: Arduino
}

/**
  * @brief  This function does an CRC check of an application loaded in a memory bank.
  * @param  start: start of user flash area
  * @retval FLASHIF_OK: user flash area successfully erased
  *         other: error occurred
  */
uint32_t FLASH_If_Check(uint32_t start)
{
// TODO: Arduino
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  destination: start address for target location
  * @param  p_source: pointer on buffer with data to write
  * @param  length: length of data buffer (unit is 32-bit word)
  * @retval uint32_t 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(uint32_t destination, uint32_t *p_source, uint32_t length)
{
    // TODO: Arduino
}

/**
  * @brief  Configure the write protection status of user flash area.
  * @retval uint32_t FLASHIF_OK if change is applied.
  */
uint32_t FLASH_If_WriteProtectionClear( void ) {
    // TODO: Arduino
}
/**
  * @brief  Modify the BFB2 status of user flash area.
  * @param  none
  * @retval HAL_StatusTypeDef HAL_OK if change is applied.
  */
/*
// TODO: Arduino
HAL_StatusTypeDef FLASH_If_BankSwitch(void)
{
}
*/



void FlashPageErase( uint32_t page, uint32_t banks )
{
    // TODO: Arduino
}

uint8_t EepromMcuWriteBuffer( uint32_t addr, uint8_t *buffer, uint16_t size )
{   
    // TODO: Arduino
}

uint8_t EepromMcuReadBuffer( uint32_t addr, uint8_t *buffer, uint16_t size )
{
    // TODO: Arduino
}

void EepromMcuSetDeviceAddr( uint8_t addr )
{
    // TODO: Arduino
    // assert_param( FAIL );
}

uint8_t EepromMcuGetDeviceAddr( void )
{
    // TODO: Arduino
    // assert_param( FAIL );
    return 0;
}


/********************************************************************/
/*                         Wake Up local functions                  */
/********************************************************************/



/*!
* WakeUpAlarmMSecond : Configures the application wake up timer with a delay duration in ms
 * When the timer expires , the rtc block generates an It to wake up the Mcu 
 * \remark this function is not used by the LoRaWAN object, only provided for application purposes.
 * \param [IN]  int delay in ms
 * \param [OUT] void         
 */

void WakeUpAlarmMSecond ( int delay) {
    // TODO: Arduino 1
}
/*!
* WakeUpAlarmMecond : Configure the wake up timer with a delay duration in second
 * \remark this function is not used by the LoRaWAN object, only provided for application purposes.
 * When the timer expires , the rtc block generates an It to wake up the Mcu 
 * 
 * \param [IN]  int delay in s
 * \param [OUT] void         
 */
void WakeUpAlarmSecond ( int delay) {
    // TODO: Arduino 1
}


/*************************************************************/
/*           Mcu Object Definition Constructor               */
/*************************************************************/
McuArduino::McuArduino(PinName mosi, PinName miso, PinName sclk )  {
    Func = DoNothing; // don't modify
    obj = NULL;       // don't modify
    McuMosi = mosi;   // don't modify
    McuMiso = miso;   // don't modify
    McuSclk = sclk;   // don't modify
}     


McuArduino::~McuArduino(){
      // to be completed by mcu providers
} 

/*******************************************/
/*                  Mcu Init               */
/*******************************************/
void McuArduino::InitMcu( void ) {
    // system clk Done with mbed to be completed by mcu providers if mbed is removed
      /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    InitGpio( );
    UartInit();
    InitSpi () ;
    RtcInit ();
}

/*******************************************/
/*            GPIO Init                    */
/*******************************************/
void McuArduino::InitGpio ( ) {
    pinMode( LORA_CS, OUTPUT );
    if ( LORA_RESET != NULL ) {
        pinMode( LORA_RESET, OUTPUT );
    }
}


void McuArduino::SetValueDigitalOutPin ( PinName Pin, int Value ) {
    if ( Pin != NULL ) {
        digitalWrite( Pin, Value );
    }
}


int McuArduino::GetValueDigitalInPin ( PinName Pin ) {
    if ( Pin != NULL ) {
        return digitalRead( Pin );
    } else {
        return 0;
    }
}


void McuArduino::Init_Irq ( PinName pin) {
    pinMode( pin, INPUT );
} 
  
/******************************************************************************/
/*                                Mcu Spi Api                                 */
/******************************************************************************/
    /** Create a SPI master connected to the specified pins
    *
    *  @param mosi SPI Master Out, Slave In pin
    *  @param miso SPI Master In, Slave Out pin
    *  @param sclk SPI Clock pin
    */

void McuArduino::InitSpi ( ){
    SPI.begin();
}


    
/** Write to the SPI Slave and return the response
*
*  @param value Data to be sent to the SPI slave
*
*  @returns
*    Response from the SPI slave
*/
uint8_t McuArduino::SpiWrite(int value){
    
    uint8_t rxData = 0;

    // TODO: Arduino - Check if there is two transactions

    /*
    while( LL_SPI_IsActiveFlag_TXE ( SPI1 ) == 0  ){};
    LL_SPI_TransmitData8 (SPI1, uint8_t (value&0xFF));
    while( LL_SPI_IsActiveFlag_RXNE ( SPI1 ) == 0 ){};
    rxData =  LL_SPI_ReceiveData8( SPI1 );
    return (rxData);
    */

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    rxData = SPI.transfer(value);
    SPI.endTransaction();
}


/******************************************************************************/
/*                                Mcu Flash Api                               */
/******************************************************************************/
int McuArduino::RestoreContext(uint8_t *buffer, uint32_t addr, uint32_t size){
     /* have to be implemented by mcu providers
    the following code propose a lite implementation without any error cases*/
    uint16_t sizet = size & 0xFFFF;
    EepromMcuReadBuffer( addr, buffer, sizet );
    return ( 0 );
}
static uint8_t copyPage [2048] ;
int McuArduino::WriteFlashWithoutErase(uint8_t *buffer, uint32_t addr, uint32_t size){
    // TODO: Arduino
    return ( 0 ); 
}



int McuArduino::StoreContext(const void *buffer, uint32_t addr, uint32_t size){
    // TODO: Arduino
    return ( 0 ); 
} 
   


/******************************************************************************/
/*                                Mcu RTC Api                                 */
/******************************************************************************/
void McuArduino::RtcInit (void)
{
    // TODO: Arduino
}

uint32_t McuArduino::RtcGetTimeMs( void )
{
    return millis();
}

uint32_t McuArduino::RtcGetTimeSecond( void )
{
    return millis()/1000;
}



/******************************************************************************/
/*                           Mcu Uart Api                                     */
/******************************************************************************/
static int uart_putchar (char c, FILE *)
{
    Serial.write(c) ;
    return 0 ;
}

void hal_printf_init() {
    // create a FILE structure to reference our UART output function
    static FILE uartout;
    memset(&uartout, 0, sizeof(uartout));

    // fill in the UART file descriptor with pointer to writer.
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

    // The uart is the standard output device STDOUT.
    stdout = &uartout ;
}

void McuArduino::UartInit ( void ) {
    // TODO - Arduino: In main only ? Serial.begin();
};

void McuArduino::MMprint( const char *fmt, ...){
#if DEBUG_TRACE == 1
  va_list argp;
  va_start(argp, fmt);
  // TODO - Arduino: Implement ? vprint(fmt, argp);
  va_end(argp);
#endif
};

void sleepAndWakeUp (void) {
    // TODO - Arduino
}


void sleepAndWakeUpCool (void) {
    // TODO - Arduino
}
/******************************************************************************/
/*                                Mcu Sleep Api                               */
/******************************************************************************/
void McuArduino::GotoSleepSecond (int duration ) {
#if LOW_POWER_MODE == 1
    int cpt = duration ;
    while ( cpt > ( WATCH_DOG_PERIOD_RELEASE ) ) {
        cpt -= WATCH_DOG_PERIOD_RELEASE ;
        WakeUpAlarmSecond( WATCH_DOG_PERIOD_RELEASE );
        sleepAndWakeUp();
        WatchDogRelease ( );
    }
    WakeUpAlarmSecond( cpt );
    sleepAndWakeUp();
# else
    int cpt = duration ;
    WatchDogRelease ( );
    while ( cpt > ( WATCH_DOG_PERIOD_RELEASE ) ) {
        cpt -= WATCH_DOG_PERIOD_RELEASE ;
        mwait( WATCH_DOG_PERIOD_RELEASE );
        WatchDogRelease ( );
    }
    mwait( cpt );
    WatchDogRelease ( );
#endif
}

void McuArduino::GotoSleepMSecond (int duration ) {
#if LOW_POWER_MODE == 1
    WakeUpAlarmMSecond ( duration );
    sleepAndWakeUpCool();
    WatchDogRelease ( );
# else
    mwait_ms ( duration ) ;
    WatchDogRelease ( );
#endif
}


/******************************************************************************/
/*                             Mcu WatchDog Api                               */
/******************************************************************************/

/*!
 * Watch Dog Init And start with a period befor ereset set to 32 seconds
*/
void McuArduino::WatchDogStart ( void ) {
    // TODO - Arduino
}
/*!
 * Watch Dog Release
*/
void McuArduino::WatchDogRelease ( void ) {
    // TODO - Arduino
};
/******************************************************************************/
/*                             Mcu LOwPower timer Api                         */
/******************************************************************************/
void McuArduino::LowPowerTimerLoRaInit ( ) {
    // TODO: Arduino
};

/*!
 * LowPowerTimerLoRa AttachMsecond
 *
 * \param void (* _Func) (void *) a static method member of the current Obj
 * \param *_obj a pointer to the current objet
 * \param int delay in ms delay should be between 1ms and 16s.
 * \param [OUT] void         
 * \remark the code  Func =  _Func ; and obj  = _obj; isn't mcu dependent
 * \remark starts the LoRaWAN dedicated timer and attaches the IRQ to the handling Interupt SErvice Routine in the LoRaWAN object.
 */
void McuArduino::StartTimerMsecond ( void (* _Func) (void *) , void * _obj, int delay){
    // TODO: Arduino
};


void  McuArduino::AttachInterruptIn(  void (* _Funcext) (void *) , void * _objext) {
    // TODO - Arduino 1
    // attachInterrupt(digitalPinToInterrupt((_objext), _Funcext, RISING);
};
