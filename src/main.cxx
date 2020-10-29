#include "controller.hxx"
#include "model.hxx"

int main(int argc, char* argv[])

try {
    ///
    /// Don't change this command-line processing, as the grader
    /// will expect to be able to start your program this way.
    ///
    int width, height;
    switch (argc) {
        case 1:
            width  = height = 6;
            break;
        case 3:
            width  = std::stoi(argv[1]);
            height = std::stoi(argv[2]);
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " [WIDTH HEIGHT]\n";
            return 1;
    }

    // You can change how you start your game class if you want (but
    // you probably don't need to):
    Controller controller(width, height);
    controller.run();
}

// This prints out error messages if, say, the command-line argument
// cannot be parsed as `int`s.
catch (std::exception const& e) {
    std::cerr << argv[0] << ": " << e.what() << "\n";
    return 1;
}