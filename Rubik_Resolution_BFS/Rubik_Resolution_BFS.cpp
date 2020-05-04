/**
    File    : Rubik_Resolution_BFS.cpp
    Author  : Menashe Rosemberg
    Created : 2020.02.06            Version: 20200503.2.1

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
#include "Rubik_Resolution_BFS.h"

BFS_ResolveThe::BFS_ResolveThe(const Rubik_Engine& cube) : Cube(cube),
                                                           SpinsListBase(this->GenerateListOfMoves()),
                                                           Steps(1, this->SpinsListBase.size()) {}  //Create the first level of the tree (first leaves)

ListBaseOfSpins_T BFS_ResolveThe::GenerateListOfMoves() const noexcept {
                  ListBaseOfSpins_T PossiblesSpins;

                  constexpr uint8_t MinOfPossibleMoves =  18;
                  PossiblesSpins.reserve(MinOfPossibleMoves * ((this->Cube.SidesSize() - (this->Cube.SidesSize() % 2)) / 2));

                  CubeSideSize_T Level = this->Cube.SidesSize();

                  do {--Level;
                      bool Direction = COUNTERCLOCKWISE; //false
                      do {
                          for (SpinBlocksAt layer = LINE; layer != NOSPIN; layer = SpinBlocksAt(layer +1))
                              PossiblesSpins.emplace_back(layer, Level, Direction);
                      } while ((Direction = !Direction));
                  } while (Level);

                  return PossiblesSpins;
}

bool BFS_ResolveThe::LeavesIteration() noexcept {
     this->Steps.back() = this->SpinsListBase.size();   //Reset leaf

     do { --this->Steps.back();
            this->Cube.spin(this->SpinsListBase[this->Steps.back()]);

            if (this->Cube.isFinished()) {
                this->DSteps2Solution = this->Steps;
                  return false;
            }

            this->Cube.spinback(this->SpinsListBase[this->Steps.back()]);

     } while (this->Steps.back());

    return true;
}

void BFS_ResolveThe::BranchesInteration() noexcept {
     if (this->Steps.size() > 1) { //tree has branches
         Steps_T Idx = this->Steps.size() - 1;
         do {
            this->Cube.spinback(this->SpinsListBase[this->Steps[--Idx]]);

            if (--this->Steps[Idx]) {
                do {
                    this->Cube.spin(this->SpinsListBase[this->Steps[Idx]]);
                } while (++Idx < this->Steps.size() - 1);

                return;
            }

            this->Steps[Idx] = this->SpinsListBase.size() - 1;      //Reset branch

         } while (Idx);
     }

     //reach the base of tree.
     this->Steps.back() = this->SpinsListBase.size() - 1;           //Turn leaves in branch
     for (auto& step : this->Steps)
          this->Cube.spin(this->SpinsListBase[step]);

     this->Steps.emplace_back(this->SpinsListBase.size());          //Create new leaves
}

LofSpins_T BFS_ResolveThe::Now() noexcept {
           if (!this->Cube.isFinished())
                while (this->LeavesIteration())
                       this->BranchesInteration();

           return this->CreateSolutionSteps();
}

LofSpins_T BFS_ResolveThe::CreateSolutionSteps() const noexcept {
           LofSpins_T LofSpins;
           LofSpins.reserve(this->DSteps2Solution.size());

           for (auto& step : this->DSteps2Solution)
                LofSpins.emplace_back(this->SpinsListBase[step]);

           return LofSpins;
}
