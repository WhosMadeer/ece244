//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include <cmath>

#include "Shape.h"
#include "Triangle.h"

// Build a Triangle object
Triangle::Triangle(string n, float x1_, float y1_, float x2_, float y2_, float x3_, float y3_) :Shape(n, 0, 0) {
    // cout << "in the constructure values: " << n << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << endl;

    x1 = x1_;
    y1 = y1_;
    x2 = x2_;
    y2 = y2_;
    x3 = x3_;
    y3 = y3_;
    Shape::setXCentre((x1_ + x2_ + x3_) / 3);
    Shape::setYCentre((y1_ + y2_ + y3_) / 3);
}

Triangle::~Triangle() {
    // Nothing to do
}

// Accessor
float Triangle::getx1() const {
    return x1;
}

float Triangle::gety1() const {
    return y1;
}

float Triangle::getx2() const {
    return x2;
}

float Triangle::gety2() const {
    return y2;
}

float Triangle::getx3() const {
    return x3;
}

float Triangle::gety3() const {
    return y3;
}

// Mutator
void Triangle::setx1(float n) {
    x1 = n;
}

void Triangle::sety1(float n) {
    y1 = n;
}

void Triangle::setx2(float n) {
    x2 = n;
}

void Triangle::sety2(float n) {
    y2 = n;
}


void Triangle::setx3(float n) {
    x3 = n;
}

void Triangle::sety3(float n) {
    y3 = n;
}

void Triangle::draw() const {
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);

    // Print the information
    cout << "triangle: " << name << " "
        << x_centre << " " << y_centre
        << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << computeArea()
        << endl;
}

float Triangle::computeArea() const {
    return abs((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2))) / 2;
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}
