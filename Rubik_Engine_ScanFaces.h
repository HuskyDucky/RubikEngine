/**
    File    : Rubik_Engine_ScanFaces.h
    Author  : Menashe Rosemberg
    Created : 2019.12.21            Version: 20200125.4

    Rubik Engine - ScanFace Definition

    Copyright (c) 2019 TheArquitect (Menashe Rosemberg) rosemberg@ymail.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
///ATTENTION: The procedure to scan the cube:
///           1. The faces is always scanned from the block on Left|Top to Right|Down.
///           2. Turn the cube:
///           2.1 choose any face to be a face base. That is the FRONT - Scan this face.
///           2.2 turn cube clockwise to scan the next faces RIGHT, BACK and LEFT
///           2.3 turn back to FRONT face (one more turn clockwise). Turn the cube down in its horizontal axis and scan the TOP face
///           2.4 turn the cube up in its horizontal axis twice and scan the BOTTOM face
#ifndef SCANFACES_H
#define SCANFACES_H

#include <cmath>
#include "Rubik_Engine_Global.h"

constexpr uint8_t LIN = 0;
constexpr uint8_t COL = 1;
constexpr uint8_t LAY = 2;
constexpr uint8_t BitLIN = 2;
constexpr uint8_t BitCOL = 4;
constexpr uint8_t BitLAY = 8;

class ClassScanFaces {
    protected:
       struct ScanFaces {
              ScanFaces(Cube_T& cubebase, function<BlkPosition_T(const Coord_T&)>& block_coordenate);

           bool scan(const FacePosition_E Face, vector<Color_E>&& FaceColors) noexcept;
           ProtoCube_T commitScannedFaces() noexcept;

           private:
               Cube_T& CubeBase;
               const CubeSideSize_T SideSize;                                     // Layer    Col      Lin
               const QofBlksPerFace_T FaceSize;                                   // bit3     bit2     bit1   bit0
               static constexpr CubeSideSize_T ColorPositionOnProtoCube[TofFACES] { (0<<3) + (1<<2) + (1<<1) + 0,   //FRONT
                                                                                    (1<<3) + (0<<2) + (1<<1) + 1,   //RIGHT
                                /* If the bit321 = 0 the coord is unchangeble.  */  (0<<3) + (1<<2) + (1<<1) + 1,   //BACK
                                /* bit0 = 0 => fix position is 0                */  (1<<3) + (0<<2) + (1<<1) + 0,   //LEFT
                                /* bit0 = 1 => fix position is this->SideSize-1 */  (1<<3) + (1<<2) + (0<<1) + 0,   //TOP
                                                                                    (1<<3) + (1<<2) + (0<<1) + 1    //BOTTOM
               };

               function<BlkPosition_T(const Coord_T&)>& Block_Coordenate;

               array<vector<Color_E>, TofFACES> ScannedFaces;            //Scan cube faces

               ProtoCube_T CreateProtoCube() const noexcept;

               inline BlocksPosToFace_T BlocksPositionsToThe(const FacePosition_E Face) const noexcept; //Return a list of blocks' position basede on the face
               inline bool scan_ValidateNewFace(const vector<Color_E>& FaceColors) const noexcept;
               void AlignBackLeftTopFaces() noexcept;
       };
};

#endif
