#include <SFML/Graphics.hpp>
#include "classCoin.h"
#include <iostream>
#include <random>
class Cloud
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	double speed;
	Coin* coin;
	bool coinExist;
	Cloud()
	{		
		speed = 0.5f;
		coinExist = true;
		if (!texture.loadFromFile("cloud.png"))
		{
			std::cout << "Failed to load a cloud texture" << std::endl;
		}
		sprite = sf::Sprite(texture);
		sprite.setScale(0.7f, 0.7f);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> xx(0, 450);
		int x = xx(gen);
		sprite.setPosition(x, 750);		
		coin = new Coin(x, 750);
		std::cout << "The cloud has been created" << std::endl;
	}
	~Cloud()
	{
		std::cout << "The cloud has been deleted" << std::endl;
	}
};
