//
// Created by Avery on 3/3/20.
//
#include "controller.hxx"
#include "../.cs211/lib/ge211/include/ge211_event.hxx"

#include <ge211.hxx>

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites);
}

ge211::Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_frame(double)
{
    model_.update();
}

void Controller::on_key(ge211::Key key) {
    if (key == ge211::Key::up()){
        if (!model_.get_goose_alive()){
            model_.set_goose_alive();
        }
        ge211::Position nxt = {model_.get_goose().x, model_.get_goose().y -1};
        if (model_.valid_move(nxt)){
            model_.set_goose(nxt);
        }
    }
    if (key == ge211::Key::down()){
        if (!model_.get_goose_alive()){
            model_.set_goose_alive();
        }
        ge211::Position nxt = {model_.get_goose().x, model_.get_goose().y +1};
        if (model_.valid_move(nxt)){
            model_.set_goose(nxt);
        }
    }
    if (key == ge211::Key::left()){
        if (!model_.get_goose_alive()){
            model_.set_goose_alive();
        }
        ge211::Position nxt = {model_.get_goose().x -1, model_.get_goose().y};
        if (model_.valid_move(nxt)){
            model_.set_goose(nxt);
        }
    }
    if (key == ge211::Key::right()){
        if (!model_.get_goose_alive()){
            model_.set_goose_alive();
        }
        ge211::Position nxt = {model_.get_goose().x +1, model_.get_goose().y};
        if (model_.valid_move(nxt)){
            model_.set_goose(nxt);
        }
    }
}