#pragma config(Sensor, S3,     sCompass,       sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "rdpartyrobotcdr-v2.4/drivers/HTMC-driver.h"

task main()
{
  HTMCstartCal(sCompass);
  while (nNxtButtonPressed != 3)
  {
  }
  HTMCstopCal(sCompass);
}
