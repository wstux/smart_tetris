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
 * File:   tetris_window.h
 * Author: wstux
 * 
 */

#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H

#include <ncurses.h>


namespace tetris
{
namespace gui
{
namespace console
{


class AbstractTetrisWindow
{
public:
  AbstractTetrisWindow(int height, int width, int y, int x);

  virtual ~AbstractTetrisWindow();
  
  virtual void paint() = 0;
  
  
protected:
  WINDOW *m_pWnd;
};


class BoardWindow : public AbstractTetrisWindow
{
  typedef AbstractTetrisWindow Base;
  
public:
  BoardWindow(int height, int width, int y, int x);

  virtual ~BoardWindow();
  
  void paint();
};


class NextShapeWindow : public AbstractTetrisWindow
{
  typedef AbstractTetrisWindow Base;
  
public:
  NextShapeWindow(int height, int width, int y, int x);

  virtual ~NextShapeWindow();
  
  void paint();
};


class ScoreWindow : public AbstractTetrisWindow
{
  typedef AbstractTetrisWindow Base;
  
public:
  ScoreWindow(int height, int width, int y, int x);

  virtual ~ScoreWindow();
  
  void paint();
};


}  // namespace console
}  // namespace gui
}  // namespace tetris

#endif /* TETRIS_WINDOW_H */

