#define TRIG_PIN 8
#define ECHO_PIN 9

bool running = false;
unsigned long lastMeasureTime = 0;
unsigned long startTime = 0;
const unsigned long interval = 100; // 500 ms = 0.5 s

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Times,Measures");
}

void loop() {
  // Lecture des commandes série
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "START") {
      running = true;
      startTime = millis(); // temps de départ
    } else if (command == "STOP") {
      running = false;
    }
  }

  // Si mesure activée et délai écoulé
  if (1) {
    lastMeasureTime = millis();
    float distance_cm = mesurerHauteur();

    // Envoi formaté : hauteur ; temps depuis START
    Serial.print(millis() - startTime);
    Serial.print(",");
    Serial.println(distance_cm, 2);
  }
}

// Fonction pour mesurer la hauteur
float mesurerHauteur() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duree = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30 ms
  float distance = duree * 0.0343 / 2; // en cm

  return distance;
}
