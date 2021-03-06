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
  // Change the value of frec to obtain a different value of the Bode diagram
   float frec=2;  //rad/s =2*pi*frec =Hz T=1/(2*pi*frec)
   int y=125.0+50*sin((millis()*frec/1000.0));
  

  analogWrite(3,y);
    if(flag==1)
      {
        Serial.print(y-125);
        Serial.print(",");
        Serial.println(ps-132.1);
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
    for(int i = 0; i <  N; i++)
      {
        ps=ps+vector[i];
       }
    ps=(10/N)*ps;
    flag=1;
  }

void pulsos()
  {
    contador=contador+1;
  }
