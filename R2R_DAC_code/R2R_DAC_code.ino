#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11

#define FREQ A0
#define SWITCH_PIN 2         //Push button to switch waveform

#define N 50            //Samples per cycle

volatile int switch_state = HIGH;

int table_index = 0;
uint8_t v_level;

uint16_t ARR_check = 35;

//Lookup tables for waveforms
int wave_table[N];

uint8_t curr_table = 1;

void timer1_init();

//Function definitions to generate wave tables
void get_sine_table();
void get_rsaw_table();
void get_lsaw_table();
void get_triangle_table();


void setup() {
  DDRB = B1111;      //Set Pins 8-11 as Inputs
  
  timer1_init();    //Initiate timer

  //initiate button interrupt to change waveform
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switch_pin_ISR, FALLING);

  //Initialize wave tables
  get_sine_table();
}

void loop(){
  ARR_check = analogRead(FREQ)+35;
  if (abs(ARR_check - OCR1A) > 25){
    OCR1A = ARR_check;  
    }
  
  delay(50);
  }

void timer1_init(){
  noInterrupts();        
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 35;               //Compare Value
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1<<CS11);       // 8 prescaler 
  TIMSK1 |= (1 << OCIE1A);   // enable timer compare interrupt

  interrupts();     
}

ISR(TIMER1_COMPA_vect){
  v_level = wave_table[table_index];
  PORTB = v_level;         
  table_index = (table_index+1)%N;
  
}

void switch_pin_ISR(){
  curr_table = (curr_table + 1)%4;
    switch(curr_table){
    case 0:
      get_sine_table();
      break;
    
    case 1:
      get_rsaw_table();
      break;
    
    case 2:
      get_lsaw_table();
      break;

    case 3:
      get_triangle_table();
      break;
    }
  }

void get_sine_table(){
  for (int i = 0; i < N; i++){
    wave_table[i] = int(7.5+7.5*sin(i*(2*3.14)/N));
  }
}

void get_rsaw_table(){
  for (int i = 0; i < N; i++){
    wave_table[i] = int(i*(15.0/N));
  }
}

void get_lsaw_table(){
  for (int i = 0; i < N; i++){
    wave_table[i] = int(15 - i*(15.0/N));
  }
}

void get_triangle_table(){
  for (int i = 0; i < N; i++){
    if (i<(N/2)){
      wave_table[i] = int(i*(15.0/(N/2)));
      }
    else{
      wave_table[i] = int(15 - (i-N/2)*(15.0/(N/2)));
      }
  }
}
