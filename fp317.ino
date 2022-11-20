/*
 * File: FP317.ino
 * Implements the FP317_gfx class and draws some stuff to play around
 * 
 * Created by Andrew (Novar Lynx) (C) 2022
 */
 
#include "FP317_gfx.h"
#include "MAX3000_Font4.h"
#include "MAX3000_Font6.h"
#include "MAX3000_Font8.h"

FP317_gfx* gfx;

void setup() {
  // put your setup code here, to run once:
  gfx = new FP317_gfx();
  //driver->clearDisplay();
  delay(1000);
}

void loop() {

gfx->setCursor(1,10);
delay(10);
gfx->setTextColor(1);
gfx->setFont(&luminator_6);
gfx->println("MEOW");
delay(1000);
gfx->println("OwO");
delay(1000);



for (int i=0; i <= 25; i++) {
  gfx->clearDisplay();
  gfx->setCursor(5,10);
  gfx->print(i);
  delay(100);
}
delay(1000);
  gfx->setLag(5);
  gfx->clearDisplay();
  gfx->setCursor(1,10);
  gfx->setFont(&luminator_4);
  gfx->println("69420");
  gfx->setCursor(2,18);
  gfx->setFont(&luminator_6);
  gfx->println("nice");
delay(1000);
  gfx->setLag(10);

  gfx->clearDisplay();
  gfx->drawCircle(14, 14, 2, 1);
  gfx->drawCircle(14, 14, 4, 1);
  gfx->drawCircle(14, 14, 6, 1);
  gfx->drawCircle(14, 14, 8, 1);
  gfx->drawCircle(14, 14, 10, 1);
  delay(1000);
  gfx->drawCircle(14, 14, 10, 0);
  gfx->drawCircle(14, 14, 6, 0);
  gfx->drawCircle(14, 14, 8, 0);
  gfx->drawCircle(14, 14, 4, 0);
  gfx->drawCircle(14, 14, 2, 0);
  gfx->setLag(0);

  gfx->setCursor(8,12);
  gfx->setFont(&luminator_8);
  gfx->println(":3");
  
  delay(1000);
  
delay(5000);
  gfx->clearDisplay();
  delay(5000);
  
}
