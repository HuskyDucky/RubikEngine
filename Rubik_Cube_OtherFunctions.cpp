/**
    File    : Rubik_Cube_OtherFunctions.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.2

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

Cube_T Rubik::randomize(uint16_t NoInterations) noexcept {
       mt19937 RandBase(chrono::steady_clock::now().time_since_epoch().count());

       uniform_real_distribution<float> ClockWiseOrOtherWise(0.0, 1.0);
       bernoulli_distribution isClockWise(ClockWiseOrOtherWise(RandBase));
       uniform_int_distribution<Layer_T> Layer(0, 2);                //Enum FlipBlocksAt
       uniform_int_distribution<CubeSideSize_T>  Level(0, this->SideSize-1);

       while (NoInterations) {
             --NoInterations;
             this->flip(FlipTo_T(static_cast<FlipBlocksAt>(Layer(RandBase)),
                        Level(RandBase),
                        static_cast<TurnBlocks>(isClockWise(RandBase))));
       }

       return this->Cube;
}

void Rubik::operator()(const Rubik& OriCube) noexcept {
     if (OriCube.TofBlocks == this->TofBlocks) {
        this->Cube.clear();

        this->XYZ[LAYER] = 0;
        do {
            this->XYZ[LINE] = 0;
            do {
                this->XYZ[COLUMN] = 0;
                do {
                    this->Cube.emplace_back(OriCube.Block_OriginalPosition(XYZ), OriCube.Block_FacesList(XYZ));
                } while (++this->XYZ[COLUMN] < this->SideSize);
            } while (++this->XYZ[LINE] < this->SideSize);
        } while (++this->XYZ[LAYER] != this->SideSize);
     }
}

void Rubik::reset() noexcept {
     this->Cube.clear();
     this->Cube.reserve(this->TofBlocks);

     BlkPosition_T BlockPos = 0;
     this->XYZ[LINE] = 0;
     do {
        this->XYZ[COLUMN] = 0;
         do {
             this->XYZ[LAYER] = 0;
             do {
                 FaceList_T ColorPos;

                 if (this->XYZ[LINE] == 0)
                    ColorPos.emplace_back(Color_E::WHITE, FacePosition_E::FRONT);
                 else if (this->XYZ[LINE] == this->SideSize-1)
                         ColorPos.emplace_back(Color_E::YELLOW, FacePosition_E::BACK);

                 if (this->XYZ[COLUMN] == 0)
                    ColorPos.emplace_back(Color_E::RED, FacePosition_E::TOP);
                 else if (this->XYZ[COLUMN] == this->SideSize-1)
                         ColorPos.emplace_back(Color_E::ORANGE, FacePosition_E::BOTTOM);

                 if (this->XYZ[LAYER ] == 0)
                    ColorPos.emplace_back(Color_E::BLUE, FacePosition_E::LEFT);
                 else if (this->XYZ[LAYER ] == this->SideSize-1)
                         ColorPos.emplace_back(Color_E::GREEN, FacePosition_E::RIGHT);

                 this->Cube.emplace_back(BlockPos++, move(ColorPos));

             } while (++this->XYZ[LAYER] != this->SideSize);
         } while (++this->XYZ[COLUMN] != this->SideSize);
     } while (++this->XYZ[LINE] != this->SideSize);
}
