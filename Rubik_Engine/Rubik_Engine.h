/**
    File    : Rubik_Engine.h
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200501.1

    Copyright (c) 2019 TheArquitect (Menashe Rosemberg) rosemberg@ymail.com

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
    SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
    OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#ifndef RUBIKENGINE_H
#define RUBIKENGINE_H

#include <chrono>
#include <random>
#include <memory>
#include <iostream>

#include "Rubik_Engine_Global.h"
#include "Rubik_Engine_MoveTypes.h"
#include "Rubik_Engine_ScanFaces.h"

typedef BlkPosition_T QofBlocks_T;        //CubeSideSize_T(255) ^ 3 = 16,581,375 free to use

using From_To = pair<CubeSideSize_T, CubeSideSize_T>;
using AxisPosition_T = pair<CubeSideSize_T, CubeSideSize_T>;

#define Layer0to0 {0, 0}
#define Layer0toL {0, this->SideSize-1}
#define LayerLto0 {this->SideSize-1, 0}
#define LayerLtoL {this->SideSize-1, this->SideSize-1}

struct Rubik_Engine : private ClassBlock, ClassScanFaces {
       Rubik_Engine();
       Rubik_Engine(const Rubik_Engine& OriCube);
      ~Rubik_Engine();

       CubeSideSize_T SidesSize() const noexcept;
       QofBlocks_T TotalOfBlocks() const noexcept;

       //Cube info
            bool isFinished() const noexcept;
            bool operator==(const Rubik_Engine& CompCube) noexcept;

       //Block info
            FaceList_T Block_FacesList(const Coord_T& xyz) const noexcept;

       //Moves
            void spin(const SpinTo_T& SpinThe) noexcept;
            void spinback(const SpinTo_T& spinThe) noexcept;
            void spin(const SpinBlocksAt Layer, const CubeSideSize_T Level, const TurnBlock isClockWise) noexcept;

       //feed the class with a real Rubik Cube
            bool scan(const FacePosition_E Face, vector<Color_E>&& Colors) noexcept; //If some Face was ill-scanned just pass it again to scan
            bool commitScannedFaces() noexcept;                                      //Inconsistences can be fixed just pass to scan the correction of ill-scanned Faces

       //others actions
            Cube_T randomize(uint16_t NoInterations) noexcept;                       //Automatically save this new randomization
            void operator()(const Rubik_Engine& OriCube) noexcept;                   //Copy Cube
            void reset() noexcept;

    private:
        const CubeSideSize_T SideSize;                                      //The max blocks is 255 not 256. This last value is reserved to internal use of this class
        const QofBlocks_T TofBlocks;
        Cube_T Cube;

        //Cube Aux variables
            Coord_T XYZ;
            SpinBlocksAt CurrLayer2Move;
            const From_To *Abs_Axis = nullptr;
            const From_To *Ord_Axis = nullptr;
            const From_To CW_Abs_Axis[4] = {Layer0to0, Layer0toL, LayerLtoL, LayerLto0};     //Abs and Ord Axes determine the block position on the
            const From_To CW_Ord_Axis[4] = {Layer0toL, LayerLtoL, LayerLto0, Layer0to0};     //CurrLayer2Move to Clockwise spin
            const From_To CCWAbs_Axis[4] = {Layer0to0, LayerLto0, LayerLtoL, Layer0toL};     //Abs and Ord Axes determine the block position on the
            const From_To CCWOrd_Axis[4] = {Layer0toL, Layer0to0, LayerLto0, LayerLtoL};     //CurrLayer2Move to CounterClockwise spin

        //Spin helps
            AxisPosition_T spin_NextCoords(const CubeSideSize_T CubeFace, const CubeSideSize_T BlockNo) const noexcept;
            BlkPosition_T spin_CalcBlockPosition(const AxisPosition_T AxesHV) noexcept;

        //General
            function<BlkPosition_T(const Coord_T&)> Block_Coordenate;   //Calculate the block position in the cube - will be passed to ScannedFaces


            unique_ptr<ScanFaces> ScannedFaces;                         //Used only when the user wants to scan a real cube
            void ReleaseScannedFaces() noexcept;

        void Rubik_Engine_Initializer() noexcept;
        Rubik_Engine& operator=(const Rubik_Engine&) = delete;
};

#endif
