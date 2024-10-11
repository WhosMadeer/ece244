//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Author Name, Date
//  Created by Mahir Khandaker on 2024-09-23

#include "Ball.h"

Ball::Ball()
{
    x = 0;
    y = 0;
    velocity_x = 0;
    velocity_y = 0;
    id = 0;
}

Ball::Ball(double x_coord, double y_coord, double velocity_x_ball, double velocity_y_ball, int id_ball)
{
    x = x_coord;
    y = y_coord;
    velocity_x = velocity_x_ball;
    velocity_y = velocity_y_ball;
    id = id_ball;
}

double Ball::getX()
{
    return x;
}

int Ball::getID()
{
    return id;
}

void Ball::update()
{
    velocity_y = velocity_y - 0.02 * timeStep;

    y = y + velocity_y * timeStep;
    x = x + velocity_x * timeStep;
}

int Ball::overlap(Ball &b)
{
    double dx = -1, dy = -1;

    double cond1 = x + width - b.x;
    double cond2 = b.x + b.width - x;
    double cond3 = y + height - b.y;
    double cond4 = b.y + b.height - y;

    if (cond1 > 0 || cond2 > 0)
    {
        if (cond1 > cond2)
        {
            dx = cond1;
        }
        else if (cond1 <= cond2)
        {
            dx = cond2;
        }
    }
    if (cond3 > 0 || cond4 > 0)
    {
        if (cond3 > cond4)
        {
            dy = cond3;
        }
        else if (cond3 <= cond4)
        {
            dy = cond4;
        }
    }
    if (dx > dy && dy <= 0)
    {
        return HORIZONTAL_OVERLAP;
    }
    else if (dy > dx && dx <= 0)
    {
        return VERTICAL_OVERLAP;
    }

    return NO_OVERLAP;
}

int Ball::overlap(Player &p)
{
    // * consider only the hitbox of the player and not the ball

    if (x - width <= p.getX() + p.getWidth())
    {
        if (p.getY() < y && p.getY() + p.getHeight() > y + height)
        {
            return HORIZONTAL_OVERLAP;
        }
        else
        {
            return NO_OVERLAP;
        }
    }
    else
    {
        return NO_OVERLAP;
    }
}

void Ball::bounce(Ball arr[], int ballCount, Player player)
{
    if (x >= WIDTH) // * IF x is less than 0, then its out of bounds and the player loses
    {
        velocity_x = -1 * velocity_x;
    }
    if (y >= HEIGHT - 1 || y <= 0)
    {
        velocity_y = -1 * velocity_y;
    }

    if (overlap(player) == HORIZONTAL_OVERLAP)
    {
        velocity_x = -1 * velocity_x;
    }

    for (int i = 0; i < ballCount; i++)
    {
        if (arr[i].id != id)
        {
            int a = overlap(arr[i]);
            if (a == HORIZONTAL_OVERLAP)
            {
                // arr[i].velocity_x = -1 * arr[i].velocity_x;
                velocity_x = -1 * velocity_x;
            }
            if (a == VERTICAL_OVERLAP)
            {
                // arr[i].velocity_y = -1 * arr[i].velocity_y;
                velocity_y = -1 * velocity_y;
            }
        }
    }
}

void Ball::draw(Screen &screen_to_draw_to)
{
    screen_to_draw_to.addPixel(x, y, 'o');
}
