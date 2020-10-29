//
// Created by Avery on 3/3/20.
//

#ifndef FINAL_PROJECT_CONTROLLER_HXX
#define FINAL_PROJECT_CONTROLLER_HXX

#endif //FINAL_PROJECT_CONTROLLER_HXX

#pragma once

#include "model.hxx"
#include <ge211.hxx>
#include "view.hxx"

// The main game class
class Controller : public ge211::Abstract_game
{
public:
    // Constructs a game with `size` as both its width and height.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if `size` is less than 2
    //    or greater than 8.
    explicit Controller(int size = 8);

    // Constructs a game with the given width and height.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if either dimension is less
    //    than 2 or greater than 8.
    Controller(int width, int height);


// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //

    // TODO: Add any input handlers you need, e.g.:
    void on_key(ge211::Key key) override;

    void on_frame(double) override;


    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model            model_;
    View             view_;

};
