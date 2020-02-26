/**
    File    : Rubik_Cube.h
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.2

    Rubik Program - Cube Definition

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
#ifndef CUBE_H
#define CUBE_H

#include <chrono>
#include <random>
#include <memory>
#include <iostream>

#include "Rubik_Cube_Global.h"
#include "Rubik_Cube_FlipTo.h"
#include "Rubik_ScanFaces.h"

typedef BlkPosition_T QofBlocks_T;        //CubeSideSize_T(255) ^ 3 = 16,581,375 free to use

using From_To = pair<CubeSideSize_T, CubeSideSize_T>;
using AxisPosition_T = pair<CubeSideSize_T, CubeSideSize_T>;

#define Layer0to0 {0, 0}
#define Layer0toL {0, this->SideSize-1}
#define LayerLto0 {this->SideSize-1, 0}
#define LayerLtoL {this->SideSize-1, this->SideSize-1}

struct Rubik : private ClassBlock, ClassScanFaces {
       Rubik();
       Rubik(const Rubik& OriCube);
      ~Rubik();

       CubeSideSize_T SidesSize() const noexcept;
       QofBlocks_T TotalOfBlocks() const noexcept;

       //Cube info
            bool isFinished() const noexcept;
            float PercentualDone() const noexcept;
            bool operator==(const Rubik& CompCube) noexcept;

       //Block info
            bool isBlockInPosition(const Coord_T& xyz) const noexcept;
            FaceList_T Block_FacesList(const Coord_T& xyz) const noexcept;
            BlkPosition_T Block_OriginalPosition(const Coord_T& xyz) const noexcept;

       //Move blocks
            void flip(const FlipTo_T& FlipThe) noexcept;
            void flip(const FlipBlocksAt Layer, const CubeSideSize_T Level, const TurnBlocks isClockWise) noexcept;

       //feed the class with a real Rubik Cube
            bool scan(const FacePosition_E Face, vector<Color_E>&& Colors) noexcept; //If some Face was ill-scanned just pass it again to scan
            bool commitScannedFaces() noexcept;                                      //Inconsistences can be fixed just pass to scan the correction of ill-scanned Faces

       //others actions
            Cube_T randomize(uint16_t NoInterations) noexcept;       //Automatically save this new randomization
            void operator()(const Rubik& OriCube) noexcept;          //Copy Cube
            void reset() noexcept;

    private:
        const CubeSideSize_T SideSize;                              //The max blocks is 255 not 256. This last value is reserved to internal use of this class
        const QofBlocks_T TofBlocks;
        Cube_T Cube;

        //Cube Aux variables
            Coord_T XYZ;
            FlipBlocksAt CurrLayer2Move;
            const From_To *Abs_Axis = nullptr;
            const From_To *Ord_Axis = nullptr;
            const From_To CW_Abs_Axis[4] = {Layer0to0, Layer0toL, LayerLtoL, LayerLto0};     //Abs and Ord Axes determine the block position on the
            const From_To CW_Ord_Axis[4] = {Layer0toL, LayerLtoL, LayerLto0, Layer0to0};     //CurrLayer2Move to Clockwise flip
            const From_To CCWAbs_Axis[4] = {Layer0to0, LayerLto0, LayerLtoL, Layer0toL};     //Abs and Ord Axes determine the block position on the
            const From_To CCWOrd_Axis[4] = {Layer0toL, Layer0to0, LayerLto0, LayerLtoL};     //CurrLayer2Move to CounterClockwise flip

        //Flip
            AxisPosition_T flip_NextCoords(const CubeSideSize_T CubeFace, const CubeSideSize_T BlockNo) const noexcept;
            BlkPosition_T flip_CalcBlockPosition(const AxisPosition_T AxesHV) noexcept;

        //General
            function<BlkPosition_T(const Coord_T&)> Block_Coordenate;  //Calculate the block position in the cube - will be passed to ScannedFaces


            unique_ptr<ScanFaces> ScannedFaces;                         //Used only when the user wants to scan a real cube
            void ReleaseScannedFaces() noexcept;

        void Rubik_Initializer() noexcept;
        Rubik& operator=(const Rubik&) = delete;
};

#endif
