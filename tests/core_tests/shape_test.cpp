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
 * File:   shape_test.cpp
 * Author: wstux
 * 
 */

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "tetris_shape.h"

/*
 * Simple C++ Test Suite
 */


void testShape()
{
  srand(time(NULL));
  
  tetris::core::Shape shape;
  shape.setRandomShape();
  
  tetris::core::Shape newShape = shape;
  
  if(shape != newShape)
  {
    std::cout << "%TEST_FAILED% time=0 testname=testShape (shape_test) message=error create shape" << std::endl;
    std::cout << "shape:\n" << shape << std::endl;
    std::cout << "newShape:\n" << newShape << std::endl;
  }
}


void testShapeElements()
{
  srand(time(NULL));
  
  tetris::core::Shape shape;
  shape.setShape(tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Bottom);
  tetris::core::ShapeBlock block;
  block[0] = tetris::core::Position(0, 1);
  block[1] = tetris::core::Position(1, 1);
  block[2] = tetris::core::Position(2, 1);
  block[3] = tetris::core::Position(0, 2);
  
  bool result(true);
  for(const tetris::core::Position &origPos : shape.block())
  {
    if( std::find_if( block.begin(), block.end(), [&origPos](const tetris::core::Position &pos) -> bool { return origPos == pos; } ) == block.end())
      result = false;
  }
    
  if( !result )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testShapeElements (shape_test) message=error shape element positions" << std::endl;
    std::cout << "shape:\n" << shape << std::endl;
  }
}


void testRotate()
{
  tetris::core::Shape shape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Bottom );
  shape.rotate(1);
  
  tetris::core::Shape ethalonShape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Left );
  
  if( shape != ethalonShape )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testRotate (shape_test) message=error rotate shape" << std::endl;
    std::cout << "shape:\n" << shape << std::endl;
    std::cout << "ethalonShape:\n" << ethalonShape << std::endl;
  }
}


void testCircleRotate()
{
  tetris::core::Shape shape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Bottom );
  for(int i =0; i < 5; ++i)
    shape.rotate(1);
  
  tetris::core::Shape ethalonShape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Left );
  
  if( shape != ethalonShape )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testCircleRotate (shape_test) message=error rotate shape" << std::endl;
    std::cout << "shape:\n" << shape << std::endl;
    std::cout << "ethalonShape:\n" << ethalonShape << std::endl;
  }
}


void testBackRotate()
{
  tetris::core::Shape shape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Bottom );
  shape.rotate(-1);
  
  tetris::core::Shape ethalonShape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Right );
  
  if( shape != ethalonShape )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testBackRotate (shape_test) message=error back rotate shape" << std::endl;
    std::cout << "shape:\n" << shape << std::endl;
    std::cout << "ethalonShape:\n" << ethalonShape << std::endl;
  }
}


void testNoneRotate()
{
  tetris::core::Shape shape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Bottom );
  shape.rotate(0);
  
  tetris::core::Shape ethalonShape( tetris::core::ShapeType::LShape, tetris::core::Shape::RotateType::Bottom );
  
  if( shape != ethalonShape )
  {
    std::cout << "%TEST_FAILED% time=0 testname=testNoneRotate (shape_test) message=error back rotate shape" << std::endl;
    std::cout << "shape:\n" << shape << std::endl;
    std::cout << "ethalonShape:\n" << ethalonShape << std::endl;
  }
}


int main(int argc, char** argv)
{
  clock_t allTestsTime;
  clock_t testTime;
  
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "%SUITE_STARTING% shape_test" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  allTestsTime = clock();
  
  // testShape
  std::cout << "%TEST_STARTED% testShape (shape_test)" << std::endl;
  testTime = clock();
  testShape();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testShape (shape_test)" << std::endl;
  
  // testShapeElements
  std::cout << "%TEST_STARTED% testShapeElements (shape_test)" << std::endl;
  testTime = clock();
  testShapeElements();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testShapeElements (shape_test)" << std::endl;

  // testRotate
  std::cout << "%TEST_STARTED% testRotate (shape_test)" << std::endl;
  testTime = clock();
  testRotate();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testRotate (shape_test)" << std::endl;
  
  // testCircleRotate
  std::cout << "%TEST_STARTED% testCircleRotate (shape_test)" << std::endl;
  testTime = clock();
  testCircleRotate();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testCircleRotate (shape_test)" << std::endl;
  
  // testBackRotate
  std::cout << "%TEST_STARTED% testBackRotate (shape_test)" << std::endl;
  testTime = clock();
  testBackRotate();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testBackRotate (shape_test)" << std::endl;
  
  // testNoneRotate
  std::cout << "%TEST_STARTED% testNoneRotate (shape_test)" << std::endl;
  testTime = clock();
  testNoneRotate();
  testTime = clock() - testTime;
  std::cout << "%TEST_FINISHED% time=" << ( ((float)testTime) / CLOCKS_PER_SEC ) << " testNoneRotate (shape_test)" << std::endl;

  
  allTestsTime = clock() - allTestsTime;
  std::cout << "%SUITE_FINISHED% time=" << ( ((float)allTestsTime) / CLOCKS_PER_SEC ) << std::endl;

  return (EXIT_SUCCESS);
}

