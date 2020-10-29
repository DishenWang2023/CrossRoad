#include "view.hxx"

using namespace ge211;

static int const grid_size = 72;
static int const spacing = 0;
static int const small_grid_size = grid_size - spacing;

ge211::Color const white = ge211::Color::white();
ge211::Color const black = ge211::Color::black();
ge211::Color const green = ge211::Color::medium_green();
ge211::Color const yellow = ge211::Color::medium_yellow();
ge211::Color const grey = ge211::Color{70,70,70};


View::View(Model const& model)
        : model_(model),
          sans_("sans.ttf",15),
          blockadeSpr({small_grid_size,small_grid_size},black),
          gooseSpr("goose2.png"),
          gooseMSpr("goose_muted.png"),
          car1Spr("car1.png"),
          car2Spr("car2.png"),
          car3Spr("car3.png"),
          coinSpr("coin.png"),
          grassSpr({small_grid_size,small_grid_size},green),
          roadSpr({small_grid_size,small_grid_size},grey),
          levelSpr(ge211::Text_sprite("",sans_)),
          coin_countSpr(ge211::Text_sprite("",sans_)),
          liveSpr(ge211::Text_sprite("",sans_))
{}

void View::draw(Sprite_set& set)
{
    int top = grid_size * model_.board().dimensions().height/8;
    int middle = initial_window_dimensions().width/2;

    if(model_.won_game){
        levelSpr.reconfigure(ge211::Text_sprite::Builder(sans_).message(
                "You Won!"));
        set.add_sprite(levelSpr, {middle - levelSpr.dimensions().width / 2, 0});
    }
    else {
        if (model_.get_goose_alive()) {
            liveSpr.reconfigure(
                    ge211::Text_sprite::Builder(sans_).message("alive"));
        } else {
            liveSpr.reconfigure(
                    ge211::Text_sprite::Builder(sans_).message("dead"));
        }
        levelSpr.reconfigure(ge211::Text_sprite::Builder(sans_).message(
                "Level " + std::to_string(model_.get_level()+1)));
        coin_countSpr.reconfigure(ge211::Text_sprite::Builder(sans_).message(
                "Coin: " + std::to_string(model_.get_coin_count())));

        set.add_sprite(levelSpr, {middle - levelSpr.dimensions().width / 2, 0});
        set.add_sprite(coin_countSpr, {initial_window_dimensions().width - coin_countSpr.dimensions().width -3, 0});
        set.add_sprite(liveSpr, {1, 0});

        for (ge211::Position board_pos : model_.board()) {
            int x = grid_size * board_pos.x + spacing / 2; // if change this, lmk bc im using the math in controller
            int y = grid_size * board_pos.y + spacing / 2 + top;
            ge211::Position screen_pos = {x, y};
            if (model_[board_pos] == Player::blockade) {
                set.add_sprite(blockadeSpr, screen_pos, 1);
            } else if (model_[board_pos] == Player::coin) {
                set.add_sprite(coinSpr, screen_pos, 1, Transform::scale(.15));

            }
            if (board_pos == model_.get_goose()) {
                if (model_.get_goose_alive()){
                    set.add_sprite(gooseSpr, screen_pos, 4, Transform::scale(.2));
                }
                else{
                    set.add_sprite(gooseMSpr, screen_pos, 4, Transform::scale(.2));
                }
            }
            if (board_pos.y % 2 == 1) {
                set.add_sprite(grassSpr, screen_pos, 0);
            } else {
                set.add_sprite(roadSpr, screen_pos, 0);
            }
        }
        int i = 0;
        for (Car carr: model_.cars_) {
            int x = grid_size * carr.car_pos.x + spacing / 2; // if change this, lmk bc im using the math in controller
            int y = grid_size * carr.car_pos.y + spacing / 2 + top;
            ge211::Position screen_pos = {x, y};
            if (i % 3 == 0){
                set.add_sprite(car1Spr, screen_pos, 6, Transform::scale(.15));
            }
            else if (i % 3 == 1){
                set.add_sprite(car2Spr, screen_pos, 5, Transform::scale(.15));
            }
            else {
                set.add_sprite(car3Spr, screen_pos, 4, Transform::scale(.15));
            }
            ++i;
        }
    }
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    Dimensions grid = grid_size * model_.board().dimensions();
    grid.height += grid_size * model_.board().dimensions().height/2;
    return grid;
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "CrossyRoad";
}

