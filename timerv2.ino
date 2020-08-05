//only uno now, no more nan0
//A0 above 900 when not touched, jumps to around sub 700 when touched
//A5 above 900 when not touched, jumps to ariund sub 800 when touched   
#include <elapsedMillis.h>
#include <LiquidCrystal.h> 
//fuck wire.h
byte sw= 2; //change to whatever input you choose
byte ledstate = 0; //led state
byte state = 0; //program state
byte istate = 0; //inspection state
byte sstate = 0; //solve state
bool oof = 1; //blinking light
int red, green, blue = 0; //rgb values
byte do_shit_once = 0; //do shit onces
byte inspection = 0; //inspections time pastesed
unsigned long sec = 0, min = 0, mili = 0; //used to calculate final time
unsigned long time = 0; //save time
LiquidCrystal lcd(12, 8, 6, 5, 4, 3); //lcd object

void setup()
{
    pinMode(sw, INPUT_PULLUP); //switch press
    lcd.begin(16, 2);
    Serial.begin(9600);
}

void loop()
{
    while (state == 0) //setting up leds
    {
        analogWrite(9, red);
        analogWrite(10, green);
        analogWrite(11, blue);
        //red
        while(ledstate == 0)
        {
            if(analogRead(2) == 0)
            {
                if (red < 255)
                {
                    red+= 1;
                }
                else
                {
                    red = red;
                }
                analogWrite(9, red);
                delay(10);
            }
            else if (analogRead(2) == 1023)
            {
                if(red > 0)
                {
                    red-= 1;
                }
                else
                {
                    red = red;
                }
                analogWrite(9, red);
                delay(10);
            }
            if(analogRead(4) == 0)
            {
                delay(300);
                ledstate = 1;
            }
            if (digitalRead(sw) == LOW)
            {
                delay(300);
                state = 1;
                break;
            }
        }
        //green
        while (ledstate == 1)
        {
            if(analogRead(2) == 0)
            {
                if (green < 255)
                {
                    green+= 1;
                }
                else
                {
                    green = green;
                }
                analogWrite(10, green);
                delay(10);
            }
            else if (analogRead(2) == 1023)
            {
                if(green > 0)
                {
                    green-= 1;
                }
                else
                {
                    green = green;
                }
                analogWrite(10, green);
                delay(10);   
            }
            if(analogRead(4) == 0)
            {
                delay(300);
                ledstate = 2;
            }
            else if(analogRead(4) == 1023)
            {
                delay(300);
                ledstate = 0;
            }
            if (digitalRead(sw) == LOW)
            {
                delay(300);
                state = 1;
                break;
            }
        }
        //blue
        while (ledstate == 2)
        {
            if(analogRead(2) == 0)
            {
                if (blue < 255)
                {
                    blue+= 1;
                }
                else
                {
                    blue = blue;
                }
                analogWrite(11, blue);
                delay(10);
            }
            else if (analogRead(2) == 1023)
            {
                if(blue > 0)
                {
                    blue-= 1;
                }
                else
                {
                    blue = blue;
                }
                analogWrite(11, blue);
                delay(10);
            }
            if(analogRead(4) == 1023)
            {
                delay(300);
                ledstate = 1;
            }
            if (digitalRead(sw) == LOW)
            {
                delay(300);
                state = 1;
                break;
            }
        }
    }
    while (state == 1)//began inspection
    {
        elapsedMillis x;
        lcd.clear();
        lcd.print("Inspection Time:");
        lcd.setCursor(0,1);
        lcd.print(inspection);
        while (do_shit_once == 0)//so it will only do the above code one time.
        {           
            while (istate == 0)//before they put their hands on timer
            {
                if (x >= 1000) //inspection time has gone up 1 seconds
                {
                    inspection+=1;
                    if (inspection >= 18) //dnf lmao
                    {
                        state = 69;
                        istate = 3;
                        break;
                    }
                    else //no dnf
                    {
                        lcd.clear();
                        lcd.print("Inspection Time:");
                        lcd.setCursor(0,1);
                        lcd.print(inspection);
                        x = 0;
                    }
                }
                if (analogRead(0) <= 700 && analogRead(5) <= 800)
                {
                    for(byte i = 9; i<= 11; i++)
                    {
                        analogWrite(i, 0);
                    }
                    istate = 1;
                    break;
                }
            }
            while (istate == 1) //after hands on timer
            {
                elapsedMillis hold;
                while (hold < 550)//takes hands off too early
                {
                    if (x >= 1000)
                    {
                        inspection+=1;
                        if (inspection >= 18)
                        {
                            state = 69;
                            istate = 3;
                            hold = 1000;
                            break;
                        }
                        else
                        {
                            lcd.clear();
                            lcd.print("Inspection Time:");
                            lcd.setCursor(0,1);
                            lcd.print(inspection);
                            x = 0;
                        }
                    }
                    if (analogRead(0) > 700 && analogRead(5) > 800)
                    {
                        analogWrite(9, red);
                        analogWrite(10, green);
                        analogWrite(11, blue);
                        break;
                    }
                }
                while (hold >= 550)//take hands off now
                {
                    if (x >= 1000)
                    {
                        inspection+=1;
                        if (inspection >= 18)
                        {
                            state = 69;
                            istate = 2;
                            break;
                        }
                        else
                        {
                            lcd.clear();
                            lcd.print("Inspection Time:");
                            lcd.setCursor(0,1);
                            lcd.print(inspection);
                            x = 0;
                        }
                    }
                    if (analogRead(0) > 700 && analogRead(5) > 800)
                    {                    
                        analogWrite(9, red);
                        analogWrite(10, green);
                        analogWrite(11, blue);
                        lcd.clear();
                        lcd.print("Solve");
                        istate = 2;
                        state = 2;
                        break;
                    }
                }
            }
            while (istate == 2)
            {
                do_shit_once = 1;
                break;
            }
            while (istate == 3)
            {
                do_shit_once = 2;
                break;
            }
        }
        while (do_shit_once == 1)
        {   
            state = 2;
            break;
        }
        while (do_shit_once == 2)
        {
            state = 69;
            break;
        }
    }
    while (state == 2)//solving
    {
        elapsedMillis time; //how much time will you take?
        do_shit_once = 1;
        while (do_shit_once == 1) //do above code once pls
        {
            elapsedMillis light;
            while (light < 100)
            {
                if (analogRead(0) <= 700 && analogRead(5) <= 800) //calcularing final time as well as displaying it
                {
                    ledstate = 0;
                    analogWrite(9, red);
                    analogWrite(10, green);
                    analogWrite(11, blue);
                    min = time/60000;
                    sec = (time-(min*60000))/1000;
                    mili = (time-(min*60000))-(sec*1000);
                    lcd.clear();
                    lcd.print("Your time was:");
                    lcd.setCursor(0,1);
                    if (min > 0 && min < 10)
                    {
                        lcd.print("0");
                    }
                    lcd.print(min);
                    lcd.print(":");
                    if (sec < 10)
                    {
                        lcd.print("0");
                    }
                    lcd.print(sec);
                    lcd.print(".");
                    lcd.print(mili);
                    do_shit_once = 2;
                    break;
                }
            }
            while (light >= 100)
            {
                onoff();
                light = 0;
            }
        }
        while (do_shit_once == 2)
        {
            state = 3;
            break;
        }
    }
    while (state == 3) //reset
    {
        if (digitalRead(sw)== LOW)
        {
            do_shit_once = 0;
            ledstate = 0;
            istate = 0;
            sstate = 0;
            oof = 1;
            inspection = 0;
            sec = 0;
            min = 0;
            mili = 0;
            time = 0;
            lcd.clear();
            state = 0;
            break;
        }
    }
    while (state == 69) //dnf
    {
        do_shit_once = 0;
        ledstate = 0;
        istate = 0;
        sstate = 0;
        oof = 1;
        inspection = 0;
        sec = 0;
        min = 0;
        mili = 0;
        lcd.clear();
        lcd.print("DNF");
        time = 0;
        state = 0;
        break;
    }
}

void onoff() //turns light on and off
{
        if (oof == 0)
        {
            analogWrite(9, red);
            analogWrite(10, green);
            analogWrite(11, blue);
            oof = 1;
        }
        else
        {
            analogWrite(9, 0);
            analogWrite(10, 0);
            analogWrite(11, 0);
            oof = 0;
        }
}
//Funny skeleton
/*
░░░░░░░░░░▄▄▀▀▀▀▀▀▀▀▀▄▄░░░░░░░░░░
░░░░░░░░░█░░░░░░░░░░░░░█░░░░░░░░░
░░░░░░░░█░░░░░░░░░░▄▄▄░░█░░░░░░░░
░░░░░░░░█░░▄▄▄░░▄░░███░░█░░░░░░░░
░░░░░░░░▄█░▄░░░▀▀▀░░░▄░█▄░░░░░░░░
░░░░░░░░█░░▀█▀█▀█▀█▀█▀░░█░░░░░░░░
░░░░░░░░▄██▄▄▀▀▀▀▀▀▀▄▄██▄░░░░░░░░ 
░░░░░░▄█░█▀▀█▀▀▀█▀▀▀█▀▀█░█▄░░░░░░ 
░░░░░▄▀░▄▄▀▄▄▀▀▀▄▀▀▀▄▄▀▄▄░▀▄░░░░░ 
░░░░░█░░░░▀▄░█▄░░░▄█░▄▀░░░░█░░░░░ 
░░░░░░▀▄▄░█░░█▄▄▄▄▄█░░█░▄▄▀░░░░░░ 
░░░░░░░░▀██▄▄███████▄▄██▀░░░░░░░░ 
░░░░░░░░████████▀████████░░░░░░░░ 
░░░░░░░▄▄█▀▀▀▀█░░░█▀▀▀▀█▄▄░░░░░░░ 
░░░░░░░▀▄▄▄▄▄▀▀░░░▀▀▄▄▄▄▄▀░░░░░░░
*/