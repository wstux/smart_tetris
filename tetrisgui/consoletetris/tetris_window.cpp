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
 * File:   tetris_window.cpp
 * Author: wstux
 * 
 */

#include "tetris_window.h"


namespace tetris
{
namespace gui
{
namespace console
{


AbstractTetrisWindow::AbstractTetrisWindow(int height, int width, int y, int x)
{
  m_pWnd = newwin(height, width, y, x);
}


AbstractTetrisWindow::~AbstractTetrisWindow()
{
}


BoardWindow::BoardWindow(int height, int width, int y, int x)
  : Base(height, width, y, x)
{}


BoardWindow::~BoardWindow()
{
}


void BoardWindow::paint()
{
  box(m_pWnd, 0, 0);
  wrefresh(m_pWnd);
}


NextShapeWindow::NextShapeWindow(int height, int width, int y, int x)
  : Base(height, width, y, x)
{}


NextShapeWindow::~NextShapeWindow()
{
}


void NextShapeWindow::paint()
{
  box(m_pWnd, 0, 0);
  wrefresh(m_pWnd);
}


ScoreWindow::ScoreWindow(int height, int width, int y, int x)
  : Base(height, width, y, x)
{}


ScoreWindow::~ScoreWindow()
{
}


void ScoreWindow::paint()
{
  box(m_pWnd, 0, 0);
  wrefresh(m_pWnd);
}


}  // namespace console
}  // namespace gui
}  // namespace tetris