/* Shitty stackmat timer 
Made for Arduino Uno 
Atmega 328
You can figure out the stuff
BE SMART AND ADJUST THE PIN VALUES THAT I USED TO SUIT YOUR BOARD
My pins can be found on my video: 
*/ 
int sensor; //730 - 790 = finger covering
bool button = 0; //1 is pressed
byte press; //button press or no
byte state = 0; //program state
bool start = 0; 
float time = 0.0;

void setup()
{
    Serial.begin(9600);
    pinMode(7, INPUT); //button
    //literally all leds
    pinMode(2, OUTPUT); //not needed if leds arent used
    pinMode(3, OUTPUT); //not needed if leds arent used
    pinMode(9, OUTPUT);
}

void loop()
{
    while (state == 0) //check if button pressed, initialization
    {
        time = 0; //these variables being set to 0 is incase they reset
        start = 0;
        press = digitalRead(7);
        sensor = analogRead(5); 
        if (press == 0)
        {
            if (button == 0)
            {
                delay(300);
                button = 1;
            }
            else if(button == 1)
            {
                delay(300);
                button = 0;
            }
        }
        if (sensor >= 730 && sensor <= 790 && button == 1) //they are ready to start
        {
            digitalWrite(9, HIGH); //tells them the timer is ready
            state = 1;
        }
    }
    while (state == 1) //timer is ready to go
    {
        sensor = analogRead(5); //read sensor
        if (sensor > 790)
        {
            if (digitalRead(9) == HIGH) //turns and LED off, and sets the button back to 0 allowing for reusablitiy
            {
                digitalWrite(9, LOW);
                button = 0; 
            }
            time+= 100; //addind time 

            //this section here makes leds blink (YOU CAN REMOVE AND NOT SET UP LEDS PLUS MAKE TIME MORE ACCURATE)
            if (digitalRead(2) == LOW && digitalRead(3) == LOW)
            {
                digitalWrite(2, HIGH);
                delay(100);
            }
            else if (digitalRead(2) == HIGH && digitalRead(3) == LOW)
            {
                digitalWrite(2, LOW);
                digitalWrite(3, HIGH);
                delay(100);
            }
            else if (digitalRead(2) == LOW && digitalRead(3) == HIGH)
            {
                digitalWrite(3, LOW);
                digitalWrite(2, HIGH);
                delay(100);
            }
            //Asthetic 

            Serial.println(time); //can comment out so the person doesnt see their time, also faster shit
            start = 1; //here so this all has to happen before timer can stop
        }
        if (sensor >= 730 && sensor <= 790 && start == 1)
        {
            state = 2;
        }
    }
    while (state == 2) //ending
    {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        Serial.print("Your time was: ");
        Serial.print(time/1000);
        Serial.println(" seconds.");
        Serial.println("Press the button you originally pressed to start again. If not, then do whatever, idk.");
        state = 3; //lmao how many of there am I gonna make
    }
    while (state == 3) //resetting for real this time
    {
        press = digitalRead(7);
        if (press == 0)
        {
            state = 0;
        }
    }
}