/**
 ******************************************************************************
  @file    other functions
  @author  Joel Daricou  <joel.daricou@cern.ch>
  @brief   all other functions
 ******************************************************************************
*/


/**
  This function is used to create another thread so as not to block the program (adding "delays"),
  but use a timing scanned by internal timers (millis).

  The parameter is the time to set (in milliseconds).

  The function returns:
  - [true] if the set time has already elapsed;
  - [false] if the set time has not yet passed.
*/
bool otherThread (uint32_t mSeconds) {
  static uint32_t previusMillis = 0;
  uint32_t currentMillis = millis();
  if (currentMillis - previusMillis > mSeconds) {
    previusMillis = currentMillis;
    return true;
  }
  else {
    return false;
  }
}


/**
  This function is used to create another thread so as not to block the program (adding "delays"),
  but use a timing scanned by internal timers (millis).

  The parameter is the time to set (in milliseconds).

  The function returns:
  - [true] if the set time has already elapsed;
  - [false] if the set time has not yet passed.
*/
bool softwareDelay (uint32_t mSeconds) {
  static uint32_t previusMillis = 0;
  uint32_t currentMillis = millis();
  if (currentMillis - previusMillis > mSeconds) {
    previusMillis = currentMillis;
    return true;
  }
  else {
    return false;
  }
}


/**
  This function is used to create a software delay using a micros() function,
  you can wait and at the same time execute the imon_routine().

  The parameter is the time to set (in microseconds).
*/
void delay_with_current_measure(uint32_t delay_us) {
  uint32_t previusTime = micros();
  uint32_t currentTime = previusTime;
  while ((currentTime - previusTime) < delay_us) {
    imon_measure_routine();
    currentTime = micros();
  }
}


/**
  This function is used to copy an array into another.
*/
void copyArray (int32_t *from, float *to, uint16_t sizeOf, float correction) {
  for (uint8_t i = 0; i < sizeOf; i++) {
    to[i] = from[i] * correction;
  }
}


/**
  This function is used to send the vgate_value and imon_value arrays via SerialUSB,
  in order to be read and stored by a data logger connected to the USB port.
*/
void send_usb_data (float *v_value, float *i_value, uint32_t sizeOf) {
  float val;
  for (uint8_t i = 0; i < sizeOf; i++) {
    val = v_value[i];
    USB.print(val);
    USB.print(',');
  }
  for (uint8_t i = 0; i < sizeOf; i++) {
    val = i_value[i];
    USB.print(val);
    USB.print(',');
  }
  USB.println();
}
