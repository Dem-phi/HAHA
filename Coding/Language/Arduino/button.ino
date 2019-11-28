#include <arduino.h>

void Foreward();
void Inversion();
int A = 2 ;
int B = 3 ;

void setup()
{
    pinMode(A,INPUT);
    pinMode(B,INPUT);
    pinMode(9,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    attachInterrupt(0,Foreward,RISING);
    attachInterrupt(1,Inversion,RISING);
}

void loop()
{
    delay(100);
}

void Foreward ()
{
    int i ;
    for ( i = 0; i <= 255; i=i+5)
    {
        digitalWrite(11,HIGH);
        digitalWrite(12,LOW);
        analogWrite(9,i);
        delay(10);
    }
    delay(1000);
}

void Inversion()
{
    int i ;
    for ( i = 0; i<= 255 ; i=i+5)
    {
        digitalWrite(11,LOW);
        digitalWrite(12,HIGH);
        analogWrite(9,i);
        delay(10);
    }
    delay(1000);
}