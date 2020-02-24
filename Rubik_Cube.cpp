/**
    File    : Rubik_Cube.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.1

    Rubik Program - Cube Definition

    Menashe Rosemberg   Israel +972-52-323-0538
    Copyright(c) 2019      All rights reserved.

    Software distributed under the MIT License is distributed on an "AS IS" BASIS,
    NO WARRANTIES OR CONDITIONS OF ANY KIND, explicit or implicit.
**/
#include "Rubik_Cube.h"

CubeSideSize_T Rubik::SidesSize() const noexcept { return this->SideSize; }
QofBlocks_T Rubik::TotalOfBlocks() const noexcept { return this->TofBlocks; }

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

bool Rubik::operator==(const Rubik& CompCube) noexcept {
     if (CompCube.TotalOfBlocks() == this->TofBlocks) {
        this->XYZ[LAYER] = 0;
        do {
            this->XYZ[LINE] = 0;
            do {
                this->XYZ[COLUMN] = 0;
                do {
                    if (this->Cube[this->Block_Coordenate(XYZ)] != CompCube.Block_FacesList(XYZ))
                        return false;
                } while (++this->XYZ[COLUMN] < this->SideSize);
            } while (++this->XYZ[LINE] < this->SideSize);
        } while (++this->XYZ[LAYER] != this->SideSize);
     }

     return true;
}

bool Rubik::isBlockInPosition(const Coord_T& xyz) const noexcept {
     const QofBlocks_T Pos = this->Block_Coordenate(xyz);
     return Pos < this->TofBlocks && Pos == this->Cube[Pos].OriginalBlockPosition();
}

BlkPosition_T Rubik::Block_OriginalPosition(const Coord_T& xyz) const noexcept {
              return this->Cube[this->Block_Coordenate(xyz)].OriginalBlockPosition();
}

FaceList_T Rubik::Block_FacesList(const Coord_T& xyz) const noexcept {
           return this->Cube[this->Block_Coordenate(xyz)].FacesList();
}

void Rubik::flip(const FlipBlocksAt Layer, const CubeSideSize_T Level, const TurnBlocks isClockWise) noexcept {
     this->flip(FlipTo_T(Layer, Level, isClockWise));
}
void Rubik::flip(const FlipTo_T& FlipThe) noexcept {

     if (FlipThe.Level < this->SideSize) {

        this->CurrLayer2Move = FlipThe.Layer;
        this->XYZ[FlipThe.Layer] = FlipThe.Level;   //Define which layer will be moved: Line, column or face(center)

        if (FlipThe.isClockWise) {
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

            Block NextBlock = this->Cube[Coords1];                                                     NextBlock.moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
            this->Cube[Coords1] = this->Cube[Coords0];                                                 this->Cube[Coords1].moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
            swap(NextBlock, this->Cube[this->CalcBlockPosition(this->Next_Coords(2, Block2Move))]);    NextBlock.moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
            swap(NextBlock, this->Cube[this->CalcBlockPosition(this->Next_Coords(3, Block2Move))]);    NextBlock.moveColors(this->CurrLayer2Move, FlipThe.isClockWise);
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

bool Rubik::scan(const FacePosition_E Face, vector<Color_E>&& Colors) noexcept {
     if (this->ScannedFaces.get() == nullptr)
        this->ScannedFaces.reset(new ScanFaces(this->Cube, this->Block_Coordenate));

     return this->ScannedFaces->scan(Face, move(Colors));
}

bool Rubik::commitScannedFaces() noexcept {
     if (this->ScannedFaces.get() != nullptr) {
        ProtoCube_T ProtoCube = this->ScannedFaces->commitScannedFaces();
        if (ProtoCube.size()) {
           Cube_T NewCube;
           BlkPosition_T ProtoBlkIndex = 0;
           do {
               for (auto& oldBlock : this->Cube)
                   if (oldBlock.HasColors(ProtoCube[ProtoBlkIndex]) &&
                      none_of(NewCube.cbegin(), NewCube.cend(), [&](const Block& b) { return b.OriginalBlockPosition() == oldBlock.OriginalBlockPosition(); })) {
                      NewCube.emplace_back(oldBlock.OriginalBlockPosition(), move(ProtoCube[ProtoBlkIndex]));
                      break;
                   }

               if (ProtoBlkIndex != NewCube.size() - 1)
                  return false;

           } while (++ProtoBlkIndex != this->TofBlocks);

           this->Cube.swap(NewCube);

           this->ReleaseScannedFaces();
           return true;
        }
    }

    return false;
}

void Rubik::ReleaseScannedFaces() noexcept {
    if (this->ScannedFaces.get() != nullptr) {
       ScanFaces* ptr = ScannedFaces.release();
       delete ptr;
    }
}
