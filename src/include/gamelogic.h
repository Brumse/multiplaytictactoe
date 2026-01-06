#pragma once

#include <array>

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
    Player getWinner() const;

private:
    static constexpr unsigned int rows{3};
    static constexpr unsigned int cols{3};
    static constexpr unsigned int fieldSize{rows*cols};

    std::array<Player, fieldSize> m_playingField;

    Player getRowWinner(const unsigned int row) const;
    Player getColumnWinner(const unsigned int col) const;
    Player getDiagonalWinner() const;
};
