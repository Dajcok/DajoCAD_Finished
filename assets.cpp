#include "assets.h"

#include <iostream>
#include <cmath>

#define PI 3.14159265

dcad::assets::assets(std::size_t index, sf::Vector2f position) :
	position(position),
	index(index)
{
	targetShape.setPrimitiveType(sf::Lines);
	targetShape.resize(this->getPointCount());

	update();
}

void dcad::assets::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(targetShape, states);
}

void dcad::assets::setPosition(const sf::Vector2f& position)
{
	this->position = position;

	update();
}

void dcad::assets::setSize(int sizeX)
{
	this->sizeX = sizeX;

	update();
}

void dcad::assets::setRotation(float &angle)
{
	this->angle = angle;

	update();
}

sf::Vector2f dcad::assets::getPosition() const
{
	return this->position;
}

sf::Vector2f dcad::assets::getPoint(std::size_t index) const
{
	if (this->index == 1)
	{
		switch (index)
		{
			case 0: return position;
			case 1: return sf::Vector2f(position.x + 40 * (std::cos((90 * PI / 180) + angle)), position.y + 40 * (std::sin((90 * PI / 180) + angle)));

			case 2: return sf::Vector2f((position.x - (sizeX * std::cos(angle + PI))) + 10 * (std::cos((90 * PI / 180) + angle)), position.y - (sizeX * std::sin(angle + PI)) + 10 * (std::sin((90 * PI / 180) + angle)));
			case 3: return sf::Vector2f((position.x - (sizeX * std::cos(angle + PI))) - 10 * (std::cos((90 * PI / 180) + angle)), position.y - (sizeX * std::sin(angle + PI)) - 10 * (std::sin((90 * PI / 180) + angle)));
		}
	}

	if (this->index == 2)
	{
		switch (index)
		{
			case 0: return sf::Vector2f(position.x + 10 * (std::cos((90 * PI / 180) + angle)), position.y + 10 * (std::sin((90 * PI / 180) + angle)));
			case 1: return sf::Vector2f(position.x - 10 * (std::cos((90 * PI / 180) + angle)), position.y - 10 * (std::sin((90 * PI / 180) + angle)));

			case 2: return sf::Vector2f((position.x - (sizeX * std::cos(angle + PI))) + 10 * (std::cos((90 * PI / 180) + angle)), position.y - (sizeX * std::sin(angle + PI)) + 10 * (std::sin((90 * PI / 180) + angle)));
			case 3: return sf::Vector2f((position.x - (sizeX * std::cos(angle + PI))) - 10 * (std::cos((90 * PI / 180) + angle)), position.y - (sizeX * std::sin(angle + PI)) - 10 * (std::sin((90 * PI / 180) + angle)));
		}
		
	}
}

std::size_t dcad::assets::getPointCount() const
{
	return shapeBuffSize;
}

void dcad::assets::update()
{
	for (int i = 0; i < shapeBuffSize; i++)
	{
		targetShape[i].position = this->getPoint(i);
	}
	updateColor();
}

void dcad::assets::updateColor()
{
	for (int i = 0; i < shapeBuffSize; i++)
	{
		targetShape[i].color = this->color;
	}
}


