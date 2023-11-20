/**
 * Point.cpp
 * Project UID 2e6ea4e086ea6a06753e819c30923369
 *
 * EECS 183
 * Project 4: CoolPics
 *
 * Andreas Andrade
 * aadredre
 *
 * code for point(coordinates)
 */

#include "Point.h"

// for the declaration of DIMENSION
#include "utility.h"

//Check RME's for function descriptions

Point::Point() {
    x = 0;
    y = 0;
}
    
Point::Point(int xVal, int yVal) {
    x = checkRange(xVal);
    y = checkRange(yVal);
}

void Point::setX(int xVal) {
    x = xVal;
    
}

int Point::getX() {
    
    return x;
}

void Point::setY(int yVal) {
    
    y = yVal;
}
    
int Point::getY() {
   
    return y;
}

void Point::read(istream& ins) {
    x = checkRange(x);
    y = checkRange(y);
    char dummy;
    ins >> dummy >> x >> dummy >> y >> dummy;
}

void Point::write(ostream& outs) {
    
    outs << "(" << checkRange(x) << "," << checkRange(y) << ")";
}

int Point::checkRange(int val) {
    if(!(val >= 0 && val < DIMENSION)) {
        if(val < 0) {
            return 0;
        } else {
            val = DIMENSION - 1;
            return val;
        }
        
    } else {
        return val;
    }
}


istream& operator >> (istream& ins,  Point& pt)
{
    pt.read(ins);
    return ins;
}

ostream& operator<< (ostream& outs, Point pt)
{
    pt.write(outs);
    return outs;
}
