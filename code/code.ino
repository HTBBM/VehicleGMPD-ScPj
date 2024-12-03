
/*
 * This example turns the ESP32 into a Bluetooth LE gamepad that presses buttons and moves axis
 *
 * At the moment we are using the default settings, but they can be canged using a BleGamepadConfig instance as parameter for the begin function.
 *
 * Possible buttons are:
 * BUTTON_1 through to BUTTON_16
 * (16 buttons by default. Library can be configured to use up to 128)
 *
 * Possible DPAD/HAT switch position values are:
 * DPAD_CENTERED, DPAD_UP, DPAD_UP_RIGHT, DPAD_RIGHT, DPAD_DOWN_RIGHT, DPAD_DOWN, DPAD_DOWN_LEFT, DPAD_LEFT, DPAD_UP_LEFT
 * (or HAT_CENTERED, HAT_UP etc)
 *
 * bleGamepad.setAxes sets all axes at once. There are a few:
 * (x axis, y axis, z axis, rx axis, ry axis, rz axis, slider 1, slider 2)
 *
 * Library can also be configured to support up to 5 simulation controls
 * (rudder, throttle, accelerator, brake, steering), but they are not enabled by default.
 *
 * Library can also be configured to support different function buttons
 * (start, select, menu, home, back, volume increase, volume decrease, volume mute)
 * start and select are enabled by default
 */
                      //Xaxis Yaxis 0 0 LeftTrigger RightTrigger
 //bleGamepad.setAxes(32767, med, 0, 0, 32767, 32767);

#include <Arduino.h>
#include <BleGamepad.h>
#include <LiquidCrystal.h>

#define YLed 0
#define RLed 2
#define GLed 4

  #define line1 23
  #define line2 25
  #define line3 22
  #define column1 26
  #define column2 32

long RightAxis      = 32767;
int ZeroAxis        = 32767/2; //This will be the meddium between triggered and stopped, or a thing like that
int LeftAxis       = 0;

int RightPot       = 0;
int zeroPot         = 4095/2;
int LeftPot         = 4095;


// byte Cols[2] = {26,32};
// byte Rows[3] = {22,23,25};
// String RowsValue[2][3] = {{"A","B","C"}, {"D","E","F"}};

BleGamepad bleGamepad;
BleGamepadConfiguration bleGamepadConfig;

LiquidCrystal lcd(19, 33, 18, 21, 5, 15);

String makeBar(byte quantity){
  String initialString = "";
  for (byte i = 0; i < quantity; i++){
    initialString += "\"";
  }
  return initialString;
}

void BlinkLed(int pin){
  for(byte i = 254; i > 0; i--){
    analogWrite(pin, i);
    delay(3);
  }
}


void ShowInScreen(byte direction, byte qtd){
  lcd.clear();
  if (direction == 1){
    lcd.setCursor(7,0);
    lcd.print("\"\"");
    String lines = makeBar(qtd);
    lcd.print(lines);
  }else if (direction == 2) {
    
    lcd.setCursor(2,0);
    String lines = makeBar(qtd);
    lcd.print(lines);
    lcd.print("\"\"");
  } else{
    lcd.setCursor(7,0);
    lcd.print("\"\"");
  }

  
}



void setup()
{

    pinMode(column1, OUTPUT);
    pinMode(column2, OUTPUT);
    pinMode(line1, INPUT_PULLUP);
    pinMode(line2, INPUT_PULLUP);
    pinMode(line3, INPUT_PULLUP);
    Serial.begin(115200);
    
    Serial.println("Starting BLE work!");
    
    bleGamepadConfig.setSoftwareRevision("Software Rev 1");
    bleGamepadConfig.setSerialNumber("000000001");
    bleGamepadConfig.setModelNumber("1.0");
    bleGamepadConfig.setFirmwareRevision("1.0");
    bleGamepadConfig.setHardwareRevision("1.0");
    bleGamepad.begin(&bleGamepadConfig);  
    
    lcd.begin(16, 2);
    lcd.print("LCD funcionando");

  // for (byte i = 0; i < 2; i++){
  //   pinMode(Cols[i], OUTPUT);
  // }

  // for (byte i = 0; i < 3; i++){
  //   pinMode(Rows[i], INPUT_PULLUP);
  // }

    analogWrite(GLed, 0);
    analogWrite(RLed, 0);
    

    // The default bleGamepad.begin() above enables 16 buttons, all axes, one hat, and no simulation controls or special buttons
}

void loop()
{
    if (bleGamepad.isConnected())
    {

        


      analogWrite(YLed, 0);
      analogWrite(RLed, 0);
      analogWrite(GLed, 255);

        
      

              

      // bleGamepad.setAxes(32767, med, 0, 0, 0, 32767);
      // bleGamepad.setHat1(HAT_DOWN_RIGHT);
      // // All axes, sliders, hats etc can also be set independently. See the IndividualAxes.ino example
      // delay(500);

      // Serial.println("Release button 5 and start. Move all axes to min. Set DPAD (hat 1) to centred.");
      
      // bleGamepad.releaseStart();
      // bleGamepad.setHat1(HAT_CENTERED);
      // bleGamepad.setAxes(0, med, 0, 0, 0, 0, 0, 0);
      // delay(500);
      
      // bleGamepad.setAxes(med, med, 0, 0, 0, 0);

      // delay(500);

      

      digitalWrite(column1, LOW);
      digitalWrite(column2, HIGH);
      if (digitalRead(line1) == false)
      {
          Serial.println("botão START");
          bleGamepad.press(BUTTON_10);
          delay(150);
          bleGamepad.release(BUTTON_10);
      }
      if (digitalRead(line2) == false)
      {
          Serial.println("botão SQUARE");
          bleGamepad.press(BUTTON_1);
          delay(150);
          bleGamepad.release(BUTTON_1);
      }

      if (digitalRead(line3) == false)
      {
          Serial.println("botão X");
          bleGamepad.press(BUTTON_2);
          delay(150);
          bleGamepad.release(BUTTON_2);
      }

      digitalWrite(column1, HIGH);
      digitalWrite(column2, LOW);
      if (digitalRead(line1) == false)
      {
          Serial.println("botão SELECT");
          bleGamepad.press(BUTTON_9);
          delay(150);
          bleGamepad.release(BUTTON_9);
      }
      if (digitalRead(line2) == false)
      {
          Serial.println("botão CIRCLE");
          bleGamepad.press(BUTTON_3);
          delay(150);
          bleGamepad.release(BUTTON_3);
      }
      
      if (digitalRead(line3) == false)
      {
           Serial.println("botão CIRCLE");
          bleGamepad.press(BUTTON_4);
          delay(150);
          bleGamepad.release(BUTTON_4);
      }


      int AxisX = map(analogRead(14), 0, 4095, 0, 32767);
      byte qtdByDir = round(map(AxisX, 0, 32767, 0, 6));
      byte percent = round(map(AxisX, 0, 32767, 0, 100));

      

      if (percent > 50){
      ShowInScreen(1,qtdByDir);
      } else if (percent < 50) {
      ShowInScreen(2,qtdByDir);
      } else{
      ShowInScreen(3,0);
      }

        

      // Serial.println(AxisX);
      // Serial.println(percent);
      // Serial.println(qtdByDir);
      
      //bleGamepad.setAxes(AxisX, ZeroAxis);
      bleGamepad.setAxes(AxisX);
      // bleGamepad.setRightTrigger(32767);
      // bleGamepad.setZ(32767);
      // bleGamepad.setSlider2(32767);
      // bleGamepad.press(BUTTON_5);
    
      int acell = map(analogRead(34), 0, 4095, 0, 100);
      int acellTrigger = map(acell * 2.5, 0, 100, 32767, 0);
      Serial.println(acell);
      if (acell > 18){
        Serial.println("acelerando");
        bleGamepad.setRightTrigger(acellTrigger);
      }else{
        bleGamepad.setRightTrigger(32767);
      }
        

       
    } else {
      delay(250);
      BlinkLed(YLed);
      digitalWrite(GLed,0);
      analogWrite(GLed, 0);
      analogWrite(RLed, 255);
    }
}


