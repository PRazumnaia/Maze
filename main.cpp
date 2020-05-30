#include "maps.h"
#include <SFML/Graphics.hpp>
#include <sstream>


using namespace sf;


class PLAYER {

public:
  float dx, dy;
  FloatRect rect;
  Sprite sprite;
  float currentFrame;

  PLAYER(Texture &image) {
    sprite.setTexture(image);
    rect = FloatRect(50, 40, 29, 29);

    dx = dy = 0.1;
    currentFrame = 0;
  }
};

int main()
{
    RandomGeneration(7);
    RenderWindow window( VideoMode(1924,1080), "Test");

    Font font;
    font.loadFromFile("CyrilicOld.TTF");
    Text text("", font, 20);
    text.setFillColor(Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    Texture t;
    t.loadFromFile("hero.png");

    PLAYER p(t);
	
    Clock clock;
    Clock gameTimeClock;
    
    CircleShape MyCircle(100.f);
    MyCircle.setFillColor(Color::Green);

    while (window.isOpen())
    {
        int gameTime = 50;
        float time = clock.getElapsedTime().asMicroseconds();
        gameTime -= gameTimeClock.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 800;
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        std::ostringstream gameTimeString;    
	    gameTimeString << gameTime;		
		text.setString(L"Время игры: "+gameTimeString.str());
		text.setPosition(200, 200);
		
        window.clear();
        window.clear(Color::White);
        window.draw(p.sprite);
        window.draw(text);//рисую этот текст
        window.display();
    }

    window.clear();
    window.clear(Color::White);

    RectangleShape rectangle(Vector2f(32, 32));
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) {
        if (TileMap[i][j] == 'B') //стена
          rectangle.setFillColor(Color::Black);
        if (TileMap[i][j] == 'Z') //монетка первого типа
          rectangle.setFillColor(Color::Yellow);
        if (TileMap[i][j] == 'X') //монетка второго типа
          rectangle.setFillColor(Color::Green);
        if (TileMap[i][j] == 'C') //монетка третьего типа
          rectangle.setFillColor(Color::Blue);
        if (TileMap[i][j] == ' ')
          continue;

        rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
        window.draw(rectangle);
      }
    window.draw(p.sprite);
    window.display();
  }

  return 0;
}
