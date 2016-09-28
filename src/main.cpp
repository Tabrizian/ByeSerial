#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "serial/serial.h"

using namespace std;

void hexToInt(char *arr, int len, uint8_t* result){
    int halfOfLen = len / 2;
    for(int i = 0; i < halfOfLen; i++) {
        char token[2];
        sprintf(token, "%.*s", 2, arr);
        int number = (int) strtol(token, NULL, 16);
        result[i] = number;
        arr = arr + 2;
    }
}

void intToHex(string bytesArray) {
    int len = bytesArray.length();
    for(int i = 0; i < len; i++) {
        printf("%02x\n", (int) bytesArray[i]);
    }
}

int main(int argc, char **argv) {
    serial::Serial serial("/dev/ttyUSB0", 9600,
            serial::Timeout::simpleTimeout(100));

    if(argc == 3) {
        int sizeOfData = strlen(argv[1]);
        uint8_t result[sizeOfData / 2];
        hexToInt(argv[1], sizeOfData, result);
        serial.write(result, sizeOfData / 2);
        serial.flush();
        string toRead;
        int dataRead = serial.read(toRead, atoi(argv[2]));
        intToHex(toRead);
    }
    serial.close();

    return 0;
}
