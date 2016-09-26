#include <iostream>

#include "serial/serial.h"

using namespace std;

int main(int argc, char **argv) {
    serial::Serial my_serial("/dev/ttyUSB0", 9600, serial::Timeout::simpleTimeout(1000));

    uint8_t dataArray[] = {0x01, 0x01, 0x30, 0x00, 0x00, 0x01, 0xf2, 0xca};
    size_t bytes_wrote = my_serial.write(dataArray, 8);
    cout << bytes_wrote << ", Bytes read: ";
    my_serial.read(1);
}
