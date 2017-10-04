# README

Calculate the hypervolume of pareto front via Hypervolume by Slicing Objectives

## Compile

```bash
mkdir .build
cd .build
cmake ..
make
```

## Usage

```bash
./hypervolume path/to/file/path
```

## Input file

The input file contains all the sampled points, the Pareto front and the reference point would be extracted.

The input file looks like this:

```
-3 -1 -1
-1 -3 -1
0 0 0
-2 -2 -2
-1 -1 -3
```

and `0 0 0` would be the reference point.
