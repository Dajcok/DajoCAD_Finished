#ifndef DCAD_DIMENSIONINGLINE_H
#define DCAD_DIMENSIONINGLINE_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>

namespace dcad
{
	class dimensioningLine : public sf::Drawable
	{
	public:
		dimensioningLine(const int& size = 0);

		void setPosition(const sf::Vector2f& position);

		const sf::Vector2f& getPosition();

		void setSize(const int& size);

		const int& getSize() const;

		virtual std::size_t getPointCount() const;

		void setColor(sf::Color color);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setRotation(const float& rotation);

		const float& getRotation();

	private:
		int size;
		float rotation;

		sf::VertexArray dLine;
		sf::Color color;
		sf::Vector2f position;

		sf::Vector2f getCoor(std::size_t index);

		void update();

		void updateColor();

	};
}
#endif DCAD_DIMENSIONINGLINE_H