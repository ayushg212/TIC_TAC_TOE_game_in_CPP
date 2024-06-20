# Tic Tac Toe Game

This project contains two C++ programs for playing the classic Tic Tac Toe game:
1. **Multiplayer Tic Tac Toe** - Play with another player.
2. **Tic Tac Toe vs Computer** - Play against the computer using the Minimax algorithm.

## Table of Contents
- [Description](#description)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Code Overview](#code-overview)
  - [Multiplayer Tic Tac Toe](#multiplayer-tic-tac-toe)
  - [Tic Tac Toe vs Computer](#tic-tac-toe-vs-computer)

## Description

### Multiplayer Tic Tac Toe
This program allows two players to play Tic Tac Toe against each other on a grid of customizable size. The players take turns to place their symbols ('X' or 'O') on the grid, and the first player to align their symbols in a row, column, or diagonal wins the game.

### Tic Tac Toe vs Computer
This program allows a single player to play Tic Tac Toe against the computer. The computer uses the Minimax algorithm to choose its moves, making the game challenging and fun.

## Requirements
- A C++ compiler (e.g., `g++`)

## Installation
1. Clone the repository or download the source code files.
2. Ensure you have a C++ compiler installed on your system.

## Usage

### Multiplayer Tic Tac Toe
1. Compile the `tic_tac_toe.cpp` file:
    ```sh
    g++ tic_tac_toe.cpp -o tic_tac_toe
    ```
2. Run the compiled program:
    ```sh
    ./tic_tac_toe
    ```

### Tic Tac Toe vs Computer
1. Compile the `tic_tac_toe_computer.cpp` file:
    ```sh
    g++ tic_tac_toe_computer.cpp -o tic_tac_toe_computer
    ```
2. Run the compiled program:
    ```sh
    ./tic_tac_toe_computer
    ```

## Code Overview

### Multiplayer Tic Tac Toe
- **File:** `tic_tac_toe.cpp`
- **Description:** This file contains the code for the multiplayer Tic Tac Toe game. It includes functions for initializing the grid, taking player inputs, checking for winning conditions, and displaying the grid.

### Tic Tac Toe vs Computer
- **File:** `tic_tac_toe_computer.cpp`
- **Description:** This file contains the code for the Tic Tac Toe game where the player competes against the computer. It includes functions for the computer's strategy using the Minimax algorithm, checking for winning conditions, and taking player inputs.

#### Minimax Algorithm
The computer uses the Minimax algorithm to determine the best possible move. The core part of the Minimax algorithm is implemented in the following function:

```cpp
struct prob
{
    float win_prob, loss_prob, draw_prob;
};

prob findBestMove(char grd[max_size][max_size], int depth, int player_number)
{
    vector<pair<int,int>> to_fill;
    for(int i = 0; i < max_size; i++)
        for(int j = 0; j < max_size; j++)
            if(grd[i][j] == '-') to_fill.push_back({i, j});
    if(to_fill.size() == 1)
    {
        int i = to_fill[0].first;
        int j = to_fill[0].second;
        grd[i][j] = player_symbol(player_number);
        if(check_win(i, j, player_number, grd))
        {
            grd[i][j] = '-';
            if(depth == 0)
                win.push_back({i+1, j+1});
            return {1, 0, 0};
        }
        else
        {
            grd[i][j] = '-';
            if(depth == 0)
                draw.push_back({i+1, j+1});
            return {0, 0, 1};
        }
    }
    for(int z = 0; z < to_fill.size(); z++)
    {
        int i = to_fill[z].first;
        int j = to_fill[z].second;
        grd[i][j] = player_symbol(player_number);
        if(check_win(i, j, player_number, grd))
        {
            grd[i][j] = '-';
            if(depth == 0)
                win.push_back({i+1, j+1});
            return {1, 0, 0};
        }
        grd[i][j] = '-';
    }
    prob result;
    bool w = 0, d = 0, l = 0;
    for(int z = 0; z < to_fill.size(); z++)
    {
        int i = to_fill[z].first;
        int j = to_fill[z].second;
        grd[i][j] = player_symbol(player_number);
        result = findBestMove(grd, depth+1, (player_number+1)%2);
        if(result.draw_prob == 1)
        {
            d = 1;
            if(depth == 0)
                draw.push_back({i+1, j+1});
        }
        else if(result.win_prob == 1)
        {
            l = 1;
            if(depth == 0)
                loss.push_back({i+1, j+1});
        }
        else if(result.loss_prob == 1)
        {
            w = 1;
            if(depth == 0)
                win.push_back({i+1, j+1});
        }
        grd[i][j] = '-';
    }
    if(w)
        return {1, 0, 0};
    else if(d)
        return {0, 0, 1};
    else
        return {0, 1, 0};
}
