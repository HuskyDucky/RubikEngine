/**
    File    : Rubik_Cube_Global.h
    Author  : Menashe Rosemberg
    Created : 2019.10.26            Version: 20191228.2

    Rubik Program - Cube General Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
///ATTENTION: The procedure to scan the cube:
///           1. The faces is always scanned from the block on Left|Top to Right|Down.
///           2. Turn the cube:
///           2.1 choose any face to be a face base. That is the FRONT - Scan this face.
///           2.2 turn cube clockwise to scan the next faces RIGHT, BACK and LEFT
///           2.3 turn back to FRONT face (one more turn clockwise). Turn the cube down in its horizontal axis and scan the TOP face
///           2.4 turn the cube up in its horizontal axis twice and scan the BOTTOM face
#ifndef CUBE_GLOBAL_H
#define CUBE_GLOBAL_H

#include <array>
#include <vector>
#include <algorithm>

#include "Rubik_Block.h"

constexpr uint8_t TofFACES = 6;

typedef uint8_t CubeSideSize_T;           //max blocks is 255 (the last value - 256 - is reserved to internal use of the class)
typedef uint16_t QofBlksPerFace_T;        //255 x 255 = 65.025 free to use

//Cube (and ScanFaces)
using Cube_T = vector<ClassBlock::Block>;
using Coord_T = array<CubeSideSize_T, 3>;
//Scanfaces (and Cube)
using BlocksPosToFace_T = vector<QofBlksPerFace_T>;
using ProtoCube_T = vector<FaceList_T>;

#endif
