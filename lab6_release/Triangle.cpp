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

#include "Shape.h"
#include "Triangle.h"
#include <cmath>

// Constructor
Triangle::Triangle(string n, float x1, float y1, float x2, float y2, float x3, float y3)
    : Shape(n, (x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
    }

// Destructor
Triangle::~Triangle()
{
    // Nothing specific to clean up
}

// Draw the triangle
void Triangle::draw() const
{
    cout << std::fixed;
    cout << std::setprecision(2);
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre << " "
         << x1 << " " << y1 << " "
         << x2 << " " << y2 << " "
         << x3 << " " << y3 << " "
         << computeArea() << endl;
}

// Compute the area of the triangle using the determinant formula
float Triangle::computeArea() const
{
    return (0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
}


// Clone the triangle
Shape *Triangle::clone() const
{
    return new Triangle(*this);
}
