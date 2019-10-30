#include "game.h"



Game::Game()
	: mWindow(sf::VideoMode(wWidth, wHeight), "Pong Game")
{
	defaultWall();
	leftPaddle.defaultPaddle(); rightPaddle.defaultPaddle();
	defaultPaddleState();
	defaultBallState();
	middleLine.setSize(sf::Vector2f(1, wHeight));
	middleLine.setPosition(sf::Vector2f(wWidth / 2.f, 0));
	/*isPlaying = true;
	isSingle = true;*/
	font.loadFromFile("resource\\SUBWT___.ttf");
	Score1.setFont(font);
	Score1.setString("0");
	Score1.setCharacterSize(50);
	Score1.setPosition((mWindow.getSize().x) / 4, 20);
	Score1.setFillColor(sf::Color::White);
	Score2.setFont(font);
	Score2.setString("0");
	Score2.setCharacterSize(50);
	Score2.setPosition(3*(mWindow.getSize().x) / 4, 20);
	Score2.setFillColor(sf::Color::White);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
		/*processEvents();
		update(clock.restart());
		render();*/
	}
}



void Game::processEvents()
{
	sf::Event ev;
	while (mWindow.pollEvent(ev))
	{
		switch (ev.type) {
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleInput(ev.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleInput(ev.key.code, false);
			break;
		}
	}
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (isPlaying && key == sf::Keyboard::W)
	{
		leftPaddle.setUpState(isPressed);
	}
	if (isPlaying && key == sf::Keyboard::S)
	{
		leftPaddle.setDownState(isPressed);
	}
	if (!isSingle)
	{
		if (isPlaying && key == sf::Keyboard::Up)
		{
			rightPaddle.setUpState(isPressed);
		}
		if (isPlaying && key == sf::Keyboard::Down)
		{
			rightPaddle.setDownState(isPressed);
		}
	}
	//Processed only when key is pressed
	if (isPressed)
	{
		if (isOver)
		{
			if (key == sf::Keyboard::Escape)
			{
				isMainMenu = true;
				isOver = false;
				reset();
			}
			if (key == sf::Keyboard::Enter)
			{
				isOver = false;
				isPlaying = true;
				reset();
			}
		}
		if (isMainMenu)
		{
			mainMenu.navigate(key);
			//Exit game from main menu
			if (key == sf::Keyboard::Escape)
			{
				mWindow.close();
			}
			//Start game in multiplayer mode
			if (mainMenu.getRightState() && key == sf::Keyboard::Enter)
			{
				isMainMenu = false;
				isSingle = false;
				isPlaying = true;
			}
			//State game in single player mode
			if (mainMenu.getLeftState() && key == sf::Keyboard::Enter)
			{
				isMainMenu = false;
				isSingle = true;
				isPlaying = true;
				rightPaddle.setSpeed(2);
			}
		}
		
		
		//Pause game;
		if (isPlaying && key == sf::Keyboard::Escape)
		{
			isPlaying = false;
		}
		//Pause menu input
		if (!isPlaying && !isMainMenu && !isOver)
		{
			pauseMenu.navigate(key);
			if (key == sf::Keyboard::Enter)
			{
				switch (pauseMenu.getState())
				{
				case 1:
					isPlaying = true;
					break;
				case 2:
					isPlaying = false;
					reset();
					isMainMenu = true;
					break;
				case 3:
					mWindow.close();
					break;
				default:
					break;
				}
			}
		}
	}
}

void Game::update(sf::Time TimePerFrame)
{
	if (isPlaying)
	{
		if (isSingle == true)
		{
			processBot();
		}
		updateBall();
		updatePaddle();
		updateScore();
		processWinning();
		/*
		movement = sf::Vector2f(0, 0);
		movement = rightPaddle.getDirection() * rightPaddle.getSpeed();
		rightPaddle.move(movement);*/
	}
	else if (isMainMenu)
	{
		mainMenu.updateMenu();
	}
	else if (isOver)
	{

	}
	else
	{
		pauseMenu.updateMenu();
	}
	
}

void Game::render()
{
	mWindow.clear();
	if (isPlaying)
	{
		mWindow.draw(middleLine);
		mWindow.draw(leftPaddle);
		mWindow.draw(rightPaddle);
		mWindow.draw(NewBall);
		mWindow.draw(upperWall);
		mWindow.draw(lowerWall);
		mWindow.draw(Score1);
		mWindow.draw(Score2);
	}
	else if(isMainMenu)
	{
		mWindow.draw(mainMenu.title);
		mWindow.draw(mainMenu.leftBox);
		mWindow.draw(mainMenu.rightBox);
		mWindow.draw(mainMenu.leftText);
		mWindow.draw(mainMenu.rightText);
	}
	else if (isOver)
	{
		mWindow.draw(over.guideMessage);
		if (leftPaddle.getScore() >= 10)
			mWindow.draw(over.P1Win);
		else
			mWindow.draw(over.P2Win);
	}
	else
	{
		mWindow.draw(pauseMenu.title);
		mWindow.draw(pauseMenu.upperBox);
		mWindow.draw(pauseMenu.upperText);
		mWindow.draw(pauseMenu.midleBox);
		mWindow.draw(pauseMenu.midleText);
		mWindow.draw(pauseMenu.bottomBox);
		mWindow.draw(pauseMenu.bottomText);
	}
	mWindow.display();
}

void Game::defaultWall()
{
	float wallWidth = 20.f;
	upperWall.setSize(sf::Vector2f(wWidth, wallWidth));
	lowerWall.setSize(sf::Vector2f(wWidth, wallWidth));
	upperWall.setFillColor(sf::Color::White); 
	lowerWall.setFillColor(sf::Color::White);
	upperWall.setPosition(sf::Vector2f(0.f, 0.f));
	lowerWall.setPosition(sf::Vector2f(0.f, wHeight - wallWidth));
}

void Game::defaultPaddleState()
{
	leftPaddle.setPosition(sf::Vector2f(0.f,wHeight/2.f));
	leftPaddle.setScore(0);
	leftPaddle.setSpeed(5);
	rightPaddle.setPosition(sf::Vector2f(wWidth-rightPaddle.getSize().x,wHeight/2.f));
	rightPaddle.setScore(0);
	rightPaddle.setSpeed(5);
}

void Game::defaultBallState()
{
	NewBall.setSpeed(2);
	NewBall.setPosition(sf::Vector2f(wWidth/2.f, wHeight/2.f));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> uniform_distance(1, std::nextafter(360, DBL_MAX));
	float angle;
	float x, y;
	sf::Vector2f direction;

	do {
		angle = uniform_distance(gen);
		//x = cos(angle * (std::_Pi / 180)) * NewBall.getDirection().x - sin(angle * (std::_Pi / 180)) * NewBall.getDirection().y;
		//y = sin(angle * (std::_Pi / 180)) * NewBall.getDirection().x + cos(angle * (std::_Pi / 180)) * NewBall.getDirection().y;
		direction = MoveableObject::rolateVector(NewBall.getDirection(), angle);
		direction = MoveableObject::normalizeVector(direction);
		angle = MoveableObject::angleInDegree(direction);
	} while ((angle > 45 && angle < 135) || (angle < -45 && angle > -135));
	NewBall.setDirection(direction);
}

void Game::checkWallCollision()
{
	if ((NewBall.getPosition().y - NewBall.getRadius()) <= upperWall.getSize().y)
	{
		NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
	}
	if ((NewBall.getPosition().y + NewBall.getRadius()) >= (wHeight - lowerWall.getSize().y))
	{
		NewBall.setDirection(NewBall.getDirection().x, -NewBall.getDirection().y);
	}
}

void Game::checkPaddleCollision()
{
	float angle;
	float paddleDirection;
	if ((NewBall.getPosition().x - NewBall.getRadius()) <= (leftPaddle.getPosition().x + leftPaddle.getSize().x) && NewBall.getPosition().y >= (leftPaddle.getPosition().y - leftPaddle.getSize().y/2.f) && NewBall.getPosition().y <= (leftPaddle.getPosition().y + leftPaddle.getSize().y/2.f))
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
		NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
		//paddleDirection = leftPaddle.getDirection().y;
		////if (paddleDirection != 0)
		//{
		//	angle = MoveableObject::angleInDegree(NewBall.getDirection());
		//	if (angle > 0)
		//	{
		//		if (paddleDirection > 0)
		//		{
		//			angle = 90 - angle;
		//			angle /= 2;
		//		}
		//		else if (paddleDirection < 0)
		//		{
		//			angle /= 2;
		//		}
		//	}
		//	else
		//	{
		//		if (paddleDirection < 0)
		//		{
		//			angle = -90 - angle;
		//			angle /= 2;
		//		}
		//		else if (paddleDirection > 0)
		//		{
		//			angle /= 2;
		//		}
		//	}
		//	if (paddleDirection != 0)
		//	NewBall.setDirection(MoveableObject::rolateVector(NewBall.getDirection(), angle));
		//}
	}
	if ((NewBall.getPosition().x + NewBall.getRadius()) >= rightPaddle.getPosition().x && NewBall.getPosition().y >= (rightPaddle.getPosition().y - rightPaddle.getSize().y / 2.f) && NewBall.getPosition().y <= (rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f))
	{
		NewBall.setDirection(-NewBall.getDirection().x, NewBall.getDirection().y);
		NewBall.setSpeed(NewBall.getSpeed() + NewBall.getSpeed() * 0.1);
	}
}

void Game::randomCollision()
{
	
}

void Game::updateBall()
{
	checkWallCollision();
	if ((NewBall.getPosition().x + NewBall.getRadius()) <= 0)
	{
		//P2 scored
		rightPaddle.setScore(rightPaddle.getScore() + 1);
		defaultBallState();
	}
	if ((NewBall.getPosition().x - NewBall.getRadius()) >= wWidth)
	{
		//P1 scored
		leftPaddle.setScore(leftPaddle.getScore() + 1);
		defaultBallState();
	}
	sf::Vector2f movement;
	movement = NewBall.getDirection() * NewBall.getSpeed();
	NewBall.move(movement);
}

void Game::updatePaddle()
{
	checkPaddleCollision();
	sf::Vector2f leftMove(0, 0);
	sf::Vector2f rightMove(0, 0);
	if (isPlaying && leftPaddle.getUpState() && (leftPaddle.getPosition().y - leftPaddle.getSize().y / 2.f) >= upperWall.getSize().y)
	{
		leftPaddle.setDirection(0.f,-1.f);
	}
	if (isPlaying && leftPaddle.getDownState() && (leftPaddle.getPosition().y + leftPaddle.getSize().y / 2.f) <= (wHeight - lowerWall.getSize().y))
	{
		leftPaddle.setDirection(0.f, 1.f);
	}
	leftMove = leftPaddle.getSpeed() * leftPaddle.getDirection();
	if (isPlaying && rightPaddle.getUpState() && (rightPaddle.getPosition().y - rightPaddle.getSize().y / 2.f) >= upperWall.getSize().y)
	{
		rightPaddle.setDirection(0.f, -1.f);
	}
	if (isPlaying && rightPaddle.getDownState() && (rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f) <= (wHeight - lowerWall.getSize().y))
	{
		rightPaddle.setDirection(0.f, 1.f);
	}
	rightMove = rightPaddle.getSpeed() * rightPaddle.getDirection();
	leftMove = leftPaddle.getSpeed() * leftPaddle.getDirection();
	
	leftPaddle.move(leftMove);
	
	rightPaddle.move(rightMove);


	leftPaddle.setDirection(0.f, 0.f);
	rightPaddle.setDirection(0.f, 0.f);
	
}

void Game::updateScore()
{
	Score1.setString(std::to_string(leftPaddle.getScore()));
	Score2.setString(std::to_string(rightPaddle.getScore()));
}

void Game::processWinning()
{
	if (leftPaddle.getScore() >= 10 || rightPaddle.getScore() >= 10)
	{
		isPlaying = false;
		isOver = true;
	}
}

void Game::processBot()
{
	sf::Vector2f ballPosition(NewBall.getPosition());
	sf::Vector2f botPosition(rightPaddle.getPosition());
	float paddleLength = rightPaddle.getSize().y;
	if (NewBall.getDirection().x > 0)
	{
		if (ballPosition.y < botPosition.y - paddleLength / 2 + paddleLength / 4)
		{
			rightPaddle.setDirection(sf::Vector2f(0, -1));
		}
		else if (ballPosition.y > botPosition.y + paddleLength / 2 - paddleLength / 4)
		{
			rightPaddle.setDirection(sf::Vector2f(0, 1));
		}
		else
		{
			rightPaddle.setDirection(sf::Vector2f(0, 0));
		}
	}
}

void Game::reset()
{
	defaultBallState();
	defaultPaddleState();
}
