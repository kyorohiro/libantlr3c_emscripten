# antlr3 's runtime C for emscripten

copy from http://www.antlr3.org/download/C/
and tiny modify


# BUILD Runtime
```
cd 3.4
ninja -f build.emcc.osx.ninja
```

# USE
```
antlr3 Calc.g
emcc -c CalcLexer.c -o CalcLexer.bc -I. -I/usr/local/Cellar/libantlr3c/3.4_1/include -DHAVE_MALLOC_H
emcc -c CalcParser.c -o CalcParser.bc -I. -I/usr/local/Cellar/libantlr3c/3.4_1/include -DHAVE_MALLOC_H
emcc -c test.c -o test.bc -I. -I/usr/local/Cellar/libantlr3c/3.4_1/include -DHAVE_MALLOC_H
emcc -o a.js test.bc CalcLexer.bc CalcParser.bc libantlr3c.bc -DHAVE_MALLOC_H -O2
```
