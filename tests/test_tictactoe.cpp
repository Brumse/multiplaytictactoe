#include <gtest/gtest.h>
#include "tictactoe.h"

TEST(tictactoe, illegal_access) {
    using Player = Tictactoe::Player;
    Tictactoe t;

    EXPECT_FALSE(t.putMarker(-1, Player::player1));
    EXPECT_FALSE(t.putMarker(10, Player::player1));
    EXPECT_FALSE(t.putMarker(3, Player::none));
}

TEST(tictactoe, double_put) {
    using Player = Tictactoe::Player;
    Tictactoe t;

    EXPECT_TRUE(t.putMarker(5, Player::player1));
    
    EXPECT_FALSE(t.putMarker(5, Player::player1));
    EXPECT_FALSE(t.putMarker(5, Player::player2));
}

TEST(tictactoe, horizontal_win_player1_row1){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(2, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(3, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::player1);
}

TEST(tictactoe, horizontal_win_player2_row1){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player2);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(2, Player::player2);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(3, Player::player2);
    EXPECT_EQ(t.getWinner(), Player::player2);
}

TEST(tictactoe, horizontal_notwin_player2){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(2, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(3, Player::player2);
    EXPECT_EQ(t.getWinner(), Player::none);
}

TEST(tictactoe, vertical_win_player1){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(4, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(7,Player::player1);
    EXPECT_EQ(t.getWinner(),Player::player1);
}

TEST(tictactoe, vertical2_win_player1){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(3, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(6, Player::player1);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(9,Player::player1);
    EXPECT_EQ(t.getWinner(),Player::player1);
}
TEST(tictactoe, diagonal_win_player2){
    using Player = Tictactoe::Player;

    Tictactoe t;

    t.putMarker(1, Player::player2);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(5, Player::player2);
    EXPECT_EQ(t.getWinner(), Player::none);
    t.putMarker(9, Player::player2);
    EXPECT_EQ(t.getWinner(), Player::player2);
}

