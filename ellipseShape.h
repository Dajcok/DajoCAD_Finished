#ifndef DCAD_ELLIPSESHAPE_H
#define DCAD_ELLIPSESHAPE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace dcad
{
	class ellipseShape : public sf::Shape
	{
	public:

		explicit ellipseShape(const sf::Vector2f& radius = sf::Vector2f(0.f, 0.f));

		void setRadius(const sf::Vector2f& radius);

		const sf::Vector2f& getRadius() const;


		virtual std::size_t getPointCount() const;

		virtual sf::Vector2f getPoint(std::size_t index) const;

		void setPointCount(std::size_t pointCount);

	private:
		std::size_t pointCount;
		sf::Vector2f radius;
	};
}

#endif DCAD_ELLIPSESHAPE_H
