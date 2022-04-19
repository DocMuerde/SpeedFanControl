#include <TimerOne.h>
# define N 10
volatile long int contador=0;
volatile int vector[N];
volatile float ps=0;
volatile int flag=0;


void setup() {
  // put your setup code here, to run once:
  
  Timer1.initialize(100000);
  Timer1.attachInterrupt(func_ISR);
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(INT0, pulsos ,CHANGE);
  Serial.begin(9600);
  Serial.print("PWM");
  Serial.print(",");
  Serial.println("W"); 
  for(int i=0;i<N;i++)
      vector[i]=0;
}

void loop() {
  // Y change from 125 to 175 each 5 seconds
  int y=125+ (50*((millis()/5000)%2));
  analogWrite(3,y);
    if(flag==1)
      {
        Serial.print(y);
        Serial.print(",");
        Serial.println(ps);
        flag=0;
      }
}

void func_ISR() 
  {
    for(int p = N-1; p >= 1; p --)
      {
        vector[p]=vector[p-1];
       }
    vector[0]=contador;
    contador=0;
    ps=0;
    for(int i = 0; i <  N; i += 1)
      {
        ps=ps+vector[i];
       }
    ps=10*ps/N;
    flag=1;
  }

  void pulsos()
  {
    contador=contador+1;
  }
