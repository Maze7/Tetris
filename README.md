# GameCollection
Firstly this project was designed to be a Tetris Remake in C++ for one of our University exams. 
We expanded it to a little GameCollection. 

The main "feature" is still Tetris, but we programmed Snake and FlappyBird as well. 

You can add your own games to it, see "Contribution"for more explanation.

## Build (Linux)
### SFML
You have to install sfml first.
ArchLinux: `pacman -S sfml`
Sample Ubuntu explanation: http://seriousitguy.blogspot.com/2014/05/how-to-setup-sfml-on-ubuntu-1404-lts.html

```
git clone https://github.com/Maze7/Tetris
cd Tetris
./autogen.sh && ./autogen.sh
make all
```
Run it with `./GameCollection`. You need xdg to open the help file. 


**Windows**

We do not provide an buildfile (like cmake) for windows. But it is fully compatible. 
- Clone this repo and import files as a "new project from existing code" in Visual Studio.
- Install SFML-32 (sample tutorial: https://www.youtube.com/watch?v=axIgxBQVBg0) 
- Change your subsystem to None/Console
- fin

# Contribution
Follows // TODO

# Site note
Due to an unclear copyright situation, the most files in "static" directory wasn't published. Maybe one day they will be uploaded. 
