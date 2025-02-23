#include <Servo.h>
#include <FastLED.h>

#define LED_PIN 6
#define NUM_LEDS 72

CRGB leds[NUM_LEDS];
Servo myServo;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.print("Arduino active");
  Serial.print("\n");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(8, OUTPUT);

  Serial.begin(9600);

  //servo
  myServo.attach(9);
  myServo.write(0);

  //leds
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();

  // roof
  digitalWrite(8, LOW);

  for (int i=0; i<3; i++) // Blink 3 times
  {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
  }
}

// the loop function runs over and over again forever
void loop() {
                 
  if (Serial.available())
  {
    // Test for com
    char c = Serial.read();
    if (c == '0') {
      digitalWrite(LED_BUILTIN, 0); // close roof
      Serial.print("closing roof");
      Serial.print("\n");
      myServo.write(0);
    }
    else if (c == '1') {
      digitalWrite(LED_BUILTIN, 1); // open roof
      Serial.print("opening roof");
      Serial.print("\n");
      myServo.write(90);
    }

    else if (c == '2') { // shower on
      digitalWrite(8, HIGH);
      Serial.print("shower on");
      Serial.print("\n");
    }
    else if (c == '3') { // shower off
      digitalWrite(8, LOW);
      Serial.print("shower off");
      Serial.print("\n");
    }
    else if (c == '4') { // leds on
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
      }
      FastLED.show();
      Serial.print("leds on");
      Serial.print("\n");
    }
    else if (c == '5') { // leds off
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
      Serial.print("leds off");
      Serial.print("\n");
    }
    else if (c == 'c') { // change led color
      int r = Serial.parseInt();
      int g = Serial.parseInt();
      int b = Serial.parseInt();

      fill_solid(leds, NUM_LEDS, CRGB(r,g,b));
      FastLED.show();
      Serial.print("leds on");
      Serial.print("\n");
    }
  }
}


