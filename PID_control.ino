#include <TimerOne.h>
# define N 20
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
  
  Serial.print("REF");
  Serial.print(",");
  Serial.print("W");
  Serial.print(",");
  Serial.println("PWM"); 
  
  for(int i=0;i<N;i++)
      vector[i]=0;
}

void loop() {
  static float eac=0,ea=0;
  float e;
  float kp=1.5;
  float ki=0.1;
  int ref;
  int u;
    if(flag==1)
      {
        // The reference change from 132 to 182 to 232 each 5s
        ref=132+ (50*((millis()/15000)%3));
        e=ref-ps;
        eac+=e;
        u=125+kp*e+ki*eac;
        if (u<0)
          u=0;
        if (u>255)
          u=255;
        analogWrite(3,u); 
             
        Serial.print(ref);
        Serial.print(",");
        Serial.print(ps);
        Serial.print(",");
        Serial.println(u);
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
