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
#include <iostream>
#include <iomanip>

#include "tetris_core.h"

/*
 * Simple C++ Test Suite
 */


void testGame()
{
  tetris::core::TetrisCore tetrisCore;
  tetrisCore.start();
  
  tetris::core::TetrisCore::Board oldBoard = tetrisCore.board();
  tetris::core::TetrisCore::Board tetrisBoard;
  
  bool result(true);
  for(int i = 0; i < 30; ++i)
  {
    tetrisCore.timeout();
    tetrisBoard = tetrisCore.board();
    
    result &= tetrisBoard == oldBoard;
    if( result )
      break;
        
    oldBoard = tetrisBoard;
  }
  
  if( result )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testGame (core_test) message=error plying to game" << std::endl;
    std::cout << "tetrisBoard:\n" << tetrisBoard << std::endl;
  }
}


void testGamePause()
{
  tetris::core::TetrisCore tetrisCore;
  tetrisCore.start();
  for(int i = 0; i != 10; ++i)
    tetrisCore.timeout();
  
  tetris::core::TetrisCore::Board oldBoard = tetrisCore.board();
  
  tetrisCore.pause();
  for(int i = 0; i != 10; ++i)
    tetrisCore.timeout();
      
  tetris::core::TetrisCore::Board tetrisBoard = tetrisCore.board();
  if( oldBoard != tetrisBoard )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testGamePause (core_test) message=error pause game" << std::endl;
    std::cout << "tetrisBoard:\n" << tetrisBoard << std::endl;
  }
}


void testMoveLeft()
{
  tetris::core::TetrisCore tetrisCore;
  tetrisCore.start();
  for(int i = 0; i < 100; ++i)
    tetrisCore.moveLeft();
  tetris::core::TetrisCore::Board tetrisBoard = tetrisCore.board();
  
  tetris::core::TetrisCore::Board zeroBoard;
  zeroBoard.resize( tetrisCore.boardHeight() );
  for(int i = 0; i < tetrisCore.boardHeight(); ++i)
    zeroBoard[i].resize(tetrisCore.boardWidth(), tetris::core::ShapeType::NoShape);
  
  if( tetrisBoard == zeroBoard )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testMoveLeft (core_test) message=error move block to left" << std::endl;
    std::cout << "tetrisBoard:\n" << tetrisBoard << std::endl;
  }
}


void testMoveRight()
{
  tetris::core::TetrisCore tetrisCore;
  tetrisCore.start();
  for(int i = 0; i < 100; ++i)
    tetrisCore.moveRight();
  tetris::core::TetrisCore::Board tetrisBoard = tetrisCore.board();
  
  tetris::core::TetrisCore::Board zeroBoard;
  zeroBoard.resize( tetrisCore.boardHeight() );
  for(int i = 0; i < tetrisCore.boardHeight(); ++i)
    zeroBoard[i].resize(tetrisCore.boardWidth(), tetris::core::ShapeType::NoShape);
    
  if( tetrisBoard == zeroBoard )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testMoveRight (core_test) message=error move block to right" << std::endl;
    std::cout << "tetrisBoard:\n" << tetrisBoard << std::endl;
  }
}


void testStart()
{
  tetris::core::TetrisCore tetrisCore;
  tetrisCore.start();
  tetris::core::TetrisCore::Board tetrisBoard = tetrisCore.board();
  
  tetris::core::TetrisCore::Board board;
  board.resize( tetrisCore.boardHeight() );
  for(int i = 0; i < tetrisCore.boardHeight(); ++i)
    board[i].resize(tetrisCore.boardWidth(), tetris::core::ShapeType::NoShape);
    
  if( tetrisBoard == board )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testStart (core_test) message=error start game" << std::endl;
    std::cout << "tetrisBoard:\n" << tetrisBoard << std::endl;
  }
}


void testTimeout()
{
  tetris::core::TetrisCore tetrisCore;
  tetris::core::TetrisCore::Board oldBoard = tetrisCore.board();
  
  for(int i = 0; i != 10; ++i)
    tetrisCore.timeout();
      
  tetris::core::TetrisCore::Board tetrisBoard = tetrisCore.board();
  if( oldBoard != tetrisBoard )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testTimeout (core_test) message=error game playing without preess start" << std::endl;
    std::cout << "tetrisBoard:\n" << tetrisBoard << std::endl;
  }
}


int main(int argc, char** argv)
{
  clock_t allTestsTime;
  clock_t testTime;
  
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "%SUITE_STARTING% core_test" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;
  
  allTestsTime = clock();

  // testGame
  std::cout << "%TEST_STARTED% testGame (core_test)\n" << std::endl;
  testTime = clock();
  testGame();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testGame (core_test)" << std::endl;
  
  // testGamePause
  std::cout << "%TEST_STARTED% testGamePause (core_test)\n" << std::endl;
  testTime = clock();
  testGamePause();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testGamePause (core_test)" << std::endl;  
  
  // testMoveLeft
  std::cout << "%TEST_STARTED% testMoveLeft (core_test)\n" << std::endl;
  testTime = clock();
  testMoveLeft();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testMoveLeft (core_test)" << std::endl;
  
  // testMoveRight
  std::cout << "%TEST_STARTED% testMoveRight (core_test)\n" << std::endl;
  testTime = clock();
  testMoveRight();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testMoveRight (core_test)" << std::endl;
  
  // testStart
  std::cout << "%TEST_STARTED% testStart (core_test)\n" << std::endl;
  testTime = clock();
  testStart();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testStart (core_test)" << std::endl;
  
  // testTimeout
  std::cout << "%TEST_STARTED% testTimeout (core_test)\n" << std::endl;
  testTime = clock();
  testTimeout();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testTimeout (core_test)" << std::endl;

  allTestsTime = clock() - allTestsTime;
  std::cout << "%SUITE_FINISHED% time=" << ( ((float)allTestsTime) / CLOCKS_PER_SEC ) << std::endl;

  return (EXIT_SUCCESS);
}

