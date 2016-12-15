#include "TXLib.h"

void planeDraw(int x, int y, double zoom, int countWindows, int countMotors, bool rearMotor, int chassisAngle);

int main()
{
    double planeX = 500;
    double planeSpeed = 0.5;
    double monkeyX = 100;
    double monkeySpeed = 1.1;
    int nomerShaga = 0;

    txCreateWindow(1360, 572);

    HDC  fon = txLoadImage ("fon.bmp");
    HDC  fon1 = txLoadImage ("fon1.bmp");
    HDC  monkey = txLoadImage ("monkey.bmp");

    while (!GetAsyncKeyState(VK_ESCAPE)) {

        if (nomerShaga % 2 == 0) {
            txBitBlt (txDC(), 0,   0,   1360, 572, fon, 0, 0);
        }

        if (nomerShaga % 2 == 1) {
            txBitBlt (txDC(), 0,   0,   1360, 572, fon1, 0, 0);
        }

        planeX = planeX + planeSpeed;
        monkeyX = monkeyX + monkeySpeed;

        planeDraw(planeX, 200, 2, 8, 1, true, 90);
        txBitBlt (txDC(), monkeyX,   0,   84, 100, monkey, 0, 0);

        nomerShaga = nomerShaga + 1;
        txSleep(30);
    }

    txDeleteDC (fon);
    txDeleteDC (fon1);
    txDeleteDC (monkey);
    return 0;
}

void planeDraw(int x, int y, double zoom, int countWindows, int countMotors, bool rearMotor, int chassisAngle)
{
    double cAngle = chassisAngle*M_PI/180;
    txSetColor (TX_BLACK, 2);
    txSetFillColor (TX_YELLOW);

    POINT aircraft[8] = {{x + ROUND(  8*zoom), y - ROUND(16*zoom)},
                         {x + ROUND( 11*zoom), y                 },
                         {x + ROUND( 84*zoom), y                 },
                         {x + ROUND( 84*zoom), y + ROUND( 7*zoom)},
                         {x + ROUND( 97*zoom), y + ROUND( 7*zoom)},
                         {x + ROUND(100*zoom), y + ROUND(16*zoom)},
                         {x                  , y + ROUND(16*zoom)},
                         {x                  , y - ROUND(16*zoom)}};
    txPolygon (aircraft, 8);

    //wings
    POINT topwing[4] =  {{x + ROUND( 40*zoom), y                 },
                         {x + ROUND( 32*zoom), y - ROUND( 8*zoom)},
                         {x + ROUND( 52*zoom), y - ROUND( 8*zoom)},
                         {x + ROUND( 60*zoom), y                 }};
    txPolygon (topwing, 4);

    POINT bottomwing[4] =
                        {{x + ROUND( 40*zoom), y + ROUND(16*zoom)},
                         {x + ROUND( 28*zoom), y + ROUND(28*zoom)},
                         {x + ROUND( 48*zoom), y + ROUND(28*zoom)},
                         {x + ROUND( 60*zoom), y + ROUND(16*zoom)}};

    txPolygon (bottomwing, 4);
    //head
    txLine               (x + ROUND( 84*zoom), y                  ,
                          x + ROUND( 97*zoom), y + ROUND( 7*zoom));
    //windows
    txSetFillColor (TX_BLACK);
    for (int i = 0; i < countWindows; i++)
    {
        txCircle         (x +
         (12 + 60*i/countWindows)*zoom, y +  7*zoom, 3*zoom);
    }

    //Motors
    txSetFillColor (TX_LIGHTGRAY);
    if (rearMotor)
    {   POINT rmotor[4] =
           {{x + ROUND( (8 + 15 / 16) *zoom), y - ROUND( 11 *zoom)},
            {x + ROUND( 16            *zoom), y - ROUND( 11 *zoom)},
            {x + ROUND( 16            *zoom), y - ROUND( 10 *zoom)},
            {x + ROUND( (8 + 18 / 16) *zoom), y - ROUND( 10 *zoom)}};
        txPolygon (rmotor, 4);
    }
    if (countMotors > 0)
    {
        for (int i = 0; i < countMotors; i++)
        {   POINT bottommotor[4] =
               {{x + ROUND((47 + 8 * (i + 1) / countMotors) *zoom),
                 y + ROUND((29 - 8 * (i + 1) / countMotors) *zoom)},
                {x + ROUND((55 + 8 * (i + 1) / countMotors) *zoom),
                 y + ROUND((29 - 8 * (i + 1) / countMotors) *zoom)},
                {x + ROUND((55 + 8 * (i + 1) / countMotors) *zoom),
                 y + ROUND((31 - 8 * (i + 1) / countMotors) *zoom)},
                {x + ROUND((45 + 8 * (i + 1) / countMotors) *zoom),
                 y + ROUND((31 - 8 * (i + 1) / countMotors) *zoom)}};
            txPolygon (bottommotor, 4);

            POINT topmotor[4] =
               {{x + ROUND(( 51 + 6 * (i + 1) / countMotors) *zoom),
                 y + ROUND(( -9 + 6 * (i + 1) / countMotors) *zoom)},
                {x + ROUND(( 55 + 6 * (i + 1) / countMotors) *zoom),
                 y + ROUND(( -9 + 6 * (i + 1) / countMotors) *zoom)},
                {x + ROUND(( 55 + 6 * (i + 1) / countMotors) *zoom),
                 y + ROUND((-10 + 6 * (i + 1) / countMotors) *zoom)},
                {x + ROUND(( 50 + 6 * (i + 1) / countMotors) *zoom),
                 y + ROUND((-10 + 6 * (i + 1) / countMotors) *zoom)}};
            txPolygon (topmotor, 4);
        }
    }

    //Chassis
    if (cAngle>0)
    {
        txSetFillColor (TX_BLACK);
        txLine  (x + ROUND( 80                  * zoom),
                 y + ROUND( 16                  * zoom),
                 x + ROUND((80 + 5*cos(cAngle)) * zoom),
                 y + ROUND((16 + 5*sin(cAngle)) * zoom));
        txCircle(x + ROUND((80 + 5*cos(cAngle)) * zoom),
                 y + ROUND((16 + 5*sin(cAngle)) * zoom), 2*zoom);
        txLine  (x + ROUND( 25                  * zoom),
                 y + ROUND( 16                  * zoom),
                 x + ROUND((25 + 5*cos(cAngle)) * zoom),
                 y + ROUND((16 + 5*sin(cAngle)) * zoom));
        txCircle(x + ROUND((25 + 5*cos(cAngle)) * zoom),
                 y + ROUND((16 + 5*sin(cAngle)) * zoom), 2*zoom);
    }

}
