
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
#include <LiquidCrystal_I2C.h>

#define YLed 0
#define RLed 2
#define GLed 4

  #define line1 25
  #define line2 26
  #define line3 27
  #define column1 32 
  #define column2 33

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

LiquidCrystal_I2C lcd (0x27, 16,2);

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

// void reducexByFor(*int x, byte quantity, byte seconds){
  
// }

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
    
    lcd.init();
     lcd.backlight();  
    lcd.print("LCD funcionando");

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
          Serial.println("botão SELECT");
          bleGamepad.press(BUTTON_10);
          delay(450);
          bleGamepad.release(BUTTON_10);
      }
      if (digitalRead(line2) == false)
      {
          Serial.println("botão X");
          bleGamepad.press(BUTTON_1);
          delay(450);
          bleGamepad.release(BUTTON_1);
      }

      if (digitalRead(line3) == false)
      {
          Serial.println("botão A");
          bleGamepad.press(BUTTON_2);
          delay(450);
          bleGamepad.release(BUTTON_2);
      }

      digitalWrite(column1, HIGH);
      digitalWrite(column2, LOW);
      if (digitalRead(line1) == false)
      {
          Serial.println("botão START");
          bleGamepad.press(BUTTON_9);
          delay(450);
          bleGamepad.release(BUTTON_9);
      }
      if (digitalRead(line2) == false)
      {
          Serial.println("botão B");
          bleGamepad.press(BUTTON_3);
          delay(450);
          bleGamepad.release(BUTTON_3);
      }
      
      if (digitalRead(line3) == false)
      {
           Serial.println("botão Y");
          bleGamepad.press(BUTTON_4);
          delay(450);
          bleGamepad.release(BUTTON_4);
      }


      int AxisX = map(analogRead(14), 0, 4095, 0, 32767);
      byte qtdByDir = round(map(AxisX, 0, 32767, 0, 6));
      byte AxisPercent = round(map(AxisX, 0, 32767, 0, 100));
      
      


      if (AxisPercent > 50){
      ShowInScreen(1,qtdByDir);
      } else if (AxisPercent < 50) {
      ShowInScreen(2,qtdByDir);
      } else{
      ShowInScreen(3,0);
      }

        

      // Serial.println(AxisX);
      // Serial.println(AxisPercent);
      // Serial.println(qtdByDir);
      
      //bleGamepad.setAxes(AxisX, ZeroAxis);
    
      int acellTrigger = map(analogRead(34), 0, 2500, 0, 30000);

      int breakTrigger = map(analogRead(35), 0, 2500, 0, 30000);

      //int acellTrigger = round(map(acellPercent * 2, 0, 100, 0, (32767/6*4)));
      //bleGamepad.setRightTrigger(acellTrigger);
      bleGamepad.setAxes(AxisX, 0, 0, 0, breakTrigger, acellTrigger);

      byte percentAcell = map(acellTrigger, 0, 30000, 0, 100);
      byte percentBreak = map(breakTrigger, 0, 30000, 0, 100);
     
      Serial.print("Acelerador: ");
      Serial.print(percentAcell);
      Serial.print("% ");
      Serial.print("Freio: ");
      Serial.print(percentBreak);
      Serial.println("%");
      

      
      // if (acellPercent < 40){
      //   bleGamepad.setRightTrigger(0);
      // } else{
      //   Serial.println("acelerando");
      //  bleGamepad.setRightTrigger(acellTrigger);
      // }

        

       
    } else {
      delay(250);
      BlinkLed(YLed);
      digitalWrite(GLed,0);
      analogWrite(GLed, 0);
      analogWrite(RLed, 255);
    }
}


