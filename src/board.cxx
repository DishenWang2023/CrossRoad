//
// Created by Avery on 3/3/20.
//
// Changed by Dishen on 03/06/2020

#include "../.cs211/lib/ge211/include/ge211_geometry.hxx"
#include "board.hxx"

using namespace ge211;

Board::Board(Dimensions dims)
        : dims_(dims)
{
}

Dimensions Board::dimensions() const
{
    return dims_;
}

bool Board::good_position(ge211::Position pos) const
{
    return 0 <= pos.x && pos.x <= dims_.width &&
           0 <= pos.y && pos.y <= dims_.height;
}

Player Board::operator[](ge211::Position pos) const
{
    bounds_check_(pos);
    return get_(pos);
}

Board::reference Board::operator[](Position pos)
{
    bounds_check_(pos);
    return {*this, pos};
}

Rectangle Board::all_positions() const
{
    return Rectangle::from_top_left({0, 0}, dims_);
}

Player Board::get_(ge211::Position pos) const
{
    if (blockade_[pos])
        return Player::blockade;
    else if (coin_[pos])
        return Player::coin;
    else if (grass_[pos])
        return Player::grass;
    else if (road_[pos])
        return Player::road;
    else
        return Player::neither;
}

void Board::set_(ge211::Position pos, Player player)
{
    switch (player) {
        case Player::blockade:
            blockade_[pos] = true;
            coin_[pos] = false;
            grass_[pos] = false;
            road_[pos] = false;
            break;

        case Player::coin:
            blockade_[pos] = false;
            coin_[pos] = true;
            grass_[pos] = false;
            road_[pos] = false;
            break;

        case Player::grass:
            blockade_[pos] = false;
            coin_[pos] = false;
            grass_[pos] = true;
            road_[pos] = false;
            break;

        case Player::road:
            blockade_[pos] = false;
            coin_[pos] = false;
            grass_[pos] = false;
            road_[pos] = true;
            break;

        default: //need default case?
            blockade_[pos] = false;
            coin_[pos] = false;
            grass_[pos] = false;
            road_[pos] = false;
    }
}
/*
void Board::set_all(Position_set pos_set, Player player)
{
    switch (player) {
        case Player::blockade:
            blockade_ |= pos_set;
            coin_ &= ~pos_set;
            grass_ &= ~pos_set;
            road_ &= ~pos_set;
            break;

        case Player::coin:
            blockade_ &= ~pos_set;
            coin_ |= pos_set;
            grass_ &= ~pos_set;
            road_ &= ~pos_set;
            break;

        case Player::grass:
            blockade_ &= ~pos_set;
            coin_ &= ~pos_set;
            grass_ |= pos_set;
            road_ &= ~pos_set;
            break;

        case Player::road:
            blockade_ &= ~pos_set;
            coin_ &= ~pos_set;
            grass_ &= ~pos_set;
            road_ |= pos_set;
            break;

        default:
            blockade_ &= ~pos_set;
            coin_ &= ~pos_set;
            grass_ &= ~pos_set;
            road_ &= ~pos_set;
    }
}
 */

void Board::bounds_check_(ge211::Position pos) const
{
    if (!good_position(pos))
        throw Client_logic_error("Board: position out of bounds");
}

Board::reference::reference(Board& board, ge211::Position pos) noexcept
        : board_(board)
        , pos_(pos)
{ }

Board::reference&
Board::reference::operator=(reference const& that) noexcept
{
    *this = Player(that);
    return *this;
}

Board::reference&
Board::reference::operator=(Player player) noexcept
{
    board_.set_(pos_, player);
    return *this;
}

Board::reference::operator Player() const noexcept
{
    return board_.get_(pos_);
}