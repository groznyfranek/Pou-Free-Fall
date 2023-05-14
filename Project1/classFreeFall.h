#include <SFML/Graphics.hpp>

#include "classCloud.h"
#include "classPou.h"

#include <windows.h>
#include <iostream>
#include <vector>

class FreeFall
{
private:
    int time;
    int coins;
    int hits;
public:
    sf::RenderWindow* window;
    sf::Image* icon;
    sf::Texture coinTexture;
    sf::Sprite coinSprite;
    std::vector<Cloud*> clouds;
    Pou* pou;
    sf::Text text;
    sf::Font font;
    sf::Clock score;
    std::string label;
    FreeFall()
	{
        window = new sf::RenderWindow(sf::VideoMode(600, 800), "Free fall");
        icon = new sf::Image;
        clouds.push_back(new Cloud);
        pou = new Pou;
        
        if (!coinTexture.loadFromFile("coin.png")) std::cout << "Failed to load coin texture" << std::endl;
        coinSprite = sf::Sprite(coinTexture);
        coinSprite.setScale(0.12f, 0.12f);
        coinSprite.setPosition(15, 45);

        time = 0;
        coins = 0;
        hits = 0;
        score.restart();       

        if (!icon->loadFromFile("pouTexture.png")) std::cout << "Failed to load icon" << std::endl;
        
        window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

        label = " Score: " + std::to_string(time) + "\n" + std::to_string(coins) + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nHits: " + std::to_string(hits)+"/5";
        if (!font.loadFromFile("./font.ttf")) std::cout << "Failed to load font" << std::endl;
        
        text.setFont(font);
        text.setOutlineThickness(1.0f);
        text.setOutlineColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(0, 0));
        text.setString(label);
	}
    void run()
    {
        while (window->isOpen())
        {
            sf::Event e;
            while (window->pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                    window->close();
            }
            clock();
            render();   
            moveClouds();
            pouMove();
            collisions();

            if (hits >= 5)
            {
                std::string str =  "You hit 5 clouds \n Result: ";
                str += std::to_string(time);
                str += "\n Coins: ";
                str += std::to_string(coins);
                LPCSTR lpcstr = static_cast<LPCSTR>(str.c_str());
                bool accept = MessageBoxA(NULL, lpcstr,"You have lost" , MB_OK);
                window->close();
            }

        }
        
    }
    void clock()
    {
        time = score.getElapsedTime().asSeconds();
        label = " Score: " + std::to_string(time) + " \n         " + std::to_string(coins) + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nhits: " + std::to_string(hits)+"/5";
        text.setString(label);
    }
    void render()
    {
        window->clear(sf::Color(40, 140, 225));
        for (const auto& cloud : clouds)
        {
            window->draw(cloud->sprite);
            if(cloud->coinExist) window->draw(cloud->coin->sprite);
        }
        window->draw(pou->sprite);
        window->draw(coinSprite);
        window->draw(text);
        window->display();
    }
    void moveClouds()
    {
        std::vector<Cloud*> cloudsCopy = clouds;

        for (auto& cloud : clouds)
        {
            sf::Vector2f pos = cloud->sprite.getPosition();
            pos.y -= (cloud->speed) * 0.5;
            cloud->sprite.setPosition(pos);

            pos = cloud->coin->sprite.getPosition();
            pos.y -= (cloud->speed) * 0.5;
            cloud->coin->sprite.setPosition(pos);
        }
        
        for (auto& cloud : cloudsCopy)
        {
            if (cloud->sprite.getPosition().y == 300) clouds.push_back(new Cloud);
            if (cloud->sprite.getPosition().y < 0) erase(cloud);
        }
        
       
    }
    void erase(Cloud* c)
    {
        auto it = std::find(clouds.begin(), clouds.end(), c);
        if (it != clouds.end())
        {
            clouds.erase(it);
            delete c;
        }
    }
    void pouMove()
    {
        double speed = 200.f;
        sf::Vector2f newPosition = pou->sprite.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            newPosition.x -= speed * pou->deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            newPosition.x += speed * pou->deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            newPosition.y -= speed * pou->deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            newPosition.y += speed * pou->deltaTime;
        }
        if(newPosition.x > 0 && newPosition.x < 510) pou->sprite.setPosition(newPosition);
    }
    void collisions()
    {
        for (auto& cloud : clouds)
        {
            if (checkCollisionCloud(pou, cloud))
            {
                erase(cloud);
                ++hits;
            }
            if (checkCollisionCoin(pou, cloud->coin))
            {
                cloud->coinExist = false;
                delete cloud->coin;
                ++coins;
            }
        }
    }
    bool checkCollisionCloud(Pou* pou, Cloud* cloud)
    {
        sf::FloatRect pouBounds = pou->sprite.getGlobalBounds();
        sf::FloatRect cloudBounds = cloud->sprite.getGlobalBounds();
        return pouBounds.intersects(cloudBounds);
    }
    bool checkCollisionCoin(Pou* pou, Coin* coin)
    {
        sf::FloatRect pouBounds = pou->sprite.getGlobalBounds();
        sf::FloatRect coinBounds = coin->sprite.getGlobalBounds();
        return pouBounds.intersects(coinBounds);
    }
};
