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

#include <cstdlib>
#include <ctime>
#include <algorithm>

#include <testing/testdefs.h>

#include "core/tetris_shape.h"

TEST(shape_fixture, create)
{
    ::srand(::time(NULL));

    tetris::core::Shape shape;
    shape.setRandomShape();
  
    tetris::core::Shape newShape = shape;
  
    EXPECT_TRUE(shape == newShape);
}

TEST(shape_fixture, element_positions)
{
    ::srand(::time(NULL));

    tetris::core::Shape shape;
    shape.setShape(tetris::core::ShapeType::LShape,
                   tetris::core::Shape::RotateType::Bottom);

    tetris::core::ShapeBlock block;
    block[0] = tetris::core::Position(0, 1);
    block[1] = tetris::core::Position(1, 1);
    block[2] = tetris::core::Position(2, 1);
    block[3] = tetris::core::Position(0, 2);

    for(const tetris::core::Position &origPos : shape.block()) {
        tetris::core::ShapeBlock::const_iterator it = 
            std::find_if(block.begin(), block.end(),
                         [&origPos](const tetris::core::Position &pos) -> bool {
                             return origPos == pos;
                         });
        EXPECT_TRUE(it != block.end())
            << "position[" << origPos.x << "; " << origPos.y << "] not found"
            << std::endl << "shape:\n" << shape;
    }
}

TEST(shape_fixture, rotate)
{
    tetris::core::Shape ethalon(tetris::core::ShapeType::LShape,
                                tetris::core::Shape::RotateType::Left);

    tetris::core::Shape shape(tetris::core::ShapeType::LShape,
                              tetris::core::Shape::RotateType::Bottom );
    shape.rotate(1);

    EXPECT_TRUE(shape == ethalon)
        << "shape:" << std::endl << shape << std::endl
        << "ethalon:" << std::endl << ethalon;
}

TEST(shape_fixture, circle_rotate)
{
    tetris::core::Shape ethalon(tetris::core::ShapeType::LShape,
                                tetris::core::Shape::RotateType::Left);

    tetris::core::Shape shape(tetris::core::ShapeType::LShape,
                              tetris::core::Shape::RotateType::Bottom);
    for(size_t i = 0; i < 5; ++i) {
        shape.rotate(1);
    }

    EXPECT_TRUE(shape == ethalon)
        << "shape:" << std::endl << shape << std::endl
        << "ethalon:" << std::endl << ethalon;
}

TEST(shape_fixture, back_rotate)
{
    tetris::core::Shape ethalon(tetris::core::ShapeType::LShape,
                                tetris::core::Shape::RotateType::Right);

    tetris::core::Shape shape(tetris::core::ShapeType::LShape,
                              tetris::core::Shape::RotateType::Bottom);
    shape.rotate(-1);

    EXPECT_TRUE(shape == ethalon)
        << "shape:" << std::endl << shape << std::endl
        << "ethalon:" << std::endl << ethalon;
}

TEST(shape_fixture, none_rotate)
{
    tetris::core::Shape ethalon(tetris::core::ShapeType::LShape,
                                tetris::core::Shape::RotateType::Bottom);

    tetris::core::Shape shape(tetris::core::ShapeType::LShape,
                              tetris::core::Shape::RotateType::Bottom);
    shape.rotate(0);

    EXPECT_TRUE(shape == ethalon)
        << "shape:" << std::endl << shape << std::endl
        << "ethalon:" << std::endl << ethalon;
}


int main(int /*argc*/, char** /*argv*/)
{
    return RUN_ALL_TESTS();
}

