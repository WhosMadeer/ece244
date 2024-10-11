//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Author Name, Date
//  Created by Mahir Khandaker on 2024-09-23

#include "Player.h"

Player::Player()
{
    x = 0;
    y = 0;
    width = 1;
    height = 3;
}

Player::Player(double x_coord, double y_coord, int height_player)
{
    x = x_coord;
    y = y_coord;
    width = 1;
    height = height_player;
}

double Player::getX()
{
    return x;
}

double Player::getY()
{
    return y;
}

int Player::getHeight()
{
    return height;
}

int Player::getWidth()
{
    return width;
}

void Player::decreaseHeight(int delta_to_decrease_by)
{
    if (height - delta_to_decrease_by >= 3)
    {
        height = height - delta_to_decrease_by;
    }
}

void Player::update(char c)
{

    if (c == 'A')
    {
        if (y + height + 2 < HEIGHT - 1)
        {
            y += 2;
        }
        else if (y + height + 1 <= HEIGHT)
        {
            y += 1;
        }
    }
    if (c == 'B')
    {
        if (y - 2 > 0)
        {
            y -= 2;
        }
        else if (y - 1 >= 0)
        {
            y -= 1;
        }
    }
    // if (y > 0 || y < HEIGHT - 1)
    // {
    //     switch (c)
    //     {
    //     case 'A':
    //         if (y + height + 2 < HEIGHT - 1)
    //         {
    //             y += 2;
    //         }
    //         break;
    //     case 'B':
    //         if (y - 2 > 0)
    //         {
    //             y -= 2;
    //         }
    //         break;
    //     }
    // }
}

void Player::draw(Screen &screen_to_draw_to)
{
    for (double i = 0.0; i < height; i++)
    {
        for (double j = 0.0; j < width; j++)
        {
            screen_to_draw_to.addPixel(x + j, y + i, '#');
        }
    }
}
