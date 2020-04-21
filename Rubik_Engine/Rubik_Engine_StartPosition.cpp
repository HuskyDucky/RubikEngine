/**
    File    : Rubik_Engine_StartPosition.cpp
    Author  : Menashe Rosemberg
    Created : 2020.03.10            Version: 20200316.3.3

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
//#include "Rubik_Engine.h"
//
//LofTurns_T Rubik_Engine::TurnCubeToStartPosition() noexcept {
//           LofTurns_T TurningCube;
//
//           if (this->SideSize % 2) {
//
//               NofSteps_T spins2Make = 0;
//               SpinTo_T Spin2(LINE,                                     //Spin2.Layer      - prepare to rotate horizontally
//                             (this->SideSize - 1) / 2,                  //Spin.Level       - reference the middlest layer. It won't change
//                              CLOCKWISE);                               //Spin.isClockWise - direction to rotate
//
//               auto TurnOtherBlocks = [&]() {      //it is cheaper rotate the others blocks after found the block position
//                                       for (; spins2Make; --spins2Make) {
//                                            TurningCube.emplace_back(Spin2.Layer, Spin2.isClockWise);
//
//                                            CubeSideSize_T level = 0;
//                                            do {
//                                                 if (level != Spin2.Level)      //exclude the middlest layer. It is in position already
//                                                     this->spin(Spin2.Layer, level, Spin2.isClockWise);
//                                            } while (++level != this->SideSize);
//                                       }
//               };
//
//               //Positioning Central block of Front Face (White block)
//                    Coord_T BlkFace = {Spin2.Level, Spin2.Level, 0};          //Central block position
//
//                    for (; !this->isBlockInPosition(BlkFace) && spins2Make < 4; ++spins2Make) //Front central block is in position? (white)?
//                         this->spin(Spin2);
//
//                    switch (spins2Make) {
//                           case 3: //White block is at left face
//                                   Spin2.isClockWise = COUNTERCLOCKWISE;
//                                   spins2Make = 1;
//                                   break;
//                           case 4: //White block is not in front, right, back or left faces
//                                   Spin2.Layer = COLUMN;                       //Prepare to rotate vertically
//                                   this->spin(Spin2);                          //try Top --- TurnBlock::CLOCKWISE
//                                   if (!this->isBlockInPosition(BlkFace)) {    //White block isn't in top then it is in bottom
//                                       Spin2.isClockWise = COUNTERCLOCKWISE;   //prepare to rotate to bottom
//                                       this->spin(Spin2);                      //return to Original position
//                                       this->spin(Spin2);                      //Bottom
//                                       }
//                                   spins2Make = 1;
//                    }
//                    TurnOtherBlocks();
//
//               //Positioning Central block of LEFT Face (Blue block)
//                    BlkFace = {Spin2.Level, 0, Spin2.Level};                      //Central block position at LEFT face
//                    Spin2.Layer = LAYER;                                          //Prepare to rotate axially
//
//                    for (spins2Make = 0; !this->isBlockInPosition(BlkFace) && spins2Make < 4; ++spins2Make) //Left central block is in position? (blue)
//                         this->spin(Spin2);
//
//                    if (spins2Make == 3) {
//                        Spin2.isClockWise = !Spin2.isClockWise;
//                        spins2Make = 1;
//                    }
//
//                    TurnOtherBlocks();
//
//                //The others central blocks are in position already :)
//           }
//
//           return TurningCube;
//}
