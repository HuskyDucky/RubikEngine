# RubikEngine
Rubik_Engine simulate a Rubik Cube

compiled on gcc 9.3

### Cube commands

## Scanning a real cube
  `Rubik_Engine::scan`   -> scan a cube's face
  
  `Rubik_Engine::commit` -> update the cube with the scanned faces
  
## Moving layers
  `Rubik_Engine::flip` -> move the cube's blocks

  `Rubik_Engine::TurnCubeToStartPosition` -> Turn the the cube to it initial position
  
## Cube's status
  `Rubik_Engine::isFinished`   -> Indicate if the cube is finished (blocks original position)

  `Rubik_Engine::PercentalDone`-> Indicate how much of the cube's blocks are in the right position

  `Rubik_Engine::==(rubik)`    -> Compare two cubes

## Blocks info
  `Rubik_Engine::isBlockInPosition`      -> Inform it the block in the informed coordenate is in the original position

  `Rubik_Engine::Block_FacesList`        -> Return a list of the blockś faces in their position on the block

  `Rubik_Engine::Block_OriginalPosition` -> Return the original position of a block in the informed coordenate
  
## General commands
  `Rubik_Engine::randomize`  -> Randomize the cube

  `Rubik_Engine::(rubik)`    -> Copy a cube

  `Rubik_Engine::reset`      -> The cube's blocks return to their original positions
  
