#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test")
{
    CHECK( 1 + 1 == 2 );
}

//initial conditions
TEST_CASE("initial conditions")
{
    Model m;
    //initial goose dead
    CHECK(!m.goose_alive);
    CHECK(m.get_goose().x == m.board_.dimensions().width / 2);
    CHECK(m.get_goose().y == m.board_.dimensions().height -1);
}

TEST_CASE("gain coin")
{
    Model m;
    m.board_[m.goose_] = Player::coin;
    m.update();
    CHECK(m.coin_count == 1);
    CHECK(m.board_[m.goose_] == Player::grass);
}

TEST_CASE("goose smash car")
{
    Model m;
    m.cars_.clear();
    m.set_goose_alive();
    m.set_goose({m.board_.dimensions().width-1,2});
    CHECK(m.get_goose_alive());
    m.board_[m.goose_] = Player::coin;
    m.update();
    CHECK(m.get_coin_count() == 1);
    m.cars_.push_back(Car({3, 2}, -3));
    m.set_goose({1,2});
    CHECK(m.get_goose_alive());
    //in order to make cars appear to move at a humanly detectable speed (seeing as update is called every 1/60 a second),
    //a car with velocity -3 is only updated for every 50 calls to update (as coded in Model::compute_velocity_multiplier)
    for (int i = 0; i < 50; ++i){
        m.update();
    }
    CHECK(m.cars_[0].car_pos.x == 2);
    CHECK(m.get_goose_alive());
    for (int i = 0; i < 50; ++i){
        m.update();
    }
    CHECK(m.get_goose_alive());
    CHECK(m.cars_[0].car_pos.x ==1);
    CHECK(m.goose_.x ==1);
    for (int i = 0; i < 5; ++i){ // when goose hits car, update is stalled 5 times so that human player can see goose hitting car
        m.update();
    }
    CHECK(!m.get_goose_alive());
    CHECK(m.get_coin_count() == 0);
    CHECK(m.level == 0);
    CHECK(m.get_goose().x == m.board_.dimensions().width / 2);
    CHECK(m.get_goose().y == m.board_.dimensions().height -1);
}

TEST_CASE("move goose")
{
    Model m;
    m.set_goose({1,1});
    CHECK(m.get_goose() == Position {1,1});
}

TEST_CASE("advance to next level")
{
    Model m;
    CHECK(m.level == 0);
    m.cars_.clear();
    m.board_[m.goose_] = Player::coin;
    m.update();
    m.board_[m.goose_] = Player::coin;
    m.update();
    CHECK(m.coin_count == 2);
    m.set_goose({0,0});
    // when a goose reaches the top, update is lagged by 15 calls to make the UI look slightly paused (better look for the user)
    // this allows human player to be able to see goose hit the top row before there is a transition to the next level
    for (int i = 0; i < 15; ++i){
        m.update();
    }
    CHECK(m.level == 1); // level increases by one
    CHECK(m.get_goose().x == m.board_.dimensions().width / 2); // goose position reverts back to bottom middle
    CHECK(m.get_goose().y == m.board_.dimensions().height -1); // goose position reverts back to bottom middle
    CHECK(m.coin_count == 2); // makes sure coin count remains the same as levels change
}

TEST_CASE("car out of bounds"){
    Model m;
    m.cars_[0].car_pos.x = 0;
    CHECK(!m.car_out_of_bounds(m.cars_[0]));
    m.cars_[0].car_pos.x = -1;
    CHECK(m.car_out_of_bounds(m.cars_[0]));
    m.update();
    CHECK(m.cars_[0].car_pos.x == m.board_.dimensions().width - 1);
    CHECK(!m.car_out_of_bounds(m.cars_[0]));
}

TEST_CASE("where can the goose move?"){
    Model m;
    CHECK(m.valid_move(m.get_goose()));
    m.board_[m.goose_] = Player::grass;
    CHECK(m.valid_move(m.get_goose()));
    m.board_[m.goose_] = Player::coin;
    CHECK(m.valid_move(m.get_goose()));
    m.board_[m.goose_] = Player::blockade;
    CHECK(!m.valid_move(m.get_goose()));
    m.goose_.y = m.board_.dimensions().height;
    CHECK(!m.valid_move(m.get_goose()));
    m.goose_.y = m.board_.dimensions().height -1;
    m.goose_.x = m.board_.dimensions().width;
    CHECK(!m.valid_move(m.get_goose()));
    m.goose_.x = -1;
    CHECK(!m.valid_move(m.get_goose()));
}
