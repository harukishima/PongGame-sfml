#ifndef __PADDLE_H__
#define __PADDLE_H__

#include<SFML\Graphics.hpp>
#include"MoveableObject.h"

class Paddle : public sf::RectangleShape, public MoveableObject
{
private:
	bool isUp = false; //true: paddle move up
	bool isDown = false; //true: paddle move down
	int mScore = 0; //Player's score
public:
	Paddle();
	virtual ~Paddle() = default;

	void setScore(const int&);
	int getScore();

	void defaultPaddle();
	void setUpState(bool state);
	void setDownState(bool state);
	bool getUpState();
	bool getDownState();

};


#endif // !__PADDLE_H__