/**
    File    : Rubik_Engine_ScanFaces_CreateProtoCube.cpp
    Author  : Menashe Rosemberg
    Created : 2019.12.09            Version: 20200125.2.1

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
#include "Rubik_Engine_ScanFaces.h"

ProtoCube_T ClassScanFaces::ScanFaces::CreateProtoCube() const noexcept {
            ProtoCube_T ProtoCube(pow(this->SideSize, 3), FaceList_T());
            //Associate the the scanned faces - colors - with the proto blocks (this->ScannedFaces)
            FacePosition_E Face = FRONT;
            do {
                BlocksPosToFace_T BlockPosList = this->BlocksPositionsToThe(Face);
                QofBlksPerFace_T IIt = BlockPosList.size();
                do {--IIt;
                    ProtoCube[BlockPosList[IIt]].emplace_back(this->ScannedFaces[Face][IIt], Face);
                } while (IIt != 0);
            } while ( (Face = FacePosition_E(Face + 1)) != NONEPOSITION);

    return ProtoCube;
}

BlocksPosToFace_T ClassScanFaces::ScanFaces::BlocksPositionsToThe(const FacePosition_E Face) const noexcept {
                  CubeSideSize_T CPIPC = this->ColorPositionOnProtoCube[Face];
                  auto setInitialCoord = [&](uint8_t Bit) -> CubeSideSize_T { if (~CPIPC & (1 << Bit) && (CPIPC & 1))
                                                                                 return this->SideSize-1;
                                                                              return 0;
                                                                            };
                  Coord_T xyz { setInitialCoord(3),     //Layer = 8
                                setInitialCoord(2),     //Col   = 4
                                setInitialCoord(1) };   //Lin   = 2

                  if (Face == BACK || Face == BOTTOM)
                     swap(xyz[LIN], xyz[LAY]);

                  BlocksPosToFace_T ColorsPosList; ColorsPosList.reserve(TofFACES);

                  CubeSideSize_T IIt = 0;
                  do {
                      ColorsPosList.emplace_back(this->Block_Coordenate(xyz));
                      //cout << "\nx=" << static_cast<uint16_t>(xyz[LIN]) <<  " y=" << static_cast<uint16_t>(xyz[COL]) <<  " z=" << static_cast<uint16_t>(xyz[LAY]) << " BlockPos= " << ColorsPosList.back();

                      if (CPIPC & BitCOL) {
                         if (++xyz[COL] == this->SideSize) {
                            xyz[COL] = 0;
                            if (CPIPC & BitLIN)
                                ++xyz[LIN];
                            else
                                ++xyz[LAY];
                         }
                      } else if (CPIPC & BitLAY && ++xyz[LAY] == this->SideSize) {
                                xyz[LAY] = 0;
                                ++xyz[LIN];
                      }
                  } while (++IIt < this->FaceSize);

    //cout << '\n';
    return ColorsPosList;
}
