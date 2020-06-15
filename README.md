# Groebner Basis Lib
There is a small GroebnerLib manual.

## instal & launch
This one will create folder "GroebnerBasis" in current dirrectory.
```bash
git clone https://github.com/cdraugr/GroebnerBasis.git
```
In that folder you can write `make` at `GroebnerLib/`, it will create solved library: `GroebnerLib.a`.

## how to compile it

You can compile it like any other `.a` lib. (Example on `TestGroebnerLib/Makefile`)

`make clean`, `make fclean` and `make re` are included in bout folders.

## how to use it

Just write `include "PolynomialSet.h"` in your .cpp/.h file to use all `gb::` features.
