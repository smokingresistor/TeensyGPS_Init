#include "BMsg838.h"
#include "GPSSerialMessageCom.h"
#include <Wire.h>

BMsg838 gps;

void setup()
{
char messagetype[64];
memset(messagetype,0,64);

Serial.begin(115200);
Serial2.begin(9600);
Serial.print("BMsg838 System reset.\r\n"); 
SendBinaryMessagetoGPSreceiver(gps.ResetGNSS(1, 15, 6, 9,11, 30, 25, 20, 133, 1200), gps.SendStream,gps.RecVBinarybuf,0,2000);
SendBinaryMessagetoGPSreceiver(gps.SetSerialPort(115200, 1), gps.SendStream,gps.RecVBinarybuf,0,2000);
Serial2.begin(115200);
delay(4000);    
SendBinaryMessagetoGPSreceiver(gps.SetBinaryMessagetype(), gps.SendStream,gps.RecVBinarybuf,0,2000); 
delay(3000);    
SendBinaryMessagetoGPSreceiver(gps.SetPositionRate(50), gps.SendStream,gps.RecVBinarybuf,0,2000);
delay(3000);    
if(SendBinaryMessagetoGPSreceiver(gps.GetSoftVersion(), gps.SendStream,gps.RecVBinarybuf,0,2000)==3);
    if(waitingRespondandReceive(gps.RecVBinarybuf,0x80,2000)>7){
          BinaryRecvMsgtype(messagetype,gps.RecVBinarybuf);
          Serial.println(messagetype); 
          GPSSoftVersiondata* versioninfo=gps.ResponseSoftVersion();
          printSoftversion(versioninfo);        
    }
Serial.println("System Configuration Complete");
} 

void loop()
{

}  

