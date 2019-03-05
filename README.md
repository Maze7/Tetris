# GameCollection
Firstly, this project was designed to be a Tetris Remake in C++ for one of our University exams. 
We expanded it to a little GameCollection. 

The main "feature" is still Tetris, but we programmed Snake and FlappyBird as well. 

You can add your own games to it, see "Contribution" for more explanation.

## Build

**Linux**

Most package manager does have sfml in repositorys (warning, debian-stretch SFML version is too old, use SDK instead).

ArchLinux: `pacman -S sfml automake autoconf`¸

Ubuntu: `apt install libsfml-dev pkg-config dh-autoreconf`

Build dependencies for Debian/Ubuntu
```
./autogen.sh && make all
```
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
./autogen-mac.sh && make all
```

**Windows**
1. Import project into Visual Studio (2017) with given Tetris.sln and Tetris.vcxproj. 
2. Download SFML 32bit matching your visual studio version (ex. https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip) and copy it to your solution directory and name it SFML32.
3. Copy all .dll from SFML32/bin to your solution directory
Compile with release mode (Windows Subsystem) or in debug mode (Console Application).

## Installation 
You can download the release files from our archive. In every platform you need to download the static directory and put it along with the GameCollection binary.
In Windows, the DLL files (which are included in release archive) needs to be in the same directory too. 

Currently we does not have an installer for windows and no PKGBUILDS for linux, but maybe one day :)

(Additional Dependencies for minimal Server: libopenal1 libvorbis-dev)

## Contribution
TODO

## Credits
TODO

## License
TODO
