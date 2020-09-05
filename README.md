# Huffman
A console application that encodes and decodes data using the Huffman algorithm

## Build
The cmake system is used to build the project. The user just needs to specify the name of the file to be built after the command and call the make command after that
## Usage
The application supports 2 main functions: encode information and decode. Example of how the encoding command works:
```
$ ./Huffman_archiver -c -f test_file.txt - o encdoed_information.bin
```
15678 
6172
482
Source file size (source data): 15678 bytes, compressed data size (without additional information): 6172 bytes, additional data size: 482 bytes. Total compressed file size: 6172 + 482 = 6654 bytes.

Example of how the decoding command works:
```
$ ./Huffman_archiver -u -f encdoed_information.bin -o data.txt
```
6172
15678
482
In addition to the application itself, a testing system is implemented that runs on the command
```
$ ./Huffman_archiver_test
```
