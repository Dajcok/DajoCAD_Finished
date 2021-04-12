#include "ellipseShape.h"

dcad::ellipseShape::ellipseShape(const sf::Vector2f & radius) :
	radius(radius)
{
	{
		pointCount = 30;
		update();
	}
}

void dcad::ellipseShape::setRadius(const sf::Vector2f& radius)
{
	this->radius = radius;
	update();
}

const sf::Vector2f& dcad::ellipseShape::getRadius() const
{
	return radius;
}

std::size_t dcad::ellipseShape::getPointCount() const
{
	return pointCount;
}

sf::Vector2f dcad::ellipseShape::getPoint(std::size_t index) const
{
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / getPointCount() - pi / 2;
	float x = std::cos(angle) * radius.x;
	float y = std::sin(angle) * radius.y;

	return sf::Vector2f(radius.x + x, radius.y + y);
}

void dcad::ellipseShape::setPointCount(std::size_t pointCount)
{
	this->pointCount = pointCount;
	update();
}