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
 * File:   tetris_core.h
 * Author: wstux
 * 
 */

#ifndef TETRIS_CORE_H
#define TETRIS_CORE_H

#include <iosfwd>
#include <vector>

#include "tetris_shape.h"


namespace tetris
{
namespace core
{


class TetrisCore
{
private:
  enum { BoardWidth = 12, BoardHeight = 22 };
  
  
public:
  typedef std::vector<ShapeType> BoardLine;
  
  typedef std::vector< std::vector<ShapeType> > Board;
      
      
public:
  TetrisCore();
  
  ~TetrisCore() {}
  
//  Board board() { return m_board; }
  
  Board board() const;
  
  int boardHeight() const { return BoardHeight; }
  
  int boardWidth() const { return BoardWidth; }
  
  void fastForward();
  
  int level() { return m_level; }
  
  bool moveLeft() { return moveShape(-1, 0, 0); }

  bool moveRight() { return moveShape(1, 0, 0); }

  void pause();
  
  bool rotateLeft() { return moveShape(0, 0, -1); }

  bool rotateRight() { return moveShape(0, 0, 1); }
  
  int score() const { return m_score; }
  
  void start();
  
  void timeout();
  
    /// @return Timeout step-timer in msecs
  int timerDelay() const;
  
  
protected:
  bool destroyLine(const int line);
  
  
private:
  ShapeType boardElement(int x, int y) const;
  
  void clearBoard();
  
  void landChanged();
  
    /// @brief Function for moving shape on board
    /// @param const int xStep - step on X axis
    /// @param const int yStep - step on Y axis
    /// @param const int rotate - rotate
    /// @return Applying operation flag
  bool moveShape(const int xStep, const int yStep, const int rotate);
  
  void setBoardElement(int x, int y, const ShapeType type);
  
  
public:
    /// Current shape
  Shape m_curShape;
  
    /// Next shape to be used
  Shape m_nextShape;
  
  Board m_board;
  
  bool m_isStarted;
  
  bool m_isPause;
  
  bool m_isGameOver;
  
  int m_level;
  
  int m_score;
  
  int m_destroedLines;
};


bool operator==(const TetrisCore::Board &left, const TetrisCore::Board &right);

bool operator!=(const TetrisCore::Board &left, const TetrisCore::Board &right);

std::ostream& operator<<(std::ostream &os, const TetrisCore::Board &board);


} // namespace core
} // namespace tetris

#endif /* TETRIS_CORE_H */
