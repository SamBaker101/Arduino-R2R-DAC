#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11

int DAC_bus[] = {PIN_8, PIN_9, PIN_10, PIN_11};

void test_run();

void test_run2();

void setup() {
  DDRB = B00001111;      //Set Pins 8-11 as Inputs

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
  for (int v_level = 0; v_level < 15; v_level++){
    PORTB = v_level;         
    delay(1);
  }
}
