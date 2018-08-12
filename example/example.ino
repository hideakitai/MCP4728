#include <Wire.h>
#include "MCP4728.h"

MCP4728 dac;

void setup()
{
    Serial.begin(115200);  // initialize serial interface for print()

    Wire.begin(21, 22);
    dac.attatch(Wire, 14);
    dac.readRegisters();

    dac.selectVref(MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::INTERNAL_2_8V, MCP4728::VREF::INTERNAL_2_8V);
    dac.selectPowerDown(MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_500KOHM, MCP4728::PWR_DOWN::GND_500KOHM);
    dac.selectGain(MCP4728::GAIN::X1, MCP4728::GAIN::X1, MCP4728::GAIN::X2, MCP4728::GAIN::X2);
    dac.analogWrite(MCP4728::DAC_CH::A, 111);
    dac.analogWrite(MCP4728::DAC_CH::B, 222);
    dac.analogWrite(MCP4728::DAC_CH::C, 333);
    dac.analogWrite(MCP4728::DAC_CH::D, 444);

    dac.enable(true);

    dac.readRegisters();
    printStatus();
    delay(5000);
}


void loop()
{
    static int count = 0;
    if (++count > 4000)  count = 0;

    dac.analogWrite(count, count, count, count);

    delay(10);
    dac.readRegisters();
    printStatus();
}

void printStatus()
{
    Serial.println("NAME     Vref  Gain  PowerDown  DACData");
    for (int i = 0; i < 4; ++i)
    {
        Serial.print("DAC");
        Serial.print(i, DEC);
        Serial.print("   ");
        Serial.print("    ");
        Serial.print(dac.getVref(i), BIN);
        Serial.print("     ");
        Serial.print(dac.getGain(i), BIN);
        Serial.print("       ");
        Serial.print(dac.getPowerDown(i), BIN);
        Serial.print("       ");
        Serial.println(dac.getDACData(i), DEC);

        Serial.print("EEPROM");
        Serial.print(i, DEC);
        Serial.print("    ");
        Serial.print(dac.getVref(i, true), BIN);
        Serial.print("     ");
        Serial.print(dac.getGain(i, true), BIN);
        Serial.print("       ");
        Serial.print(dac.getPowerDown(i, true), BIN);
        Serial.print("       ");
        Serial.println(dac.getDACData(i, true), DEC);
    }
    Serial.println(" ");
}