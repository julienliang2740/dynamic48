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
![image](https://github.com/user-attachments/assets/73d8fa01-bbe1-4292-a52f-69110ee68016)

**Rotate Clockwise**
![image](https://github.com/user-attachments/assets/1f977e70-a25e-4d0f-a78d-f7264ba5cca7)

**Flip Up**
![image](https://github.com/user-attachments/assets/c3a37bf5-2152-42f9-bcc1-b048189e51c8)

**Flip Sideways**
![image](https://github.com/user-attachments/assets/7f3e2d2e-77a6-4eda-8a3b-e44e24f0e3d6)

(original: https://play2048.co/)
