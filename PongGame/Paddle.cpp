#include "Paddle.h"

Paddle::Paddle()
{
}

void Paddle::defaultPaddle()
{
	setSize(sf::Vector2f(20.f, 100.f));
	mSpeed = 5;
	mDirection = sf::Vector2f(0, 0);
	setOrigin(sf::Vector2f(0, getSize().y / 2));
}
