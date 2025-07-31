#include "tictactoe.h"

Tictactoe::Tictactoe()
{
    m_playingField.fill(Player::none);
}

Tictactoe::~Tictactoe()
{
}

bool Tictactoe::putMarker(int position, Player player)
{
    if (player == Player::none)
    {
        return false;
    }

    if (position <= 0 || position > fieldSize)
    {
        return false;
    }

    if (m_playingField[position - 1] != Player::none)
    {
        return false;
    }

    m_playingField[position - 1] = player;

    return true;
}

Tictactoe::Player Tictactoe::getWinner() const
{
    for (int row = 0; row < rows; row++)
    {
        const auto winner = getRowWinner(row);
        if (winner != Player::none)
        {
            return winner;
        }
    }

    for (int col = 0; col < cols; col++)
    {
        const auto winner = getColumnWinner(col);
        if (winner != Player::none)
        {
            return winner;
        }
    }

    const auto winner = getDiagonalWinner();
    if(winner != Player::none) {
        return winner;
    }

    return Player::none;
}

Tictactoe::Player Tictactoe::getDiagonalWinner() const
{
    // Left right diagonal
    {
        unsigned int startpos = 0;
        Player p = m_playingField[startpos];
        if (p != Player::none &&
            m_playingField[startpos + 4] == p &&
            m_playingField[startpos + 8] == p)
            {
                return p;
            }
        }
        
        // Right left diagonal
        {
            unsigned int startpos = 2;
            Player p = m_playingField[startpos];
        if (p != Player::none &&
            m_playingField[startpos + 2] == p &&
            m_playingField[startpos + 4] == p)
        {
            return p;
        }
    }

    return Player::none;
}

Tictactoe::Player Tictactoe::getRowWinner(const unsigned int row) const
{
    unsigned int startPos = row * 3;

    Player p = m_playingField[startPos];

    if (p == Player::none)
    {
        return Player::none;
    }

    if (m_playingField[startPos + 1] == p && m_playingField[startPos + 2] == p)
    {
        return p;
    }
    else
    {
        return Player::none;
    }
}

Tictactoe::Player Tictactoe::getColumnWinner(const unsigned int col) const
{
    unsigned int startPos = col;

    Player p = m_playingField[startPos];

    if (p == Player::none)
    {
        return Player::none;
    }

    if (m_playingField[startPos + 3] == p && m_playingField[startPos + 6] == p)
    {
        return p;
    }
    else
    {
        return Player::none;
    }
}
