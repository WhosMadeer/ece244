//
//  Rectangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Rectangle_h
#define Rectangle_h

#include <iostream>
#include <string>
using namespace std;


// This class implements the rectangle Shape objects.
// ECE244 Student: Write the definition of the class here.


#include "Shape.h"

class Rectangle : public Shape {
private:
    float width, height;                  // The width and height of the rectangle

public:
    // Constructor
    Rectangle(string n, float xcent, float ycent, float w, float h);

    // Destructor
    virtual ~Rectangle();

    // Accessor
    float getWidth() const;       // Returns the width of the circle

    float getHeight() const;       // Returns the height of the circle


    // Mutator
    void setWidth(float w);       // Sets the width of the circle

    void setHeight(float w);       // Sets the height of the circle

    // Utility methods
    virtual void draw() const;     // Draws thye circle; for the assignment it
    // prints the information of the circle

    virtual float computeArea() const;   // Computes the area of the circle

    virtual Shape* clone() const;  // Clones the object
};


#endif /* Rectangle_h */


