# RubikCube
RubikCube simulation including randomizing flips.

written on gcc 9.2.

### Cube commands

## Scanning a real cube
  'rubik::scan'   -> scan a cube's face
  'rubik::commit  -> update the cube with the scanned faces
  
## Moving layers
  'rubik::flip' -> move the cube's blocks
  
## Cube's status
  'rubik::isFinished'   -> Indicate if the cube is finished (blocks original position)
  'rubik::PercentalDone -> Indicate how much of the cubeś blocks are in the right position
  
## General commands
  'rubik::randomize'  -> Randomize the cube
  'rubik::(rubik)'    -> Copy a cube
  'rubik::reset'      -> The cube's blocks return to their original positions
  
