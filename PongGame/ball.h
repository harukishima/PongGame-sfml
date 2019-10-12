#ifndef __BALL_H__
#define __BALL_H__


#include<SFML/Graphics.hpp>


const sf::Time TimePerFrame = sf::seconds(1.f / 144.f);
const unsigned int wWidth = 800;
const unsigned int wHeight = 600;
const float dBallSpeed = 50;

class Ball : public sf::CircleShape
{
protected:
	float mSpeed;
	sf::Vector2f mDirection;
public:
	Ball();
	Ball(float, float, float, float);
	virtual ~Ball();

	void setSpeed(float);
	void setDirection(float,float);
	void setDirection(const sf::Vector2f&);
	float getSpeed();
	sf::Vector2f getDirection();
	static sf::Vector2f normalizeVector(const sf::Vector2f&);
};



#endif // !__BALL_H__



