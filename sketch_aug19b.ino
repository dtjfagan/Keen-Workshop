// 100K NTC Thermistor + 100K series resistor voltage divider
// Wiring: 5V -> Thermistor -> A0 (junction) -> 100K Resistor -> GND

const int THERMISTOR_PIN = A0;

const float SERIES_RESISTOR = 100000.0;   // fixed resistor value (ohms)
const float NOMINAL_RESISTANCE = 100000.0; // thermistor resistance at 25°C
const float NOMINAL_TEMPERATURE = 25.0;    // reference temp for nominal resistance (°C)
const float B_COEFFICIENT = 3950.0;        // Beta coefficient - check your thermistor's datasheet

const int NUM_SAMPLES = 5; // average a few readings to reduce noise

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Average several ADC readings
  long total = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    total += analogRead(THERMISTOR_PIN);
    delay(10);
  }
  float adc = (float)total / NUM_SAMPLES;

  // Thermistor is on the HIGH side of the divider (5V -> therm -> A0 -> resistor -> GND)
  float resistance = SERIES_RESISTOR * (1023.0 / adc - 1.0);

  // Beta equation (Steinhart-Hart simplified)
  float steinhart = resistance / NOMINAL_RESISTANCE;      // R/Ro
  steinhart = log(steinhart);                             // ln(R/Ro)
  steinhart /= B_COEFFICIENT;                              // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);       // + (1/To)
  steinhart = 1.0 / steinhart;                              // invert
  float tempC = steinhart - 273.15;                        // convert to °C
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.print(" ohms\tTemp: ");
  Serial.print(tempC);
  Serial.print(" *C / ");
  Serial.print(tempF);
  Serial.println(" *F");

  delay(1000);
}
