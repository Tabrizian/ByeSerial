#include <iostream>

#include "serial/serial.h"

using namespace std;

int main(int argc, char **argv) {
    serial::Serial my_serial("/dev/ttyUSB0", 9600, serial::Timeout::simpleTimeout(1000));

    size_t bytes_wrote = my_serial.write("Hello");
    cout << bytes_wrote << ", Bytes read: ";
}
