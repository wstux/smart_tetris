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
 * File:   tetris_core.cpp
 * Author: wstux
 * 
 */

#include "tetris_core.h"
#include "tetris_shape.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>


namespace tetris
{
namespace core
{


TetrisCore::TetrisCore()
  : m_isStarted(false)
  , m_isPause(false)
  , m_isGameOver(false)
  , m_level(1)
  , m_score(0)
  , m_destroedLines(0)
{
  m_board.resize(BoardHeight);
  for(int i = 0; i < BoardHeight; ++i)
    m_board[i].resize(BoardWidth, ShapeType::NoShape);
}


TetrisCore::~TetrisCore()
{}


/*! @fn Board board() const
 *  @brief Запрос актуального игрового поля
 *  @return Актуальное игровое поле
 */
TetrisCore::Board TetrisCore::board() const
{
  Board board = m_board;
  for(const Position &pos : m_curShape.block())
    board[ m_curShape.y()+pos.y ][ m_curShape.x()+pos.x ] = m_curShape.type();
  
  return board;
}


ShapeType TetrisCore::boardElement(int x, int y) const
{
  assert( (x >= 0) && (x < BoardWidth) );
  assert( (y >= 0) && (y < BoardHeight) );
  
  return m_board[y][x];
}


void TetrisCore::clearBoard()
{
  for(int i = 0; i < BoardHeight; ++i)
  {
    for(int j = 0; j < BoardWidth; ++j)
      m_board[i][j] = ShapeType::NoShape;
  }
}


bool TetrisCore::destroyLine(const int line)
{
  if((line < 0) || (line >= BoardHeight))
    return false;
  
  // удаление заданной строки
  m_board.erase( std::next(m_board.begin(), line) );
  // добавление новой пустой строки в начало доски
  m_board.insert( m_board.begin(), BoardLine(BoardWidth, ShapeType::NoShape) );
  
  return true;
}


void TetrisCore::fastForward()
{
  if(m_isGameOver)
    return;
  
  if( !moveShape (0, 1, 0) )
    return;
  
  timeout();
}


void TetrisCore::landChanged()
{
  std::list<int> linesToCheckOnRemove;
  for(const Position &pos : m_curShape.block())
  {
    linesToCheckOnRemove.push_back( pos.y+m_curShape.y() );    
    setBoardElement( pos.x+m_curShape.x(), pos.y+m_curShape.y(), m_curShape.type());
  }
  
  linesToCheckOnRemove.sort();
  linesToCheckOnRemove.unique();
  int destroedLines(0);
  for(int line : linesToCheckOnRemove)
  {
    if( std::find(m_board[line].begin(), m_board[line].end(), ShapeType::NoShape) == m_board[line].end() )
      if( destroyLine(line) ) ++destroedLines;
  }
  
  m_destroedLines += destroedLines;
  m_level = m_destroedLines / 10 + 1;
//  m_score += 50 * destroedLines + m_level;
  switch (destroedLines)
  {
  case 0:
    break;
  case 1:
    m_score += 50 * m_level;
    break;
  case 2:
    m_score += 100 * m_level;
    break;
  case 3:
    m_score += 300 * m_level;
    break;
  case 4:
    m_score += 1200 * m_level;
    break;
  default:
    break;
  }
}


/*! @fn bool moveShape(const int xStep, const int yStep, const int rotate)
 *  @brief Функция изменения положения блока на игровом поле
 *  @param const int xStep - шаг по оси X
 *  @param const int yStep - шаг по оси Y
 *  @param const int rotate - поворот блока
 *          1 - поворот игрового блока против часовой стрелки
 *          -1 - поворот игрового блока по часовой стрелке
 *  @return Флаг успешности операции
 *          true - блок перемещен
 *          false - блок не удалось переместить
 */
bool TetrisCore::moveShape(const int xStep, const int yStep, const int rotate)
{
  if(!m_curShape.isValid())
    return false;
  
  m_curShape.rotate(rotate);
  
  bool isCanMove(true);
  for(const Position &pos : m_curShape.block())
  {
    int x = m_curShape.x() + pos.x + xStep;
    int y = m_curShape.y() + pos.y + yStep;
    if( x < 0 || x >= BoardWidth || y >= BoardHeight || boardElement(x, y) != ShapeType::NoShape )
    {
        isCanMove = false;
        break;
    }
  }
  
  if(!isCanMove)
    m_curShape.rotate(-rotate);
  else
    m_curShape.setShapePos( Position(m_curShape.x()+xStep, m_curShape.y()+yStep) );
  
  return isCanMove;
}


void TetrisCore::pause()
{
  m_isPause = true;
}


void TetrisCore::setBoardElement(int x, int y, const ShapeType type)
{
  assert( (x >= 0) && (x < BoardWidth) );
  assert( (y >= 0) && (y < BoardHeight) );
  
  m_board[y][x] = type;
}


void TetrisCore::start()
{
  if(!m_isPause)
  {
    clearBoard();

    m_level = 1;
    m_score = 0;
    m_destroedLines = 0;

    m_isStarted = true;
    m_isPause = false;

    m_curShape.setRandomShape();
    m_nextShape.setRandomShape();

    m_curShape.setShapePos( Position(BoardWidth/2, 0) );
  }
}


int TetrisCore::timerDelay() const
{
  return ( 100 + 900 * pow(0.75, m_level-1) );
}


void TetrisCore::timeout()
{
  if( moveShape(0, 1, 0) )
    return;
  
  landChanged();
  
  m_curShape = m_nextShape;
  m_nextShape.setRandomShape();
  
  m_curShape.setShapePos( Position(BoardWidth/2, 0) );
}


std::ostream& operator<<(std::ostream &os, const TetrisCore::Board& board)
{  
  for(unsigned int i = 0; i < board.size(); ++i)
  {
    for(const ShapeType item : board[i])
    {
      if(item == ShapeType::NoShape)
        os << "* ";
      else
        os << item << " ";
    }
    
    if(i != board.size()-1)
      os << std::endl;
  }
  
  return os;
}


} // namespace core
} // namespace tetris
