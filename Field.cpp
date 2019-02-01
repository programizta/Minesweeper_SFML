#include "saper.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Font.hpp>

Field::Field() // konstruktor pojedynczego pola
{
    mine = false;
    covered = true;
    flag = false;

    mine_color = sf::Color::Red; // tam gdzie mina to kolor czerwony pola
    covered_color = sf::Color::Cyan; // gdy zakryte pole to kolor Cyan
    uncovered_color = sf::Color::Green; // gdy odkryte pole to kolor zielony
    flag_color = sf::Color::Magenta; // gdy jest flaga to kolor Magenta
    square.setSize(sf::Vector2f(38, 38)); // pojedyncze pole ma rozmiary 38x38 pikseli
    easy.setSize(sf::Vector2f(200, 100));
    easy.setPosition(50, 470);
    easy.setFillColor(sf::Color::Green);
    medium.setSize(sf::Vector2f(200, 100));
    medium.setPosition(470, 470);
    medium.setFillColor(sf::Color::Green);
    hard.setSize(sf::Vector2f(200, 100));
    hard.setPosition(902, 470);
    hard.setFillColor(sf::Color::Green);
    start.setSize(sf::Vector2f(200, 100));
    start.setPosition(902, 300);
    start.setFillColor(sf::Color::Green);

    font.loadFromFile("Font\arial.ttf");

    easy_t.setFont(font);
    easy_t.setString("Easy");
    easy_t.setPosition(90, 484);
    easy_t.setColor(sf::Color::Black);
    easy_t.setCharacterSize(50);

    medium_t.setFont(font);
    medium_t.setString("Medium");
    medium_t.setPosition(480, 484);
    medium_t.setColor(sf::Color::Black);
    medium_t.setCharacterSize(50);

    hard_t.setFont(font);
    hard_t.setString("Hard");
    hard_t.setPosition(945, 484);
    hard_t.setColor(sf::Color::Black);
    hard_t.setCharacterSize(50);

    start_t.setFont(font);
    start_t.setString("START!");
    start_t.setPosition(917, 315);
    start_t.setColor(sf::Color::Black);
    start_t.setCharacterSize(50);
}

void Field::place_mine() // metoda ustawiajaca mine
{
    mine = true;
}

bool Field::is_mine() // metoda sprawdzajaca wartosc logiczna miny na pojedynczym polu
{
    if (mine) return true;
    return false;
}

void Field::uncover() // metoda ukrywajaca pojedyncze pole
{
    covered = false;
}

bool Field::is_covered() // metoda zwracajaca wartosc logiczna zakrycia pola
{
    return covered;
}

bool Field::is_flag() // metoda zwracajaca wartosc logiczna zakrycia pola
{
    return flag;
}

void Field::place_flag() // metoda zakrywajaca pojedyncze pole
{
    flag = true;
}

void Field::change_flag() // metoda zmieniajaca wartosc logiczna zakrycia/odkrycia pola
{
    if (flag) flag = false;
    else flag = true;
}

void Field::draw_square(sf::RenderWindow & win) //metoda rysujaca pojedynczy kwadrat
{
	win.draw(square);
}

void Field::draw_buttons(sf::RenderWindow & win)
{
    win.draw(easy);
    win.draw(medium);
    win.draw(hard);
    win.draw(start);
}

void Field::setting(int x, int y) //metoda potrzebna do zmiany pozycji pola
{
	square.setPosition(x, y);
}

void Field::uncovered_c() // metoda koloryjaca odkryte pole
{
	square.setFillColor(uncovered_color);
}

void Field::covered_c() // metoda kolorujaca zakryte pole
{
	square.setFillColor(covered_color);
}

void Field::place_flag_c() // metoda kolorujaca pole, na ktorym umieszczamy flage
{
    square.setFillColor(flag_color);
}

void Field::mine_c()
{
    square.setFillColor(mine_color);
}

void Field::easy_pressed()
{
    easy.setFillColor(sf::Color::Cyan);
}

void Field::medium_pressed()
{
    medium.setFillColor(sf::Color::Cyan);
}

void Field::hard_pressed()
{
    hard.setFillColor(sf::Color::Cyan);
}

void Field::draw_text(sf::RenderWindow & win)
{
    win.draw(easy_t);
    win.draw(medium_t);
    win.draw(hard_t);
    win.draw(start_t);
}
