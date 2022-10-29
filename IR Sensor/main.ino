int IRSensor = 2;
int LED = 13;

void setup()
{
    pinMode(IRSensor, INPUT);
    pinMode(LED, OUTPUT);
}

void loop()
{
    int statusSensor = digitalRead(IRSensor);

    if (statusSensor == 1)
    {
        digitalWrite(LED, LOW);
    }

    else
    {
        digitalWrite(LED, HIGH);
    }
}