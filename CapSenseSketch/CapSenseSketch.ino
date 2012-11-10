#include <CapSense.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapSense   cs_4_2 = CapSense(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapSense   cs_4_6 = CapSense(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapSense   cs_4_8 = CapSense(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

#define fingers=4;


void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
  
pinMode(A11, OUTPUT);
pinMode(A12, OUTPUT);
pinMode(A13, OUTPUT);
pinMode(A14, OUTPUT);
pinMode(A15, OUTPUT);
analogWrite(A11, 0);
analogWrite(A12, 0);
analogWrite(A13, 0);
analogWrite(A14, 0);
analogWrite(A15, 0);

}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capSense(30);
    //long total2 =  cs_4_6.capSense(30);
    //long total3 =  cs_4_8.capSense(30);
    int filter[] = {0, 0, 0, 0, 0};

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.println("\t");
    for(int i = 0; i < sizeof(filter) - 1; i++) {
      filter[i] = filter[i + 1];
    }
    filter[sizeof(filter) - 1] = total1;
    //take average in filter
    int sum = 0;
    for(int i = 0; i < sizeof(filter); i++) {
      sum += filter[i];
    }
    int average = sum / sizeof(filter);
    
    //Serial.print(total2);                  // print sensor outputmM 2
    Serial.print("\t");
    //Serial.println(total3);                // print sensor output 3

    delay(10);                             // arbitrary delay to limit data to serial port 
}

/*void change( int wierd_one)
{
  char* pin=['A',(wierd_one-1)%fingers]
  
  pinMode(pin,OUTPUT);
  
  delay(10);
  
    pinMode(
}
*/
