# Facecatch

This program allows you to detect a face on a picture.
[Viola And Jones original paper](https://www.cs.cmu.edu/~efros/courses/LBMV07/Papers/viola-cvpr-01.pdf)

## Getting Started

### Prerequisites

This program has been tested with the following environment

```
GCC 6.3.1
SDL library 1.2.15
GTK+2.0
```

### Usage

For the GUI:

```
cd src/
make
./main
```

For the CLI:

```
cd src/
make facecatch
./facecatch PICTURE
```

## Description

Once executed, the program loads an interface. It will help you load images
and add them to the database. Once added, the program will ask you the name
of the person and will display the image. You then have to press any key to
launch the analysis of the image. After a short period of time, the picture
will refresh with the 3 most probable positions of a face in the picture.

## Cleaning

To remove all the compiled files:

```
make clean
```

## Authors

A program made by 44lointain:
- DEWOLF Valentin
- FORESTIER Francois
- HINSBERGER Agathe
- IDE Mickael


Thank you for using our program.
