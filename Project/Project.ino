#include <SoftwareSerial.h>
SoftwareSerial hc05(9,10);
const int pir=8, lr=A0, relay=13;
int pmode, lmode;
char state='0';
void setup()
{
  hc05.begin(9600);
  pinMode(pir,INPUT);
  pinMode(lr,INPUT);
  pinMode(relay,OUTPUT);
}

void loop()
{
  pmode=digitalRead(pir);
  lmode=analogRead(lr);
  if(hc05.available()>0)
    state=hc05.read();
  if(state=='1')
  {
    if(pmode==HIGH && lmode>=512)
    {
      hc05.write("LIGHT ON");
      digitalWrite(relay,HIGH);
      delay(5000);
    }
    else
    {
      digitalWrite(relay,LOW);
      hc05.write("LIGHT OFF");
      delay(1000);
    }
  }
  else if(state=='0')
  {
    digitalWrite(relay,LOW);
    if(pmode==HIGH)
    {
      hc05.write("INTRUSION ALERT");
      delay(1000);
    }
    else
    {
      hc05.write("Surveillance");
      delay(1000);
    }
  }
}
