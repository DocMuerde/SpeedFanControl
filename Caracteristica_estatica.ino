#include <TimerOne.h>
# define N 40
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
// change this value to compute a diferent value of the steady state response
  int u=255; 
    if(flag==1)
      {
        analogWrite(3,u);     
        Serial.print(u);
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
