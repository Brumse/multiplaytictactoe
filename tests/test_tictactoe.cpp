#include <gtest/gtest.h>
#include "tictactoe.h"


TEST(tictactoe, horizontal_win_player1){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(2, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(3, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::player1);
}

TEST(tictactoe, horizontal_notwin_player2){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(2, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(3, Player::player2);
    EXPECT_EQ(t.checkWinner(), Player::none);
}

TEST(tictactoe, vertical_win_player1){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(4, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(7,Player::player1);
    EXPECT_EQ(t.checkWinner(),Player::player1);
}

TEST(tictactoe, vertical2_win_player1){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(3, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(6, Player::player1);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(9,Player::player1);
    EXPECT_EQ(t.checkWinner(),Player::player1);
}
TEST(tictactoe, diagonal_win_player2){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player2);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(5, Player::player2);
    EXPECT_EQ(t.checkWinner(), Player::none);
    t.putMarker(9, Player::player2);
    EXPECT_EQ(t.checkWinner(), Player::player2);
}

