# Kerschek
## _License Plate Detector, A Good One !_

Kerschek is a fast and robust C application to detect french license plates in images.

## Features

- Load Image and detect License Plate
- Load Video and perform Motion Detection

## Requirements

Kersheck is developped under _Linux_, and  uses a few softwares to make the plate detection possible :

- [Simple DirectMedia Layer]
- [FFmpeg] - Video converter
- [MPlayer] - Video player
- [Gocr] - GNU's Optical character recognitoion software

## Installation
Kerschek requires [Make](https://www.gnu.org/software/make/) to run.
```bash
#Go to the root of the repository
$ cd projet_s4_epita

#Build the project
$ make kerschek

#Go to the binaries folder
$ cd src/bin

#Launch the application
$ ./kerschek
```

[//]:#

   [FFmpeg]: <https://ffmpeg.org/>
   [Mplayer]: <https://mplayerhq.hu/>
   [Gocr]: <http://jocr.sourceforge.net/>
   [Simple DirectMedia Layer]: <https://www.libsdl.org/>