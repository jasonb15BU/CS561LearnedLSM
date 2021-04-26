initialize with:
g++ -o LSMLearned LSMLearned.cpp

run with:
./learnLSM.exe

fileSize: size of first file
levels: number of levels (each one exponentially larger than the last by power of fileSize)

recommended: fileSize 4, levels 15

inputs:

tests:
linear -> does a linear regression learned search on the data (2 million points)
binary -> does binary search on data (2 million points)


exit -> exit the program