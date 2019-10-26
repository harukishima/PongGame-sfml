#include "Paddle.h"

Paddle::Paddle()
{
}

void Paddle::defaultPaddle()
{
	setSize(sf::Vector2f(2.f, 100.f));
	mSpeed = 5;
	mDirection = sf::Vector2f(0, 0);
	setOrigin(sf::Vector2f(0, getSize().y / 2));
}

void Paddle::setUpState(bool state)
{
	isUp = state;
}

void Paddle::setDownState(bool state)
{
	isDown = state;
}

bool Paddle::getUpState()
{
	return isUp;
}

bool Paddle::getDownState()
{
	return isDown;
}

bool Paddle::operator==(const Paddle&p) const
{
	return ((mSpeed == p.mSpeed) && (mDirection == p.mDirection) && (getSize() == p.getSize()) && (getPosition().x == p.getPosition().x) && (getPosition().y == p.getPosition().y));
}
