#pragma once
#ifndef DCAD_ASSETS_H
#define DCAD_ASSETS_H



#include <SFML/Graphics.hpp>

#include <vector>

namespace dcad
{
	class assets : public sf::Shape
	{
	public:
		assets(std::size_t index = 0, sf::Vector2f position = sf::Vector2f(0,0));

		void setPosition(const sf::Vector2f& position);

		void setSize(int sizeX);

		void setRotation(float &angle);

		sf::Vector2f getPosition() const;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual sf::Vector2f getPoint(std::size_t index) const;

		virtual std::size_t getPointCount() const;
		
		void update();
		void updateColor();

		sf::VertexArray targetShape;

		sf::Vector2f position;
		sf::Color color = sf::Color::Green;

		std::size_t index;
		int sizeX = 20;
		int shapeBuffSize = 4;
		float angle = 0;

	};	
}

#endif DCAD_ASSETS_H

