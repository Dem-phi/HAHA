#include <Arduino.h>
#include <MsTimer2.h>

#define ENCODER_A 2
#define ENCODER_B 3
#define Pi 3.14159

void getEncoder();
int PID_Controller(float target_velocity,float current_velocity);
void Control();

volatile long encoderVal;//get the value of encoder
float velocity;
int PERIED = 50;//one cycle
int TARGET = 30;//target velocity
float EK[3];//EK[0] means now,EK[1] means last moment,EK[2] means earlier
float UK = 0;// 当前值 UK = Uk+Kp*EK[0]

void setup()
{
    TCCR1B = TCCR1B & B11111000 | B00000001;
    pinMode(ENCODER_A,INPUT);
    pinMode(ENCODER_B,INPUT);
    pinMode(10,OUTPUT);//connect to ENA of L298N
    pinMode(11,OUTPUT);//connect to IN1 ~
    pinMode(12,OUTPUT);//connect to IN2 ~
    attachInterrupt(0,getEncoder,CHANGE);
    Serial.begin(9600);
    MsTimer2::set(PERIED,Control);
    MsTimer2::start();
}

void loop()
{
    Serial.print("the velocity is ")
    Serial.println(velocity);
    delay(PERIED);
}

void getEncoder()
{
    if(digitalRead(ENCODER_A) == LOW)
    {
        if(digitalRead(ENCODER_B)==LOW)
        {
            encoderVal--;//inverse
        }
        else
        {
            encoderVal++;
        }
        
    }
    else
    {
        if(digitalRead(ENCODER_B)==LOW)
        {
            encoderVal++;
        }
        else
        {
            encoderVal--;
        }
        
    }
    
}

int PID_Controller(float target_velocity,float current_velocity)
{
    float output;
    int Kp = 1 ,Ti = 10,Td =0 ,T = PERIED;
    float q0 = Kp*(1+T/Ti+Td/T);
    float q1 = (-Kp)*(1+2*Td/T);
    float q2 = Kp*Td/T;
    EK[0] = target_velocity - current_velocity;
    UK = UK + q0*EK[0] + q1*EK[1] + q2*EK[2];
    EK[2] = EK[1];
    EK[1] = EK[0];
    return (int)output;
}

void Control()
{
    velocity = (encoderVal/780.0)*Pi*2.0*(1000/PERIED);
    encoderVal = 0;
    int output = PID_Controller(TARGET,velocity);
    if (output > 0)
    {
        if(output > 255)
        {
            output = 255;
        }
        digitalWrite(11,HIGH);
        digitalWrite(12,LOW);
        analogWrite(10,output);
    }
    else
    {
        if(output < -255);
        {
            output = -255;
        }
        digitalWrite(11,LOW);
        digitalWrite(12,HIGH);
        analogWrite(10,abs(output));
    }
}