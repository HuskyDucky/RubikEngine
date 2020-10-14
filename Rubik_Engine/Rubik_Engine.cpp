/**
    File    : Rubik_Engine.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20201014.1

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

Rubik_Engine::Rubik_Engine() : SideSize(3),   //This class is not ready yet to more than 3 blocks per corner
                               TofBlocks(pow(SideSize, 3)) {
      this->Rubik_Engine_Initializer();

      this->reset();
}

Rubik_Engine::Rubik_Engine(const Rubik_Engine& OriCube) : SideSize(3),   //This class is not ready yet to more than 3 blocks per corner
                                                          TofBlocks(pow(SideSize, 3)) {
      this->Rubik_Engine_Initializer();

      this->operator()(OriCube);
}

void Rubik_Engine::Rubik_Engine_Initializer() noexcept {
     if (this->SideSize < 3 && this->SideSize < numeric_limits<CubeSideSize_T>::max()-2) {
        cout << "\n\nThis rubik cube can have 3 to " << static_cast<uint64_t>(numeric_limits<CubeSideSize_T>::max()-2) << " blocks size to every face only\n" << endl;
        abort();
     }

     //It could be a regular function but inheritaged class will use it by passing it as parameter (better than use friend)
     this->Block_Coordenate = [&](const Coord_T& xyz) -> BlkPosition_T {
                                                         return xyz[LINE  ] * this->SideSize +
                                                                xyz[COLUMN] +
                                                                xyz[LAYER ] * this->SideSize * this->SideSize;
     };
}

Rubik_Engine::~Rubik_Engine() { this->ReleaseScannedFaces(); }
