#include "ball.h"

Ball::Ball()
{
	mSpeed = 1;
	mDirection.x = sqrt(2)/2.f;
	mDirection.y = sqrt(2)/2.f;
	setRadius(10);
	setOrigin(getRadius(), getRadius());
	setPosition((float)wWidth / 2, (float)wHeight / 2);
}

Ball::Ball(float radius, float speed, float x, float y)
{
	setRadius(radius);
	setOrigin(getRadius() / 2, getRadius() / 2);
	mSpeed = speed;
	setPosition(x, y);
}

Ball::~Ball()
{
}

void Ball::setSpeed(float speed)
{
	mSpeed = speed;
}

void Ball::setDirection(float x, float y)
{
	mDirection.x = x;
	mDirection.y = y;
}

float Ball::getSpeed()
{
	return mSpeed;
}

sf::Vector2f Ball::getDirection()
{
	return mDirection;
}

