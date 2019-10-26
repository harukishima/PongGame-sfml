#include "MainMenu.h"

MainMenu::MainMenu()
{
	//Set title
	titleFont.loadFromFile("sansation.ttf");
	title.setFont(titleFont);
	title.setCharacterSize(50);
	title.setString("Pong Game");
	title.setPosition(280, 100);
	
	

	//Set left box
	leftBox.setSize(sf::Vector2f(200, 60));
	leftBox.setFillColor(sf::Color::Transparent);
	leftBox.setOutlineThickness(2);
	leftBox.setOutlineColor(sf::Color::White);
	leftBox.setPosition(sf::Vector2f(150, 320));
	//Left box text
	leftText.setFont(titleFont);
	leftText.setCharacterSize(20);
	leftText.setString("Single player");
	leftText.setFillColor(sf::Color::White);
	leftText.setPosition(sf::Vector2f(leftBox.getPosition().x + 45, leftBox.getPosition().y + 15));
	

	//Set right box
	rightBox = leftBox;
	rightBox.setPosition(sf::Vector2f(450, 320));
	//Right box text
	rightText = leftText;
	rightText.setString("Multiplayer");
	rightText.setPosition(sf::Vector2f(rightBox.getPosition().x + 55, rightBox.getPosition().y + 15));

}

void MainMenu::setLeftState(bool l)
{
	isLeft = l;
}

void MainMenu::setRightState(bool r)
{
	isRight = r;
}

bool MainMenu::getLeftState()
{
	return isLeft;
}

bool MainMenu::getRightState()
{
	return isRight;
}

void MainMenu::updateMenu()
{
	if (isLeft)
	{
		leftBox.setFillColor(sf::Color::White);
		leftText.setFillColor(sf::Color::Black);
	}
	else
	{
		leftBox.setFillColor(sf::Color::Transparent);
		leftText.setFillColor(sf::Color::White);
	}

	if (isRight)
	{
		rightBox.setFillColor(sf::Color::White);
		rightText.setFillColor(sf::Color::Black);
	}
	else
	{
		rightBox.setFillColor(sf::Color::Transparent);
		rightText.setFillColor(sf::Color::White);
	}
}

void MainMenu::navigate(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Left)
	{
		isLeft = true;
		isRight = false;
	}
	if (key == sf::Keyboard::Right)
	{
		isRight = true;
		isLeft = false;
	}
}
