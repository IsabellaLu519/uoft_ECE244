//
//  Rectangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class here

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Rectangle.h"

// Constructor
Rectangle::Rectangle(string n, float xcent, float ycent, float w, float h)
    : Shape(n, xcent, ycent){
        width = w;
        height = h;
    }
      // Destructor
      Rectangle::~Rectangle()
{
    // Nothing specific to clean up
}

// Accessors
float Rectangle::getWidth() const
{
    return width;
}

float Rectangle::getHeight() const
{
    return height;
}

// Mutators
void Rectangle::setWidth(float w)
{
    width = w;
}

void Rectangle::setHeight(float h)
{
    height = h;
}

// Draw the rectangle
void Rectangle::draw() const
{
    cout << std::fixed;
    cout << std::setprecision(2);
    cout << "rectangle: " << name << " "
         << x_centre << " " << y_centre << " "
         << width << " " << height << " "
         << computeArea() << endl;
}

// Compute the area of the rectangle
float Rectangle::computeArea() const
{
    return (width * height);
}

// Clone the rectangle
Shape *Rectangle::clone() const
{
    return (new Rectangle(*this));
}
