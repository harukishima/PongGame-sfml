#include "ball.h"

Ball::Ball()
{
	mSpeed = 1;
	mDirection.x = 1;
	mDirection.y = -10;
	mDirection = normalizeVector(mDirection);
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

void Ball::setDirection(const sf::Vector2f& v)
{
	mDirection = v;
}

float Ball::getSpeed()
{
	return mSpeed;
}

sf::Vector2f Ball::getDirection()
{
	return mDirection;
}

sf::Vector2f Ball::normalizeVector(const sf::Vector2f& v)
{
	float vLength = sqrt(pow(v.x, 2) + pow(v.y, 2));
	return sf::Vector2f(v.x / vLength, v.y / vLength);
}