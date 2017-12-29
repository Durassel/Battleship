#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "structures.h"
#include "print.h"
#include "board.h"
#include "ship.h"

int main()
{
    /// Establish a connection with the server
        // Create socket
        // Configuration (address, port)
        // Connection to the server

    /// Establish a connection with a client
        // Connection with another client
            // Send invite
            // Wait until response (Accept : game start / Deni : invite a new one)

    /// Initialization
    // Boards declaration
    Cell Main[ROWS][COLUMNS];
    Cell Mark[ROWS][COLUMNS];
    // Fleet
    int fleet = CARRIER_NB + BATTLESHIP_NB + SUBMARINE_NB + DESTROYER_NB;
    int enemyFleet = 1;
    // Coordinates
    int coordinates[2] = {0};
    // Boards initialization
    init(Main);
    init(Mark);

    // Ships placement
    printf("---------------------------- Initialization ----------------------------\n");
    refresh(Main);
    setup(Main);

    /// Send msg to the server to notify ship placement is finished
        // Server process : when 2 players are ready, launch (give priority to a player)

    /// Game start
    do {
        /// Receive msg from server
        // If enemy move
        printf("Enemy move : %s", coordinates);
        // Respond with hit or miss
        if (Main[coordinates[0]][coordinates[1]].type != '-') { // If hit
            Main[coordinates[0]][coordinates[1]].type = lower(Main[coordinates[0]][coordinates[1]].type); // Put a lower case
            // Check if ship is sunken
            result = check(Main, coordinates);
            if (result == 1)
                fleet--;
            // Send msg to the server : hit
            if (fleet == 0)
                // Send msg to the server : end game
        } else {
            // Send msg to the server : miss
        }

        /// It's my turn : send coordinates
        // Printing boards
        print(Main, Mark);
        // Select coordinates
        selectCoordinates(Mark, coordinates, "Error: You have already shot at this place.");
        // Send coordinates to the server
            // Server process : send msg to the opponent (print : "Enemy move : coordinates")
                // Opponent responds with : hit or miss
            // Server send it to me
        // Receive hit or miss
        if (hit) {
            Mark[coordinates[0]][coordinates[1]].type = 'x';
        } else {
            Mark[coordinates[0]][coordinates[1]].type = 'X';
        }
        // Receive msg if enemy fleet is empty
        enemyFleet = 0;
    } while (enemyFleet > 0);

    /// Print winner / loser

    /// Ask to retry
        // Send response to the server
            // Server process : 2 players agreement -> retry

    /// Disconnect
        // Server process : break connection between 2 clients

    /// Close socket
        // End of program

    return 0;
}

