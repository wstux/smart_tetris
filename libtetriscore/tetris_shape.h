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
 * File:   tetris_shape.h
 * Author: wstux
 * 
 */

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H

#include <array>
#include <iosfwd>


namespace tetris
{
namespace core
{


  /// 
enum ShapeType
{
  NoShape = 0,
  
  LShape,
  
  MirroredLShape,
  
  TShape,
  
  SShape,
  
  ZShape,
  
  LineShape,
  
  SquareShape,
  
  ShapeType_size
};


struct Position
{
public:
  Position()
    : x(0)
    , y(0)
  {}
    
  Position(int xPos, int yPos)
    : x(xPos)
    , y(yPos)
  {}
  
  bool operator==(const Position &right) const
  {
    return (x == right.x) && (y == right.y);
  }
  
  bool operator!=(const Position &right) const
  {
    return (x != right.x) || (y != right.y);
  }
    
  void setPos(const int x, const int y)
  {
    this->x = x;
    this->y = y;
  }


public:  
  int x;
  
  int y;
};
typedef std::array< Position, 4 > ShapeBlock;


class Shape
{
public:
  enum RotateType
  {
    Bottom = 0,

    Left,

    Top,

    Right,

    RotateType_size
  };
  
  
public:
  Shape();
  
  Shape(const ShapeType type, const RotateType rotate);
  
  ~Shape() {}
  
  const ShapeBlock& block() const { return m_shape; }
  
  bool isValid() const { return m_type != ShapeType::NoShape; }
    
  void rotate(const int rotate);
  
  void setRandomShape();
  
  void setShape(const ShapeType type, const RotateType rotate);
  
  void setShapePos(const Position &pos) { m_shapePos = pos; }
  
  ShapeType type() const { return m_type; }
  
  int x() const { return m_shapePos.x; }
  
  int y() const { return m_shapePos.y; }
  
  bool operator==(const Shape &right) const;
  
  bool operator!=(const Shape &right) const;
  
  friend std::ostream& operator<<(std::ostream &os, const Shape &shape);
  
  
private:
  ShapeBlock getShapeBlock(const ShapeType type, const RotateType rotate) const;
  
  
private:
  Position m_shapePos;
  
  ShapeType m_type;
  
  RotateType m_rotate;
  
  ShapeBlock m_shape;
  
  int m_width;
  
  int m_height;
};


} // namespace core
} // namespace tetris

#endif /* TETRIS_SHAPE_H */

