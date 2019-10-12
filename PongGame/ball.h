#ifndef __BALL_H__
#define __BALL_H__


#include<SFML/Graphics.hpp>
#include"MoveableObject.h"



const float dBallSpeed = 50;

class Ball : public sf::CircleShape, public MoveableObject
{
public:
	Ball();
	Ball(float, float, float, float);
	virtual ~Ball();

	
};



#endif // !__BALL_H__



