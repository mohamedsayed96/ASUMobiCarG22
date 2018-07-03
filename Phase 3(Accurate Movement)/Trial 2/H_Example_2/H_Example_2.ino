#include <NewPing.h>
#define sensor1 12
#define sensor2 13
#define sensor3 4

#define M1A 6
#define M1B 7
#define M2A 8
#define M2B 9


#define EN1 5
#define EN2 10

# define echo A0
#define trig A1

# define encoder_left_pin 2
#define encoder_right_pin 3
NewPing sonar(trig,echo, 200);
char Bluetooth;
int l1;
int l2;
int l3;
int Laststate;


const float TICK_MULTI =4;
int distance=0;
int Number_Ticks=0;
int encoder_left=0;
int encoder_right=0;
        
//prototypes for functions
void Forward(int speed);
void Backward(int speed);
void Right(int speed);
void Left(int speed);
void Stop();

void setup()
{
 pinMode(encoder_left_pin, INPUT_PULLUP);
 pinMode(encoder_right_pin, INPUT_PULLUP);
  
 pinMode(echo,OUTPUT);
 pinMode(trig,OUTPUT);
 pinMode(M1A,OUTPUT);
 pinMode(M1B,OUTPUT);
 pinMode(M2A,OUTPUT);
 pinMode(M2B,OUTPUT);
 pinMode(EN1,OUTPUT);
 pinMode(EN2,OUTPUT);
 pinMode(sensor1,INPUT);
 pinMode(sensor2,INPUT);
 pinMode(sensor3,INPUT);
 Serial.begin(9600);


  attachInterrupt(digitalPinToInterrupt(encoder_left_pin), countLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_right_pin), countRight, CHANGE);
  
 }

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0)
{
  Bluetooth=Serial.read();
  Serial.println(Bluetooth);
  if(Bluetooth=='Q')
  {
    Phase1();
    }

  if(Bluetooth=='W')
  {
    Phase2();
    }  
  if(Bluetooth=='E')
  {
    Phase3();
    }

  }
}

void Phase1()
{
  Serial.println("I am in Phase 1");
while(1)
{
  Bluetooth = Serial.read();
 if(Bluetooth=='W')
 Phase2();
 if(Bluetooth=='E')
 Phase3();


 unsigned int distanceInCms = sonar.ping() / US_ROUNDTRIP_CM;
       if(Bluetooth == 'F' && distanceInCms<40) Forward(255); //Stop();
      else if(Bluetooth=='F') Forward(255);
      else if(Bluetooth=='B') Backward(255);
       else if(Bluetooth=='R') Right(255);
       else if(Bluetooth=='L') Left(255);
       else Stop();
  
  
  }
}
void Phase2()
{
  Serial.println("I am in Phase 2");
while(1)
{
  Bluetooth = Serial.read();
 if(Bluetooth=='Q')
 Phase1();
 if(Bluetooth=='E')
 Phase3();

l1=digitalRead(sensor1);
l2=digitalRead(sensor2);
l3=digitalRead(sensor3);
if((l1==0&&l2==1&&l3==1 )||(l1==0&&l2==0&&l3==1))
        {
          Left(90);
          Laststate=1;
         }
         else if((l1==1&&l2==1&&l3==0)||(l1==1&&l2==0&&l3==0))
         {
          Right(90);
          Laststate=3;
          } 
          else if(l1==1&&l2==0&&l3==1) 
         {
          Forward(90);
          Laststate=2;
          }
          else if((l1==0&&l2==0&&l3==0)||(l1==1&&l2==1&&l3==1)) 
          { 
              if(Laststate==2)Forward(90);
              else if(Laststate==3) Right(90);
              else if(Laststate==1) Left(90);
            
            }
  
  }
}
void Phase3()
{
   Serial.println("I am in Phase 3");
while(1)
{
 Bluetooth = Serial.read();
 if(Bluetooth=='W')
 Phase2();
 if(Bluetooth=='Q')
 Phase1();


  if(Bluetooth=='d')
  {
   /* while (Bluetooth !='d')
    {
      distance= Bluetooth + distance*10;
      
      }
*/
distance=200;
      Serial.print("Distance ");
      Serial.println(distance);
    Number_Ticks = TICK_MULTI*distance;

Serial.print("Number_Ticks: ");
    Serial.println(Number_Ticks);
    
      Serial.print("Encoder Left ");
      Serial.println(encoder_left);

      Serial.print("Encoder Right ");
      Serial.println(encoder_right);

      

      Serial.println("__________________________");


    while(Number_Ticks>encoder_left && Number_Ticks>encoder_right)
    {
      Serial.print("Encoder Left");
      Serial.println(encoder_left);

      Serial.print("Encoder Right");
      Serial.println(encoder_right);

      
      Forward(200);
      }
    
Stop();

    }
  
  }
Stop();
}
// directions functions
void Forward(int speed)
{
      digitalWrite(M1A,HIGH);
      digitalWrite(M1B,LOW);

      digitalWrite(M2A,LOW);
      digitalWrite(M2B,HIGH);
      analogWrite(EN1,speed+50);
      analogWrite(EN2,speed);
  }
void Backward(int speed)
{
  digitalWrite(M1A,LOW);
      digitalWrite(M1B,HIGH);

      digitalWrite(M2A,HIGH);
      digitalWrite(M2B,LOW);
      analogWrite(EN1,speed);
      analogWrite(EN2,speed);
  }
  void Right(int speed)
  {
      digitalWrite(M1A,HIGH);
      digitalWrite(M1B,LOW);

      digitalWrite(M2A,LOW);
      digitalWrite(M2B,LOW);

           analogWrite(EN1,speed);
      analogWrite(EN2,speed);
    }

void Left(int speed)
{     
      digitalWrite(M1A,LOW);
      digitalWrite(M1B,LOW);

      digitalWrite(M2A,LOW);
      digitalWrite(M2B,HIGH);
           analogWrite(EN1,speed);
      analogWrite(EN2,speed);
  }
  void Stop()
  {
      digitalWrite(M1A,LOW);
      digitalWrite(M1B,LOW);
      digitalWrite(M2A,LOW);
      digitalWrite(M2B,LOW);
      digitalWrite(EN1,LOW);
      digitalWrite(EN2,LOW);
     
    }


void countLeft() {
  encoder_left++;
}

void countRight() {
  encoder_right++;
}    


