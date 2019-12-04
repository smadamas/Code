#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;
using namespace sf;

class Tile{
private:
    int number;
    bool revealed;
    bool flagged;
    int has_mine;
    int xCoord;
    int yCoord;
    int adj_mines;
    Tile* neighbors[8];

public:

    Tile(){
        number = 0;
        revealed = 0;
        flagged = 0;
        has_mine = 0;
        xCoord = 0;
        yCoord = 0;
        adj_mines = 0;
        neighbors;

    }
    Tile(int xCoord, int yCoord){
        number = 0;
        revealed = 0;
        flagged = 0;
        has_mine = 0;
        this->xCoord = xCoord;
        this->yCoord = yCoord;
        adj_mines = 0;
        neighbors;
    }

    void setNumber(int i){
        number = i;
    }

    int getNumber(){
        return number;
    }

    void setMine(char mine_presence){
        has_mine = mine_presence - '0';
    }

    int getMine(){
        return has_mine;
    }

    void setRevealed(bool value){
        revealed = value;
    }

    bool getRevealed(){
        return revealed;
    }

    void setFlagged(bool value){
        flagged = value;
    }

    bool getFlagged(){
        return flagged;
    }

    void setCoords(int x, int y){
        xCoord = x;
        yCoord = y;
    }


    void setNeighbor(Tile* tile, int position){
        neighbors[position] = tile;
    }

    Tile* getNeighbor(int position){
        return neighbors[position];
    }

    void setAdjMines(int total){
        adj_mines = total;
    }

    int getAdjMines(){
        return adj_mines;
    }
};

class Board{
private:
    string gameState;
    int mines_left;

public:
    Tile tiles[400];
    vector<int> visitedTiles;

    //Menu Stuff
    Texture happyface;
    Texture loseface;
    Texture winface;
    Texture test;
    Texture debug;
    Sprite face_sprite;
    Sprite debug_sprite;
    Sprite test_sprite1;
    Sprite test_sprite2;
    Sprite test_sprite3;

    //Game Stuff
    Texture hiddenTexture;
    Texture revealedTexture;
    Texture flagTexture;
    Texture mineTexture;
    Texture Tex1;
    Texture Tex2;
    Texture Tex3;
    Texture Tex4;
    Texture Tex5;
    Texture Tex6;
    Texture Tex7;
    Texture Tex8;
    Sprite hiddenSprite;
    Sprite revealedSprite;
    Sprite flagSprite;
    Sprite mineSprite;
    Sprite numberSprite;

    //Number Stuff
    Texture dig0;
    Texture dig1;
    Texture dig2;
    Texture dig3;
    Texture dig4;
    Texture dig5;
    Texture dig6;
    Texture dig7;
    Texture dig8;
    Texture dig9;
    Texture neg;
    Texture digits;
    Sprite digitSprite2;
    Sprite digitSprite1;
    Sprite negSprite;


    Board(){
        RenderWindow window;
        gameState = "Playing";
        mines_left = 50;
    }

    string getState(){
        return gameState;
    }
    void setState(string input){
        gameState = input;
    }

    int getMinesLeft(){
        return mines_left;
    }

    void setMinesLeft(int input){
        mines_left = input;
    }

    void loadTest(int test_num){
        ifstream read;
        char mines[400];
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
                mines[counter] = (char)entry;
                //cout << "Step 2: " << mines[counter] << endl;
                counter++;
            }
        }

        for (unsigned int i = 0; i < 400; i++){
            tiles[i].setMine(mines[i]);
            //cout << "Step 3: " << tiles[i].getMine() << endl;
        }
        cout << "Loaded Test" << endl;

        makeNeighbors();

    }

    void makeNeighbors(){
        int number = -1;
        int adj_mines = 0;
        for (unsigned int i = 0; i < 400; i++){
            for (unsigned int j = 0; j < 8; j++){
                switch (j){
                    case 0:
                        number = i - 25 - 1;
                        break;
                    case 1:
                        number = i - 25;
                        break;
                    case 2:
                        number = i - 25 + 1;
                        break;
                    case 3:
                        number = i + 1;
                        break;
                    case 4:
                        number = i + 25 + 1;
                        break;
                    case 5:
                        number = i + 25;
                        break;
                    case 6:
                        number = i + 25 - 1;
                        break;
                    case 7:
                        number = i - 1;
                        break;
                }

                    if (i%25 == 0 && (j == 0 || j == 6 || j == 7)){
                        tiles[i].setNeighbor(nullptr, j);
                    }
                    else if ((i+1)%25 == 0 && (j == 2 || j == 3 || j == 4)){
                        tiles[i].setNeighbor(nullptr, j);
                    }
                    else if (i >= 375 && (j == 4 || j == 5 || j == 6)){
                        tiles[i].setNeighbor(nullptr, j);
                    }
                    else if (i <= 24 && (j == 0 || j == 1 || j == 2)){
                        tiles[i].setNeighbor(nullptr, j);
                    }
                    else {
                        adj_mines += tiles[number].getMine();
                        tiles[i].setNeighbor(&tiles[number], j);
                    }
            }
            tiles[i].setAdjMines(adj_mines);
            adj_mines = 0;
        }
        cout << "Made neighbors" << endl;
    }

    void Reset(){
        int mineCount = 0;
        int index;

        //Loading random mines
        for (unsigned int i = 0; i < 400; i++){
            tiles[i].setMine('0');
        }
        while (mineCount < 50){
            index = (rand() % 400);
            if (tiles[index].getMine() == 0){
                tiles[index].setMine('1');
                mineCount++;
            }
        }

        for (unsigned int x = 0; x < 400; x++){
            tiles[x].setRevealed(false);
            tiles[x].setFlagged(false);
        }
        gameState = "Playing";
        makeNeighbors();
    }

    void RecursiveReveal(Tile* input, int tileNum){
        vector<int>::iterator it;
        bool found = false;
        for (unsigned int i = 0; i < 8; i++){
            if (input->getNeighbor(i) != nullptr){
                for (unsigned int j = 0; j < visitedTiles.size(); j++){
                    if (j == input->getNeighbor(i)->getNumber()){
                        found = true;
                    }
                }
                if (input->getNeighbor(i)->getAdjMines() == 0 && !found && !input->getNeighbor(i)->getRevealed()){
                    visitedTiles.push_back(input->getNumber());
                    RecursiveReveal(input->getNeighbor(i), input->getNeighbor(i)->getNumber());
                }
                else {
                    input->getNeighbor(i)->setRevealed(true);
                }
            }
            found = false;
        }
        input->setRevealed(true);
        visitedTiles.clear();
    }

    void setDigits(int input){
        digits.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png");
        input = abs(input);
        int digWidth = digits.getSize().x;
        int digHeight = digits.getSize().y;

        neg.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(10*(digWidth/11), 0, digWidth/11, digHeight));
        dig0.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(0, 0, digWidth/11, digHeight));
        dig1.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(digWidth/11, 0, digWidth/11, digHeight));
        dig2.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(2*(digWidth/11), 0, digWidth/11, digHeight));
        dig3.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(3*(digWidth/11), 0, digWidth/11, digHeight));
        dig4.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(4*(digWidth/11), 0, digWidth/11, digHeight));
        dig5.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(5*(digWidth/11), 0, digWidth/11, digHeight));
        dig6.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(6*(digWidth/11), 0, digWidth/11, digHeight));
        dig7.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(7*(digWidth/11), 0, digWidth/11, digHeight));
        dig8.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(8*(digWidth/11), 0, digWidth/11, digHeight));
        dig9.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/digits.png", IntRect(9*(digWidth/11), 0, digWidth/11, digHeight));

        negSprite.setTexture(neg);
        switch (input%10){
            case 0:
                digitSprite2.setTexture(dig0);
                break;
            case 1:
                digitSprite2.setTexture(dig1);
                break;
            case 2:
                digitSprite2.setTexture(dig2);
                break;
            case 3:
                digitSprite2.setTexture(dig3);
                break;
            case 4:
                digitSprite2.setTexture(dig4);
                break;
            case 5:
                digitSprite2.setTexture(dig5);
                break;
            case 6:
                digitSprite2.setTexture(dig6);
                break;
            case 7:
                digitSprite2.setTexture(dig7);
                break;
            case 8:
                digitSprite2.setTexture(dig8);
                break;
            case 9:
                digitSprite2.setTexture(dig9);
                break;
        }
        switch (input/10){
            case 0:
                digitSprite1.setTexture(dig0);
                break;
            case 1:
                digitSprite1.setTexture(dig1);
                break;
            case 2:
                digitSprite1.setTexture(dig2);
                break;
            case 3:
                digitSprite1.setTexture(dig3);
                break;
            case 4:
                digitSprite1.setTexture(dig4);
                break;
            case 5:
                digitSprite1.setTexture(dig5);
                break;
            case 6:
                digitSprite1.setTexture(dig6);
                break;
            case 7:
                digitSprite1.setTexture(dig7);
                break;
            case 8:
                digitSprite1.setTexture(dig8);
                break;
            case 9:
                digitSprite1.setTexture(dig9);
                break;
        }
    }

    void BuildBoard(RenderWindow &window){

        int thisX;
        int thisY;
        int imgHeight;
        int imgWidth;
        int col;
        int row;

        //Reset the digits display
        setDigits(getMinesLeft());
        //Draw both digits and neg
        if (getMinesLeft() < 0){
            negSprite.setPosition(Vector2f(0, 512));
            window.draw(negSprite);
        }
        digitSprite1.setPosition(Vector2f(21, 512));
        window.draw(digitSprite1);
        digitSprite2.setPosition(Vector2f(42, 512));
        window.draw(digitSprite2);


        //Set Sprites with textures
        if (!hiddenTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/tile_hidden.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            hiddenTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/tile_hidden.png");
        }
        hiddenSprite.setTexture(hiddenTexture);

        if (!revealedTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/tile_revealed.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            revealedTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/tile_revealed.png");
        }
        revealedSprite.setTexture(revealedTexture);

        if (!flagTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/flag.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            flagTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/flag.png");
        }
        flagSprite.setTexture(flagTexture);

        if (!mineTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/mine.png"))
        {
            cout << "\nDidn't load properly." << endl << endl;
        }
        else{
            mineTexture.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/mine.png");
        }
        mineSprite.setTexture(mineTexture);

        imgWidth = hiddenSprite.getTexture()->getSize().x;
        imgHeight = hiddenSprite.getTexture()->getSize().y;
        thisX = 0.f; thisY = 0.f;
        col = 1; row = 1;


        for (unsigned int i = 0; i < 400; i++){
            if (tiles[i].getRevealed() && tiles[i].getMine() == 1){
                revealedSprite.setPosition(Vector2f(thisX, thisY));
                window.draw(revealedSprite);
                mineSprite.setPosition(Vector2f(thisX, thisY));
                window.draw(mineSprite);
            }
            else if (tiles[i].getRevealed()){
                revealedSprite.setPosition(Vector2f(thisX, thisY));
                window.draw(revealedSprite);
                switch (tiles[i].getAdjMines()){
                    case 0:
                        break;
                    case 1:
                        Tex1.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_1.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex1);
                        window.draw(numberSprite);
                        break;
                    case 2:
                        Tex2.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_2.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex2);
                        window.draw(numberSprite);
                        break;
                    case 3:
                        Tex3.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_3.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex3);
                        window.draw(numberSprite);
                        break;
                    case 4:
                        Tex4.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_4.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex4);
                        window.draw(numberSprite);
                        break;
                    case 5:
                        Tex5.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_5.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex5);
                        window.draw(numberSprite);
                        break;
                    case 6:
                        Tex6.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_6.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex6);
                        window.draw(numberSprite);
                        break;
                    case 7:
                        Tex7.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_7.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex7);
                        window.draw(numberSprite);
                        break;
                    case 8:
                        Tex8.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/number_8.png");
                        numberSprite.setPosition(Vector2f(thisX, thisY));
                        numberSprite.setTexture(Tex8);
                        window.draw(numberSprite);
                        break;
                }
            }
            else if (!tiles[i].getRevealed() && tiles[i].getFlagged()){
                hiddenSprite.setPosition(Vector2f(thisX, thisY));
                window.draw(hiddenSprite);
                flagSprite.setPosition(Vector2f(thisX, thisY));
                window.draw(flagSprite);
            }
            else {
                hiddenSprite.setPosition(Vector2f(thisX, thisY));
                window.draw(hiddenSprite);
            }

            tiles[i].setCoords((int)thisX, (int)thisY);

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
        if (gameState == "Playing"){
            if (!happyface.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_happy.png"))
            {
                cout << "\nDidn't load properly." << endl << endl;
            }
            else{
                happyface.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_happy.png");
                face_sprite.setTexture(happyface);
                face_sprite.setPosition(Vector2f(300, 512));
                window.draw(face_sprite);
            }
        }
        else if (gameState == "Lost"){
            if (!loseface.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_lose.png"))
            {
                cout << "\nDidn't load properly." << endl << endl;
            }
            else{
                loseface.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_lose.png");
                face_sprite.setTexture(loseface);
                face_sprite.setPosition(Vector2f(300, 512));
                window.draw(face_sprite);
            }
        }
        else if (gameState == "Won"){
            if (!winface.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_win.png"))
            {
                cout << "\nDidn't load properly." << endl << endl;
            }
            else{
                winface.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/face_win.png");
                face_sprite.setTexture(winface);
                face_sprite.setPosition(Vector2f(300, 512));
                window.draw(face_sprite);
            }
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
            test_sprite1.setPosition(Vector2f(768 - (4*imgWidth), 512));
            window.draw(test_sprite1);

            test.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/test_2.png");
            test_sprite2.setTexture(test);
            test_sprite2.setPosition(Vector2f(768 - (3*imgWidth), 512));
            window.draw(test_sprite2);

            test.loadFromFile("/Users/smadamas/Desktop/Code/Minesweeper/Project_Minesweeper/images/test_3.png");
            test_sprite3.setTexture(test);
            test_sprite3.setPosition(Vector2f(768 - (2*imgWidth), 512));
            window.draw(test_sprite3);
        }
    }
};


int main()
{
    bool is_clicked = false;

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

    //Initialize Board
    Board gameBoard = Board();
    for (unsigned int i = 0; i < 400; i++){
        gameBoard.tiles[i].setNumber(i);
    }

    gameBoard.Reset();

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            // check the type of the event...
            switch (event.type){
                // window closed
                case Event::Closed:
                    window.close();
                    break;

                //pressing left click
                case Event::MouseButtonPressed:
                    int row;
                    int col;
                    int tileNum;
                    int tiles_left = 0;


                    //Wheres the mouse?
                    sf::Vector2f Mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    std::cout << "Mouse.x = " << Mouse.x << ", Mouse.y = " << Mouse.y << std::endl;

                    if (event.mouseButton.button == Mouse::Left){
                        //cout << "Left button was pressed" << endl;

                        //Test Clicked
                        if (gameBoard.test_sprite1.getGlobalBounds().contains(Mouse)){
                            gameBoard.Reset();
                            gameBoard.loadTest(1);
                        }
                        else if (gameBoard.test_sprite2.getGlobalBounds().contains(Mouse)){
                            gameBoard.Reset();
                            gameBoard.loadTest(2);
                        }
                        else if (gameBoard.test_sprite3.getGlobalBounds().contains(Mouse)){
                            gameBoard.Reset();
                            gameBoard.loadTest(3);
                        }

                        //Tile Clicked
                        if (Mouse.x <= 800 && Mouse.y <= 512){
                            Tile* ref;
                            row = floor((int)Mouse.y/32);
                            col = floor(((int)Mouse.x)/32);
                            tileNum = 25*(row) + (col); //corrections for 0th row/col
                            if (!gameBoard.tiles[tileNum].getFlagged()){
                                if (gameBoard.tiles[tileNum].getMine() == 1){ //reveal mines because you clicked one and lost
                                    for (unsigned int x = 0; x < 400; x++){
                                        if (gameBoard.tiles[x].getMine() == 1){
                                            gameBoard.tiles[x].setRevealed(true);
                                        }
                                    }
                                    gameBoard.setState("Lost");
                                    cout << "Game Over!" << endl;
                                }
                                else {
                                    gameBoard.tiles[tileNum].setRevealed(true);
                                    ref = &gameBoard.tiles[tileNum];
                                    if (gameBoard.tiles[tileNum].getAdjMines() == 0){
                                        gameBoard.makeNeighbors();
                                        gameBoard.RecursiveReveal(ref, tileNum);
                                    }
                                }

                                //Game Won?
                                for (unsigned int x = 0; x < 400; x++){
                                    if (!gameBoard.tiles[x].getMine() && !gameBoard.tiles[x].getRevealed()){
                                        tiles_left += 1;
                                    }
                                }
                                if (tiles_left == 0){
                                    gameBoard.setState("Won");
                                    cout << "You Win!" << endl;
                                    for (unsigned int x = 0; x < 400; x++){
                                        if (gameBoard.tiles[x].getMine() == 1){
                                            gameBoard.tiles[x].setFlagged(true);
                                            gameBoard.setMinesLeft(00);
                                        }
                                    }
                                }
                            }
                        }


                        //Reset Game, Face Clicked
                            if (gameBoard.face_sprite.getGlobalBounds().contains(Mouse)){
                                gameBoard.Reset();
                            }


                        //Debug == Reveal mines
                            if (gameBoard.debug_sprite.getGlobalBounds().contains(Mouse)){
                                if (is_clicked == false){
                                    for (unsigned int x = 0; x < 400; x++){
                                        if (gameBoard.tiles[x].getMine() == 1){
                                            gameBoard.tiles[x].setRevealed(true);
                                        }
                                    }
                                    is_clicked = true;
                                }
                                else {
                                    for (unsigned int x = 0; x < 400; x++){
                                        if (gameBoard.tiles[x].getMine() == 1){
                                            gameBoard.tiles[x].setRevealed(false);
                                        }
                                    }
                                    is_clicked = false;
                                }

                            }


                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        if (Mouse.x <= 800 && Mouse.y <= 512){
                            row = floor((int)Mouse.y/32);
                            col = floor(((int)Mouse.x)/32);
                            tileNum = 25*(row) + (col); //corrections for 0th row/col

                            if (gameBoard.tiles[tileNum].getFlagged()){
                                gameBoard.tiles[tileNum].setFlagged(false);
                                gameBoard.setMinesLeft(gameBoard.getMinesLeft()+1);
                            }
                            else {
                                gameBoard.tiles[tileNum].setFlagged(true);
                                gameBoard.setMinesLeft(gameBoard.getMinesLeft()-1);
                            }
                        }
                    }
                    break;
            }
        }

        window.clear();

        //Draw the gameboard one every instant?
        gameBoard.BuildBoard(window);

        window.display();
    }

//load images from images folder and lay out hidden tiles, etc.
//make 400 tiles (25 by 16)



    return 0;
}