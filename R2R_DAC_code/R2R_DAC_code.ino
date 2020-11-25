#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11

#define N 15

int DAC_bus[] = {PIN_8, PIN_9, PIN_10, PIN_11};

int v_level = 0;

void timer1_init();

void draw_saw();

void setup() {
  DDRB = B1111;      //Set Pins 8-11 as Inputs

  timer1_init();    //Initiate timer
}

void loop(){
  }

void timer1_init(){
  noInterrupts();        
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 125;                //Compare Value
  TCCR1B |= (1 << WGM12);      // CTC mode
  TCCR1B |= (1<<CS11);    // 8 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();     
}


ISR(TIMER1_COMPA_vect){
  PORTB = v_level;         
  v_level = (v_level + 1) % 16;
}
