#pragma once

#include <ge211.hxx>

#include <vector>

#include "Player.hxx"
#include "../.cs211/lib/ge211/include/ge211_geometry.hxx"
#include <iostream>
#include "board.hxx"






//
// Model classes:
//



// The position of one car, its velocity, and whether it's still there.
struct Car
{
    Car(ge211::Position car_pos, int velocity);

    //The top-left corner
    ge211::Position car_pos;

    //car's velocity
    int velocity;

};

//The whole state of the game
class Model
{
public:
    // Constructs a model with `size` as both its width and height.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if `size` is less than 2
//    or greater than 8.
    explicit Model(int width = 8, int height = 8);

// Constructs a model with the given width and height.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if either dimension is less
//    than 2 or greater than 8.
    Model(int width, int height, int level, int coin_count, bool goose_alive);



// Returns the player at the given position, or `Player::neither` if
// the position is unoccupied.
//
// ERRORS:
//  - Throws `ge211::Client_logic_error` if the position is out of
//    bounds.


    //
    // Private data members
    //

    //playing board
    Board board_;

    bool won_game;

    size_t counter_of_update;

    size_t counter_of_update2;

    //Top left position of the goose
    ge211::Position goose_;

    bool goose_alive;


    //coin count
    int coin_count;

    //level of game (easy = 0, medium = 1, hard = 2)
    int level;

    //Test access
    friend struct Test_accss;


    //
    //Public Functions
    //

    Player operator[](ge211::Position) const;

    //Returns goose position
    ge211::Position get_goose() const{
        return goose_;
    }

    //sets goose position
    void set_goose(ge211::Position pos);

    //set and get goose status
    void set_goose_alive();

    bool get_goose_alive() const{
        return goose_alive;
    }

    //Reset car position when it reaches end of screen
    void reset_car(int i);

    //returns true if car off of screen
    bool car_out_of_bounds(Car const& car1);


    //updates the model state for one time step
    void update();

    //change level of game
    void change_level();

    //reset level when goose dies (goose location changes, coin count sets to zero)
    void reset_level();

    //get coin count
    int get_coin_count() const{
        return coin_count;
    }

    //reset coin count
    void reset_count();

    bool valid_move(ge211::Position pos) const;

    int get_level() const{
        return level;
    }


    //the cars
    std::vector<Car> cars_;

    ge211::Rectangle board() const;

private:
    //
    // possible helper functions
    //

    //determines whether goose hits the given object
    bool goose_hits_top_() const;
    bool goose_hits_left_(ge211::Position pos) const;
    bool goose_hits_right_(ge211::Position pos) const;
    bool goose_hits_bottom_(ge211::Position pos) const;
    bool goose_hits_blockade_(ge211::Position pos) const;
    bool goose_hits_car_() const;
    bool goose_hits_coin_() const;

    int compute_velocity_multiplier(int vel);



    //resets the goose location and dead state when the level restarts
    void reset_goose_();


    //removes the indicated coin
    void destroy_hit_coin_();

    //sets the blocks in their initial state per round
    void set_blockades();

    //sets coins in their initial state per round
    void set_coins();

    void set_cars();

    void clear_all();



};

