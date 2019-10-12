#ifndef __PADDLE_H__
#define __PADDLE_H__

#include<SFML\Graphics.hpp>
#include"MoveableObject.h"

class Paddle : public sf::RectangleShape, public MoveableObject
{
public:
	Paddle();
	virtual ~Paddle() = default;
	void defaultPaddle();
};


#endif // !__PADDLE_H__