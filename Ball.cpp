#pragma once
#include "ball.h"
void Ball::Move()
{
	x += dx;
	y += dy;
};
Ball::Ball()
{
	active = false;
};
Ball::Ball(float x_, float y_, float r_)
{
	x = x_;
	y = y_;
	r = r_;
};