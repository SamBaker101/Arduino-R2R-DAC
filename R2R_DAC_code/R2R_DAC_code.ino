#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11

int DAC_bus[] = {PIN_8, PIN_9, PIN_10, PIN_11};

void test_run();

void test_run2();

void setup() {
  for (int k = 0; k < 4; k++){
    pinMode(DAC_bus[k], OUTPUT);
  }

}

void loop() {
  test_run2();  
}


void test_run(){
  for (int i = 0; i < 4; i++){
    digitalWrite(DAC_bus[i], HIGH);
    delay(5);
    }
  for (int i = 0; i < 4; i++){
    digitalWrite(DAC_bus[4-i], LOW);
    delay(5);
    }
  }

//saw tooth test function
void test_run2(){
  for (int i = 0; i < 15; i++){
    int value = i;
    for (int k = 0; k < 4; k++){
      digitalWrite(DAC_bus[k], value%2);
      value = value/2;
    }
    delay(1);
  }
}
