# BinDB
**Disclaimer:** This project is for educational purpose only. Feel free to use
anything here, but be warned that nothing is guaranteed to be production ready.

BinDB implements a very simple database having its own query language and
storage model.

## Table of Contents
- [Features](#features)
- [Build](#build)

## Features
- **Query Language:** Custom query language by implementing a lexer and
  abstract syntax tree.

## Build
To build BinDB you first have to get the source code by cloning the repository.

    git clone ssh://git@github.com/flohansen/bindb

To build the BinDB binary you just have to run

    make

This will compile the project into the binary `bindb`.
