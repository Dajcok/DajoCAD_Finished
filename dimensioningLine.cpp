#include "dimensioningLine.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265

dcad::dimensioningLine::dimensioningLine(const int & size) :
	size(size)
{
	{
		dLine.setPrimitiveType(sf::Lines);
		dLine.resize(getPointCount());

		position = sf::Vector2f(0, 0);
		rotation = 0;

		update();
	}
}

void dcad::dimensioningLine::setPosition(const sf::Vector2f& position)
{
	this->position = position;

	update();
}

const sf::Vector2f & dcad::dimensioningLine::getPosition()
{
	return position;
}

void dcad::dimensioningLine::setSize(const int& size)
{
	this->size = size;

	if (this->size < 0)
	{
		this->size = size * -1;
	}

	update();
}

const int& dcad::dimensioningLine::getSize() const
{
	return size;
}

std::size_t dcad::dimensioningLine::getPointCount() const
{
	return 14;
}

sf::Vector2f dcad::dimensioningLine::getCoor(std::size_t index)
{
	float rotation = this->rotation * PI / 180;

	sf::Vector2f basePoint = sf::Vector2f(position.x + (std::cos((270 * PI / 180) + rotation) * 14), position.y + (std::sin((270 * PI / 180) + rotation) * 14));
	sf::Vector2f basePoint1 = sf::Vector2f(position.x + (std::cos(rotation) * size), position.y + (std::sin(rotation) * size));
	sf::Vector2f basePoint2 = sf::Vector2f(basePoint1.x + (std::cos((270 * PI / 180) + rotation) * 14), basePoint1.y + (std::sin((270 * PI / 180) + rotation) * 14));

	switch (index)
	{
	default:
	case 0: return position;
	case 1: return sf::Vector2f(position.x + (std::cos((270 * PI / 180) + rotation) * 21), position.y + (std::sin((270 * PI / 180) + rotation) * 21));

	case 2: return basePoint;
	case 3: return sf::Vector2f(basePoint.x + (std::cos((315 * PI / 180) + rotation) * sqrt(98)), basePoint.y + (std::sin((315 * PI / 180) + rotation) * sqrt(98)));

	case 4: return basePoint;
	case 5: return sf::Vector2f(basePoint.x + (std::cos((45 * PI / 180) + rotation) * sqrt(98)), basePoint.y + (std::sin((45 * PI / 180) + rotation) * sqrt(98)));

	case 6: return basePoint1;
	case 7: return sf::Vector2f(basePoint1.x + (std::cos((270 * PI / 180) + rotation) * 21), basePoint1.y + (std::sin((270 * PI / 180) + rotation) * 21));

	case 8: return basePoint2;
	case 9: return sf::Vector2f(basePoint2.x + (std::cos((225 * PI / 180) + rotation) * sqrt(98)), basePoint2.y + (std::sin((225 * PI / 180) + rotation) * sqrt(98)));

	case 10: return basePoint2;
	case 11: return sf::Vector2f(basePoint2.x + (std::cos((135 * PI / 180) + rotation) * sqrt(98)), basePoint2.y + (std::sin((135 * PI / 180) + rotation) * sqrt(98)));

	case 12: return basePoint;
	case 13: return basePoint2;
	}
}

const float& dcad::dimensioningLine::getRotation()
{
	return rotation;
}

void dcad::dimensioningLine::setRotation(const float& rotation)
{
	this->rotation = rotation;

	update();
}

void dcad::dimensioningLine::update()
{
	for (int i = 0; i < getPointCount(); i++)
	{
		dLine[i].position = getCoor(i);
	}

	updateColor();
}

void dcad::dimensioningLine::setColor(sf::Color color)
{
	this->color = color;

	updateColor();
}

void dcad::dimensioningLine::updateColor()
{
	for (int i = 0; i < getPointCount(); i++)
	{
		dLine[i].color = color;
	}
}

void dcad::dimensioningLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dLine, states);
}


