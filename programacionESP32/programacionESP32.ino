// Adafruit IO Publish & Subscribe Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.

#include "config.h"

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
//int count = 0;
String datos = ""; //almacenara los datos provenientes del pic
float aX,aY,aZ;
// Track time of last published messages and limit feed->save events to once
// every IO_LOOP_DELAY milliseconds.
//
// Because this sketch is publishing AND subscribing, we can't use a long
// delay() function call in the main loop since that would prevent io.run()
// from being called often enough to receive all incoming messages.
//
// Instead, we can use the millis() function to get the current time in
// milliseconds and avoid publishing until IO_LOOP_DELAY milliseconds have
// passed.
#define IO_LOOP_DELAY 6000
unsigned long lastUpdate = 0;

// set up the 'counter' feed
AdafruitIO_Feed *accelx = io.feed("Acelerationx");
AdafruitIO_Feed *accely = io.feed("Acelerationy");
AdafruitIO_Feed *accelz = io.feed("Acelerationz");

void setup() {

  // start the serial connection
  Serial.begin(115200);
  Serial2.begin(19200);
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  //counter->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  //counter->get();

}

void loop() {


  
  while(Serial2.available()){
      char entrante = Serial2.read();
      if( entrante != '\n') datos.concat(entrante);
      else{
        Serial.println(datos);
        aX = (datos.substring(0,7)).toFloat();
        aY = (datos.substring(7,14)).toFloat();
        Serial.println(datos.substring(14,21));
        aZ = (datos.substring(14,21)).toFloat();
        datos = "";
      }
  }

  
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
//     save count to the 'counter' feed on Adafruit IO
    Serial.print("sending -> ");
    Serial.println(aX);
    accelx->save(aX);
    Serial.print("sending -> ");
    Serial.println(aY);
    accely->save(aY);
    Serial.print("sending -> ");
    Serial.println(aZ);
    accelz->save(aZ);

    // increment the count by 1
    //count++;

    // after publishing, store the current time
    lastUpdate = millis();
  }

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
//void handleMessage(AdafruitIO_Data *data) {

  //Serial.print("received <- ");
  //Serial.println(data->value());

//}
