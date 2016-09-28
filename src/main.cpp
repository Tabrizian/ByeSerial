#include <iostream>
#include <cstring>
#include <cstdlib>

#include "serial/serial.h"

using namespace std;

uint8_t* hexToInt(char *arr, int len){
    int halfOfLen = len / 2;
    uint8_t res[halfOfLen];
    for(int i = 0; i < halfOfLen; i++) {
        char token[2];
        sprintf(token, "%.*s", 2, arr);
        int number = (int) strtol(token, NULL, 16);
        res[i] = number;
        cout << "i is " << i << " : " << number << endl;
        arr = arr + 2;
    }
}

int main(int argc, char **argv) {
    serial::Serial serial("/dev/ttyUSB0", 9600,
            serial::Timeout::simpleTimeout(1000));

    if(argc == 2) {
        int sizeOfData = strlen(argv[1]);
        uint8_t* readyToWrite = hexToInt(argv[1], sizeOfData);
        serial.write(readyToWrite, sizeOfData / 2);
        serial.flush();
    } else if (argc == 3) {
        if(strcmp(argv[0], "-r") == 0) {
            string read = serial.read(atoi(argv[1]));
            cout << read;
        }
    }
    serial.close();
}
