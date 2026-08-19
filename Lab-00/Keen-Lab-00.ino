// Cytron SHIELD-MD10 (single channel, terminals A/B) driving a 12V DC motor at full speed
// PWM/DIR pins are jumper-selectable on the shield — confirm against the silkscreen
// next to the jumpers on your board. These match Cytron's official example sketch.

const int PWM_PIN = 3;   // Speed control
const int DIR_PIN = 2;   // Direction control

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, HIGH); // HIGH = one direction; flip to LOW to reverse
                                // (if "forward" comes out backwards, swap the A/B motor leads instead)
  analogWrite(PWM_PIN, 120);   // 255 = full speed
}

void loop() {
  // Motor holds full speed continuously
}
