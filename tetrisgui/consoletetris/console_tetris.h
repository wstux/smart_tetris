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
 * File:   console_tetris.h
 * Author: wstux
 * 
 */

#ifndef CONSOLE_TETRIS_H
#define CONSOLE_TETRIS_H

#include <map>
#include <ncurses.h>
#include <string>


namespace tetris
{
namespace core { class TetrisCore; }

namespace gui
{
namespace console
{


class Timer;


class ConsoleTetris
{
private:
  enum CtrlPos
  {
    Pos_Start = 0,
    
    Pos_Pause = 2,
    
    Pos_Stop  = 4,
    
    Pos_Quit  = 6,
    
    Pos_Size
  };
  
  typedef std::map<CtrlPos, std::string> ButtonMap;
  
  
public:
  ConsoleTetris();

  ~ConsoleTetris();

  void show();
  
  
protected:
  void init();
  
  void paint();
  
  
private:
  void initColors();
  
  void mouseEvent();
  
  void paintBoard();
  
  void paintCtrl();
  
  void paintNextShapeBoard();
  
  void paintScore();
  
  void printShape(WINDOW *pWnd, int y, int x, int color);
    
  
private:
  core::TetrisCore *m_pCore;
  
  bool m_isQuit;
  
  WINDOW *m_pBoardWnd;
  
  WINDOW *m_pNextShapeWnd;
  
  WINDOW *m_pScoreWnd;
  
  WINDOW *m_pCtrlWnd;
  
  Timer *m_pTimer;
  
  const int m_menuColorId;
  
  CtrlPos m_pressedButton;
  
  ButtonMap m_btnMap;
};


}  // namespace console
}  // namespace gui
}  // namespace tetris

#endif /* CONSOLE_TETRIS_H */

