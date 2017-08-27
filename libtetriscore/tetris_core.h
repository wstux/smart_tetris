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
  
  typedef std::vector< BoardLine > Board;
      
      
public:
  TetrisCore();
  
  ~TetrisCore();
    
    /// @fn Board board() const
    /// @brief Запрос актуального игрового поля
    /// @return Актуальное игровое поле
  Board board() const;
  
    /// @fn int boardHeight() const
    /// @brief Запрос высоты игрового поля
    /// @return Высота игрового поля
  int boardHeight() const { return BoardHeight; }
  
    /// @fn int boardWidth() const
    /// @brief Запрос ширины игрового поля
    /// @return Ширина игрового поля
  int boardWidth() const { return BoardWidth; }
  
  void fastForward();
  
    /// @fn int level() const
    /// @brief Запрос уровня
    /// @return Уровень
  int level() const { return m_level; }
  
    /// @fn bool moveLeft()
    /// @brief Смещение игрового блока на одну ячейку влево
    /// @return Флаг успешности операции
    ///         true - блок смещен влево
    ///         false - блок не удалось сместить
  bool moveLeft() { return moveShape(-1, 0, 0); }

    /// @fn bool moveRight()
    /// @brief Смещение игрового блока на одну ячейку вправо
    /// @return Флаг успешности операции
    ///         true - блок смещен вправоо
    ///         false - блок не удалось сместить
  bool moveRight() { return moveShape(1, 0, 0); }

  void pause();
  
    /// @fn bool rotateLeft()
    /// @brief Поворот игрового блока по часовой стрелке
    /// @return Флаг успешности операции
    ///         true - блок удалось повернуть
    ///         false - блок не удалось повернуть
  bool rotateLeft() { return moveShape(0, 0, -1); }

    /// @fn bool rotateRight()
    /// @brief Поворот игрового блока против часовой стрелки
    /// @return Флаг успешности операции
    ///         true - блок удалось повернуть
    ///         false - блок не удалось повернуть
  bool rotateRight() { return moveShape(0, 0, 1); }
  
    /// @fn int score() const
    /// @brief Запрос текущего игрового счета
    /// @return Текущий игровой счет
  int score() const { return m_score; }
  
  void start();
  
  void timeout();
  
    /// @return Timeout step-timer in msecs
  int timerDelay() const;
  
  
protected:
  ShapeType boardElement(int x, int y) const;
  
  void clearBoard();
  
  bool destroyLine(const int line);
  
  void landChanged();
  
    /// @fn bool moveShape(const int xStep, const int yStep, const int rotate)
    /// @brief Функция изменения положения блока на игровом поле
    /// @param const int xStep - шаг по оси X
    /// @param const int yStep - шаг по оси Y
    /// @param const int rotate - поворот блока
    ///         1 - поворот игрового блока против часовой стрелки
    ///         -1 - поворот игрового блока по часовой стрелке
    /// @return Флаг успешности операции
    ///         true - блок перемещен
    ///         false - блок не удалось переместить
  bool moveShape(const int xStep, const int yStep, const int rotate);
  
  void setBoardElement(int x, int y, const ShapeType type);
  
  
private:
    /// Текущий игровой блок
  Shape m_curShape;
  
    /// Следующий игровой блок
  Shape m_nextShape;
  
    /// Игровая доска
  Board m_board;
  
    /// Флаг запущенности игры
  bool m_isStarted;
  
    /// Флаг остановки игры на паузу
  bool m_isPause;
  
    /// Флаг окончания игры
  bool m_isGameOver;
  
    /// Текущий уровень
  int m_level;
  
    /// Текущий счет
  int m_score;
  
    /// Количество уничтоженных линий
  int m_destroedLines;
};


std::ostream& operator<<(std::ostream &os, const TetrisCore::Board& board);


} // namespace core
} // namespace tetris

#endif /* TETRIS_CORE_H */
