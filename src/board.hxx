#pragma once

#include "Player.hxx"
#include "move.hxx"

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Board
{

public:
    explicit Board(ge211::Dimensions dims);

    ge211::Dimensions dimensions() const;

    Player operator[](ge211::Position pos) const;

    class reference;

    reference operator[](ge211::Position pos);

    bool good_position(ge211::Position pos) const;

    ge211::Rectangle all_positions() const;

private:
    Player get_(ge211::Position) const;
    void set_(ge211::Position, Player);

    void bounds_check_(ge211::Position) const;

    ge211::Dimensions   dims_;
    Position_set        blockade_;
    Position_set        coin_;
    Position_set        grass_;
    Position_set        road_;
};


///
/// Helper classes
///

class Board::reference
{
    Board&           board_;
    ge211::Position  pos_;

    friend class Board;

    reference(Board&, ge211::Position) noexcept;

public:
    // Assigns the value of `that` to the object of `this`.
    reference& operator=(reference const&) noexcept;

    // Assigns to the object of the reference.
    reference& operator=(Player) noexcept;

    // Returns the value of the reference.
    operator Player() const noexcept;
};


