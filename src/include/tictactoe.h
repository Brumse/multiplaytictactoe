#pragma once

class Tictactoe
{
public:
    enum class Player
    {
        none,
        player1,
        player2
    };

    Tictactoe();
    ~Tictactoe();

    bool putMarker(int position, Player player);
    Player checkWinner() const;

private:
};
