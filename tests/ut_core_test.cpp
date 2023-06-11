/*
 * Copyright (C) 2017 wstux
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   core_test.cpp
 * Author: wstux
 * 
 */

#include <stdlib.h>
#include <ctime>

#include <testing/testdefs.h>

#include "core/tetris_core.h"

/*
 * Simple C++ Test Suite
 */


TEST(core_fixture, game)
{
    tetris::core::TetrisCore core;
    core.start();

    tetris::core::TetrisCore::Board old_board = core.board();

    for(size_t i = 0; i < 30; ++i) {
        core.gameStep();
        tetris::core::TetrisCore::Board board = core.board();

        EXPECT_TRUE(board != old_board) << board;
    }
}

TEST(core_fixture, pause)
{
    tetris::core::TetrisCore core;
    core.start();
    for(size_t i = 0; i < 10; ++i) {
        core.gameStep();
    }

    tetris::core::TetrisCore::Board old_board = core.board();

    core.pause();
    for(size_t i = 0; i < 10; ++i) {
        core.gameStep();
    }
      
    tetris::core::TetrisCore::Board board = core.board();
    EXPECT_TRUE(board == old_board) << board;
}

TEST(core_fixture, forward)
{
    tetris::core::TetrisCore core;
    tetris::core::TetrisCore::Board old_board = core.board();
    tetris::core::TetrisCore::Board board;

    for(size_t i = 0; i < 10; ++i) {
        core.fastForward();
    }

    board = core.board();
    EXPECT_TRUE(board == old_board) << "forward works without start game";

    old_board = board;
    core.start();
    for(size_t i = 0; i < 10; ++i) {
        core.fastForward();
    }

    board = core.board();
    EXPECT_TRUE(board != old_board) << "forward doesn't works with start game";

    old_board = board;
    core.pause();
    for(size_t i = 0; i < 10; ++i) {
        core.fastForward();
    }

    board = core.board();
    EXPECT_TRUE(board == old_board) << "forward works with pause game";
}

TEST(core_fixture, move_left)
{
    tetris::core::TetrisCore core;
    core.start();
    for(size_t i = 0; i < 100; ++i) {
        core.moveLeft();
    }
    tetris::core::TetrisCore::Board board = core.board();

    tetris::core::TetrisCore::Board zero_board;
    zero_board.resize(core.boardHeight());
    for(int i = 0; i < core.boardHeight(); ++i) {
        zero_board[i].resize(core.boardWidth(), tetris::core::ShapeType::NoShape);
    }

    EXPECT_TRUE(board != zero_board);
}

TEST(core_fixture, move_right)
{
    tetris::core::TetrisCore core;
    core.start();
    for(size_t i = 0; i < 100; ++i) {
        core.moveRight();
    }
    tetris::core::TetrisCore::Board board = core.board();

    tetris::core::TetrisCore::Board zero_board;
    zero_board.resize(core.boardHeight());
    for(int i = 0; i < core.boardHeight(); ++i) {
        zero_board[i].resize(core.boardWidth(), tetris::core::ShapeType::NoShape);
    }

    EXPECT_TRUE(board != zero_board);
}

TEST(core_fixture, start)
{
    tetris::core::TetrisCore core;
    core.start();
    tetris::core::TetrisCore::Board board = core.board();
  
    tetris::core::TetrisCore::Board zero_board;
    zero_board.resize(core.boardHeight());
    for(int i = 0; i < core.boardHeight(); ++i) {
        zero_board[i].resize(core.boardWidth(), tetris::core::ShapeType::NoShape);
    }

    EXPECT_TRUE(board != zero_board);
}

TEST(core_fixture, timeout)
{
    tetris::core::TetrisCore core;
    tetris::core::TetrisCore::Board old_board = core.board();

    for(size_t i = 0; i < 10; ++i) {
        core.gameStep();
    }

    tetris::core::TetrisCore::Board board = core.board();
    EXPECT_TRUE(board == old_board);
}


int main(int /*argc*/, char** /*argv*/)
{
    return RUN_ALL_TESTS();
}

