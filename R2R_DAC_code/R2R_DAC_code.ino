#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11

#define SWITCH_PIN 2         //Push button to switch waveform

#define N 50

volatile int switch_state = HIGH;

int table_index = 0;
int v_level;

int sine_table[50];
int rsaw_table[50];
int lsaw_table[50];
int triangle_table[50];

int curr_table = 1;

void timer1_init();
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
  get_rsaw_table();
  get_lsaw_table();
  get_triangle_table();
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
  switch(curr_table){
    case 0:
      v_level = sine_table[table_index];
      break;
    
    case 1:
      v_level = rsaw_table[table_index];
      break;
    
    case 2:
      v_level = lsaw_table[table_index];
      break;

    case 3:
      v_level = triangle_table[table_index];
      break;
    }
  PORTB = v_level;         
  table_index = (table_index + 1)%(N);
}

void switch_pin_ISR(){
  curr_table = (curr_table + 1)%4;
  }

void get_sine_table(){
  for (int i = 0; i < N; i++){
    sine_table[i] = int(7.5+7.5*sin(i*(2*3.14)/N));
  }
}

void get_rsaw_table(){
  for (int i = 0; i < N; i++){
    rsaw_table[i] = int(i*(15.0/N));
  }
}

void get_lsaw_table(){
  for (int i = 0; i < N; i++){
    lsaw_table[i] = int(15 - i*(15.0/N));
  }
}

void get_triangle_table(){
  for (int i = 0; i < N; i++){
    if (i<(N/2)){
      triangle_table[i] = int(i*(15.0/(N/2)));
      }
    else{
      triangle_table[i] = int(15 - (i-N/2)*(15.0/(N/2)));
      }
  }
}
