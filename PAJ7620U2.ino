/*
	Project  : LaLiMat project (https://www.youtube.com/playlist?list=PLJBKmE2nNweRXOebZjydkMEiq2pHtBMOS in Chinese)
 	file     : PAJ7620U2.ino
	Author   : ykchau
 	youtube  : youtube.com/ykchau888
  	Licenese : GPL-3.0
   	Please let me know if you use it commercial project.
*/

#include <Wire.h>

#include "PAJ7620U2.h"

/* 
Notice: When you want to recognize the Forward/Backward gesture or other continuous gestures, your gestures' reaction time must less than GES_REACTION_TIME(0.8s). 
        You also can adjust the reaction time according to the actual circumstance.
*/

PAJ7620 GestureSensor;
byte GS_data = 0, GS_data1 = 0;

void setup() {
    byte error = 0;

    Serial.begin(115200);

    error = GestureSensor.Init();  // initialize Paj7620 registers
    if (error) {
        Serial.print("INIT ERROR,CODE:");
        Serial.println(error);
    } else {
        Serial.println("INIT OK");
    }
    Serial.println("Please input your gestures:");
}

void loop() {
    if ( !GestureSensor.ReadReg(0x43, 1, &GS_data) ) {
        switch(GS_data) {
            case PAJ_LEFT: Serial.println("LEFT"); break;
            case PAJ_RIGHT: Serial.println("RIGHT"); break;
            case PAJ_UP: Serial.println("UP"); break;
            case PAJ_DOWN: Serial.println("DOWN"); break;
            case PAJ_PUSH: Serial.println("PUSH"); break;
            case PAJ_PULL: Serial.println("PULL"); break;
            case PAJ_CLOCKWISE: Serial.println("CLOCKWISE"); break;
            case PAJ_ANTI_CLOCKWISE: Serial.println("ANTI CLOCKWISE"); break;
            default:
                GestureSensor.ReadReg(0x44, 1, &GS_data1);
                if ( GS_data1 == PAJ_WAVE )
                    Serial.println("WAVE");
                break;
        }
    }
}
