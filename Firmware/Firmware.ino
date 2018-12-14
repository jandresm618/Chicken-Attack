// Include Libraries
#include "Arduino.h"
#include "Joystick.h"


// Pin Definitions
#define JOYSTICK_PIN_VRX	A3
#define JOYSTICK_PIN_VRY	A1
#define JOYSTICK_PIN_SW	2



// Global variables and defines

// object initialization
Joystick joystick(JOYSTICK_PIN_VRX,JOYSTICK_PIN_VRY,JOYSTICK_PIN_SW);



// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;
int flag = 0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    //Serial.println("start");
    flag = 0;
    
    //menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    //if(menuOption == '1') {
    // PS2 X Y Axis Joystick Module - Test Code
    // Read Joystick X,Y axis and press
    int joystickX =  joystick.getX();
    int joystickY =  joystick.getY();
    int joystickSW =  joystick.getSW();

    
    if(joystickX>700 && flag!=1){
      Serial.print("L");
      flag = 1;
    }else if(joystickX<250 && flag!=2){
      Serial.print("R");
      flag = 2;
    }else if(joystickY>700  && flag!=3){
      Serial.print("U");
      flag = 3;
    }else if(joystickY<250  && flag!=4){
      Serial.print("D");
      flag = 4;
    }
    if(joystickSW!=0)
      Serial.print('S');

    //Serial.println(flag);
    
    delay(200);
    
    /*Serial.println(joystickX);
    Serial.println(joystickY);
    Serial.println(joystickSW);
    */
     
    /*Serial.print(F("X: ")); Serial.print(joystickX);
    Serial.print(F("\tY: ")); Serial.print(joystickY);
    Serial.print(F("\tSW: ")); Serial.println(joystickSW);
*/
    //}
    
    
    
    /*if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    */
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) PS2 X Y Axis Joystick Module"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {
            if(c == '1') 
    			Serial.println(F("Now Testing PS2 X Y Axis Joystick Module"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
            }
        }
    }

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
