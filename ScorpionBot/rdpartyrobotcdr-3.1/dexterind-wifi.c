#pragma config(Sensor, S1,     COLOUR,              sensorCOLORNONE)
#pragma config(Sensor, S3,     DTMP,                sensorAnalogInactive)
#pragma config(Motor,  motorA,          M1,            tmotorNormal, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/common.h"
#include "drivers/dexterind-wifi.h"
#include "drivers/dexterind-temp.h"

//ubyte rxbuffer[1500];

void sendHeader(int cid) {
  ubyte linebuff[20];
  int index = 0;
  string tmpString;

  linebuff[0] = 27; // escape;
  linebuff[1] = 'S'; // the CID;
  linebuff[2] = (ubyte)cid + 48; // the CID;
  index = RS485appendToBuff(RS485txbuffer, index, linebuff, 3);

  tmpString = "HTTP/1.1 200 OK";
  //memcpy(linebuff, tmpString, strlen(tmpString));
  index = RS485appendToBuff(RS485txbuffer, index, tmpString, strlen(tmpString));
  index = RS485appendToBuff(RS485txbuffer, index, linefeed, sizeof(linefeed));

  tmpString = "Content-Type:";
  memcpy(linebuff, tmpString, strlen(tmpString));
  index = RS485appendToBuff(RS485txbuffer, index, linebuff, strlen(tmpString));

  tmpString = " text/plain";
  memcpy(linebuff, tmpString, strlen(tmpString));
  index = RS485appendToBuff(RS485txbuffer, index, linebuff, strlen(tmpString));
  index = RS485appendToBuff(RS485txbuffer, index, linefeed, sizeof(newline));
  index = RS485appendToBuff(RS485txbuffer, index, linefeed, sizeof(newline));
  linebuff[0] = 27; // escape;
  linebuff[1] = 'E'; // the CID;
  index = RS485appendToBuff(RS485txbuffer, index, endmarker, 2);
  RS485write(RS485txbuffer, index);
}


void genResponse(int cid) {
  int power = motor[motorA];
  float temp = 0.0;
  string tmpString;
  int index = 0;
  ubyte linebuff[20];
  StringFromChars(tmpString, rxbuffer);
  index = StringFind(tmpString, "/");
  StringDelete(tmpString, 0, index);
  index = StringFind(tmpString, "HTTP");
  StringDelete(tmpString, index, strlen(tmpString));
  writeDebugStreamLine("Request:%s", tmpString);
  nxtDisplayTextLine(2, "Request: ");
  nxtDisplayTextLine(3, tmpString);
  if (StringFind(tmpString, "MOTA") > 0) {
    StringDelete(tmpString, 0, 6);
    index = StringFind(tmpString, " ");
  if (index > -1)
      StringDelete(tmpString, index, strlen(tmpString));
    //power = RC_atoix(tmpString);
    power = clip(atoi(tmpString), -100, 100);
    writeDebugStreamLine("Power:%d", power);
  } else {
    writeDebugStreamLine("NO POWER: %s", tmpString);
  }

  sendHeader(cid);
  while(nxtHS_Status == HS_SENDING) wait1Msec(5);

  wait1Msec(100);

  index = 0;
  linebuff[0] = 27; // escape;
  linebuff[1] = 'S'; // the CID;
  linebuff[2] = (ubyte)cid + 48; // the CID;
  index = RS485appendToBuff(RS485txbuffer, index, linebuff, 3);
  StringFormat(tmpString, "MotorA=%d\n", power);
  memcpy(linebuff, tmpString, strlen(tmpString));
  index = RS485appendToBuff(RS485txbuffer, index, linebuff, strlen(tmpString));
  DTMPreadTemp(DTMP, temp);
  StringFormat(tmpString, "Temp: %2.2f C", temp);
  memcpy(linebuff, tmpString, strlen(tmpString));
  index = RS485appendToBuff(RS485txbuffer, index, linebuff, strlen(tmpString));
  linebuff[0] = 27; // escape;
  linebuff[1] = 'E'; // the CID;
  index = RS485appendToBuff(RS485txbuffer, index, endmarker, 2);
  RS485write(RS485txbuffer, index);
  if (power != 0) nMotorEncoderTarget[motorA] = 2000;
  motor[motorA] = power;
  if (power > 0)
    SensorType[COLOUR] = sensorCOLORGREEN;
  else if (power < 0)
    SensorType[COLOUR] = sensorCOLORBLUE;
  else if (nMotorRunState[motorA] == runStateIdle)
    SensorType[COLOUR] = sensorCOLORRED;
  else
    SensorType[COLOUR] = sensorCOLORRED;
  wait1Msec(300);
  RS485clearRead();
  closeConn(1);
  memset(RS485rxbuffer, 0, sizeof(RS485rxbuffer));
  //wait1Msec(100);
  RS485read(RS485rxbuffer, sizeof(RS485rxbuffer));
  //clear_read_buffer();
}


void parseInput()
{
  writeDebugStreamLine("Beging parsing...");
  ubyte currByte[] = {0};
  ubyte prevByte[] = {0};
  ubyte conn[] = {0};
  int cid;
  string tmpString;
  int index = 0;
  time1[T1] = 0;
  while (true)
  {
    if (time1[T1] > 300000)
      return;

    alive();
	  if (nxtGetAvailHSBytes() > 0)
	  {
      nxtReadRawHS(&currByte[0], 1);
      if ((prevByte[0] == 27) && (currByte[0] == 'F')) {
        return;
      } else if ((prevByte[0] == 27) && (currByte[0] == 'S')) {
        index = 0;
        memset(rxbuffer, 0, sizeof(rxbuffer));
        wait1Msec(1);
        nxtReadRawHS(&conn[0], 1);
        cid = conn[0] - 48;
        writeDebugStreamLine("Conn: %d", cid);
        if (cid > 1)
          return;
        while (true) {
          if (time1[T1] > 300000)
            return;

          while (nxtGetAvailHSBytes() == 0) EndTimeSlice();
          nxtReadRawHS(&currByte[0], 1);

          if ((prevByte[0] == 27) && (currByte[0] == 'F')) {
            return;
          } else if ((prevByte[0] == 27) && (currByte[0] == 'E')) {
					  rxbuffer[index--] = 0;
					  rxbuffer[index--] = 0;
					  PlaySound(soundShortBlip);
					  while(bSoundActive) EndTimeSlice();
					  break;
					}
					prevByte[0] = currByte[0];
          rxbuffer[index++] = currByte[0];
          if (index == sizeof(rxbuffer))
            return;

				}
				StringFromChars(tmpString, &rxbuffer[0]);
				writeDebugStreamLine(tmpString);
				/*
				for (int i = 0; i < ((index / 19) + 1); i++) {
					memset(BytesRead[0], 0, 20);
					memcpy(BytesRead[0], rxbuffer[i*19], 19);
					StringFromChars(tmpString, BytesRead);
					writeDebugStream(tmpString);

				}*/
				genResponse(cid);
      }
      prevByte[0] = currByte[0];
	  }
	}
}



void startDemon() {
  time1[T2] = 0;
  while (true) {
    if (time1[T2] > 1200000)
      return;
    SensorType[COLOUR] = sensorCOLORNONE;
    PlaySound(soundBlip);
    closeAllConns();
    wait1Msec(500);
	  startListen(80);
	  SensorType[COLOUR] = sensorCOLORRED;
	  clear_read_buffer();
	  parseInput();
	}
}

void startWifi() {
  while (true) {
	  configureWiFi();
	  set_verbose(false);
	  Receive();
	  wait1Msec(100);
	  startDemon();
	}
}

task main()
{
  long rate = 0;
  eraseDisplay();
  bNxtLCDStatusDisplay = true; // Enable top status line display
  writeDebugStream("Scanning for wifi sensor: ");
  rate = scanBaudRate();
  writeDebugStreamLine("%d baud", rate);
  startWifi();
//  configureWiFi();
//  set_verbose(false);
//  Receive();
//  wait1Msec(100);
  /*
  closeAllConns();
  wait1Msec(1000);
  clear_read_buffer();
  startListen(80);
  SensorType[COLOUR] = sensorCOLORRED;
  clear_read_buffer();
  parseInput();
  */
//  startDemon();
}
