/**
    File    : Rubik_Engine_ScanFaceCall.cpp
    Author  : Menashe Rosemberg
    Created : 2019.10.22            Version: 20200222.3

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

bool Rubik_Engine::scan(const FacePosition_E Face, vector<Color_E>&& Colors) noexcept {
     if (this->ScannedFaces.get() == nullptr)
        this->ScannedFaces.reset(new ScanFaces(this->Cube, this->Block_Coordenate));

     return this->ScannedFaces->scan(Face, move(Colors));
}

bool Rubik_Engine::commitScannedFaces() noexcept {
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

void Rubik_Engine::ReleaseScannedFaces() noexcept {
    if (this->ScannedFaces.get() != nullptr) {
       ScanFaces* ptr = ScannedFaces.release();
       delete ptr;
    }
}
