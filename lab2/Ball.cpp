//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Author Name, Date

#include "Ball.h"
#include "Player.h"
#include "Globals.h"
#include "Screen.h"
#include <iostream>
using namespace std;

Ball::Ball() {
    
}

Ball::Ball(double x, double y, double velocity_x, double velocity_y, int id){
    this->x = x;
    this->y = y;
    this->velocity_x = velocity_x;
    this->velocity_y = velocity_y;
    this->id = id;
}

double Ball:: getX() {
        return x;
}

int Ball:: getID() {
        return id;
}

void Ball:: update() {
    velocity_y -=  0.02 * timeStep;

    x += velocity_x * timeStep;
    y += velocity_y * timeStep;

}

int Ball::overlap(Ball& b) {
    int xOver, yOver;
    if (x+width >= b.x && (x+width - b.x <= width) && (b.y+height-y <= height) && b.y+height-y >0) {
        xOver = x+width - b.x;
        yOver = b.y+height-y;
    }
    if (x+width >= b.x && (x+width - b.x <= width) && (y+height-b.y <= height) && y+height-b.y >0) {
        xOver = x+width - b.x;
        yOver = y+height-b.y;
    }
    if (b.x+width >= x && (b.x+width - x <= width) && (y+height-b.y <= height) && y+height-b.y >0) {
        xOver = b.x+width - x;
        yOver = y+height-b.y;
    }

    if (b.x+width >= x && (b.x+width - x <= width) && (b.y+height-y <= height) && b.y+height-y >0) {
        xOver = b.x+width - x;
        yOver = b.y+height-y;
    }
    
    if (xOver > yOver) {
        return HORIZONTAL_OVERLAP;
    } else if(yOver > xOver) {
        return VERTICAL_OVERLAP;
    } else {
        return NO_OVERLAP;
    }
    
    
   
}  


int Ball:: overlap(Player& p) {

    if (x <= p.getX() + p.getWidth() && y <= p.getY() + p.getHeight() && y >= p.getY()) {
        return HORIZONTAL_OVERLAP;
    } else {
        return NO_OVERLAP;
    }


}

void Ball::bounce(Ball arr[], int ballCount, Player player){
    if(x <= 0 || x >= WIDTH-1 ){
        velocity_x = -velocity_x;
    }
    if (y <= 0 || y >= HEIGHT-1) {
        velocity_y = -velocity_y;
    }
    
    
    
    for (int i = 0; i < ballCount; i++) {
        int overlapResult = overlap(arr[i]);
        if (overlapResult != NO_OVERLAP) {
            // Handle overlap based on the type
            if (overlapResult == VERTICAL_OVERLAP) {
                velocity_y = -velocity_y; // Reverse vertical velocity
            } else if (overlapResult == HORIZONTAL_OVERLAP) {
                velocity_x = -velocity_x; // Reverse horizontal velocity
            }
            return; // Exit after handling the first overlap
        }
    }

    // Check for overlap with the player
    if (overlap(player) != NO_OVERLAP) {
        if (overlap(player) == VERTICAL_OVERLAP) {
            velocity_y = -velocity_y; // Reverse vertical velocity
        } else {
            velocity_x = -velocity_x; // Reverse horizontal velocity
        }
        return; // Exit after handling player overlap
    }
    
    }


void Ball::draw(Screen& screen_to_draw_to) {
    screen_to_draw_to.addPixel(x,y,'o');
}