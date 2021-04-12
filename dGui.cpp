#include "dGui.h"
#include <iostream>

using namespace dG;

dGui::dGui(sf::RenderWindow *window):
window (window)
{
	if (!texturesLoaded)
	{
		loadResources("dGuiLeftPanel.png", 0);
		loadResources("dGuiLeftPanel_crsrHover.png", 1);
		loadResources("dGuiLeftPanel_gridHover.png", 2);
		loadResources("dGuiLeftPanel_mMapHover.png", 3);

		texturesLoaded = true;
	}

	dGuiView.setSize({ 30, 600 });
	dGuiView.setCenter({ dGuiView.getSize().x / 2, dGuiView.getSize().y / 2 });
	dGuiView.setViewport(sf::FloatRect(0, 0, 0.015f, 0.55f));

	if(this->window != nullptr)
		this->window->setView(dGuiView);
}

bool dG::dGui::guiActive(sf::Vector2i mousePosition)
{
	if (mousePosition.x < 40 && mousePosition.y < 625)
		return true;
	else
		return false;
}

void dG::dGui::hoverChange(sf::Vector2i mousePosition)
{
	if (mousePosition.x < 35 && mousePosition.y < 55 && mousePosition.x > 12 && mousePosition.y > 30)// mriežka
	{
		finalLeftPanel = &objSprite[2];

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !firstClick_grid)
			while (1)
			{
				drawGrid = false;

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					firstClick_grid = true;
					break;
				}
			}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && firstClick_grid)
			while (1)
			{
				drawGrid = true;

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					firstClick_grid = false;
					break;
				}
			}
	}
	else if (mousePosition.x < 35 && mousePosition.y < 85 && mousePosition.x > 12 && mousePosition.y > 60) // volny pohlad
	{
		finalLeftPanel = &objSprite[1];

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !firstClick_freeLook)
			while (1)
			{
				freeLook = true;

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					firstClick_freeLook = true;
					break;
				}
			}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && firstClick_freeLook)
			while (1)
			{
				freeLook = false;

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					firstClick_freeLook = false;
					break;
				}
			}
	}

	else if (mousePosition.x < 35 && mousePosition.y < 115 && mousePosition.x > 12 && mousePosition.y > 90) // minimapa
	{
		finalLeftPanel = &objSprite[3];

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !firstClick_mMap)
			while (1)
			{
				mMap = false;

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					firstClick_mMap = true;
					break;
				}
			}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && firstClick_mMap)
			while (1)
			{
				mMap = true;

				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					firstClick_mMap = false;
					break;
				}
			}
	}

	else
		finalLeftPanel = &objSprite[0];
}

void dGui::loadResources(const char fileLocation[30], int id)
{
	if (!objTexture[id].loadFromFile(fileLocation))
	{
		std::cout << "Couldn´t create texture number: " << id + 1 << std::endl;

		system ("pause");
		exit(1);
	}

	else
	{
		std::cout << id+1 <<". texture loaded successfully" << std::endl;
	}

	objSprite[id].setTexture(objTexture[id]);
}



