/**
    File    : Rubik_Cube.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191115.1

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

Rubik::Rubik() : CubeSize(3), QTofBlocks(pow(CubeSize, 3)) {

                 if (this->CubeSize > 2 && this->CubeSize < numeric_limits<CubeSize_T>::max()) {
                    const BlockPosition_T NofBlocks = pow(this->CubeSize, 3);
                    this->CubeRandomized.reserve(NofBlocks);
                    this->Cube.reserve(NofBlocks);

                    this->Reset();

                    this->CubeRandomized = this->Cube;

                 } else {
                   puts("\n\nRubik has at least 3 blocks size to every face\n");
                   abort();
                 }
}


Cube_T Rubik::CurrentBlocksPositions() const noexcept { return this->Cube; }


bool Rubik::isFinished() const noexcept {
     QTofBlocks_T Scan = 0;

     while (Scan < this->QTofBlocks && Scan == this->Cube[Scan].OriginalBlockPosition()) ++Scan;

     return Scan == this->QTofBlocks;
}


float Rubik::PercentDone() const noexcept {
      QTofBlocks_T Done = 0;

      for (QTofBlocks_T Scan = 0; Scan < this->QTofBlocks; ++Scan)
          if (Scan == this->Cube[Scan].OriginalBlockPosition())
             ++Done;

      return 100.0 * static_cast<float>(Done) / this->QTofBlocks ;
}

inline BlockPosition_T Rubik::CalcBlockPosition_Formula() noexcept {
       return this->XYZ[0] * this->CubeSize +                           //Line
              this->XYZ[1] +                                            //Column
              this->XYZ[2] * this->CubeSize * this->CubeSize;           //Layer
}

BlockPosition_T Rubik::BlockPosition(const CubeSize_T xyz[3]) const noexcept {
                return xyz[0] * this->CubeSize +                         //Line
                       xyz[1] +                                          //Column
                       xyz[2] * this->CubeSize * this->CubeSize;         //Layer
}

BlockPosition_T Rubik::CalcBlockPosition(const AxisAOPosition_T AxesAO) noexcept {
                switch (this->CurrLayer2Move) {
                       case FlipBlocksAt::LINE   :
                            this->XYZ[FlipBlocksAt::COLUMN] = AxesAO.first;
                            this->XYZ[FlipBlocksAt::LAYER ] = AxesAO.second;
                            break;
                       case FlipBlocksAt::COLUMN :
                            this->XYZ[FlipBlocksAt::LINE  ] = AxesAO.second;
                            this->XYZ[FlipBlocksAt::LAYER ] = AxesAO.first;
                            break;
                       default:
                            this->XYZ[FlipBlocksAt::LINE  ] = AxesAO.first;
                            this->XYZ[FlipBlocksAt::COLUMN] = AxesAO.second;
                }

                return this->CalcBlockPosition_Formula();
}

AxisAOPosition_T Rubik::Next_Coords(const CubeSize_T CubeFace, const CubeSize_T BlockNo) const noexcept  {
                 AxisAOPosition_T AxesAO = { (*&Abs_Axis[CubeFace]).first,
                                             (*&Ord_Axis[CubeFace]).first };

                 if (AxesAO.first < this->Abs_Axis[CubeFace].second)
                     AxesAO.first += BlockNo;
                 else if (AxesAO.first > this->Abs_Axis[CubeFace].second)
                          AxesAO.first -= BlockNo;

                 if (AxesAO.second < this->Ord_Axis[CubeFace].second)
                     AxesAO.second += BlockNo;
                 else if (AxesAO.second > this->Ord_Axis[CubeFace].second)
                          AxesAO.second -= BlockNo;

                 return AxesAO;
}

void Rubik::Flip(const FlipBlocksAt Layer, const CubeSize_T Level, const TurnBlocks isClockWise) noexcept {

     if (Level < this->CubeSize) {

        this->CurrLayer2Move = Layer;
        this->XYZ[Layer] = Level;     //Define which layer will be moved: Line, column or face(center)

        if (isClockWise) {
           Abs_Axis = CW_Abs_Axis;
           Ord_Axis = CW_Ord_Axis;
        } else {
           Abs_Axis = CCWAbs_Axis;
           Ord_Axis = CCWOrd_Axis;
        }

        CubeSize_T Block2Move = 0;
        do {
            const BlockPosition_T Coords0 = this->CalcBlockPosition(this->Next_Coords(0, Block2Move));
            const BlockPosition_T Coords1 = this->CalcBlockPosition(this->Next_Coords(1, Block2Move));

            Block NextBlock = this->Cube[Coords1];                                                     NextBlock.moveColors(this->CurrLayer2Move, isClockWise);
            this->Cube[Coords1] = this->Cube[Coords0];                                                 this->Cube[Coords1].moveColors(this->CurrLayer2Move, isClockWise);
            swap(NextBlock, this->Cube[this->CalcBlockPosition(this->Next_Coords(2, Block2Move))]);    NextBlock.moveColors(this->CurrLayer2Move, isClockWise);
            swap(NextBlock, this->Cube[this->CalcBlockPosition(this->Next_Coords(3, Block2Move))]);    NextBlock.moveColors(this->CurrLayer2Move, isClockWise);
            this->Cube[Coords0] = NextBlock;

            ++Block2Move;

        } while (Block2Move != this->CubeSize-1);
        ///It doesn't work for cube 4x4 and so on. To do so the program needs to loop on the face's interval blocks
     }
}

void Rubik::RecoverRandomizedCube() noexcept { this->Cube = this->CubeRandomized; }

Cube_T Rubik::Randomize(uint16_t NoInterations) noexcept {
       mt19937 RandBase(chrono::steady_clock::now().time_since_epoch().count());

       uniform_real_distribution<float> ClockWiseOrOtherWise(0.0, 1.0);
       bernoulli_distribution isClockWise(ClockWiseOrOtherWise(RandBase));
       uniform_int_distribution<Direction_T> Layer(0, 3);                //Enum FlipBlocksAt
       uniform_int_distribution<CubeSize_T>  Level(0, this->CubeSize);

       while (NoInterations) {
             --NoInterations;
             this->Flip(static_cast<FlipBlocksAt>(Layer(RandBase)),
                        Level(RandBase),
                        static_cast<TurnBlocks>(isClockWise(RandBase)));
       }

       this->CubeRandomized = this->Cube;

       return this->Cube;
}

Cube_T Rubik::Reset() noexcept {

       this->Cube.clear();

       BlockPosition_T BlockPos = 0;
       for (CubeSize_T z = 0; z < this->CubeSize; ++z)
           for (CubeSize_T y = 0; y < this->CubeSize; ++y)
               for (CubeSize_T x = 0; x < this->CubeSize; ++x) {
                   vector<ColorPosition_T> ColorPos;

                   if (z == 0)
                      ColorPos.emplace_back(Color::WHITE, PositioningOn::FRONT);
                   else if (z == this->CubeSize-1)
                           ColorPos.emplace_back(Color::YELLOW, PositioningOn::BACK);

                   if (y == 0)
                      ColorPos.emplace_back(Color::RED, PositioningOn::TOP);
                   else if (y == this->CubeSize-1)
                           ColorPos.emplace_back(Color::ORANGE, PositioningOn::BOTTOM);

                   if (x == 0)
                      ColorPos.emplace_back(Color::BLUE, PositioningOn::LEFT);
                   else if (x == this->CubeSize-1)
                           ColorPos.emplace_back(Color::GREEN, PositioningOn::RIGHT);

                   this->Cube.emplace_back(BlockPos++, move(ColorPos));
               }

       return this->Cube;
}
