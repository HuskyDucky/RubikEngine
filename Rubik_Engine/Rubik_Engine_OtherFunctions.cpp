/**
    File    : Rubik_Cube_OtherFunctions.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.4

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
#include "Rubik_Engine.h"

Cube_T Rubik_Engine::randomize(uint16_t NoInterations) noexcept {
       mt19937 RandBase(chrono::steady_clock::now().time_since_epoch().count());

       uniform_real_distribution<float> ClockWiseOrOtherWise(0.0, 1.0);
       bernoulli_distribution isClockWise(ClockWiseOrOtherWise(RandBase));
       uniform_int_distribution<Layer_T> Layer(0, 2);                //Enum SpinBlocksAt
       uniform_int_distribution<CubeSideSize_T>  Level(0, this->SideSize-1);

       while (NoInterations) {
             --NoInterations;
             this->spin(SpinTo_T(static_cast<SpinBlocksAt>(Layer(RandBase)),
                        Level(RandBase),
                        static_cast<TurnBlock>(isClockWise(RandBase))));
       }

       return this->Cube;
}

void Rubik_Engine::operator()(const Rubik_Engine& OriCube) noexcept {
     if (OriCube.TofBlocks == this->TofBlocks) {
        this->Cube.clear();

        this->XYZ[LAYER] = 0;
        do {
            this->XYZ[LINE] = 0;
            do {
                this->XYZ[COLUMN] = 0;
                do {
                    this->Cube.emplace_back(OriCube.Block_OriginalPosition(XYZ), OriCube.Block_FacesList(XYZ));
                } while (++this->XYZ[COLUMN] != this->SideSize);
            } while (++this->XYZ[LINE] != this->SideSize);
        } while (++this->XYZ[LAYER] != this->SideSize);
     }
}

void Rubik_Engine::reset() noexcept {
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
