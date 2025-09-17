//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Author Name, Date

#include "Player.h"
#include "Globals.h"
#include "Screen.h"

Player::Player() {
    //x = 0.0;
    //y = 0.0;
    //height = 0;
    //width = 0;
}

Player::Player(double x, double y, int height) {
    this->x = x;
    this->y = y;
    this->height = height;
}

double Player:: getX(){
    return x;
}

double Player:: getY(){
    return y;
}

int Player:: getHeight(){
    return height;
}

int Player:: getWidth(){
    return width;
}

void Player:: decreaseHeight(int delta_to_decrease_by){
    if (height > 3) {
        height = height - delta_to_decrease_by;
    }
    
}

 void Player:: update(char c) {
    if (c == 'A') {
        if (y + height < HEIGHT - 1) { 
            y += 2;
        }
    }else if (c == 'B') {
        if(y>0)
        y -= 2;
    }
}
      
 

 void Player:: draw(Screen& screen_to_draw_to) {
    
    for (int i = 0; i < height; i++) {
        screen_to_draw_to.addPixel(x, y+i, '#');   
    }
 }

