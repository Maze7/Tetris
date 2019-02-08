# GameCollection
Firstly, this project was designed to be a Tetris Remake in C++ for one of our University exams. 
We expanded it to a little GameCollection. 

The main "feature" is still Tetris, but we programmed Snake and FlappyBird as well. 

You can add your own games to it, see "Contribution"for more explanation.

## Build

**Linux**

You have to install sfml first.

ArchLinux: `pacman -S sfml`¸

Ubuntu: `apt install libsfml-dev`

*Sample Ubuntu 14.04 explanation: http://seriousitguy.blogspot.com/2014/05/how-to-setup-sfml-on-ubuntu-1404-lts.html*

```
git clone https://github.com/Maze7/Tetris
cd Tetris
./autogen.sh && make all
```
Copy the content of "static" from our fileserver into your local static directory. 
Run it with `./GameCollection`. You need xdg to open the help file. 

**MAC OS**

Install sfml with brew:
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew install sfml
g++ 
```

The last command should't work and you will asked if you want to install XCode. Click on "Install". 
Now you can clone this repo and compile it. 

```
git clone https://github.com/Maze7/Tetris
cd Tetris
./autogen-mac.sh && make all
```

**Windows**

We do not provide an buildfile (like cmake) for windows. But it is fully compatible. 
- Clone this repo and import files as a "new project from existing code" in Visual Studio.
- Install SFML-32 (sample tutorial: https://www.youtube.com/watch?v=axIgxBQVBg0) 
- Change your subsystem to None/Console
- compile

# Contribution
Follows // TODO

# Site note
Due to an unclear copyright situation, most files in "static" directory wasn't published. Maybe one day they will be uploaded. See [this issue](https://github.com/Maze7/Tetris/issues/56) for further informations.
