#include "MoveableObject.h"

MoveableObject::MoveableObject()
{
	mSpeed = 0;
	mDirection = sf::Vector2f(0.f, 0.f);
}

void MoveableObject::setSpeed(float speed)
{
	mSpeed = speed;
}

void MoveableObject::setDirection(float x, float y)
{
	mDirection.x = x;
	mDirection.y = y;
}

void MoveableObject::setDirection(const sf::Vector2f& v)
{
	mDirection = v;
}

float MoveableObject::getSpeed()
{
	return mSpeed;
}

sf::Vector2f MoveableObject::getDirection()
{
	return mDirection;
}

sf::Vector2f MoveableObject::normalizeVector(const sf::Vector2f& v)
{
	float vLength = sqrt(pow(v.x, 2) + pow(v.y, 2));
	return sf::Vector2f(v.x / vLength, v.y / vLength);
}

double MoveableObject::vectorLength(const sf::Vector2f& a)
{
	return sqrt(pow(a.x,2)+pow(a.y,2));
}

double MoveableObject::dotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}
