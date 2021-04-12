#pragma once

#include <SFML/Graphics.hpp>



class targetCamera
{
public:
	explicit targetCamera(int wheel = 0, sf::Vector2f worldPos = sf::Vector2f(0, 0), sf::Vector2i mousePosition = sf::Vector2i(0, 0));

private:
	sf::Vector2i mousePosition;
	sf::Vector2f worldPos;
	sf::Vector2i oldMousePos;
	sf::Vector2i oldMousePosM;

	bool mousePosChange;

	sf::View camera;

	int wheel;

protected:
	friend class targetWindow;

	void cameraZoom(int maxZoom);
	void cameraMove(int index);

	void setWheelState(const int &wheel);
	void setWorldPosition(const sf::Vector2f &worldPos);
	void setMousePosition(const sf::Vector2i &mousePos);
	void setView(sf::RenderWindow &window);
	void setCenter(const sf::Vector2f &center);
	void setSize(const sf::Vector2f &size);
	sf::Vector2f getBoundaries_X();
	sf::Vector2f getBoundaries_Y();

	const sf::Vector2f getSize();

}; 

