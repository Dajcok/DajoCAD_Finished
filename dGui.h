#ifndef DGUI_H
#define DGUI_H

#include "SFML/Graphics.hpp"
#include <fstream>
#include <cstdlib>

#pragma once


namespace dG
{
	class dGui
	{
	public:
		dGui(sf::RenderWindow *window = nullptr);

		bool guiActive(sf::Vector2i mousePosition);
		void hoverChange(sf::Vector2i mousePosition);

	private:
		void loadResources(const char fileLocation[30], int id);

		sf::RenderWindow *window;

		sf::Sprite objSprite[4];
		sf::Texture objTexture[4];

		bool texturesLoaded;

	protected:
		sf::Sprite *finalLeftPanel = nullptr;
		sf::View dGuiView;

		bool drawGrid = true;
		bool freeLook = false;
		bool mMap = true;

		bool firstClick_grid = false;
		bool firstClick_freeLook = false;
		bool firstClick_mMap = false;
	};
}

#endif !DGUI_H