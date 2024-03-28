#include "PAJ7620U2.h"

byte PAJ7620::Init(void) {
    //Near_normal_mode_V5_6.15mm_121017 for 940nm
    int i = 0;
    byte data0 = 0, data1 = 0;
    //wakeup the sensor
    Wire.begin();

    Serial.println("INIT SENSOR...");

    SelectBank(BANK0);
    SelectBank(BANK0);

    ReadReg(0, 1, &data0);
    ReadReg(1, 1, &data1);

    Serial.print("Addr0 =");
    Serial.print(data0, HEX);
    Serial.print(",  Addr1 =");
    Serial.println(data1, HEX);

    if ((data0 != 0x20) || (data1 != 0x76)) {
        return 0xff;
    }
    if (data0 == 0x20) {
        Serial.println("wake-up finish.");
    }

    for (i = 0; i < INIT_REG_ARRAY_SIZE; i++) {
        WriteReg(initRegisterArray[i][0], initRegisterArray[i][1]);
    }

    SelectBank(BANK0);  //gesture flage reg in Bank0

    Serial.println("Paj7620 initialize register finished.");

    return 0;
}

byte PAJ7620::WriteReg(byte addr, byte cmd) {
    char i = 1;
    Wire.beginTransmission(PAJ7620_ID);  // start transmission to device
    //write cmd
    Wire.write(addr);            // send register address
    Wire.write(cmd);             // send value to write
    i = Wire.endTransmission();  // end transmission
    if (0 != i) {
        Serial.print("Transmission error!!!\n");
    }
    return i;
}

byte PAJ7620::ReadReg(byte addr, byte qty, byte data[]) {
    byte error;
    Wire.beginTransmission(PAJ7620_ID);
    Wire.write(addr);
    error = Wire.endTransmission();

    if (0 != error) {
        Serial.print("Transmission error!!!\n");
        return error;  //return error code
    }

    Wire.requestFrom((int)PAJ7620_ID, (int)qty);

    while (Wire.available()) {
        *data = Wire.read();
        data++;
    }
    return 0;
}

void PAJ7620::SelectBank(bank_e bank) {
    switch (bank) {
        case BANK0:
            WriteReg(PAJ7620_REGITER_BANK_SEL, PAJ7620_BANK0);
            break;
        case BANK1:
            WriteReg(PAJ7620_REGITER_BANK_SEL, PAJ7620_BANK1);
            break;
        default:
            break;
    }
}