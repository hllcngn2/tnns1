# tnns
A game prototype using the SDL2 lib

### WIP
```
./a [prob/tile] [offset]
```
- First argument is the (floating point) probability for a single tile to contribute 1 to the vegetation pool. If it's set to 2, every single tile will contribute 2 to the pool.\
- Second argument can be -1 (random) or another, potentially 0, offset value (the piece of vegetation will be placed on the tile grid with an offset, it is scaled to ASPECT_RATIO, & should reasonably be between 0 and 15).\
If these arguments are not mentioned, default values will be used.

### usage
```
make hello
./a
make
./a
./a 1
./a 2 12
./a .15 -1
```
If the size of the prototype doesn't fit, you can change the ASPECT_RATIO (and window size, in tiles (and key bindings)) in tnns.h.

### controls
**0** : quit\
**g** : display grid\
**LSHIFT + wasd** : move camera
