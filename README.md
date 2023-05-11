# Key-Value Pair Storage System
This program provides a basic Key-Value pair storage system with the ability to add, edit, and remove key-value pairs from a .txt file.

## Requirements
- C++ compiler (g++ recommended)

## Getting Started
To start the program, navigate to the directory containing the program and enter the following command into the terminal:

```
g++ -o main main.cpp
./main
```

## Usage
Upon running the program, you will be prompted with whether you would like to open a new file or update an existing one. If you choose to open a new file, you will be prompted to name the file and then to add key-value pairs to the file. If you choose to update an existing file, you will be prompted to enter the name of the file you wish to update. Once the file has been opened, you will be able to add, edit, or remove key-value pairs as desired.

## Commands
The program accepts the following commands:

- <samp>a</samp> : add a new key-value pair
- <samp>e</samp> : edit an existing key-value pair
- <samp>del</samp> : remove an existing key-value pair
- <samp>q</samp>: quit the program

## Example
```
Are you wanting to open a new File or update and existing File? new
Ok, so a new File then. What would you like to call it? my_file.txt
Ok, lets start adding Key-Value Pairs
Key: name
Value: John
Notha one?(y/n) y
Key: age
Value: 30
Notha one?(y/n) n
Thank you for using my Storage System
```