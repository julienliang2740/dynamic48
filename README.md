## Dynamic48

This is an augmented version the game 2048 built with C++. On top of the original game play, this implementation can:

- **Rotate** the board

- **Flip** the board

- **Scale dimensions** of board

To run (number for dimensions parameter is optional, defaults to 4):
```
g++ -o 2048 play.cc game.cc
./2048 <dimensions>
```

## Commands:
```
"w" or "up"
"a" or "down"
"s" or "left"
"d" or "right"
"p" or "print"
"q" or "quit"
"flipx"
"flipy"
"rotateleft"
"rotateright"
```

## Demo:
**Original Board**

**Rotate Clockwise**

**Flip Up**

**Flip Sideways**

(original: https://play2048.co/)
