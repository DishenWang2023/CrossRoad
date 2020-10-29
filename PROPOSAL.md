# Proposal: Crossy Road

## Synopsis

Gameplay

- Crossy road is an arcade game that has a Canadian Goose cross a series of roads to reach the other end of safety. In order to win, the goose must advance through three levels of increasing difficulty without getting hit by a car. Along the way, the goose will collect coins that are scattered on the road. The goose can be controlled by the user with keyboard inputs (up, down, left, right). There are vehicles driving by with varying speed depending on the level. There are three total levels (easy, medium, hard) in the current design of the game. For each level, the difficulty increases by increasing the vehicle speed and adding new elements into the game.


Elements

- Canadian Goose: A user controlled goose that can move horizontally and vertically in order to reach safety.  The goose has three states: live, dead, and pass.

- Vehicles: Vehicles are the main obstacles for the goose. If a vehicle collides with the goose, the goose restarts the current level.

- Road: Pathways which vehicles can travel on.

- Blockade: A barrier that is impassible.

- Coins: Items that can be collected.

	
Goals

- The goal of this game is to beat all three levels and collect the high amount of coins in the game. In order to do so, the goose must avoid obstacles and reach the opposite side of the road safely.


## Functional requirements

1. The coins are placed randomly throughout the screen. When visible, the coins are considered live.
2. The coin count will be displayed at the top right corner of the screen, and will start at zero.
3. The cars travel across the screen from right to left, entering the screen randomly, but can only appear on the roads.
4. In level two, the blockades are placed randomly on areas that are not roads.
5. In the dead state (the goose’s initial state in the first round) the goose starts at the bottom middle of the screen.
6. The player can set the goose into action, transitioning it from dead to live state, by pressing any of the active keys (up, down, left, right).
7. If the goose runs into the sides of the screen, bottom of the screen, or a blockade, they will not be able to proceed in that direction.
8. If the goose runs into a car, the goose will transition back to the dead state and the game will restart at the current level.
9. If the goose transitions back to the dead state, the coin count will reset to zero.
10. If the goose runs into a live coin, the coin count will increase by one.
11. When the goose runs into the live coin, the coin will disappear (coin transition to dead state).
12. If the goose reaches the top of the screen, it transitions to the pass state and the next level is loaded.
13. When the new level is loaded, the coin count carries over and the goose is placed at the bottom middle of the screen.
14. If the goose transitions to the pass state after the third level, the player has won the game.


## Open questions

1. How to keep Blockades and coins from overlapping each other at the same position. 
3. How to transition from one level to another.
4. Best type for storage of blockades and cars (vector or something else?)


