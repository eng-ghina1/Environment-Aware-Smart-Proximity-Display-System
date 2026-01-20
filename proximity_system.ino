#include <LedControl.h>
#include <NewPing.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN  5

#define TRIGGER_PIN 7
#define ECHO_PIN    8
#define MAX_DISTANCE 400

#define SAFE_DIST     100
#define CAUTION_DIST   50
#define WARNING_DIST   20


int DIN = 10;
int CS  = 12;
int CLK = 13;


DHT dht(DHTPIN, DHTTYPE);
LedControl matrix = LedControl(DIN, CLK, CS, 1);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


float hum, temp;
float soundsp, soundcm;
float duration, distance;
int iterations = 5;


void setup() {
  Serial.begin(9600);
  dht.begin();

  matrix.shutdown(0, false);
  matrix.setIntensity(0, 5);
  matrix.clearDisplay(0);
}


void loop() {

  hum  = dht.readHumidity();
  temp = dht.readTemperature();

  if (isnan(temp) || isnan(hum)) {
    displayOutOfRange();
    return;
  }

  // Speed of sound (m/s), temp + humidity compensated
  soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);
  soundcm = soundsp / 10000.0;

  duration = sonar.ping_median(iterations);

  distance = (duration / 2.0) * soundcm;

  Serial.print("Distance (cm): ");
  Serial.println(distance);

  if (distance >= 400 || distance <= 2) {
    displayOutOfRange();
  }
  else if (distance > SAFE_DIST) {
    displaySafe();
  }
  else if (distance > CAUTION_DIST) {
    displayCaution();
  }
  else if (distance > WARNING_DIST) {
    displayWarning();
  }
  else {
    displayDanger();
  }

  delay(500);
}

// -------- DISPLAY FUNCTIONS --------

void displaySafe() {
  byte smiley[8] = {
    B00111100, B01000010, B10100101, B10000001,
    B10100101, B10011001, B01000010, B00111100
  };
  draw(smiley);
}

void displayCaution() {
  byte caution[8] = {
    B00011000, B00111100, B01111110, B00011000,
    B00011000, B00011000, B00000000, B00011000
  };
  draw(caution);
}

void displayWarning() {
  byte warning[8] = {
    B00011000, B00111100, B00111100, B00011000,
    B00011000, B00000000, B00011000, B00000000
  };
  draw(warning);
}

void displayDanger() {
  byte cross[8] = {
    B10000001, B01000010, B00100100, B00011000,
    B00011000, B00100100, B01000010, B10000001
  };
  draw(cross);
  delay(80);
  matrix.clearDisplay(0);
  delay(80);
}

void displayOutOfRange() {
  byte dash[8] = {
    B00000000, B00000000, B01111110, B01111110,
    B01111110, B00000000, B00000000, B00000000
  };
  draw(dash);
}

// -------- HELPER --------
void draw(byte pattern[]) {
  for (int row = 0; row < 8; row++) {
    matrix.setRow(0, row, pattern[row]);
  }
}
