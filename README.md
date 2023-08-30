## This project uses gtest

It expects to have on the project root a directory called `googletest`
You can just git pull gtest repo to googletest

## Format doc in clion

`command + option + L`

## Wrap around iteration

modulo always returns the 0 if left of operand is evenly divisible by right side otherwise it returns
the remainder 15 % 5 = 0 but 15 % 6 is 3. This allows us to create a boundary around any incrementally
bumped numbers. Because, every time you increment until you hit a multiple of 5, like 25 30 etc, you go
back to 0.
```
1 % 5 == 1
2 % 5 == 2
3 % 5 == 3
4 % 5 == 4
5 % 5 == 0
6 % 5 == 1
7 % 5 == 2
8 % 5 == 3
9 % 5 == 4
10 % 5 == 0
backwards
0 % 5 == 5
```
