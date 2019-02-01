#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Audio.hpp>
#define M 15
#define N 15

class Field
{
    bool covered;   // mialem problem z hermetyzacja danych, czyli z dostepem
    bool flag;      // do tych prywatnych zmiennych
    bool mine;
    sf::Color covered_color;
    sf::Color mine_color;
    sf::Color flag_color;
    sf::Font font;
    sf::Color uncovered_color;
    sf::RectangleShape square; // deklaracja kwadracika
    sf::RectangleShape easy, medium, hard; // deklaracja przyciskow z wyborem poziomu trudnosci
    sf::Text easy_t, medium_t, hard_t, start_t; // deklaracja tekstu na przyciski
    sf::RectangleShape start; // deklaracja przycisku inicjujacego gre
    friend class Board;   // udalo mi sie uzyskac do nich dostep poprzez przyjazn klas

public:

    Field();
    void place_mine();
    bool is_mine();
    void uncover();
    bool is_covered();
    void place_flag();
    void change_flag();
    bool is_flag();
    void draw_square(sf::RenderWindow & win);
    void draw_buttons(sf::RenderWindow & win);
    void draw_text(sf::RenderWindow & win);
    void setting(int x, int y);
    void covered_c();
    void uncovered_c();
    void place_flag_c();
    void mine_c();
    void easy_pressed();
    void medium_pressed();
    void hard_pressed();
};

class Board
{
    Field T[M][N]; // nie wiem jak ustawic pozadane rozmiary planszy M*N

public:

    Board();
    void deploy_mines(int n, bool random);
    bool has_Mine(int x, int y);
    int count_mines(int x, int y);
    void reveal(int x, int y);
    void modify_flag(int x, int y);
    bool whether_hidden(int x, int y);
    void draw_area(sf::RenderWindow & win);
};
