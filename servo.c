#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "servo.h"

#define mDETECTOR (1<<10)
#define S3_bm (1<<7)
#define SERVO_OFFSET 12

enum ServoState {CALLIB, IDLE, IN_PROGRESS, OFFSET};
enum DetectorState {ACTIVE, INACTIVE};

struct Servo
{
    enum ServoState eState;
    unsigned int uiCurrentPosition;
    unsigned int uiDesiredPosition;
};

struct Servo sServo;

void DetectorInit()
{
    IO0DIR=IO0DIR&~(S3_bm);
}

enum DetectorState eReadDetector()
{
    if (0 == (IO0PIN & S3_bm))
    {
        return ACTIVE;
    }
    else
    {
        return INACTIVE;
    }
}

void ServoCallib(void)
{
    sServo.eState = CALLIB;
    while(eReadDetector() != ACTIVE){
    }
}

void ServoGoTo(unsigned int uiPosition)
{
    sServo.uiDesiredPosition = uiPosition;
    sServo.eState = IN_PROGRESS;
}

void Automat(void)
{
    switch(sServo.eState)
    {
    case CALLIB:
    {
        if (eReadDetector()==INACTIVE)
        {
            LedStepLeft();
            sServo.eState = CALLIB;
        }
        else
        {
            sServo.eState = OFFSET;
            sServo.uiDesiredPosition=0;
            sServo.uiCurrentPosition=0;
        }
        break;
    }
    case OFFSET:
    {
        if (sServo.uiCurrentPosition == SERVO_OFFSET)
        {
            sServo.uiCurrentPosition = 0;
            sServo.eState = IDLE;
        }
        else
        {
            sServo.uiCurrentPosition++;
            LedStepRight();
            sServo.eState = OFFSET;
        }
        break;
    }
    case IDLE:
    {
        if (sServo.uiCurrentPosition == sServo.uiDesiredPosition)
        {
            sServo.eState = IDLE;
        }
        else
        {
            sServo.eState = IN_PROGRESS;
        }
        break;
    }
    case IN_PROGRESS:
    {
        if (sServo.uiCurrentPosition != sServo.uiDesiredPosition)
				{
            if (sServo.uiCurrentPosition < sServo.uiDesiredPosition)
            {
                LedStepRight();
                sServo.uiCurrentPosition++;
            }
            else if (sServo.uiCurrentPosition > sServo.uiDesiredPosition)
            {
                LedStepLeft();
                sServo.uiCurrentPosition--;
            }
            sServo.eState = IN_PROGRESS;
        }
        else
				{
            sServo.eState = IDLE;
        }
        break;
    }
    default:
        break;
    }
}

void ServoInit(unsigned int uiServoFrequency)
{
    LedInit();
    DetectorInit();
    Timer0Interrupts_Init(1000000/uiServoFrequency,&Automat);
    ServoCallib();
}
