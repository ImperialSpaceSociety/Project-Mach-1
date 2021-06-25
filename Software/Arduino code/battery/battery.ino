int value = 0;
float voltage;
float percentage;

#define MIN_BATT 3.6
#define MAX_BATT 4.2

void setup()
{
  analogReadResolution(12);
}

void loop(){

BattLevel(&voltage, &percentage);
Serial.print(voltage);
Serial.print(" ");
Serial.println(percentage);
delay(300);

}

void BattLevel(float *v, float *p)
{
  value = analogRead(A2);
  *v = value * 3.3/4095 * 2;
  if(*v > MAX_BATT or *v < MIN_BATT)
  {
    *p = -1;
  }
  else
  {
    *p = *v * (100 / (MAX_BATT - MIN_BATT));
  }
}
