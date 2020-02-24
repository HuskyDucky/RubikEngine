# RubikCube
RubikCube simulation including randomizing flips.

written on gcc 9.2.

### Cube commands

## Scanning a real cube
  `rubik::scan`   -> scan a cube's face
  
  `rubik::commit` -> update the cube with the scanned faces
  
## Moving layers
  `rubik::flip` -> move the cube's blocks
  
## Cube's status
  `rubik::isFinished`   -> Indicate if the cube is finished (blocks original position)

  `rubik::PercentalDone`-> Indicate how much of the cube's blocks are in the right position

  `rubik::==(rubik)`    -> Compare two cubes

## Blocks info
  `rubik::isBlockInPosition`      -> Inform it the block in the informed coordenate is in the original position

  `rubik::Block_FacesList`        -> Return a list of the blockś faces in their position on the block

  `rubik::Block_OriginalPosition` -> Return the original position of a block in the informed coordenate
  
## General commands
  `rubik::randomize`  -> Randomize the cube

  `rubik::(rubik)`    -> Copy a cube

  `rubik::reset`      -> The cube's blocks return to their original positions
  
