# tnns
A game prototype using the SDL2 lib

### WIP
You can tune the amount / distribution of vegetation through the command line:
```
./a [prob/tile] [[offset]]
```
- The first argument is the (floating point) probability for a single tile to contribute 1 to the vegetation pool. If it's set to 2, every single tile will contribute 2 to the pool, effectively covering the map. Note that the distribution of vegetation is random, and a probability of 1 does not mean every tile will have vegetation on it.\
- The second argument can be -1 (completely random) or something else (the piece of vegetation will be on the tile grid with an offset). The latter is scaled to ASPECT_RATIO, and should reasonably be between 0 and 15.

### usage
```
make hello
./a
make
./a
./a 1
./a 1.5 0
./a 2 12
./a .8 6
./a .15 -1
```
If the size of the prototype doesn't fit you, you can change the ASPECT_RATIO (and window size, in tiles (and key bindings)) in tnns.h.

### controls
**0** : quit\
**g** : display grid\
**LSHIFT + wasd** : move camera
