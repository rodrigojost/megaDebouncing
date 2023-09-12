/*
  AUTHOR: Rodrigo Jost
  V1.0
  since  17.03.2022
  for ATMEGA2560 
*/

//pino do botao
#define pinoBotao 2
//flag click do botao
volatile bool pressionado = false;
//contagem de clicks
volatile uint8_t contagem = 0;

void setup() {
  Serial.begin(9600);
  //config das interrupcoes
  cli();
  //inicia habilitando interrupção de falling edge no botao
  attachInterrupt(digitalPinToInterrupt(pinoBotao), eventoFalling, FALLING);
  // Inicializacao do TC4, interrup. após 40ms para compensar bouncing  
  TCCR4A = 0;//reset do registrador
  TCCR4B = 0;//reset do registrador
  TCNT4  = 0;//inicializa contagem em zero
  OCR4A = 12499; // configuração do contador para compensar tempo de bouncing no início e final do click: 150ms do click + 50 ms de debouncing
  // habilita CTC mode
  TCCR4B |= (1 << WGM12);
  // config prescaler de 256
  TCCR4B |= (0 << CS10) | (0 << CS11)| (1 << CS12);  
  // nao habilita interrupção de tempo ainda
  TIMSK4 =0;
  sei();
}

void loop() {
  if(pressionado){
    Serial.println(contagem);
    pressionado = !pressionado;
  }
}

void eventoFalling(){
  pressionado = true; 
  contagem++;
  //desabilita interrupção de FALLING edge e ativa via RISING edge
  detachInterrupt(digitalPinToInterrupt(pinoBotao));
  //reset das flags de evento já ocorrido
  EIFR = bit (INTF4);
  attachInterrupt(digitalPinToInterrupt(pinoBotao), eventoRising, RISING); 
}

void eventoRising(){
  //desabilita RISING
  detachInterrupt(digitalPinToInterrupt(pinoBotao));
  // habilita e inicializa timer 4    
  cli();
  TIFR4 = 0xFF; //reset das flags de evento do timer 4 já ocorrido 
  TCNT4  = 0;//zera contagem
  TIMSK4 = (1 << OCIE4A);// habilita interrupção a partir de comparação
  sei();
}

ISR(TIMER4_COMPA_vect){
  //desabilita interrupcao de comparacao
  TIMSK4 = (0 << OCIE4A);
  //reset das flags de evento já ocorrido
  EIFR = bit (INTF4);
  //reativa interrupção de Falling
  attachInterrupt(digitalPinToInterrupt(pinoBotao), eventoFalling, FALLING);
}
