/**
    File    : Rubik_Resolution_General_Tests.cpp
    Author  : Menashe Rosemberg
    Created : 2019.11.15            Version: 20200421.2

    Test Rubik Engine

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
#include "../Rubik_Engine/Rubik_Engine.h"
#include "../Lib/Test.h"

bool Test_Spin3x3x3(Rubik_Engine& Cube,
                    const SpinBlocksAt Layer,
                    const uint8_t OnceTwiceThrice, function<bool(Rubik_Engine&)> Avail,
                    const bool ShowPassFail) {
     const array< const array<const string,3>,3> Description_LayerLevel = {
                        array<const string,3>({"upper", "central", "lower"}),  //LINE
                        array<const string,3>({"left" , "middle" , "right"}),  //COLUMN
                        array<const string,3>({"front", "central", "back"}) }; //LAYER
     auto Description_LayerName = [](const uint8_t L) -> const string {
          switch (L) {
                 case 0 : return string("line");
                 case 1 : return string("column");
                 default: return string("layer");
          }; };
     const array<const array<const string,2>,3> Description_SpinDirection = {
                       array<const string,2>({"right", "left"}),      //LINE
                       array<const string,2>({"up",    "down"}),      //COLUMN
                       array<const string,2>({"right", "left"}) };    //LAYER

     bool Result = true;
     bool isClockWise = false;
     for (CubeSideSize_T level = 0; level < 3; ++level)
          do {
              uint8_t OTT = OnceTwiceThrice;
              string Msg = "Spin " + Description_LayerLevel[Layer][level] + " " +
                                     Description_LayerName(Layer) + " " +
                                     Description_SpinDirection[Layer][isClockWise] +
                                     " Spinned " + to_string(OnceTwiceThrice);
              if(Msg.size() < 34) Msg.insert(Msg.size(), 34 - Msg.size(), ' ');
              Test_StepCounterMsg(Msg);
              Cube.reset();
              do {
                  Cube.spin(Layer, level, isClockWise);
              } while (--OTT);

              bool result = Avail(Cube);
              if (ShowPassFail)
                  cout << (result?"pass":"fail") << flush;
              Result &= result;

          } while ((isClockWise = !isClockWise));

      return Result;
}
