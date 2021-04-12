#pragma once

#ifndef BACKGROUNDGRID_H
#define BACKGROUNDGRID_H

#include <SFML/Graphics.hpp>

class backgroundGrid : public sf::Drawable
{
public:
	explicit backgroundGrid(sf::Color gridColor = sf::Color(166, 166, 166, 100));
	~backgroundGrid();
	bool drawMBackg(int index = 0)const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Color gridColor;

	sf::VertexArray m_background;
	sf::VertexArray background;

	int* const index = new int;
};

#endif !BACKGROUNDGRID_H
