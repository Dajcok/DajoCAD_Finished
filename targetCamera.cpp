#include "targetCamera.h"

targetCamera::targetCamera(int wheel, sf::Vector2f worldPos, sf::Vector2i mousePosition):
	wheel  (wheel),
	worldPos  (worldPos),
	mousePosition  (mousePosition)
{
	sf::View camera;
	this->camera = camera;
}

void targetCamera::cameraZoom(int maxZoom)
{
	if(maxZoom == 0)
		if (mousePosChange)
		{
			camera.setCenter(worldPos.x, worldPos.y);

			oldMousePos = mousePosition;
			

			mousePosChange = false;
		}

	if (abs(oldMousePos.x - mousePosition.x) > 20 || abs(oldMousePos.y - mousePosition.y) > 20)
		mousePosChange = true;
	

	if (wheel < 0)
		if(maxZoom != 1)
			camera.setSize(camera.getSize().x + (camera.getSize().x / 50), camera.getSize().y + (camera.getSize().y / 50));
	

	if (wheel > 0)
		if (maxZoom != 2)
			camera.setSize(camera.getSize().x - (camera.getSize().x / 50), camera.getSize().y - (camera.getSize().y / 50));		


}

void targetCamera::cameraMove(int index)
{
	
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			oldMousePosM.x = worldPos.x;
			oldMousePosM.y = worldPos.y;
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i difference;
			sf::Vector2i oldDifference;

			oldDifference = difference;

			difference.x = oldMousePosM.x - worldPos.x;
			difference.y = oldMousePosM.y - worldPos.y;

			if (oldDifference != difference)
			{
				switch (index) 
				{
				case 1:
					if (oldDifference.x > difference.x)//+x
						camera.move(difference.x, difference.y);
					break;
				case 2:
					if (oldDifference.x < difference.x)//-x
						camera.move(difference.x, difference.y);
					break;
				case 3:
					if (oldDifference.y > difference.y)//+y
						camera.move(difference.x, difference.y);
					break;
				case 4:
					if (oldDifference.y < difference.y)//-y
						camera.move(difference.x, difference.y);
					break;
				default:
						camera.move(difference.x, difference.y);
						break;
				}
			}
		}
	
}

void targetCamera::setWheelState(const int &wheel)
{
	this->wheel = wheel;
}

void targetCamera::setWorldPosition(const sf::Vector2f &worldPos)
{
	this->worldPos = worldPos;
}

void targetCamera::setMousePosition(const sf::Vector2i &mousePosition)
{
	this->mousePosition = mousePosition;
}

void targetCamera::setView(sf::RenderWindow &window)
{
	window.setView(camera);
}

void targetCamera::setCenter(const sf::Vector2f &center)
{
	camera.setCenter(center);
}

void targetCamera::setSize(const sf::Vector2f &size)
{
	camera.setSize(size);
}

sf::Vector2f targetCamera::getBoundaries_X()
{
	return sf::Vector2f(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().x + camera.getSize().x / 2);
}

sf::Vector2f targetCamera::getBoundaries_Y()
{
	return sf::Vector2f(camera.getCenter().y - camera.getSize().y / 2, camera.getCenter().y + camera.getSize().y / 2);
}

const sf::Vector2f targetCamera::getSize()
{
	return camera.getSize();
}




