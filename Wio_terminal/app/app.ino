#include "GUI.h"

static GUI gui;

void setup() {
  Serial.begin(115200);

  // while (!Serial);
  Serial.println("");
  Serial.println("******************************");
  Serial.println("        Program start         ");
  Serial.println("******************************");
  gui.setup();
}

void loop() {
  gui.tick();
  delay(5);
}
