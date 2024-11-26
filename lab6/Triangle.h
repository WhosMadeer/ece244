//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.

#include "Shape.h"

class Triangle : public Shape {
private:
    float x1, y1, x2, y2, x3, y3; // Coordinates of the triangle vertices              

public:
    // Constructor
    Triangle(string n, float x1_, float y1_, float x2_, float y2_, float x3_, float y3_);
    // Destructor
    virtual ~Triangle();

    // Accessor
    float getx1() const;       // Returns the x1 of the circle
    float gety1() const;       // Returns the x1 of the circle
    float getx2() const;       // Returns the x1 of the circle
    float gety2() const;       // Returns the x1 of the circle
    float getx3() const;       // Returns the x1 of the circle
    float gety3() const;       // Returns the x1 of the circle

    // Mutator
    void setx1(float n);       // Sets the radius of the circle
    void sety1(float n);       // Sets the radius of the circle
    void setx2(float n);       // Sets the radius of the circle
    void sety2(float n);       // Sets the radius of the circle
    void setx3(float n);       // Sets the radius of the circle
    void sety3(float n);       // Sets the radius of the circle

    // Utility methods
    virtual void draw() const;     // Draws thye circle; for the assignment it
    // prints the information of the circle

    virtual float computeArea() const;   // Computes the area of the circle

    virtual Shape* clone() const;  // Clones the object
};


#endif /* Triangle_h */


