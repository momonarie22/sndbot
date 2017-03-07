                                                                                                                                                                                                                                                                                                                                  /*
 * S&D Bot pixy functions
 * 
 * Moises Beato
 * March 2017
 */
#include "sndbot.h"
#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

uint8_t signature;
uint8_t x;                      // positon x axis
uint8_t y;                      // position y axis
uint16_t width;                 // object's width
uint16_t height;                // object's height
uint32_t area;                  // initial distance from object
uint32_t newarea;               // compare distance from object
uint8_t Xmin = 120;             // min x position
uint8_t Xmax = 200;             // max x position
uint8_t maxArea;                // max distance
uint8_t minArea;                // min distance 
uint8_t i = 0;                  // iterate between signatures
uint16_t blocks;

static void pixy_scan(void);

void pixy_setup(void)
{ 
  pixy.init();
}

void pixy_find(void)
{
   while(millis()<5000)
  {
    pixy_scan();
    area = width * height; //calculate the object area 
    maxArea = area + 500;
    minArea = area - 500;
  }
  pixy_scan(); 
   if(signature == 1)//looking for signature 1
  {
    newarea = width * height; //calculate the object area    
      if (x < Xmin)//turn left if x position < max x position    
        turn_left();
      else if (x > Xmax) //turn right if x position > max x position
        turn_right();
      else if(newarea < minArea)//go forward if object too small
          drive_forward();        
      else if(newarea > maxArea)//go backward if object too big
        drive_backward();
      else if(newarea > maxArea && newarea < minArea)
        motor_stop();
      else
      motor_stop();
   }
   else
    motor_stop();
}

static void pixy_scan(void)
{
  blocks = pixy.getBlocks();  //receive data from pixy 
  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  y = pixy.blocks[i].y;                    //get y position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get heigh
}

