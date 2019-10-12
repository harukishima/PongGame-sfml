#include "game.h"



Game::Game()
	: mWindow(sf::VideoMode(wWidth, wHeight), "Pong Game")
{
	defaultWall();

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
		if (ev.type == sf::Event::Closed) {
			mWindow.close();
		}
	}
}

void Game::update(sf::Time TimePerFrame)
{
	checkWallCollision();
	sf::Vector2f movement;
	movement = NewBall.getDirection() * NewBall.getSpeed();
	NewBall.move(movement);
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(NewBall);
	mWindow.draw(upperWall);
	mWindow.draw(lowerWall);
	mWindow.display();
}

void Game::defaultWall()
{
	upperWall.setSize(sf::Vector2f(wWidth, 20.f));
	lowerWall.setSize(sf::Vector2f(wWidth, 20.f));
	upperWall.setFillColor(sf::Color::White); 
	lowerWall.setFillColor(sf::Color::White);
	upperWall.setPosition(sf::Vector2f(0.f, 0.f));
	lowerWall.setPosition(sf::Vector2f(0.f, wHeight - 20.f));
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
