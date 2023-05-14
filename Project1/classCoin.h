#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
class Coin 
{
public:

	sf::Texture texture;
	sf::Sprite sprite;
	Coin(double x, double y)
	{
		srand(time(NULL));
		bool randomBool = rand() % 2 == 1;
		if (randomBool) x += 170;
		else x -= 50;
		if (!texture.loadFromFile("coin.png")) std::cout << "Failed to load coin texture" << std::endl;
		sprite = sf::Sprite(texture);
		sprite.setScale(0.12f, 0.12f);
		sprite.setPosition(x, y + 8);
	}
};
