#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;
using namespace sf;

class Tile{
private:
    bool revealed;
    bool flagged;
    char has_mine;
    int xCoord;
    int yCoord;
    vector<int> adjacent;

public:

    Tile(){
        revealed = 0;
        flagged = 0;
        has_mine = 0;
        xCoord = 0;
        yCoord = 0;
        adjacent;

    }
    Tile(int xCoord, int yCoord){
        revealed = 0;
        flagged = 0;
        has_mine = 0;
        this->xCoord = xCoord;
        this->yCoord = yCoord;
        adjacent;
    }

    void setMine(char mine_presence){
        has_mine = mine_presence;
    }

    char getMine(){
        return has_mine;
    }
};

class Board{
private:
    string gameState;
    int numTiles;
    int mines;
    vector<Tile> tiles;

public:
    Texture texture;
    Texture face;
    Texture digits;
    Texture test;
    Texture debug;
    Sprite sprite;
    Sprite face_sprite;
    Sprite digits_sprite;
    Sprite debug_sprite;
    Sprite test_sprite1;
    Sprite test_sprite2;
    Sprite test_sprite3;

    Board(){
        gameState = "Broken";
        numTiles = 0;
        mines = 0;
        tiles;
    }
    Board(int numTiles, int mines){
        gameState = "Playing";
        numTiles = 400;
        mines = 50;
        tiles;
    }

    void loadTest(int test_num){
        ifstream read;
        vector<char> mines;
        string currentLine;
        int entry;
        int counter = 0;
        int choice;

        if (test_num == 1){
            read.open("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/boards/testboard1.brd");
        }
        else if (test_num == 2){
            read.open("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/boards/testboard2.brd");
        }
        else if (test_num == 3){
            read.open("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/boards/testboard3.brd");
        }
        else {
            cout << "Nothing opened" << endl;
        }
        while (getline(read, currentLine)){
            for (unsigned int i = 0; i < 25; i++){
                entry = currentLine.at(i);
                //cout << "Step 1: " << (char)entry << endl;
                mines.push_back((char)entry);
                //cout << "Step 2: " << mines[counter] << endl;
                counter++;
            }
        }

        for (unsigned int i = 0; i < 400; i++){
            tiles[i].setMine(mines[i]);
            cout << "Step 3: " << tiles[i].getMine() << endl;
        }
        cout << "Done" << endl;

    }


    Board BuildBoard(RenderWindow &window, vector<Tile> input){
        Board myBoard = Board(numTiles, 50);

        int thisX;
        int thisY;
        int imgHeight;
        int imgWidth;
        int col;
        int row;

        Tile thisTile;
        int numTiles = 0;
        vector<Tile> thisBoardTiles = input;

        if (!texture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/tile_hidden.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            texture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/tile_hidden.png");
        }
        sprite.setTexture(texture);
        imgWidth = sprite.getTexture()->getSize().x;
        imgHeight = sprite.getTexture()->getSize().y;
        thisX = 0.f; thisY = 0.f;
        col = 1; row = 1;

        for (unsigned int i = 0; i < 400; i++){
            sprite.setPosition(Vector2f(thisX, thisY));
            window.draw(sprite);
            thisTile = Tile(thisX, thisY);
            thisBoardTiles.push_back(thisTile);

            if (col == 25){
                thisY += imgHeight;
                thisX = 0.f;
                col = 1;
                row++;
            }
            else {
                thisX += imgWidth;
                col++;
            }

        }

        //Other Buttons
        if (!face.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_happy.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            face.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_happy.png");
            face_sprite.setTexture(face);
            face_sprite.setPosition(Vector2f(300, 512));
            window.draw(face_sprite);
        }
        if (!digits.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            digits.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png");
            digits_sprite.setTexture(digits);
            digits_sprite.setPosition(Vector2f(0, 512));
            window.draw(digits_sprite);
        }
        if (!test.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/test_1.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            debug.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/debug.png");
            debug_sprite.setTexture(debug);
            imgWidth = debug_sprite.getTexture()->getSize().x;
            imgHeight = debug_sprite.getTexture()->getSize().y;
            debug_sprite.setPosition(Vector2f(768 - (5*imgWidth), 512));
            window.draw(debug_sprite);

            test.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/test_1.png");
            test_sprite1.setTexture(test);
            myBoard.test_sprite1.setPosition(Vector2f(768 - (4*imgWidth), 512));
            window.draw(test_sprite1);

            test.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/test_2.png");
            test_sprite2.setTexture(test);
            myBoard.test_sprite2.setPosition(Vector2f(768 - (3*imgWidth), 512));
            window.draw(test_sprite2);

            test.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/test_3.png");
            test_sprite3.setTexture(test);
            myBoard.test_sprite3.setPosition(Vector2f(768 - (2*imgWidth), 512));
            window.draw(test_sprite3);
        }

        return myBoard;
    }
};


int main()
{

    //Below is a test which just creates a green circle in a black field
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }




//make a 800 by 600 window
    RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    Board gameBoard;
    vector<Tile> thisBoardTiles;
    int test_num;


    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
                case Event::Closed:
                    window.close();
                    break;

                //pressing left click
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left)
                        {
//                        std::cout << "the left button was pressed" << endl;

                        //Wheres the mouse?
                        sf::Vector2f Mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        std::cout << "Mouse.x = " << Mouse.x << ", Mouse.y = " << Mouse.y << std::endl;


                        //Test Clicked
                        if (gameBoard.test_sprite1.getGlobalBounds().contains(Mouse)){
                            gameBoard.loadTest(1);
                        }
                        else if (gameBoard.test_sprite2.getGlobalBounds().contains(Mouse)){
                            gameBoard.loadTest(2);
                        }
                        else if (gameBoard.test_sprite3.getGlobalBounds().contains(Mouse)){
                            gameBoard.loadTest(3);
                        }

                        //For tiles, divide the x and y by 32 (rounding down) to get which tile to modify

                        //Reset Game
                        //replace face, set new random mines

                        //Debug
                        //Reveal mines

                        }
                    break;

                    //movin around the mouse
                case Event::MouseMoved:
//                    std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
//                    std::cout << "new mouse y: " << event.mouseMove.y << std::endl;

                    break;

                    // we don't process other types of events, just restart
                default:
                    break;
            }
        }

        window.clear();

        //Draw the gameboard one every instant?
        gameBoard = gameBoard.BuildBoard(window, thisBoardTiles);

        window.display();
    }

//load images from images folder and lay out hidden tiles, etc.
//make 400 tiles (25 by 16)

//make class for board, tile?

//make buttons

//helper functions - clearing board, setting flags/mines, recalc. adjacent mines

//random mine generation (50)

//make arrays for each mine


    return 0;
}