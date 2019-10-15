#ifndef __MOVEABLEOBJECT_H__
#define __MOVEABLEOBJECT_H__

#include<SFML\Graphics.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 144.f);
const unsigned int wWidth = 800;
const unsigned int wHeight = 600;

class MoveableObject
{
protected:
	float mSpeed;
	sf::Vector2f mDirection;
public:
	MoveableObject();
	virtual ~MoveableObject() = default;
	void setSpeed(float);
	void setDirection(float, float);
	void setDirection(const sf::Vector2f&);
	float getSpeed();
	sf::Vector2f getDirection();
	static sf::Vector2f normalizeVector(const sf::Vector2f&);
	static double vectorLength(const sf::Vector2f&);

};

#endif // !__MOVEABLEOBJECT_H__