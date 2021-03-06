#include "maps.h"
#include "score.h"
#include "time.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <unistd.h>

using namespace sf;

class PLAYER {
public:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    int score = 0, count = 0;

    PLAYER(Texture& image)
    {
        sprite.setTexture(image);
        rect = FloatRect(50, 40, 29, 29);

        dx = dy = 0.1;
        currentFrame = 0;
    }

    void update(float time)
    {
        rect.left += dx * time;
        Collision(0);
        rect.top += dy * time;
        Collision(1);

        currentFrame += 0.005 * time;
        if (currentFrame > 3)
            currentFrame -= 3;

        if (dy < 0)
            sprite.setTextureRect(
                    IntRect(2 + 32 * int(currentFrame), 4, 29, 29));
        if (dy > 0)
            sprite.setTextureRect(
                    IntRect(2 + 32 * int(currentFrame), 68, 29, 29));
        if (dx < 0)
            sprite.setTextureRect(
                    IntRect(2 + 32 * int(currentFrame), 36, 29, 29));
        if (dx > 0)
            sprite.setTextureRect(
                    IntRect(2 + 32 * int(currentFrame), 100, 29, 29));

        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

        dx = 0;
        dy = 0;
    }

    void Collision(int dir)
    {
        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32;
                 j++) {
                if (TileMap[i][j] == 'B') {
                    if ((dx > 0) && (dir == 0))
                        rect.left = j * 32 - rect.width;
                    if ((dx < 0) && (dir == 0))
                        rect.left = j * 32 + 32;
                    if ((dy > 0) && (dir == 1)) {
                        rect.top = i * 32 - rect.height;
                        dy = 0;
                    }
                    if ((dy < 0) && (dir == 1)) {
                        rect.top = i * 32 + 32;
                        dy = 0;
                    }
                }
                if (TileMap[i][j] == 'Z') {
                    TileMap[i][j] = ' ';
                    score += 10;
                    count++;
                }
                if (TileMap[i][j] == 'X') {
                    TileMap[i][j] = ' ';
                    score += 25;
                    count++;
                }
                if (TileMap[i][j] == 'C') {
                    TileMap[i][j] = ' ';
                    score += 50;
                    count++;
                }
            }
    }
};

void menu(RenderWindow& window, std::string path)
{
    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture;
    menuTexture1.loadFromFile(path + "images/1.jpg");
    menuTexture2.loadFromFile(path + "images/2.jpg");
    menuTexture3.loadFromFile(path + "images/3.jpg");
    aboutTexture.loadFromFile(path + "images/about.jpg");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3),
            about(aboutTexture);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(305, 200);
    menu2.setPosition(375, 500);
    menu3.setPosition(350, 350);

    while (isMenu) {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));

        if (IntRect(305, 200, 377, 90).contains(Mouse::getPosition(window))) {
            menu1.setColor(Color::Blue);
            menuNum = 1;
        }
        if (IntRect(375, 500, 217, 80).contains(Mouse::getPosition(window))) {
            menu2.setColor(Color::Blue);
            menuNum = 2;
        }
        if (IntRect(350, 350, 280, 95).contains(Mouse::getPosition(window))) {
            menu3.setColor(Color::Blue);
            menuNum = 3;
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (menuNum == 1)
                isMenu = false;
            if (menuNum == 2) {
                window.close();
                isMenu = false;
            }
            if (menuNum == 3) {
                window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape))
                    ;
            }
        }

        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.display();
    }
}

int main()
{
    std::string path;
    path.resize(1024);
    ssize_t ret = readlink("/proc/self/exe", &path[0], path.size());
    path.resize(ret);
    for (int i = 0; i < 8; i++)
        path.pop_back();
    RandomGeneration(40);
    Music LevelMusic;
    LevelMusic.openFromFile(path + "music/Music.ogg");
    RenderWindow window(VideoMode(900, 900), "Maze");
    menu(window, path);

    Font font;
    font.loadFromFile(path + "CyrilicOld.TTF");
    Text text("", font, 20);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    Clock clock;
    Clock gameTimeClock;

    Texture t, aboutTexture, ywTexture, goTexture, setexture;
    t.loadFromFile(path + "images/hero.png");
    setexture.loadFromFile(path + "images/set.png");
    aboutTexture.loadFromFile(path + "images/about.jpg");
    ywTexture.loadFromFile(path + "images/YW.jpg");
    goTexture.loadFromFile(path + "images/GO.jpg");

    PLAYER p(t);

    Sprite about(aboutTexture), yw(ywTexture), go(goTexture);
    Sprite sesprite;
    sesprite.setTexture(setexture);

    int gameTime = 60, second;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        second = gameTimeClock.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 500;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            p.dx = -0.1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            p.dx = 0.1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            p.dy = -0.1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            p.dy = 0.1;
        }

        p.update(time);

        offsetX = p.rect.left - 450;
        offsetY = p.rect.top - 300;

        window.clear();
        window.clear(Color::Black);

        if (!LevelMusic.getStatus())
            LevelMusic.play();

        RectangleShape rectangle(Vector2f(32, 32));
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') //стена
                {
                    sesprite.setTextureRect(IntRect(32, 0, 32, 32));
                }
                if (TileMap[i][j] == 'Z') //монетка первого типа
                {
                    sesprite.setTextureRect(IntRect(64, 0, 32, 32));
                }
                if (TileMap[i][j] == 'X') //монетка второго типа
                {
                    sesprite.setTextureRect(IntRect(0, 32, 32, 32));
                }
                if (TileMap[i][j] == 'C') //монетка третьего типа
                {
                    sesprite.setTextureRect(IntRect(96, 0, 32, 32));
                }
                if (TileMap[i][j] == ' ') //пол
                {
                    sesprite.setTextureRect(IntRect(0, 0, 32, 32));
                }

                sesprite.setPosition(j * 32 - offsetX, i * 32 - offsetY);
                window.draw(sesprite);
            }
        std::ostringstream gameTimeString;
        gameTimeString << timer(gameTime, second);
        std::ostringstream gameMoneyString;
        gameMoneyString << score(p.score);
        text.setString(
                L"Время игры: " + gameTimeString.str() + L"\nСобрано монет: "
                + gameMoneyString.str());
        text.setPosition(50, 50);

        window.draw(p.sprite);
        window.draw(text);
        window.display();

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::H)) {
            window.draw(about);
            window.display();
            while (!Keyboard::isKeyPressed(Keyboard::Return)) {
                gameTimeClock.restart();
            }
            gameTime = timer(gameTime, second);
        }
        if (p.count == 40) {
            LevelMusic.stop();
            window.clear();
            window.clear(Color::Black);
            window.draw(yw);
            text.setString(
                    L"Вы собрали монеток: " + gameMoneyString.str()
                    + L"\nНажмите Esc, чтобы выйти.");
            text.setPosition(340, 600);
            window.draw(text);
            window.display();
            while (!Keyboard::isKeyPressed(Keyboard::Escape))
                ;
            window.close();
        }
        if (timer(gameTime, second) == 0) {
            LevelMusic.stop();
            window.clear();
            window.clear(Color::Black);
            window.draw(go);
            text.setString(
                    L"Вы успели собрать монеток: " + gameMoneyString.str()
                    + L"\nНажмите Esc, чтобы выйти.");
            text.setPosition(350, 600);
            window.draw(text);
            window.display();
            while (!Keyboard::isKeyPressed(Keyboard::Escape))
                ;
            window.close();
        }
    }

    return 0;
}
