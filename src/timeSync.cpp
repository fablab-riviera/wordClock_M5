#include <M5StickCPlus.h>
#include <Arduino.h>
#include "neoMatrix.h"

// variable RTC de M5StackCPlus
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;
int day_last = -1; // détecter le changement de jour

// déclaration horloge internet
const char* ntpServer = "ch.pool.ntp.org";
int timeZone = 3600;

int getLastSundayOfMonth(int y, int m, int lastDayOfMonth) {
  // work only from month 3 to month 12 !!!
  int d = lastDayOfMonth;
  return lastDayOfMonth - ((d += y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7);
}
// calculate Daylight Saving Time (DST)
int getDST(int year, int month, int day) {
  int dst = 0; 
  if ( month >= 3 && month <= 10 ) {
    switch (month) {
      case 3: if (getLastSundayOfMonth(year, month, 31) <= day) dst = 1; break;
      case 10: if (getLastSundayOfMonth(year, month, 31) > day) dst = 1; break;
      default: dst = 1; break;
    }
  }
  return dst;
}
int getTimeYear() {
  M5.Rtc.GetData(&RTC_DateStruct);
  return RTC_DateStruct.Year;
}
int getTimeMonth() {
  M5.Rtc.GetData(&RTC_DateStruct);
  return RTC_DateStruct.Month;
}
int getTimeDay() {
  M5.Rtc.GetData(&RTC_DateStruct);
  return RTC_DateStruct.Date;
}
int getTimeHour() {
  M5.Rtc.GetTime(&RTC_TimeStruct);
  return RTC_TimeStruct.Hours;
}
int getTimeMinute() {
  M5.Rtc.GetTime(&RTC_TimeStruct);
  return RTC_TimeStruct.Minutes;
}
int getTimeSecond() {
  M5.Rtc.GetTime(&RTC_TimeStruct);
  return RTC_TimeStruct.Seconds;
}
String getStringDate() {
  String s = "";
  s += getTimeYear();
  s += "-";
  s += getTimeMonth()<10?"0":"";
  s += getTimeMonth();
  s += "-";
  s += getTimeDay()<10?"0":"";
  s += getTimeDay();
  return s;
}
String getStringDateLocal() {
  String s = "";
  s += getTimeDay()<10?"0":"";
  s += getTimeDay();
  s += ".";
  s += getTimeMonth()<10?"0":"";
  s += getTimeMonth();
  s += ".";
  s += getTimeYear();
  return s;
}
String getStringTime() {
  String s = "";
  s += getTimeHour()<10?"0":"";
  s += getTimeHour();
  s += ":";
  s += getTimeMinute()<10?"0":"";
  s += getTimeMinute();
  return s;
}
String getStringDateTime() {
  String s = "";
  s += getStringDate();
  s += "T";
  s += getStringTime();
  return s;
}
void rtcBegin() {
  // nthing to do for M5Strick
}
void setDateTimeManually(int y, int mo, int d, int h, int mi) {
  RTC_DateStruct.Year = y;
  RTC_DateStruct.Month = mo;
  RTC_DateStruct.Date = d;
  M5.Rtc.SetData(&RTC_DateStruct);
  RTC_TimeStruct.Hours   = h;
  RTC_TimeStruct.Minutes = mi;
  RTC_TimeStruct.Seconds = 0;
  M5.Rtc.SetTime(&RTC_TimeStruct);
}
// Syncing time from NTP Server
void setInternetTime() {
  ledsSyncOn();
  // Set ntp time to local
  configTime(timeZone, 0, ntpServer);

  // Get local time
  struct tm timeInfo;
  if (getLocalTime(&timeInfo)) {
    // Set RTC time
    RTC_DateStruct.WeekDay = timeInfo.tm_wday;
    RTC_DateStruct.Month = timeInfo.tm_mon + 1;
    RTC_DateStruct.Date = timeInfo.tm_mday;
    RTC_DateStruct.Year = timeInfo.tm_year + 1900;
    M5.Rtc.SetData(&RTC_DateStruct);

    RTC_TimeStruct.Hours   = timeInfo.tm_hour + getDST(timeInfo.tm_year+1900, timeInfo.tm_mon+1, timeInfo.tm_mday);
    RTC_TimeStruct.Minutes = timeInfo.tm_min;
    RTC_TimeStruct.Seconds = timeInfo.tm_sec;
    M5.Rtc.SetTime(&RTC_TimeStruct);
  }
  ledsSyncOff();
}
void timeSync() {
  // l'horloge est synchonisée avec l'heure internet une fois par jour, à 3 heures le matin
  if (getTimeDay() != day_last && getTimeHour() > 3) {
    setInternetTime();
    day_last = getTimeDay();
  }
}
