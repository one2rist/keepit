# KEEPIT TASK

The complete C++ source code for a program that counts the number of distinct unique words in a file whose name is passed as an argument to a program.
For example, given the file content "a horse and a dog" the program must output "4" (the word 'a' appears twice but only accounts for one distinct unique occurrence).
The input text is guaranteed to contain only 'a'..'z' and space characters in ASCII encoding.
The program should be able to handle large inputs (e.g. 32 GiB)
You can assume that all unique words fit into memory when using the data structure of your choice.
The solution must utilize all available CPU resources.
## Generate input file

```bash
./gen.sh
#generates ~32GB text file with 1 000 000 unique words separated with space.
#Adjust script to have smaller input files
```

## Build
CMAKE 3.10, C++17


```bash
./build.sh
```

## Run
```bash
./build/keepit_app test.txt
```

## CLEAN BUILD and RUN with "a horse and a dog".txt
```bash
./run.sh
```
