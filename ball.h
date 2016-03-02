#pragma once
class Ball
{

public:
	
	float x, y, dx, dy, r;
	bool active;
	Ball();
	Ball(float x_, float y_, float r_);
	void Move();
};