#pragma once
#ifndef DCAD_CURSOR_H
#define DCAD_CURSOR_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>

namespace dcad
{
	class cursor : public sf::Drawable
	{
	public:
		explicit cursor(int size = 5, sf::Vector2f position = sf::Vector2f(0, 0));

		void setSize(const int &size);

		void setPosition(sf::Vector2i position);

		sf::Vector2i getPosition();

	private:
		sf::Vector2f getCoor(std::size_t index);

		void update();

		sf::VertexArray dCursor;

		int size;	
		sf::Color color = sf::Color::White;
		sf::Vector2i position;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
#endif !DCAD_CURSOR_H