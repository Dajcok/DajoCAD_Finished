#include "backgroundGrid.h"

backgroundGrid::backgroundGrid(sf::Color gridColor) : 
	gridColor (gridColor)
	
{
	bool notEnough_x;
	bool notEnough_y;
	
	background.setPrimitiveType(sf::Lines);
	background.resize(616);

	m_background.setPrimitiveType(sf::Lines);
	m_background.resize(6016);

	std::int16_t x = 0;
	std::int16_t y = 0;
	std::size_t num = 0;

	std::int16_t m_x = 0;
	std::int16_t m_y = 0;
	std::size_t m_num = 0;

	notEnough_x = true;
	notEnough_y = true;

	//1920, 1080
	for (int i = 0; i <= 48; i++)
	{
		background[num].position = sf::Vector2f(x, 0);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(x, 1080);
		background[num].color = this->gridColor;
		num++;

		x = x + 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_x)
			{
				m_background[m_num].position = sf::Vector2f(m_x, 0);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(m_x, 1080);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_x = m_x + 4;

				if (m_num > 960)
					notEnough_x = false;
			}
		}
	}

	for (int i = 0; i <= 27; i++)
	{
		background[num].position = sf::Vector2f(0, y);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(1920, y);
		background[num].color = this->gridColor;

		num++;
		y = y + 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_y)
			{
				m_background[m_num].position = sf::Vector2f(0, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(1920, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_y = m_y + 4;

				if (m_num > 1500)
					notEnough_y = false;
			}
		}
	}

	//1920, -1080
	x = 0;
	y = 0;

	m_x = 0;
	m_y = 0;

	notEnough_x = true;
	notEnough_y = true;

	for (int i = 0; i <= 48; i++)
	{
		background[num].position = sf::Vector2f(x, 0);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(x, -1080);
		background[num].color = this->gridColor;
		num++;

		x = x + 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_x)
			{
				m_background[m_num].position = sf::Vector2f(m_x, 0);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(m_x, -1080);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_x = m_x + 4;

				if (m_num > 2460)
					notEnough_x = false;
			}
		}
	}

	for (int i = 0; i <= 27; i++)
	{
		background[num].position = sf::Vector2f(0, y);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(1920, y);
		background[num].color = this->gridColor;
		num++;

		y = y - 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_y)
			{
				m_background[m_num].position = sf::Vector2f(0, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(1920, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_y = m_y - 4;

				if (m_num > 3000)
					notEnough_y = false;
			}
		}
	}

	//-1920, -1080
	x = 0;
	y = 0;

	m_x = 0;
	m_y = 0;

	notEnough_x = true;
	notEnough_y = true;

	for (int i = 0; i <= 48; i++)
	{
		background[num].position = sf::Vector2f(x, 0);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(x, -1080);
		background[num].color = this->gridColor;
		num++;

		x = x - 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_x)
			{
				m_background[m_num].position = sf::Vector2f(m_x, 0);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(m_x, -1080);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_x = m_x - 4;

				if (m_num > 3960)
					notEnough_x = false;
			}
		}
	}

	for (int i = 0; i <= 27; i++)
	{
		background[num].position = sf::Vector2f(0, y);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(-1920, y);
		background[num].color = this->gridColor;
		num++;

		y = y - 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_y)
			{
				m_background[m_num].position = sf::Vector2f(0, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(-1920, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_y = m_y - 4;

				if (m_num > 4500)
					notEnough_y = false;
			}
		}
	}

	//-1920, 1080
	x = 0;
	y = 0;

	m_x = 0;
	m_y = 0;

	notEnough_x = true;
	notEnough_y = true;

	for (int i = 0; i <= 48; i++)
	{
		background[num].position = sf::Vector2f(x, 0);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(x, 1080);
		background[num].color = this->gridColor;
		num++;

		x = x - 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_x)
			{
				m_background[m_num].position = sf::Vector2f(m_x, 0);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(m_x, 1080);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_x = m_x - 4;

				if (m_num > 5460)
					notEnough_x = false;
			}
		}
	}

	for (int i = 0; i <= 27; i++)
	{
		background[num].position = sf::Vector2f(0, y);
		background[num].color = this->gridColor;
		num++;

		background[num].position = sf::Vector2f(-1920, y);
		background[num].color = this->gridColor;
		num++;

		y = y + 40;

		for (int i = 0; i <= 10; i++)
		{
			if (notEnough_y)
			{
				m_background[m_num].position = sf::Vector2f(0, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_background[m_num].position = sf::Vector2f(-1920, m_y);
				m_background[m_num].color = this->gridColor;
				m_num++;

				m_y = m_y + 4;

				if (m_num > 6000)
					notEnough_y = false;
			}
		}
	}
}

backgroundGrid::~backgroundGrid()
{
	delete this;
}

bool backgroundGrid::drawMBackg(int index) const
{
	*this->index = index;

	if (*this->index == 0)
		return false;

	else if (*this->index == 1)
		return true;
}


void backgroundGrid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	auto *targetPtr = &target;

	targetPtr->draw(background, states);

	if (drawMBackg(*index) == true)
		targetPtr->draw(m_background, states);
	
}