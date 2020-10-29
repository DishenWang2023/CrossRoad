#include "model.hxx"
#include "Player.hxx"
using namespace ge211;



//
// Model classes:
//

Car::Car(ge211::Position pos, int velocity)
        : car_pos(pos),
          velocity(velocity)
{}


//The whole state of the game

Model::Model(int width, int height)
        : Model(width, height, 0, 0, false)
{ }

Model::Model(int width, int height, int level, int coin_count, bool goose_alive)
        : board_({width, height}),
          goose_(ge211::Position {int(board_.dimensions().width / 2), board_.dimensions().height -1}),
          cars_(),
          coin_count(coin_count),
          level(level),
          goose_alive(goose_alive),
          won_game(false),
          counter_of_update(1),
          counter_of_update2(0)
{
    if(width < 2 || height < 2 || width > 8 || height > 8)
    {
        throw Client_logic_error("invalid board size");
    }
    cars_.clear();
    set_cars();
    set_coins();
    if (level != 0){
        set_blockades();
}
}


//updates the model state for one time step
//note about counters:
//  counters are put in place for human player detection purposes. Because update is called every 1/60 of a second,
//  it is impossible for the player to see the goose hitting the car, the goose hitting the top row, or the cars moving
//  unless update() is called less frequently. These "lags" are created to make interactions visible to the player.
void Model::update(){
        if (won_game == false) {
                if (goose_hits_top_() && !goose_hits_car_()) {
                    ++counter_of_update2;
                    if (counter_of_update2 %15 != 0) return;
                    change_level();
                    clear_all();
                    cars_.clear();
                    if (level <= 2) {
                        reset_goose_();
                        set_cars();
                        set_coins();
                        if (level != 0) {
                            set_blockades();
                        }
                    }
                }
                if (goose_hits_car_()) {
                    ++counter_of_update2;
                    if (counter_of_update2 %5 != 0) return;
                    reset_level();
                    goose_alive = false;
                }
                if (goose_hits_coin_()) {
                    destroy_hit_coin_();
                }
                for (size_t i = 0; i < cars_.size(); i++) {
                    int j = cars_[i].velocity;
                    if (counter_of_update % compute_velocity_multiplier(j) == 0) {
                        cars_[i].car_pos.x--;
                    }
                    if (car_out_of_bounds(cars_[i])) {
                        reset_car(i);
                    }
                }
                counter_of_update++;
        }

}

Player Model::operator[](Position pos) const
{
    return board_[pos];
}

void Model::set_goose(ge211::Position pos){
    goose_ = pos;
}

Rectangle Model::board() const
{
    return board_.all_positions();
}

//change level of game
void Model::change_level(){
    level++;
    if (level >= 3){
        won_game = true;
    }
}

void Model::set_goose_alive(){
    goose_alive = true;
}

//reset level when goose dies (goose location changes, coin count sets to zero)
void Model::reset_level(){
    clear_all();
    cars_.clear();
    set_cars();
    set_coins();
    if (level != 0){
        set_blockades();
    }
    reset_count();
    reset_goose_();
}

//Returns true if car goes off screen
bool Model::car_out_of_bounds(Car const& car1){
    return car1.car_pos.x < 0;
}

//Reset car position when it reaches end of screen
void Model::reset_car(int i){
    cars_[i].car_pos.x = board_.dimensions().width - 1;
}


//reset coin count
void Model::reset_count(){
    coin_count = 0;
}

int Model::compute_velocity_multiplier(int vel) {
    if (vel == -1){
        return 70;
    }
    else if (vel == -2){
        return 60;
    }
    else if (vel == -3){
        return 50;
    }
    else if (vel == -4){
        return 30;
    }
    else if (vel == -5){
        return 20;
    }
    else if (vel == -6) {
        return 15;
    }
}


//determines whether goose hits the given object
bool Model::goose_hits_top_() const{
    return goose_.y <= 0;
}

bool Model::goose_hits_left_(ge211::Position pos) const{
    return pos.x < 0;
}

bool Model::goose_hits_right_(ge211::Position pos) const{
    return pos.x >= board_.dimensions().width;
}

bool Model::goose_hits_bottom_(ge211::Position pos) const{
    return pos.y >= board_.dimensions().height;
}

bool Model::goose_hits_blockade_(ge211::Position pos) const{
    return board_[pos] == Player::blockade;
}

bool Model::valid_move(ge211::Position pos) const{
    return (!goose_hits_bottom_(pos) && !goose_hits_left_(pos) && !goose_hits_right_(pos) && !goose_hits_blockade_(pos));
}

bool Model::goose_hits_car_() const{
    for (Car carr : cars_){
        if (goose_ == carr.car_pos){
            return true;
        }
    }
    return false;
}

bool Model::goose_hits_coin_() const{
    return board_[goose_]== Player::coin;
}

//resets the goose location and dead state when the level restarts
void Model::reset_goose_(){
    goose_.x = board_.dimensions().width / 2;
    goose_.y = board_.dimensions().height -1 ;
}

//removes the indicated coin
void Model::destroy_hit_coin_() {
    coin_count++;
    board_[goose_] = Player::grass;
}

//sets the blocks in their initial state per round
void Model::set_blockades(){
    for (int i = 1; i < board_.dimensions().height; i = i+2){
        int random_pos = rand() % board_.dimensions().width;
        int random_pos2 = rand() % board_.dimensions().width;
        int random_pos3 = rand() % board_.dimensions().width;
        board_[{random_pos, i}] = Player::blockade;
        board_[{random_pos2, i}] = Player::blockade;
        board_[{random_pos3, i}] = Player::blockade;
    }
    board_[{board_.dimensions().width / 2, board_.dimensions().height -1}] = Player::grass;
}


//sets coins in their initial state per round
void Model::set_coins(){
    for (int i = 1; i < board_.dimensions().height; i = i+2){
        int random_pos = rand() % board_.dimensions().width;
        int random_pos2 = rand() % board_.dimensions().width;
        if (board_[{random_pos, i}] != Player::blockade){
            board_[{random_pos, i}] = Player::coin;
        }
        if (board_[{random_pos2, i}] != Player::blockade){
            board_[{random_pos2, i}] = Player::coin;
        }
    }
}

void Model::clear_all(){
    for (ge211::Position pos : board_.all_positions()){
        board_[pos] = Player::neither;
    }
}

//sets cars in their initial state per round
void Model::set_cars(){
    for (int i = 0; i < board_.dimensions().height; i = i+2){
        int random_vel;
        if (level ==2) {
            random_vel = rand() % 4 + 3;
        }
        else{
            random_vel = rand() % 3 + 1;
        }
        Car car1({rand() % board_.dimensions().width + 1, i}, -random_vel);
        cars_.push_back(car1);
        Car car2({rand() % board_.dimensions().width + 1, i}, -random_vel);
        cars_.push_back(car2);
        Car car3({rand() % board_.dimensions().width + 1, i}, -random_vel);
        cars_.push_back(car3);
        Car car4({rand() % board_.dimensions().width + 1, i}, -random_vel);
        cars_.push_back(car4);
    }
}


