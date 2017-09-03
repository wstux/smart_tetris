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

#include "console_tetris.h"

#include <array>
#include <ctime>

#include "tetris_core.h"
#include "tetris_shape.h"


#define KEY_ESC 27


namespace tetris
{
namespace gui
{
namespace console
{


class Timer
{
public:
  Timer();
  
  ~Timer();

  bool isTimeout() const;

  void startTimer(int delay);


private:
  clock_t m_beginTimer;

  int m_timerMsecsDelay;
  
  const clock_t m_clocks_per_msec;
};


Timer::Timer()
  : m_beginTimer()
  , m_timerMsecsDelay(0)
  , m_clocks_per_msec(CLOCKS_PER_SEC / 1000)
{}


Timer::~Timer()
{}


bool Timer::isTimeout() const
{
  if(m_timerMsecsDelay == 0)
    return true;
  
  return ((clock() - m_beginTimer) / m_clocks_per_msec) >= m_timerMsecsDelay;
}


void Timer::startTimer(int msecsDelay)
{
  m_beginTimer = clock();
  m_timerMsecsDelay = msecsDelay;
}


ConsoleTetris::ConsoleTetris()
  : m_pCore(new core::TetrisCore())
  , m_isQuit(false)
  , m_pBoardWnd(NULL)
  , m_pNextShapeWnd(NULL)
  , m_pTimer(new Timer())
  , m_menuColorId(core::ShapeType::ShapeType_size)
{
  initscr();
  init();
  
  int xPos(3),  yPos(1);
  int stepX(5), stepY(1);
  int borderWidth(1);
  int height = m_pCore->boardHeight() + 2*borderWidth;
  int width = 2 * (m_pCore->boardWidth() + borderWidth);
  m_pBoardWnd = newwin(height, width, yPos, xPos);
  
  xPos += width + stepX;
  height = 4 + 2*borderWidth;
  width = 2 * (4 + borderWidth);
  m_pNextShapeWnd = newwin(height, width, yPos, xPos);
    
  yPos += height + stepY;
  height = 4;
  m_pScoreWnd = newwin(height, width, yPos, xPos);
  
  yPos += height + 3*stepY;
  height = CtrlPos::Pos_Quit + 1;
  m_pCtrlWnd = newwin(height, width, yPos, xPos);
}


ConsoleTetris::~ConsoleTetris()
{
  endwin();
  
  delete m_pCore;
  delete m_pTimer;
}


void ConsoleTetris::init()
{
  cbreak();             // получать нажатия клавиш, но не сигналы
  noecho();             // не рисовать нажатые кнопки
  keypad(stdscr, TRUE); // принимать нажатия кнопок на основном окне
  timeout(0);           // не блокировать по getch()
  curs_set(0);          // курсор невидимый
  
  mousemask(BUTTON1_CLICKED, NULL);
  
  initColors();
}


void ConsoleTetris::initColors()
{
  start_color();
  init_pair(core::ShapeType::LShape        , COLOR_CYAN   , COLOR_BLACK);
  init_pair(core::ShapeType::MirroredLShape, COLOR_BLUE   , COLOR_BLACK);
  init_pair(core::ShapeType::TShape        , COLOR_WHITE  , COLOR_BLACK);
  init_pair(core::ShapeType::SShape        , COLOR_YELLOW , COLOR_BLACK);
  init_pair(core::ShapeType::ZShape        , COLOR_GREEN  , COLOR_BLACK);
  init_pair(core::ShapeType::LineShape     , COLOR_MAGENTA, COLOR_BLACK);
  init_pair(core::ShapeType::SquareShape   , COLOR_RED    , COLOR_BLACK);
  
  init_pair(m_menuColorId                  , COLOR_WHITE  , COLOR_BLACK);
}


void ConsoleTetris::mouseEvent()
{
  MEVENT event;
  if(getmouse(&event) != OK)
    return;
  
  if((event.x < m_pCtrlWnd->_begx) || (event.x > m_pCtrlWnd->_begx+m_pCtrlWnd->_maxx))
    return;
  if((event.y < m_pCtrlWnd->_begy) || (event.y > m_pCtrlWnd->_begy+m_pCtrlWnd->_maxy))
    return;
  
  int y = event.y - m_pCtrlWnd->_begy;
  
  switch(y)
  {
  case CtrlPos::Pos_Start:
    m_pCore->start();
    break;
  case CtrlPos::Pos_Pause:
    m_pCore->pause();
    break;
  case CtrlPos::Pos_Stop:
    m_pCore->stop();
    break;
  case CtrlPos::Pos_Quit:
    m_isQuit = true;
    break;
  default:
    break;
  }
}


void ConsoleTetris::paint()
{
  const int endX = stdscr->_maxx/2 - 3;
  for(int x = 0; x < endX; ++x)
    mvprintw(0, x, "=");
  mvprintw(0, endX, "Tetris");
  for(int x = endX + 6; x < stdscr->_maxx; ++x)
    mvprintw(0, x, "=");
  
  for(int x = 0; x < stdscr->_maxx; ++x)
    mvprintw(stdscr->_maxy, x, "=");
  
  paintBoard();
  paintNextShapeBoard();
  paintScore();
  paintCtrl();
          
  refresh();
}


void ConsoleTetris::paintBoard()
{
  box(m_pBoardWnd, 0, 0);
  
  core::TetrisCore::Board board = m_pCore->board();
  for(unsigned int y = 0; y < board.size(); ++y)
  {
    for(unsigned int x = 0; x < board[y].size(); ++x)
      printShape(m_pBoardWnd, y, x, board[y][x]);
  }
  
  if(m_pCore->isGamePaused())
    mvwprintw(m_pBoardWnd, 9, 12, "Pause");
  if(m_pCore->isGameOver())
    mvwprintw(m_pBoardWnd, 9, 9, "Game over!");
  
  wrefresh(m_pBoardWnd);
}


void ConsoleTetris::paintCtrl()
{
  wattron(m_pCtrlWnd, A_REVERSE | COLOR_PAIR(m_menuColorId));
  mvwprintw(m_pCtrlWnd, CtrlPos::Pos_Start, 0, " Start ");
  mvwprintw(m_pCtrlWnd, CtrlPos::Pos_Pause, 0, " Pause ");
  mvwprintw(m_pCtrlWnd, CtrlPos::Pos_Stop , 0, " Stop  ");
  mvwprintw(m_pCtrlWnd, CtrlPos::Pos_Quit , 0, " Quit  ");
  wattroff(m_pCtrlWnd, A_REVERSE | COLOR_PAIR(m_menuColorId));
  
  wrefresh(m_pCtrlWnd);
}


void ConsoleTetris::paintNextShapeBoard()
{
  box(m_pNextShapeWnd, 0, 0);
  
  core::Shape nextShape = m_pCore->nextShape();
  std::array< std::array<int, 4>, 4 > printArr = {};
  for(const core::Position &pos : nextShape.block())
    printArr[pos.y][pos.x] = nextShape.type();
  
  for(unsigned int y = 0; y < printArr.size(); ++y)
  {
    for(unsigned int x = 0; x < printArr[y].size(); ++x)
    {
      printShape(m_pNextShapeWnd, y, x, printArr[y][x]);
    }
  }
  
  wrefresh(m_pNextShapeWnd);
}


void ConsoleTetris::paintScore()
{
  mvwprintw(m_pScoreWnd, 0, 0, "Score:");
  mvwprintw(m_pScoreWnd, 1, 0, "%d", m_pCore->score());
  mvwprintw(m_pScoreWnd, 2, 0, "Level:");
  mvwprintw(m_pScoreWnd, 3, 0, "%d", m_pCore->level());
  
  wrefresh(m_pScoreWnd);
}


void ConsoleTetris::printShape(WINDOW *pWnd, int y, int x, int color)
{
  if(color == core::ShapeType::NoShape)
    mvwprintw(pWnd, y + 1, 2*x + 1, "  ");
  else if(color < core::ShapeType::ShapeType_size)
  {
    wattron(pWnd, A_REVERSE | COLOR_PAIR(color));
    mvwprintw(pWnd, y + 1, 2*x + 1, "  ");
    wattroff(pWnd, A_REVERSE | COLOR_PAIR(color));
  }
}


void ConsoleTetris::show()
{
  while(!m_isQuit)
  {
    paint();
    
    if(m_pTimer->isTimeout())
    {
      m_pCore->gameStep();
      m_pTimer->startTimer( m_pCore->timerDelay() );
    }
    
    switch( getch() )
    {
    case KEY_LEFT:
      m_pCore->moveLeft();
      break;
    case KEY_RIGHT:
      m_pCore->moveRight();
      break;
    case KEY_UP:
      m_pCore->rotateRight();
      break;
    case KEY_DOWN:
      m_pCore->fastForward();
//      m_pTimer->startTimer( m_pCore->timerDelay() );
      break;
    case KEY_MOUSE:
      mouseEvent();
      break;
    case 'p':
      m_pCore->pause();
      break;
    case 's':
      m_pCore->start();
      break;
    case KEY_ESC:
    case 'q':
      m_isQuit = true;
      break;      
    default:
      break;
    }
  }
}


}  // namespace console
}  // namespace gui
}  // namespace tetris
