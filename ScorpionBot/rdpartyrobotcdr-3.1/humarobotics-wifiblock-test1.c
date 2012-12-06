#pragma config(Sensor, S1,     WifiBlockPort,  sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: humarobotics-wifiblock-test1.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * humarobotics-wifiblock.h provides an API for the HumaRobotics WiFiBlock Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HumaRobotics for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 2 April 2012
 * version 0.1
 */


#include "drivers/humarobotics-wifiblock.h";

#define WIFIBLOCK_IP    "192.168.43.100"
#define WIFIBLOCK_MASK  "192.168.43.255"
#define WIFIBLOCK_GW    "192.168.43.1"
#define WIFIBLOCK_SSID  "AndroidAP"
#define WIFIBLOCK_KEY   ""


// Set to 1 if not already configured.
#define DO_WIFI_CONFIG       0

// Set to 1 to execute test, enable only one at a time
#define DO_TEST_HTTP_GET     1
#define DO_TEST_HTTP_POST    0
#define DO_TEST_TCP          0
#define DO_TEST_UDP          0


/**
 * Dump the array contents on the NXT's screen
 * @param data the array that is to be displayed
 * @param size the amount of data that should be displayed
 */
void dumpRXData(tBigByteArray &data, ubyte size)
{
  string tmpBuff;
  int bytesleft = size;
  int datalen = 0;

  for (int i =  0; i < ((size/18) + 1); i++)
	{
	  datalen = (bytesleft > 18) ? 18 : bytesleft;

	  memset(tmpBuff, 0, 20);
	  memcpy(tmpBuff, &data[i*18], datalen);
	  writeDebugStream("BUFFER: ");
	  writeDebugStreamLine(tmpBuff);
    nxtDisplayTextLine(i+4, tmpBuff);
	  bytesleft -= 18;
	}
}


/**
 * Show a fancy startup display
 */
void StartupDisplay()
{
  nxtDisplayCenteredBigTextLine(0, "WiFi");
  nxtDisplayCenteredTextLine(3, "Program to test");
  nxtDisplayCenteredTextLine(4, "Network with ");
  nxtDisplayCenteredTextLine(5, "WifiBlock");
  wait1Msec(2000);
  eraseDisplay();
  return;
}


/**
 * Main program
 */
task main () {
  StartupDisplay();

// Setup the network configuration
#if (DO_WIFI_CONFIG == 1)
  tNetworkInfo netInfo;

  stringToIp(WIFIBLOCK_IP, (tIPaddr)netInfo.IP);
  stringToIp(WIFIBLOCK_GW, (tIPaddr)netInfo.gateway);
  stringToIp(WIFIBLOCK_MASK, (tIPaddr)netInfo.netmask);
  netInfo.wifi_type = HRWB_SECURITY_OPEN;
  netInfo.wifi_ssid =  WIFIBLOCK_SSID;
  netInfo.wifi_pass = WIFIBLOCK_KEY;

  HRWBconfigNetwork(WifiBlockPort, netInfo);
#endif

#if (DO_TEST_HTTP_GET == 1)
  string tmpURL;
  tGetRequest getrequest;

  stringToIp("192.168.43.68", (tIPaddr)getrequest.IP[0]);
  getrequest.port = 80;
  tmpURL = "/wifiblock.html";
  memcpy(getrequest.URL[0], tmpURL, strlen(tmpURL) + 1);

  HRWBdoGET(WifiBlockPort, getrequest);

  dumpRXData(getrequest.RXData, getrequest.RXDataLen);

#elif (DO_TEST_HTTP_POST == 1)
  tPostRequest postrequest ;
  string tmpString;

  stringToIp("192.168.43.68", (tIPaddr)postrequest.IP);
  postrequest.port = 80;
  tmpString = "msg=hello";
  memcpy(postrequest.TXData, tmpString, strlen(tmpString) + 1);
  postrequest.TXDataLen = strlen(tmpString) + 1;

  tmpString = "/post.php";
  memcpy(postrequest.URL, tmpString, strlen(tmpString) + 1);

  HRWBdoPOST(WifiBlockPort, postrequest);

#elif (DO_TEST_TCP == 1)
  tTCPRequest tcprequest;

  stringToIp("192.168.43.68", (tIPaddr)tcprequest.IP);
  tcprequest.port = 8080;
  tmpString = "Hi from WiFiBlock\n";
  memcpy(tcprequest.TXData, tmpString, strlen(tmpString) + 1);
  tcprequest.TXDataLen = strlen(tmpString) + 1;

  HRWBdoTCP(WifiBlockPort, tcprequest);

  dumpRXData(tcprequest.RXData, tcprequest.RXDataLen);

#elif (DO_TEST_UDP == 1)
  tUDPRequest udprequest;

  stringToIp("192.168.43.68", (tIPaddr)udprequest.IP);
  udprequest.dport = 8080;
  udprequest.sport = 5000;
  tmpString = "Hi from WiFiBlock\n";
  memcpy(udprequest.TXData, tmpString, strlen(tmpString) + 1);
  udprequest.TXDataLen = strlen(tmpString) + 1;

  HRWBdoUDP(WifiBlockPort, udprequest);

  dumpRXData(udprequest.RXData, udprequest.RXDataLen);

#endif

  PlaySound(soundBeepBeep);
  while(true) EndTimeSlice();
}

/*
 * $Id: humarobotics-wifiblock-test1.c 123 2012-11-02 16:35:15Z xander $
 */
