
#include "LPD8806.h"
#include "SPI.h"
#include "math.h"

//number of leds in the system
const int n = 36;
const int nn = 22;

int x = 0;

int sysdelay = 1;

int dataPin = 11;   
int clockPin = 13;

double m1 = 0.2;
double o1 = 3.3;
double c1 = 1;

double m2 = 0.6;
double o2 = 3.1;
double c2 = 3;

double o3 = 2;
double c3 = 1.2;

//the time in ms it takes for a mutation to occur
long time;
int tm1 = 3000;
long tm1count;
int tc1 = 4000;
long tc1count;
int tm2 = 3500;
long tm2count;
int tc2 = 1500;
long tc2count;

//target mutation values
double targetm1;
double targetc1;
double targetm2;
double targetc2;
double targeto3;
double targetcx;
double targetmx;

double stepm1;
double stepc1;
double stepm2;
double stepc2;
double stepo3;
double stepmx;
double stepcx;

double randomnumber;

double cx = 0.5;
double mx = 0.175;

double f1;
double f2;
double f3;

double huearray[n];
double huearrayholder[n];

double hprime;

uint32_t c = 0;

//byte r = 60;
//byte g = 100;
//byte b = 100;
int i;




int wait = 1;

// Set the first variable to the NUMBER of pixels. 32 = 32 pixels in a row
// The LED strips are 32 LEDs per meter but you can extend/cut the strip
LPD8806 strip = LPD8806(n);;

//Declarations for HSV function
float H,S,L,Rval,Gval,Bval;
void HSL(float H, float S, float L, float& Rval, float& Gval, float& Bval);

void setup() {
  
//    strip.slowmo = true;
//        strip.pause = 20;
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();

  Serial.begin(115200);
}


void loop() {
  
  S=0.99;
  L=0.075;

  
//  HSL(hprime,S,L,Rval,Gval,Bval);
  
//  if (Bval <= 0) {Bval = Gval;}
//  Gval = 0;
//  if (Rval < 64) {Rval = 64;}
//  c = strip.Color(Rval/2,Gval/2,Bval/2);
  
//  time = millis();
    
x = 0;
for (int ii=0; ii < nn; ii++) {
  if (x == 0) {
    x = 1;
    
//    randomnumber = random(0, 256);
//    m1 = targetm1;
//    targetm1 = randomnumber / 256;
//    stepm1 = targetm1 - m1;
//    stepm1 = stepm1 / nn;
    
    randomnumber = random(1, 60);
    m2 = targetm2;
    targetm2 = randomnumber / 100;
    stepm2 = targetm2 - m2;
    stepm2 = stepm2 / nn;
    
//    randomnumber = random(0, 64);
//    c1 = targetc1;
//    targetc1 = randomnumber / 256;
//    stepc1 = targetc1 - c1;
//    stepc1 = stepc1 / nn;
//    

    randomnumber = random(1, 400);
    c2 = targetc2;
    targetc2 = randomnumber / 100;
    stepc2 = targetc2 - c2;
    stepc2 = stepc2 / nn;

    randomnumber = random(1, 600);
    o3 = targeto3;
    targeto3 = randomnumber / 100;
    stepo3 = targeto3 - o3;
    stepo3 = stepo3 / nn;
    
    randomnumber = random(2, 30);
    mx = targetmx;
    targetmx = randomnumber / 100;
    stepmx = targetmx - mx;
    stepmx = stepmx / nn;
    
    randomnumber = random(25, 80);
    cx = targetcx;
    targetcx = randomnumber / 100;
    stepcx = targetcx - cx;
    stepcx = stepcx / nn;
  }
  
//  m1 = m1 + stepm1;


  m2 = m2 + stepm2;
//  c1 = c1 + stepc1;

  c2 = c2 + stepc2;
//  o3 = o3 + 0.2;
  o3 = o3 + stepo3;
  
  cx = cx + stepcx;
  mx = mx + stepmx;
  
  for (i=0; i < n; i++) {
    double q = i;

//    double qx = square(q)
    double qx = (q * 0.2) + (log10(q+2) * 0.6);
//    Serial.print(qx);
//    Serial.print(";");
//    f1 = m1*(sin(((qx)+o1)*c1));
    f1 = 0;
    f2 = m2*sin(qx*c2);
    f3 = sin((qx*c3)+o3);
    hprime = ((f1 + f2 + f3) * mx) + cx;
    if (hprime > 1) {hprime = 1;}
    if (hprime < 0) {hprime = 0;}
    huearrayholder[i] = hprime;
//    Serial.print(i);
//    Serial.print(";");
//    Serial.print(ii);
//    Serial.print(";");
//    Serial.print(m1);
//    Serial.print(";");
//    Serial.print(m2);
//    Serial.print(";");
//    Serial.print(c1);
//    Serial.print(";");
//    Serial.print(c2);
//    Serial.print(";");
//    Serial.print(o3);
//    Serial.print(";");
//    Serial.print(f1);
//    Serial.print(";");
//    Serial.print(f2);
//    Serial.print(";");
//    Serial.print(hprime);
//    Serial.println(";");
//    delay(wait);
  }
  
  
  for (i=0; i < n/2; i++) {
    huearray[i] = huearrayholder[(n - 1) - (2 * i)];
  }
  
  for (i=n/2; i < n; i++) {
    huearray[i] = huearrayholder[(i-(n/2))*2];
  }
  
  
      
      
  for (i=0; i < n; i++) {
//    double neighboravg = (huearray[i+1] + huearray[i-1])/2;
//    if ((neighboravg - huearray[i]) > 0.065) {huearray[i] = neighboravg;}
//    if ((neighboravg - huearray[i]) < -0.065) {huearray[i] = neighboravg;}
      HSL(huearray[i],S,L,Rval,Gval,Bval);
      c = strip.Color(Rval/2,Gval/2,Bval/2);
      strip.setPixelColor(i, c);
  }
  
  strip.show();

}
  
  
  
//      delay(100);
//  rainbow(100);
//  rainbowCycle(10);
//  Serial.print(hprime);
//  Serial.print(":");
//  Serial.print(Rval);
//  Serial.print(":");
//  Serial.print(Gval);
//  Serial.print(":");
//  Serial.print(Bval);
//  for (i=0; i < n; i++) {
//    Serial.print(huearray[i]);
//    Serial.print(";");
//  }
//  Serial.println("");
  delay(sysdelay);


}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 96 * 3; j++) {     // 3 cycles of all 96 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 96));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 96 * 5; j++) {     // 5 cycles of all 96 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Chase a dot down the strip
// good for testing purposes
void colorChase(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);  // turn all pixels off
  } 
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      if (i == 0) { 
        strip.setPixelColor(strip.numPixels()-1, 0);
      } else {
        strip.setPixelColor(i-1, 0);
      }
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

//Input a value 0 to 127 to get a color value.
//The colours are a transition r - g -b - back to r
unsigned int Wheel(byte WheelPos)
{
  byte r,g,b;
  switch(WheelPos >> 5)
  {
    case 0:
      r=31- WheelPos % 32;   //Red down
      g=WheelPos % 32;      // Green up
      b=0;                  //blue off
      break; 
    case 1:
      g=31- WheelPos % 32;  //green down
      b=WheelPos % 32;      //blue up
      r=0;                  //red off
      break; 
    case 2:
      b=31- WheelPos % 32;  //blue down 
      r=WheelPos % 32;      //red up
      g=0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}

void HSL(float H, float S, float L, float& Rval, float& Gval, float& Bval)
{
  if (H < 0) {H = 0;}
  else if (H > 1) {
    while (H>1) {H = H - 1;}
  }
  if (S < 0) {S = 0;}
  else if (S > 1) {S = 1;}
  float var_1;
  float var_2;
  float Hu=H+.33;
  float Hd=H-.33;
  if ( S == 0 )                       //HSL from 0 to 1
  {
     Rval = L * 255;                      //RGB results from 0 to 255
     Gval = L * 255;
     Bval = L * 255;
  }
  else
  {
     if ( L < 0.5 ) 
       var_2 = L * ( 1 + S );
     else           
       var_2 = ( L + S ) - ( S * L );
 
     var_1 = 2 * L - var_2;
 
     Rval = round(255 * Hue_2_RGB( var_1, var_2, Hu ));
//     Serial.print("Rval:");
//     Serial.println(Hue_2_RGB( var_1, var_2, Hu ));
     Gval = round(255 * Hue_2_RGB( var_1, var_2, H ));
     Bval = round(255 * Hue_2_RGB( var_1, var_2, Hd ));
  }
 
}

float Hue_2_RGB( float v1, float v2, float vH )             //Function Hue_2_RGB
{
   if ( vH < 0 ) 
     vH += 1;
   if ( vH > 1 ) 
     vH -= 1;
   if ( ( 6 * vH ) < 1 ) 
     return ( v1 + ( v2 - v1 ) * 6 * vH );
   if ( ( 2 * vH ) < 1 ) 
     return ( v2 );
   if ( ( 3 * vH ) < 2 ) 
     return ( v1 + ( v2 - v1 ) * (.66-vH) * 6 );
   return ( v1 );
}


