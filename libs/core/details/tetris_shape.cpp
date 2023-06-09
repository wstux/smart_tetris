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
 * File:   tetris_shape.cpp
 * Author: wstux
 * 
 */

#include "core/tetris_shape.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>


namespace tetris
{
namespace core
{


Shape::Shape()
  : m_type(ShapeType::NoShape)
{
  m_shapePos = {};

  m_shape = {};
}


Shape::Shape(const ShapeType type, const RotateType rotate)
{
  setShape(type, rotate);
}



ShapeBlock Shape::getShapeBlock(const ShapeType type, const RotateType rotate) const
{
  static const int block_table[7][4][16] =
  {
    //  *** 
    //  *
    {
      { 0, 0, 0, 0,     //  ----
        1, 1, 1, 0,     //  ***-
        1, 0, 0, 0,     //  *---
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        0, 1, 1, 0,     //  -**-
        0, 0, 0, 0 },   //  ----

      { 0, 0, 1, 0,     //  --*-
        1, 1, 1, 0,     //  ***-
        0, 0, 0, 0,     //  ----
        0, 0, 0, 0 },   //  ----

      { 1, 1, 0, 0,     //  **--
        0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        0, 0, 0, 0 }    //  ----
    },

    //  ***
    //    *
    {
      { 0, 0, 0, 0,     //  ----
        1, 1, 1, 0,     //  ***-
        0, 0, 1, 0,     //  --*-
        0, 0, 0, 0 },   //  ----

      { 0, 1, 1, 0,     //  -**-
        0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        0, 0, 0, 0 },   //  ----

      { 1, 0, 0, 0,     //  *---
        1, 1, 1, 0,     //  ***-
        0, 0, 0, 0,     //  ----
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        1, 1, 0, 0,     //  **--
        0, 0, 0, 0 }    //  ----
    },

    //  ***
    //   *
    {
      { 0, 0, 0, 0,     //  ----
        1, 1, 1, 0,     //  ***-
        0, 1, 0, 0,     //  -*--
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        0, 1, 1, 0,     //  -**-
        0, 1, 0, 0,     //  -*--
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        1, 1, 1, 0,     //  ***-
        0, 0, 0, 0,     //  ----
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        1, 1, 0, 0,     //  **--
        0, 1, 0, 0,     //  -*--
        0, 0, 0, 0 }    //  ----
    },

    //  **
    // **
    {
      { 0, 0, 0, 0,     //  ----
        0, 1, 1, 0,     //  -**-
        1, 1, 0, 0,     //  **--
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        0, 1, 1, 0,     //  -**-
        0, 0, 1, 0,     //  --*-
        0, 0, 0, 0 },   //  ----

      { 0, 1, 1, 0,     //  -**-
        1, 1, 0, 0,     //  **--
        0, 0, 0, 0,     //  ----
        0, 0, 0, 0 },   //  ----

      { 1, 0, 0, 0,     //  *---
        1, 1, 0, 0,     //  **--
        0, 1, 0, 0,     //  -*--
        0, 0, 0, 0 }    //  ----
    },

    // **
    //  **
    {
      { 0, 0, 0, 0,     //  ----
        1, 1, 0, 0,     //  **--
        0, 1, 1, 0,     //  -**-
        0, 0, 0, 0 },   //  ----

      { 0, 0, 1, 0,     //  --*-
        0, 1, 1, 0,     //  -**-
        0, 1, 0, 0,     //  -*--
        0, 0, 0, 0 },   //  ----

      { 1, 1, 0, 0,     //  **--
        0, 1, 1, 0,     //  -**-
        0, 0, 0, 0,     //  ----
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        1, 1, 0, 0,     //  **--
        1, 0, 0, 0,     //  *---
        0, 0, 0, 0 }    //  ----
    },

    // ****
    {
      { 0, 0, 0, 0,     //  ----
        1, 1, 1, 1,     //  ****
        0, 0, 0, 0,     //  ----
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        0, 1, 0, 0 },   //  -*--

      { 0, 0, 0, 0,     //  ----
        1, 1, 1, 1,     //  ****
        0, 0, 0, 0,     //  ----
        0, 0, 0, 0 },   //  ----

      { 0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        0, 1, 0, 0,     //  -*--
        0, 1, 0, 0 }    //  -*--
    },

    // **
    // **
    {
      { 0, 0, 0, 0,     //  ----
        0, 1, 1, 0,     //  -**-
        0, 1, 1, 0,     //  -**-
        0, 0, 0, 0 },   //  ----

      { 0, 0, 0, 0,     //  ----
        0, 1, 1, 0,     //  -**-
        0, 1, 1, 0,     //  -**-
        0, 0, 0, 0 },   //  ----

      { 0, 0, 0, 0,     //  ----
        0, 1, 1, 0,     //  -**-
        0, 1, 1, 0,     //  -**-
        0, 0, 0, 0 },   //  ----

      { 0, 0, 0, 0,     //  ----
        0, 1, 1, 0,     //  -**-
        0, 1, 1, 0,     //  -**-
        0, 0, 0, 0 }    //  ----
    }
  };
  
  ShapeBlock result = {};
  if(type == ShapeType::NoShape)
    return result;
  
  for(unsigned int x = 0, i = 0; x < 4; ++x)
  {
    for(int y = 0; y < 4; ++y)
    {
      if(block_table[ type-1 ][ rotate ][ x + y*4] == 0)
        continue;
      
      assert( i < result.size() );
      result[i].setPos(x, y);
      ++i;
    }
  }
  
  return result;
}


void Shape::rotate(const int rotate)
{
  assert( (rotate >= -1) && (rotate <= 1) );
  if(rotate == 0)
    return;
  
  m_rotate = (RotateType)( (int)m_rotate + rotate );
  if(m_rotate >= RotateType::RotateType_size)
    m_rotate = RotateType::Bottom;
  else if(m_rotate < RotateType::Bottom)
    m_rotate = RotateType::Right;
  
  assert( (m_rotate >= RotateType::Bottom) && (m_rotate <= RotateType::RotateType_size) );
  m_shape = getShapeBlock(m_type, m_rotate);
}


void Shape::setRandomShape()
{
  ShapeType randType = (ShapeType)(rand() % (ShapeType::ShapeType_size-1) + 1);
  RotateType randRotation = (RotateType)(rand() % RotateType::RotateType_size);
  
  setShape(randType, randRotation);
  
  int minX(4);
  int minY(4);
  for(const Position &pos : m_shape)
  {
    minX = std::min(pos.x, minX);
    minY = std::min(pos.y, minY);
  }
  
  setShapePos( Position(minX, -minY) );
}


void Shape::setShape(const ShapeType type, const RotateType rotate)
{
  if((type >= ShapeType::ShapeType_size) || (rotate >= RotateType::RotateType_size))
    return;
  
  if( (m_type == type) && (m_rotate == rotate) )
    return;
  
  m_type = type;
  m_rotate = rotate;
  m_shape = getShapeBlock(m_type, m_rotate);
}


bool Shape::operator==(const Shape &right) const
{
  if(m_type != right.m_type)
    return false;
  
  if(m_shapePos != right.m_shapePos)
    return false;
  
  
  if(m_shape.size() != right.m_shape.size())
    return false;
  
  for(unsigned int i = 0; i < m_shape.size(); ++i)
  {
    if(m_shape[i] != right.m_shape[i])
      return false;
  }
  
  return true;
}


bool Shape::operator!=(const Shape &right) const
{
  return !(*this == right);
}


std::ostream& operator<<(std::ostream &os, const Shape &shape)
{
  std::array< std::array<ShapeType, 4>, 4 > printArr = {};
  for(const Position &pos : shape.m_shape)
    printArr[pos.y][pos.x] = shape.m_type;
  
  for(unsigned int i = 0; i < printArr.size(); ++i)
  {
    for(const int item : printArr[i])
    {
      if(item == ShapeType::NoShape)
        os << "* ";
      else
        os << item << " ";
    }
    
    if(i != printArr.size()-1)
      os << std::endl;
  }
  
  return os;
}


} // namespace core
} // namespace tetris
