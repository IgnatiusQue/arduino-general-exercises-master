// Copyright Benoit Blanchon 2014-2017
// MIT License
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!

#include <ArduinoJson.h>

// About
// -----
// This example shows the different ways you can use String with ArduinoJson.
// Please don't see this as an invitation to use String.
// On the contrary, you should always use char[] when possible, it's much more
// efficient in term of code size, speed and memory usage.

void setup() {
  DynamicJsonBuffer jsonBuffer;

  // You can use a String as your JSON input.
  // WARNING: the content of the String will be duplicated in the JsonBuffer.
  String input =
      "{\"sensor\":\"gpsdadsas\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  JsonObject& root = jsonBuffer.parseObject(input);

  // You can use a String to get an element of a JsonObject
  // No duplication is done.
  long time = root[String("time")];

  // You can use a String to set an element of a JsonObject
  // WARNING: the content of the String will be duplicated in the JsonBuffer.
  //root[String("time")] = time;

  // You can get a String from a JsonObject or JsonArray:
  // No duplication is done, at least not in the JsonBuffer.
  String sensor = root["sensor"];

  // Unfortunately, the following doesn't work (issue #118):
  // sensor = root["sensor"]; // <-  error "ambiguous overload for 'operator='"
  // As a workaround, you need to replace by:
  //sensor = root["sensor"].as<String>();

  // You can set a String to a JsonObject or JsonArray:
  // WARNING: the content of the String will be duplicated in the JsonBuffer.
 // root["sensor"] = sensor;

  // You can also concatenate strings
  // WARNING: the content of the String will be duplicated in the JsonBuffer.
  //root[String("sen") + "sor"] = String("gp") + "s";

  // You can compare the content of a JsonObject with a String
//  if (root["sensor"] == sensor) { 
  // Lastly, you can print the resulting JSON to a String
 // String output;
 // root.printTo(output);
   Serial.begin(115200);
   Serial.println(sensor);
}

void loop() {
  // not used in this example
}
