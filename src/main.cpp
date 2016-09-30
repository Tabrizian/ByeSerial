#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "serial/serial.h"

using namespace std;
serial::Serial serial_instance;

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
        printf("%02x", (int) bytesArray[i]);
    }
    printf("\n");
}

void boot() {
    serial_instance.setPort("/dev/ttyUSB0");
    serial::Timeout timeout = serial::Timeout::simpleTimeout(100);
    serial_instance.setTimeout(timeout);
    serial_instance.open();
}

int main(int argc, char **argv) {

    boot();
    int read;
    int sizeOfData;
    cin >> read;
    cin >> sizeOfData;
    while(true) {
        if(read == 0) {
            char data[sizeOfData];
            cin >> data;
            uint8_t result[sizeOfData / 2];
            hexToInt(data, sizeOfData, result);
            serial_instance.write(result, sizeOfData / 2);
            serial_instance.flush();
        } else if (read == 1) {
            string toRead;
            int dataRead = serial_instance.read(toRead, sizeOfData);
            intToHex(toRead);
        } else {
            return 0;
        }
        cin >> read;
        cin >> sizeOfData;
    }
    //if(argc == 4) {
    //    if(strcmp(argv[2], "-r") == 0) {
    //        int sizeOfData = strlen(argv[1]);
    //        uint8_t result[sizeOfData / 2];
    //        hexToInt(argv[1], sizeOfData, result);
    //        serial->write(result, sizeOfData / 2);
    //        serial.flush();
    //        string toRead;
    //        int dataRead = serial.read(toRead, atoi(argv[2]));
    //        intToHex(toRead);
    //    }
    //} else if (argc == 3) {
    //    if(strcmp(argv[1], "-r") == 0) {
    //        string toRead;
    //        int dataRead = serial.read(toRead, atoi(argv[2]));
    //        intToHex(toRead);
    //    }
    //} else if(argc == 2) {
    //    int sizeOfData = strlen(argv[1]);
    //    uint8_t result[sizeOfData / 2];
    //    hexToInt(argv[1], sizeOfData, result);
    //    serial.write(result, sizeOfData / 2);
    //    serial.flush();
    //}


    //serial.close();
    return 0;
}
