#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <cmath>

class Player {
public:
    float time=0;
    int currentTile=0,targetTile=0;
    Player(const std::string& pawnTexturePath, float x, float y) {
        if (!pawnTexture.loadFromFile(pawnTexturePath)) {
            std::cerr << "Could not load pawn texture" << std::endl;
            exit(1);
        }
        this->time = 0;
        pawnSprite.setTexture(pawnTexture);
        pawnSprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(pawnSprite);
    }

    int getPosition() const {
        return position;
    }

    void update(float t){
        float animSpeed=2;
        std::cout << t << std::endl ;
        this->time += t;
        if (this->time >= animSpeed){
            this->time = 0;
            if(currentTile < targetTile)currentTile ++;
            else if(currentTile > targetTile)  currentTile --;
        }


        float distance = 80.0; // Assuming each tile is 80x80 pixels
        float startX = 100,startY=670;

        int x = currentTile % 8;
        int y = std::floor(currentTile/8.0);
        if (y%2==1) x = 7-x;


        pawnSprite.setPosition(startX + distance * x, startY - y*distance);
    }

    //    void moveRight(float distance) {
    //        pawnSprite.move(distance, 0.0);
    //    }

    //    void moveLeft(float distance) {
    //        pawnSprite.move(-distance, 0.0);
    //    }

    //    void moveUp(float distance) {
    //        pawnSprite.move(0.0, -distance);
    //    }

    //    void moveDown(float distance) {
    //        pawnSprite.move(0.0, distance);
    //    }

    void moveByTiles(int tiles) {

        targetTile += tiles;
        if(targetTile <0) targetTile = 0;

        //        for (int i = 1; i <= tiles; i++) {
        //            if ((position > 0 && position < 8) || (position > 16 && position < 24) || (position > 32 && position < 40) || (position > 48 && position < 56)) {
        //                moveRight(distance);
        //            } else if (position % 8 == 0) {
        //                moveUp(distance);
        //            } else if ((position > 8 && position < 16) || (position > 24 && position < 32) || (position > 40 && position < 48) || (position > 56 && position < 64)) {
        //                moveLeft(distance);
        //            } else if (position == 64) {
        //                exit(1);
        //            }

        //            ++position;
        //        }
    }

    void moveBackByTiles(int tiles) {
        moveByTiles(-tiles);
        //        float distance = 80.0; // Assuming each tile is 80x80 pixels
        //        int newPosition = position - tiles;
        //        newPosition = std::max(1, newPosition); // Ensure the new position is not less than 1
        //        int tilesMoved = position - newPosition; // Calculate the actual number of tiles moved

        //        for (int i = 1; i <= tilesMoved; i++) {
        //            if ((position > 0 && position < 8) || (position > 16 && position < 24) || (position > 32 && position < 40) || (position > 48 && position < 56)) {
        //                moveLeft(distance);
        //            } else if (position % 8 == 0) {
        //                moveDown(distance);
        //            } else if ((position > 8 && position < 16) || (position > 24 && position < 32) || (position > 40 && position < 48) || (position > 56 && position < 64)) {
        //                moveRight(distance);
        //            } else if (position == 64) {
        //                exit(1);
        //            }

        //            --position;
        //        }
    }



private:
    sf::Texture pawnTexture;
    sf::Sprite pawnSprite;
    int position = 1;

};



class RollingDice : public sf::Sprite {
public:
    RollingDice(const std::string& path) {
        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture: " << path << std::endl;
            exit(1);
        }

        setTexture(texture_);
        setTextureRect(sf::IntRect(0, 0, 100, 100));
        setPosition(1000, 600);

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    void roll() {
        if (!is_rolling_) {
            is_rolling_ = true;
            current_frame_index_ = 0;
            total_frames_rolled_ = 0;

            // Generate a random number between 1 and 6
            result_ = (std::rand() % 6) + 1;
            std::cout << "Dice rolling... " << std::endl;
        }
    }

    bool isRolling() const {
        return is_rolling_;
    }

    int getResult() const {
        return result_;
    }

    void updateAnimation() {
        if (is_rolling_) {
            setTextureRect(dice_frames[current_frame_index_]);
            ++current_frame_index_;

            if (current_frame_index_ >= dice_frames.size()) {
                current_frame_index_ = 0;
                ++total_frames_rolled_;

                if (total_frames_rolled_ == 10) {
                    is_rolling_ = false;
                    std::cout << "Dice stopped. Result: " << result_  << std::endl;
                }
            }
            else if (total_frames_rolled_ >= 6 && result_ == current_frame_index_ ) {
                is_rolling_ = false;
                std::cout << "Dice stopped. Result: " << result_ << std::endl;
            }
        }
    }

private:
    sf::Texture texture_;
    std::vector<sf::IntRect> dice_frames = {
        sf::IntRect(0, 0, 100, 100),   // Dice side 1
        sf::IntRect(100, 0, 100, 100), // Dice side 2
        sf::IntRect(200, 0, 100, 100), // Dice side 3
        sf::IntRect(300, 0, 100, 100), // Dice side 4
        sf::IntRect(400, 0, 100, 100), // Dice side 5
        sf::IntRect(500, 0, 98, 100)  // Dice side 6
    };

    bool is_rolling_ = false;
    int current_frame_index_ = 0;
    int total_frames_rolled_ = 0;
    int result_;
};

//bool checkExitCondition(int targetTile1, int targetTile2) {
//    if (targetTile1 >= 64 || targetTile2 >= 64) {
//        return true;
//    }
//    return false;
//}



int main() {
    Player player1("Bpawn.png", 100, 670);
    Player player2("Rpawn.png", 100, 670);

    sf::RenderWindow window(sf::VideoMode(1240, 840), "My window");

    RollingDice dice1("dice.png");
    RollingDice dice2("dice.png");

    srand(time(NULL));

    bool player1_turn = true;
    bool player2_turn = false; // Added flag to track player2's turn

    bool roll_requested = false;
    bool dice1_finished_rolling = false;
    bool dice2_finished_rolling = false; // New flag to track dice animation completion




    sf::Texture SnakesAndLadders;
    if (!SnakesAndLadders.loadFromFile("SnakesLadders.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Sprite SL;
    SL.setTexture(SnakesAndLadders);
    SL.setPosition(100, 100);



    sf::Texture texture;
    if (!texture.loadFromFile("end.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture.setRepeated(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    bool d1=false;
    sf::Clock c;
    while (window.isOpen()) {
        sf::Time elapsed = c.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (player1_turn && !dice1.isRolling() && !dice1_finished_rolling) {
                    dice1.roll();
                    roll_requested = true;
                    d1 = !d1;
                } else if (player2_turn && !dice2.isRolling() && !dice2_finished_rolling) {
                    dice2.roll();
                    roll_requested = true;
                    d1 = !d1;
                }
            }
        }

        player1.update(elapsed.asSeconds());
        player2.update(elapsed.asSeconds());
        window.clear(sf::Color::Black);



        dice1.updateAnimation();
        dice2.updateAnimation();

        if (dice1.isRolling() && dice1.getResult() == 0) {
            dice1.updateAnimation();
            dice1_finished_rolling = true;
        }

        if (dice2.isRolling() && dice2.getResult() == 0) {
            dice2.updateAnimation();
            dice2_finished_rolling = true;
        }

     //ladders
        if(player1.targetTile == 9) {player1.currentTile = 23;
            player1.targetTile = 23;
        }
        if(player1.targetTile == 3) {player1.currentTile = 13;
            player1.targetTile = 13;
        }
        if(player1.targetTile == 20) {player1.currentTile = 37;
            player1.targetTile = 37;
        }
        if(player1.targetTile == 29) {player1.currentTile = 49;
            player1.targetTile = 49;
        }

     //snakes
        if(player1.targetTile == 17) {player1.currentTile = 1;
            player1.targetTile = 1;
        }
        if(player1.targetTile == 19) {player1.currentTile = 11;
            player1.targetTile = 11;
        }
        if(player1.targetTile == 54) {player1.currentTile = 37;
            player1.targetTile = 37;
        }
        if(player1.targetTile == 61) {player1.currentTile = 35;
            player1.targetTile = 35;
        }
     //player2

     //ladders
        if(player2.targetTile == 9) {player2.currentTile = 23;
            player2.targetTile = 23;
        }
        if(player2.targetTile == 3) {player2.currentTile = 13;
            player2.targetTile = 13;
        }
        if(player2.targetTile == 20) {player2.currentTile = 37;
            player2.targetTile = 37;
        }
        if(player2.targetTile == 29) {player2.currentTile = 49;
            player2.targetTile = 49;
        }
     //snakes
        if(player2.targetTile == 17) {player2.currentTile = 1;
            player2.targetTile = 1;
        }
        if(player2.targetTile == 19) {player2.currentTile = 11;
            player2.targetTile = 11;
        }
        if(player2.targetTile == 54) {player2.currentTile = 37;
            player2.targetTile = 37;
        }
        if(player2.targetTile == 61) {player2.currentTile = 35;
            player2.targetTile = 35;
        }
        if (player1.targetTile >= 63) {
            if (player1.currentTile == 64) {

                std::this_thread::sleep_for(std::chrono::seconds(7));
                window.close();
                return 0;
            }
        }
        if(player2.targetTile >= 63) {
            if(player2.currentTile == 64) {

                std::this_thread::sleep_for(std::chrono::seconds(7));
                window.close();
                return 0;
            }
        }


        if (player1.currentTile == player2.currentTile && player1.currentTile == player1.targetTile &&player2.currentTile == player2.targetTile ) {
            if (player1_turn) player2.moveByTiles(-5); // Move player1 back 5 fields
            else player1.moveByTiles(-5);
        }

        std::cout << player2.currentTile <<"/t"<< player1.currentTile<<std::endl;
        if (roll_requested && !dice1.isRolling() && !dice2.isRolling()) {
            if (player1_turn) {
                player1.moveByTiles(dice1.getResult());

            } else if (player2_turn) {
                player2.moveByTiles(dice2.getResult());
            }
            roll_requested = false;
            //            if (player1.getPosition() == player2.getPosition()) {
            //                player1.moveByTiles(-5); // Move player1 back 5 fields
            //            }
            //            if (player2.getPosition() == player1.getPosition()) {
            //                player2.moveByTiles(-5); // Move player1 back 5 fields
            //            }

            if (player1_turn) {
                player1_turn = false;
                player2_turn = true; // Switch the turn to player2
            } else {
                player1_turn = true;
                player2_turn = false; // Switch the turn back to player1
            }
        }

        window.draw(sprite);
        window.draw(SL);
        if(d1) window.draw(dice1);
        else window.draw(dice2);
        player1.draw(window);
        player2.draw(window);




        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

    return 0;
}
