#include <ev3.h>
#include <iostream>

#define LEFT_TRACE -1
#define RIGHT_TRACE 1

using namespace std;

struct motor_action {
    int leftSpeed;
    int rightSpeed;
};

/*
 * pLineTrace(): simple single sensor proportional black line tracing calculator.
 * 
 * Parameters:
 *    traceSide   - side of line tracing. -1 for left, +1 for right.
 *    refLight    - sensor detected reflected light.
 *    blackV      - black color reflected light value. Defaults to 0.
 *    whiteV      - white color reflected light value. Defaults to 100.
 *    power       - power output of motors
 *    rangeChange - range allowed for power output of motors. will allow for deviation of power output up to ±rangeChange.
 *
 * Returns:
 *    motor_action struct with values leftSpeed & rightSpeed, indicator for speed of left and right motors respectively.
 */
motor_action pLineTrace(int traceSide, int refLight, int blackV, int whiteV, int power, int rangeChange) {

    //Calibrate refLight value
    refLight = ((refLight - blackV) * 100) / (whiteV - blackV);


    //Calculate amount of power offset
    double offsetRatio = (double(refLight - 50)/50.0);
    double powerOffset = double(rangeChange)*offsetRatio;
    
    LcdTextf(1, 0, 0, "s%03d\np%03d\nbC%03d\nwC%03d\n", refLight, int(powerOffset), blackV, whiteV);

    //Calculate final desired speed of motors
    motor_action m;
    m.leftSpeed  = min(max(int(double(power) - (traceSide) * powerOffset), -100), 100);
    m.rightSpeed = min(max(int(double(power) + (traceSide) * powerOffset), -100), 100);

    return m;
}

int main() {
    InitEV3();

    PlayTone(440,200);
    Wait(500);

    int sensor = IN_3; //Sensor used for line tracing

    SetSensorMode(sensor, COL_REFLECT);
    while (!ButtonIsDown(BTNEXIT)) {
        int val = readSensor(sensor);

        auto move = pLineTrace(RIGHT_TRACE, val, 10, 100, 30, 15); //Trace on the right side, sensor range 10-100, motor speed 30±15

        OnFwdReg(OUT_B, move.leftSpeed);
        OnFwdReg(OUT_C, move.rightSpeed);
    }

    Off(OUT_B);
    Off(OUT_C);

    FreeEV3();
}
