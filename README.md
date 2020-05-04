# RubikEngine
Rubik_Engine simulate a Rubik Cube

compiled on gcc 9.3

### Cube commands

## Scanning a real cube
  `Rubik_Engine::scan`   -> scan a cube's face
  
  `Rubik_Engine::commit` -> update the cube with the scanned faces
  
## Moving layers
  `Rubik_Engine::spin`     -> move the cube's blocks

  `Rubik_Engine::spinback` -> move back the cube's blocks
  
## Cube's status
  `Rubik_Engine::isFinished` -> Indicate if the cube is finished (blocks original position)

  `Rubik_Engine::==(rubik)`  -> Compare two cubes

## Blocks info
  `Rubik_Engine::Block_FacesList` -> Return the faces and colors of specific block
  
## General commands
  `Rubik_Engine::randomize`       -> Randomize the cube

  `Rubik_Engine::operator()`      -> Copy a cube

  `Rubik_Engine::reset`      -> The cube's blocks return to their original positions
  
