/**
    File    : Rubik_Cube.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20191207.2

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

#include "Rubik_run_AuxFuncs.h"

void Rubik::operator()(const Rubik& OriCube) {
     if (OriCube.TofBlocks == this->TofBlocks) {
        this->Cube.clear();
        for (this->XYZ[LAYER] = 0; this->XYZ[LAYER] < this->SideSize; ++this->XYZ[LAYER ])
            for (this->XYZ[LINE] = 0; this->XYZ[LINE] < this->SideSize; ++this->XYZ[LINE])
                for (this->XYZ[COLUMN] = 0; this->XYZ[COLUMN] < this->SideSize; ++this->XYZ[COLUMN])
                    this->Cube.emplace_back(OriCube.Block_OriginalPosition(XYZ),
                                            OriCube.Block_ColorsAndPositions(XYZ));
     }
}

bool Rubik::isFinished() const noexcept {
     QofBlocks_T Scan = 0;

     while (Scan < this->TofBlocks && Scan == this->Cube[Scan].OriginalBlockPosition()) ++Scan;

     return Scan == this->TofBlocks;
}

float Rubik::PercentualDone() const noexcept {
      QofBlocks_T Done = 0;

      for (QofBlocks_T Scan = 0; Scan < this->TofBlocks; ++Scan)
          if (Scan == this->Cube[Scan].OriginalBlockPosition())
             ++Done;

      return 100.0 * Done / this->TofBlocks;
}

bool Rubik::isBlockInPosition(const Coord_T& xyz) const noexcept {
     const QofBlocks_T Pos = this->Block_Coordenate(xyz);
     return Pos < this->TofBlocks && Pos == this->Cube[Pos].OriginalBlockPosition();
}

BlkPosition_T Rubik::Block_OriginalPosition(const Coord_T& xyz) const noexcept {
              return this->Cube[this->Block_Coordenate(xyz)].OriginalBlockPosition();
}

ColorPositionList_T Rubik::Block_ColorsAndPositions(const Coord_T& xyz) const noexcept {
                    return this->Cube[this->Block_Coordenate(xyz)].ColorsAndPositionsList();
}

BlkPosition_T Rubik::findNearestBlockWith(const vector<Color_E>&& colors, BlkPosition_T StartSearchPos) const noexcept {
              for (; StartSearchPos < this->TofBlocks; ++StartSearchPos)
                  if (this->Cube[StartSearchPos].HasColors(colors))   //N of colors also need to match to be true
                     return StartSearchPos;

              return Position_E::NONEPOSITION;
}

void Rubik::flip(const FlipBlocksAt Layer, const CubeSideSize_T Level, const TurnBlocks isClockWise) noexcept {

     if (Level < this->SideSize) {

        this->CurrLayer2Move = Layer;
        this->XYZ[Layer] = Level;     //Define which layer will be moved: Line, column or face(center)

        if (isClockWise) {
           Abs_Axis = CW_Abs_Axis;
           Ord_Axis = CW_Ord_Axis;
        } else {
           Abs_Axis = CCWAbs_Axis;
           Ord_Axis = CCWOrd_Axis;
        }

        CubeSideSize_T Block2Move = 0;
        do {
            const BlkPosition_T Coords0 = this->CalcBlockPosition(this->Next_Coords(0, Block2Move));
            const BlkPosition_T Coords1 = this->CalcBlockPosition(this->Next_Coords(1, Block2Move));

            Block NextBlock = this->Cube[Coords1];                                                     NextBlock.moveColors(this->CurrLayer2Move, isClockWise);
            this->Cube[Coords1] = this->Cube[Coords0];                                                 this->Cube[Coords1].moveColors(this->CurrLayer2Move, isClockWise);
            swap(NextBlock, this->Cube[this->CalcBlockPosition(this->Next_Coords(2, Block2Move))]);    NextBlock.moveColors(this->CurrLayer2Move, isClockWise);
            swap(NextBlock, this->Cube[this->CalcBlockPosition(this->Next_Coords(3, Block2Move))]);    NextBlock.moveColors(this->CurrLayer2Move, isClockWise);
            this->Cube[Coords0] = NextBlock;

            ++Block2Move;

        } while (Block2Move != this->SideSize-1);
        ///It doesn't work for cube 4x4 and so on. To do so the program needs to loop on the face's interval blocks
     }
}

Cube_T Rubik::randomize(uint16_t NoInterations) noexcept {
       mt19937 RandBase(chrono::steady_clock::now().time_since_epoch().count());

       uniform_real_distribution<float> ClockWiseOrOtherWise(0.0, 1.0);
       bernoulli_distribution isClockWise(ClockWiseOrOtherWise(RandBase));
       uniform_int_distribution<Direction_T> Layer(0, 2);                //Enum FlipBlocksAt
       uniform_int_distribution<CubeSideSize_T>  Level(0, this->SideSize-1);

       while (NoInterations) {
             --NoInterations;
             this->flip(static_cast<FlipBlocksAt>(Layer(RandBase)),
                        Level(RandBase),
                        static_cast<TurnBlocks>(isClockWise(RandBase)));
       }

       return this->Cube;
}


void Rubik::reset() noexcept {

     this->Cube.clear();

     BlkPosition_T BlockPos = 0;
     for (XYZ[LINE] = 0; XYZ[LINE] < this->SideSize; ++XYZ[LINE])
         for (XYZ[COLUMN] = 0; XYZ[COLUMN] < this->SideSize; ++XYZ[COLUMN])
             for (XYZ[LAYER] = 0; XYZ[LAYER] < this->SideSize; ++XYZ[LAYER]) {
                 vector<ColorPosition_T> ColorPos;

                 if (XYZ[LINE] == 0)
                    ColorPos.emplace_back(Color_E::WHITE, Position_E::FRONT);
                 else if (XYZ[LINE] == this->SideSize-1)
                         ColorPos.emplace_back(Color_E::YELLOW, Position_E::BACK);

                 if (XYZ[COLUMN] == 0)
                    ColorPos.emplace_back(Color_E::RED, Position_E::TOP);
                 else if (XYZ[COLUMN] == this->SideSize-1)
                         ColorPos.emplace_back(Color_E::ORANGE, Position_E::BOTTOM);

                 if (XYZ[LAYER ] == 0)
                    ColorPos.emplace_back(Color_E::BLUE, Position_E::LEFT);
                 else if (XYZ[LAYER ] == this->SideSize-1)
                         ColorPos.emplace_back(Color_E::GREEN, Position_E::RIGHT);

                 this->Cube.emplace_back(BlockPos++, move(ColorPos));
             }
}
