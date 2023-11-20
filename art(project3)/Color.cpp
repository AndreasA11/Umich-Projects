/**
 * Color.cpp
 * Project UID 2e6ea4e086ea6a06753e819c30923369
 *
 * EECS 183
 * Project 4: CoolPics
 *
 * Andreas Andrade
 * aadredre
 *
 * code for color, rgb
 */
#include <cmath>
#include "Color.h"

//Check RME's for function descriptions

Color::Color() {
    red = 0;
    green = 0;
    blue = 0;
}

Color::Color(int redVal, int greenVal, int blueVal) {
    red = checkRange(redVal);
    green = checkRange(greenVal);
    blue = checkRange(blueVal);
}

int Color::checkRange(int val) {
    if(!(val >= 0 && val <= 255)) {
        if(val < 0) {
            return 0;
        } else {
            return 255;
        }
    } else {
        return val;
    }
    
}

void Color::setRed(int redVal) {
    red = checkRange(redVal);
}

int Color::getRed() {
    return red;
}

void Color::setGreen(int greenVal) {
    green = checkRange(greenVal);
}

int Color::getGreen() {
    return green;
}

void Color::setBlue(int blueVal) {
    blue = checkRange(blueVal);
}


int Color::getBlue() {
    return blue;
}

void Color::read(istream& ins) {
    ins >> red;
    red = checkRange(red);
    ins >> green;
    green = checkRange(green);
    ins >> blue;
    blue = checkRange(blue);
}

void Color::write(ostream& outs) {
    outs << checkRange(red) << " " << checkRange(green)
         << " " << checkRange(blue);
}

istream& operator >> (istream& ins, Color& color)
{
   color.read(ins);
   return ins;
}

ostream& operator << (ostream& outs, Color color)
{
   color.write(outs);
   return outs;
}
