#include <iostream>
#include <cstring>
#include <cstdlib>

#include "serial/serial.h"

using namespace std;

int main(int argc, char **argv) {
    serial::Serial serial("/dev/ttyUSB0", 9600,
            serial::Timeout::simpleTimeout(1000));

    if(argc == 1) {
        serial.write(argv[0]);
    } else if (argc == 2) {
        if(strcmp(argv[0], "-r") == 0) {
            string read = serial.read(atoi(argv[1]));
            cout << read;
        }
    }
}
