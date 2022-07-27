
bool enable_delay = false;
int shoot_delay = 0;
int min_delay = 500; 
int max_delay = 1000;
long int last_time = 0; 

int tone_frecuency = 4000;
int tone_time = 500;

bool enable_wait = false;
long int start_time = 0;

void setup() {
  pinMode(4, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Water target firmware");
  Serial.println("V: 1.0");

}

void loop() {

  while (Serial.available() > 0) {
    if (Serial.read() == 's') {
      enable_delay = true;
      shoot_delay = random(min_delay, max_delay);
      last_time = millis();
    }
  }

  if (enable_delay && millis() - last_time >= shoot_delay) {
    tone(10, tone_frecuency, tone_time);
    enable_delay = false;
    enable_wait = true;
    start_time = millis();
  }

  if (!digitalRead(4) && enable_wait) {
    enable_wait = false;
    int duration = millis() - start_time;
    Serial.print("d:");
    Serial.println(duration);
  }

}
