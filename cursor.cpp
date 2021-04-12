#include "cursor.h"
#include <iostream>


dcad::cursor::cursor(int size, sf::Vector2f position):
size(size),
position(position)
{
	dCursor.setPrimitiveType(sf::Lines);
	dCursor.resize(4);

	update();
}

void dcad::cursor::setSize(const int &size)
{
	this->size = size;
}

void dcad::cursor::setPosition(sf::Vector2i position)
{
	this->position = position;

	update();
}

sf::Vector2i dcad::cursor::getPosition()
{
	return position;
}

sf::Vector2f dcad::cursor::getCoor(std::size_t index)
{
	switch (index)
	{
		default:
			case 0: return sf::Vector2f(position.x, position.y - size);
			case 1: return sf::Vector2f(position.x, position.y + size);
			case 2: return sf::Vector2f(position.x + size, position.y);
			case 3: return sf::Vector2f(position.x - size, position.y);
	}
}

void dcad::cursor::update()
{
	for (int i = 0; i < 4; i++)
	{
		dCursor[i].position = getCoor(i);
		dCursor[i].color = color;
	}
}

void dcad::cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dCursor, states);
}
