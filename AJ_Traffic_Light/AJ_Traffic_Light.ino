int led = 13;

typedef struct SetupStep_t {
  void (*fn)(void*);  
  void* arg;
  struct SetupStep_t* next;
} SetupStep;

SetupStep* setupSteps = NULL;

void initOutput(void* pin) {
  pinMode((int)pin, OUTPUT);
}

bool addSetupStep(SetupStep* s) {
  s->next = setupSteps;
  setupSteps = s;
  return true;
}

#define DEF_LIGHT(lightName, pin) \
int lightName = pin;\
void lightName##_on() {\
  digitalWrite(lightName, HIGH);\
}\
void lightName##_off() {\
  digitalWrite(lightName, LOW);\
}\
SetupStep lightName##Setup = {\
  &initOutput, (void*)pin, NULL\
};\
bool lightName##Registered = \
  addSetupStep(&lightName##Setup);

DEF_LIGHT(we_r, 23);
DEF_LIGHT(we_y, 22);
DEF_LIGHT(we_g, 21);
DEF_LIGHT(ns_r, 20);
DEF_LIGHT(ns_y, 19);
DEF_LIGHT(ns_g, 18);

int bp = 17;

int lights[] = {we_r, we_y, we_g, ns_r, ns_y, ns_g};
uint32_t nlights = sizeof(lights) / sizeof(int);

void st() {
  delay(1000*5);
}

void lt_or_bp() {
  for (int n=0; n<10*60*2; ++n) {
    if (digitalRead(bp) == HIGH) {
      break;
    }
    digitalWrite(led, HIGH);
    delay(1);
    digitalWrite(led, LOW);
    delay(99);
  }
}

// the setup routine runs once when you press reset:
void setup() {   
  pinMode(led, OUTPUT);
  SetupStep* s = setupSteps;
  while (s != NULL) {
    s->fn(s->arg);
    s = s->next;               
  }
  pinMode(bp, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  #include "control.h"
}
