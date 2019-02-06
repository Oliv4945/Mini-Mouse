#include "ApiMcu.h"
#include "Define.h"
#include "PointToPointReceiver.h"
#include "PointToPointTransmitter.h"
#include "RadioPlaner.h"
#include "UserDefine.h"
#include "appli.h"
#include "main.h"
#include "sx1276.h"
#include "utilities.h"
#include "LoraMacDataStoreInFlash.h"
#include "LoraWanProcess.h"
#include "Define.h"
#include "utilities.h"
#include "UserDefine.h"
#include "appli.h"
#include "SX126x.h"
#include "ApiMcu.h"
#include "utilities.h"
#include "main.h"
#include "UserDefine.h"
#include "ApiMcu.h"
#include "RadioPlaner.h"
#include "Sensor.h"
#define MAX_PAYLOAD_RECEIVED 255
#define TX_ON_RX3_ID              0
#define LP_HOOK_ID                1
#define POINT_TO_POINT_TX_HOOK_ID 2
#define POINT_TO_POINT_RX_HOOK_ID 3
#define FW_VERSION 18
#define PERIOD_STATUS 100
#define WAKEUPDURATION 600 
Relay         relay;
#ifndef RELAY
LSM303H_ACC Accelero       ( PA_3 );
#endif
#define FileId 4
int16_t RxcSnr ;
int16_t RxcRssi ;
uint32_t PeriodicSchedule ; 
uint8_t UserTxPeriodicPayload [125];
uint8_t UserTxPeriodicPayloadSize;
uint8_t UserRxPayload [125];
uint8_t UserRxPayloadSize;

void PrintPtpStatistics(const StatisticCounters_t* stats,
                        const uint16_t counter);


void CallBackTxOnRx3 ( void * RadioPlanerIn) {
}

int mainPtPRxTx( void ) {
uint8_t LoRaMacNwkSKeyInit[]      = { 0x22, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
uint8_t LoRaMacAppSKeyInit[]      = { 0x11, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22};
uint8_t LoRaMacAppKeyInit[]       = { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xBB};
uint8_t AppEuiInit[]              = { 0x70, 0xb3, 0xd5, 0x7e, 0xd0, 0x00, 0xff, 0x50 };
int i;
uint8_t UserFport ;
uint8_t UserRxFport ; 

#ifdef RELAY
    uint32_t LoRaDevAddrInit            = 0x260114FC;
    uint8_t DevEuiInit[]              = { 0x38, 0x35, 0x31, 0x31, 0x18, 0x47, 0x37, 0x57 };    
    sLoRaWanKeys  LoraWanKeys  = { LoRaMacNwkSKeyInit, LoRaMacAppSKeyInit, LoRaMacAppKeyInit, AppEuiInit, DevEuiInit, LoRaDevAddrInit,OTA_DEVICE };
#else
    
    uint8_t  DevEuiInit2[]              = { 0x38, 0x35, 0x31, 0x31, 0x18, 0x47, 0x37, 0x51 };
    uint32_t LoRaDevAddrInit = 0x26011695;
    sLoRaWanKeys  LoraWanKeys  = { LoRaMacNwkSKeyInit, LoRaMacAppSKeyInit, LoRaMacAppKeyInit, AppEuiInit, DevEuiInit2, LoRaDevAddrInit,OTA_DEVICE };
#endif

mcu.InitMcu();

#ifdef SX126x_BOARD
    #define FW_VERSION     0x18
    SX126x  RadioUser( LORA_BUSY, LORA_CS, LORA_RESET,TX_RX_IT );
    RadioPLaner < SX126x > RP( &RadioUser );
    LoraWanObject<LoraRegionsEU,SX126x> Lp ( LoraWanKeys,&RP,USERFLASHADRESS); 
#endif
#ifdef SX1276_BOARD
    SX1276  RadioUser( LORA_CS, LORA_RESET, TX_RX_IT, RX_TIMEOUT_IT);
    RadioPLaner < SX1276 > RP( &RadioUser );
    LoraWanObject<LoraRegionsEU,SX1276> Lp ( LoraWanKeys,&RP,USERFLASHADRESS); 
#endif
#ifdef SX1272_BOARD
    #define FW_VERSION     0x13
    SX1272  RadioUser( LORA_CS, LORA_RESET, TX_RX_IT, RX_TIMEOUT_IT);
    RadioPLaner < SX1272 > RP( &RadioUser );
    LoraWanObject<LoraRegionsEU,SX1272> Lp ( LoraWanKeys,&RP,USERFLASHADRESS); 
#endif

PointToPointReceiver    ptpRx(&RP, POINT_TO_POINT_RX_HOOK_ID);
PointToPointTransmitter ptpTx(&RP, POINT_TO_POINT_TX_HOOK_ID);

RP.InitHook ( LP_HOOK_ID , &(Lp.packet.Phy.CallbackIsrRadio), &(Lp.packet.Phy) );
RP.InitHook ( POINT_TO_POINT_RX_HOOK_ID, &(PointToPointReceiver::Callback ),reinterpret_cast<void*>(&ptpRx));
RP.InitHook ( POINT_TO_POINT_TX_HOOK_ID, &(PointToPointTransmitter::Callback ),reinterpret_cast<void*>(&ptpTx));
RP.InitHook ( TX_ON_RX3_ID, &CallBackTxOnRx3, reinterpret_cast <void * > (&RP) );

DEBUG_MSG("Init  Done\n");
uint8_t AvailableRxPacket  = NO_LORA_RXPACKET_AVAILABLE ;
eLoraWan_Process_States LpState = LWPSTATE_IDLE;  
mcu.MMClearDebugBufferRadioPlaner ( );

UserFport       = 3;
uint8_t UserPayloadSizeClassA = 14;
uint8_t UserPayloadClassA [ 250 ];
for (int i = 0 ; i < UserPayloadSizeClassA ; i++ ) { UserPayloadClassA [i]= i; }
UserPayloadClassA [ 0 ]  = FW_VERSION ;
mcu.MMClearDebugBufferRadioPlaner ( );


#ifdef RELAY
    SStatisticRP  PowerStat;
    STask         Tx4Rx3Task;
    uint8_t payload_received[MAX_PAYLOAD_RECEIVED] = { 0x00 };
    uint8_t payload_received_size                  = 0;
    bool SendDevaddrStatus                         = true;
    bool SendDevEuiStatus                          = false;
    Tx4Rx3Task.HookId                              = TX_ON_RX3_ID;
    Tx4Rx3Task.TaskDuration                        = 200; // tbupdated with Timeonair
    Tx4Rx3Task.State                               = TASK_SCHEDULE;
    Tx4Rx3Task.TaskType                            = TX_LORA;
    uint8_t StatusFport                            = 4;
    bool JoinOnGoing                               = false;
    uint8_t toggle                                 = 1;
    int cpt                                        = 200;
    uint8_t MsgTypeClassA                          = UNCONF_DATA_UP;
    uint32_t RxAppTime                             = 0;
    uint8_t CurrentJoinDevEui[8];
    memset( CurrentJoinDevEui , 0 ,8);
    Lp.Init ();
    RadioUser.Sleep( true );
    mcu.GotoSleepMSecond ( 100 );
    Lp.SetDataRateStrategy ( MOBILE_LOWPER_DR_DISTRIBUTION );
    Lp.NewJoin();
    //Lp.RestoreContext  ( ); // to ReStore lorawan context from flash  and so avoid rejoin
    relay.AddDevaddrInWhiteList(0x26011695); 
    //relay.AddDevEuiInJoinWhiteList(DevEuiInit2);   
    while ( ( Lp.IsJoined ( ) == NOT_JOINED ) && ( Lp.GetIsOtaDevice ( ) == OTA_DEVICE) ) {   
        LpState  = Lp.Join( mcu.RtcGetTimeMs() + 200 );
        while ( ( LpState != LWPSTATE_IDLE ) && ( LpState != LWPSTATE_ERROR ) && ( LpState != LWPSTATE_INVALID ) ) {
            LpState = Lp.LoraWanProcess( &AvailableRxPacket );
            mcu.GotoSleepMSecond ( 400 );
            mcu.WatchDogRelease  ( );
        }
        mcu.GotoSleepMSecond ( 3000 );
    } 
    // At this step Join is done
    DEBUG_MSG("Join Done\n");
    ptpRx.Start(payload_received, &payload_received_size); // Start Cad Reception
    while(1) {
        uint8_t DevOrDevEui[8];
        uint8_t DevAddrOrDevEUILength;
        uint32_t Freq4RX3;
        ptpRx.GetRxPayload ( UserPayloadClassA, &UserPayloadSizeClassA, &RxAppTime, &DevOrDevEui[0], &DevAddrOrDevEUILength,&Freq4RX3 );
        if ( UserPayloadSizeClassA > 0 ) {
            DEBUG_PRINTF ( "Lengthdev  = %d \n",DevAddrOrDevEUILength );
            if (DevAddrOrDevEUILength == 4) { // CAse not a join 
                uint32_t ReceiveDevaddr = (DevOrDevEui [0] << 24) + ( DevOrDevEui [1] << 16 )+ ( DevOrDevEui [2] << 8 )+ DevOrDevEui [3] ;
                DEBUG_PRINTF ( "Lengthdev  = %d , dev addr = %x\n",DevAddrOrDevEUILength,ReceiveDevaddr );
                if ( relay.IsWhiteListedDevaddr(ReceiveDevaddr) == YES ) { 
                    DEBUG_PRINTF ( "devaddr = %x\n", ReceiveDevaddr);
                    LpState  = Lp.SendPayload( UserFport, UserPayloadClassA, UserPayloadSizeClassA, MsgTypeClassA , mcu.RtcGetTimeMs () + 200 );
                    relay.SetConfigForRx3 ( RxAppTime , ReceiveDevaddr, Freq4RX3);
                    cpt = 110;
                    SendDevaddrStatus = false ;
                    SendDevEuiStatus = false;
                }
            } else { // case join
                LpState  = Lp.SendPayload( UserFport, UserPayloadClassA, UserPayloadSizeClassA, MsgTypeClassA , mcu.RtcGetTimeMs () + 200 );
                relay.SetConfigForRx3 ( RxAppTime , DevOrDevEui, Freq4RX3);
                cpt = 110;
                SendDevaddrStatus = false ;
                SendDevEuiStatus = false;
                memcpy (CurrentJoinDevEui, DevOrDevEui, 8);
                JoinOnGoing = true;
            }
        } else if ( SendDevaddrStatus == true ){
            relay.builStatus( UserPayloadClassA, &UserPayloadSizeClassA );
            LpState  = Lp.SendPayload( StatusFport, UserPayloadClassA, UserPayloadSizeClassA, MsgTypeClassA , mcu.RtcGetTimeMs () + 2000 );
            cpt = 0;
            toggle = 1; 
            SendDevaddrStatus = false ;
        } else if  ( SendDevEuiStatus == true ) {
            cpt = 0 ;
            toggle = 0;
            relay.buildJoinStatus( UserPayloadClassA, &UserPayloadSizeClassA, RP.GetStatistic() );
            LpState  = Lp.SendPayload( StatusFport+1, UserPayloadClassA, UserPayloadSizeClassA, MsgTypeClassA , mcu.RtcGetTimeMs () + 2000 );
            SendDevEuiStatus = false;
        }
        while ( ( LpState != LWPSTATE_IDLE ) && ( LpState != LWPSTATE_ERROR ) && ( LpState != LWPSTATE_INVALID ) ) {
            LpState = Lp.LoraWanProcess( &AvailableRxPacket );
            mcu.GotoSleepMSecond ( 200 );
            mcu.WatchDogRelease  ( );
        }
        if ( AvailableRxPacket != NO_LORA_RXPACKET_AVAILABLE ) { 
            AvailableRxPacket  = NO_LORA_RXPACKET_AVAILABLE ;
            InsertTrace ( __COUNTER__, FileId );
            Lp.ReceivePayload( &UserRxFport, UserRxPayload, &UserRxPayloadSize );
            DEBUG_PRINTF("Receive on port %d  an Applicative Downlink \n DATA[%d] = [ ",UserRxFport,UserRxPayloadSize);
                    for ( i = 0 ; i < UserRxPayloadSize ; i++){
                        DEBUG_PRINTF( "0x%.2x ",UserRxPayload[i]);
                    }
            if ( UserRxPayloadSize > 0) {
                if ( ( UserRxPayloadSize == 4 ) && (UserRxFport == 1)  ) {
                    relay.AddDevaddrInWhiteList ( UserRxPayload [3] + (UserRxPayload [2] << 8) + (UserRxPayload [1] << 16) + (UserRxPayload [0] << 24) );
                    relay.RemoveDevaddrInBlackList ( UserRxPayload [3] + (UserRxPayload [2] << 8) + (UserRxPayload [1] << 16) + (UserRxPayload [0] << 24) );
                    SendDevaddrStatus = true;
                }
                if ( ( UserRxPayloadSize == 8 ) && (UserRxFport == 1)  ) {
                    relay.AddDevEuiInJoinWhiteList ( UserRxPayload );
                    relay.RemoveDevEuiInJoinBlackList ( UserRxPayload );
                    SendDevEuiStatus = true;
                }
                if ( ( UserRxPayloadSize == 4 ) && (UserRxFport == 2) ) {
                    uint32_t Removedevaddr =  UserRxPayload [3] + (UserRxPayload [2] << 8) + (UserRxPayload [1] << 16) + (UserRxPayload [0] << 24);
                    relay.RemoveDevaddrInWhiteList ( Removedevaddr );
                    SendDevaddrStatus = true;
                }
                if ( ( UserRxPayloadSize == 8 ) && (UserRxFport == 2) ) {
                    relay.RemoveDevEuiInJoinWhiteList ( UserRxPayload );
                    SendDevEuiStatus = true;
                }
                if ( UserRxPayloadSize > 9 )   {
                    uint32_t ReceiveDevaddr = relay.ExtractDevaddrDownLink(UserRxPayload);
                    DEBUG_PRINTF ( "ReceiveDevaddr = 0x%x\n", ReceiveDevaddr);
                    DEBUG_PRINTF("Receive on port %d  an Applicative Downlink \n DATA[%d] = [ ",UserRxFport,UserRxPayloadSize);
                        for ( i = 0 ; i < UserRxPayloadSize ; i++){
                            DEBUG_PRINTF( "0x%.2x ",UserRxPayload[i]);
                        }
                        DEBUG_MSG ( "]\n");
                    if ( ( relay.IsRx3Activated ( ReceiveDevaddr ) == YES ) && ( relay.GetConfigForRx3 ( &(Tx4Rx3Task.StartTime) , ReceiveDevaddr, &(ptpRx.Tx4Rx3Param.Frequency) ) == OK ) ) {
                        DEBUG_PRINTF("Receive on port %d  an Applicative Downlink \n DATA[%d] = [ ",UserRxFport,UserRxPayloadSize);
                        for ( i = 0 ; i < UserRxPayloadSize ; i++){
                            DEBUG_PRINTF( "0x%.2x ",UserRxPayload[i]);
                        }
                        DEBUG_MSG ( "]\n");
                        RP.EnqueueTask (Tx4Rx3Task, UserRxPayload, &UserRxPayloadSize, ptpRx.Tx4Rx3Param ); //@tbd RadioPlaner  timeonair
                        relay.ClearRx3Activation (RX3_DISABLE, ReceiveDevaddr  ); 
                    } else if ( JoinOnGoing == true ){ // Have to be robustified with a token 
                        if ( ( relay.IsRx3Activated ( CurrentJoinDevEui ) == YES ) && ( relay.GetConfigForRx3 ( &(Tx4Rx3Task.StartTime), CurrentJoinDevEui,&(ptpRx.Tx4Rx3Param.Frequency) ) == OK ) ) {
                        RP.EnqueueTask (Tx4Rx3Task, UserRxPayload, &UserRxPayloadSize, ptpRx.Tx4Rx3Param ); //@tbd RadioPlaner  timeonair
                        relay.ClearRx3Activation (RX3_DISABLE, CurrentJoinDevEui  );  
                        JoinOnGoing = false;
                        } 
                    }
                  
                }
            } else {
                DEBUG_MSG ("Receive Ack \n");
            }
        }
      
        cpt++;
        if ( ( cpt > PERIOD_STATUS ) && (toggle == 1) ) {
            SendDevEuiStatus  =  true  ;
            SendDevaddrStatus =  false ;
        }
        if ( ( cpt > PERIOD_STATUS ) && (toggle == 0) ) {
            SendDevaddrStatus = true  ;
            SendDevEuiStatus  = false  ;
        }
        mcu.GotoSleepMSecond ( 2000 );
    }
#else
    SHT21 Sht21 ( PB_14 );
    Sht21.PowerSht();
    bool start_tx        = true; 
    uint8_t DummyPayloadSend[10];
    uint8_t DummyPayloadSize = 10;
    Lp.Init ();
    RadioUser.Sleep( true );
    mcu.GotoSleepMSecond ( 100 );
    Lp.SetDataRateStrategy ( USER_DR_DISTRIBUTION );
    Lp.ActivateRX3 (); 
    mcu.InitGpioOut (PA_5);
    mcu.SetValueDigitalOutPin (PA_5, 1); // switch in iddle mode the TimeOf flight sensor
    uint32_t RunningTime = 0 ;
    Accelero.Running =1;
    mcu.mwait_ms (200);
    Accelero.InitConfig (); 
    Accelero.ReadStatusAccelero();
    ptpTx.SetDevAddr ( DevEuiInit2,8 );
    uint8_t FirstJoin = 0;
    Accelero.ClearIrqAccelero();
    UserPayloadClassA[0]  = 0x17 ;
    UserPayloadSizeClassA = 6; 
    uint32_t next_start = mcu.RtcGetTimeMs();

    while (1) {
       
        if ( Accelero.Running == 1) {                                 // wake up in interrupt coming from accelero
            if ( Accelero.AcceleroWup () )  {
                Accelero.ClearIrqAccelero();
                DEBUG_MSG ("Debout\n");
                DEBUG_PRINTF("status accelero = %d\n",Accelero.ReadStatusAccelero());
                UserPayloadClassA[5] = Accelero.Temperature ; 
                DEBUG_PRINTF("status accelero Temp  = %d\n", UserPayloadClassA[5] );
                Accelero.PowerOffLSM303H_ACC ();
                Accelero.Running = 0;
                RunningTime = mcu.RtcGetTimeSecond ();
                start_tx = true;
            }
        } 
        if   ( Accelero.Running == 0 ) {                                                        // Normal mode send payload in lora + relay 
            if ( start_tx ) {
                DEBUG_MSG ("lora\n");
                start_tx = false;
                ptpTx.SetChannelDr (  Lp.GetNextFrequency ( ), Lp.GetNextDataRate  ( ) );
                uint32_t NextSendSlot = ptpTx.Start(DummyPayloadSend, DummyPayloadSize);
                if ( ( Lp.IsJoined ( ) == NOT_JOINED ) && ( Lp.GetIsOtaDevice ( ) == OTA_DEVICE) ) {       
                    LpState  = Lp.Join( NextSendSlot );
                    FirstJoin = 0;
                } else {
                    if ( FirstJoin == 0 ) {
                        ptpTx.SetDevAddr( Lp.GetDevAddr() );
                        UserPayloadClassA[1] =  ( Lp.GetDevAddr() >> 24 );
                        UserPayloadClassA[2] =  ( Lp.GetDevAddr() >> 16 ) & 0xFF;   
                        UserPayloadClassA[3] =  ( Lp.GetDevAddr() >> 8 ) & 0xFF;
                        UserPayloadClassA[4] =  ( Lp.GetDevAddr() ) & 0xFF;
                        //ptpTx.SetDevAddr( LoRaDevAddrInit );
                        ptpTx.ClearDevEui ();
                        FirstJoin = 1;
                    }
                    if ( AvailableRxPacket != NO_LORA_RXPACKET_AVAILABLE ) { 
                        AvailableRxPacket  = NO_LORA_RXPACKET_AVAILABLE ;
                        InsertTrace ( __COUNTER__, FileId );
                        Lp.ReceivePayload( &UserRxFport, UserRxPayload, &UserRxPayloadSize );
                        if ( UserRxPayloadSize > 0) {
                            DEBUG_PRINTF("Receive on port %d  an Applicative Downlink \n DATA[%d] = [ ",UserRxFport,UserRxPayloadSize);
                            for ( i = 0 ; i < UserRxPayloadSize ; i++){
                                DEBUG_PRINTF( "0x%.2x ",UserRxPayload[i]);
                            }
                        } else {
                            DEBUG_MSG ("Receive Ack \n");
                        }
                        LpState  = Lp.SendPayload( UserFport, UserRxPayload, UserRxPayloadSize, UNCONF_DATA_UP,NextSendSlot );
                    } else {
                        LpState  = Lp.SendPayload( UserFport, UserPayloadClassA, UserPayloadSizeClassA, UNCONF_DATA_UP,NextSendSlot );
                    }
                }
            }
           
            while ( ( LpState != LWPSTATE_IDLE ) && ( LpState != LWPSTATE_ERROR ) && ( LpState != LWPSTATE_INVALID ) ) {
                LpState = Lp.LoraWanProcess( &AvailableRxPacket );
                mcu.GotoSleepMSecond ( 200 );
                mcu.WatchDogRelease  ( );
            }
            if ( ( (mcu.RtcGetTimeSecond () - RunningTime ) > WAKEUPDURATION ) &&  ( Accelero.Running == 0 )) { // Goto sleep and wait it from accelero
                DEBUG_MSG ("Dodo\n");
                Accelero.Running = 1;
                Accelero.PowerLSM303H_ACC ();
                Accelero.InitConfig (); 
                Accelero.ReadStatusAccelero();
            } else {
                if((int32_t)(next_start - mcu.RtcGetTimeMs() ) <= 0){
                    start_tx = true;
                    next_start = mcu.RtcGetTimeMs() + 20000;
                }
            }

        }
       
    mcu.GotoSleepMSecond ( 5000 );
    }
#endif
}