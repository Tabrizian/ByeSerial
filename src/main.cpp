#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "serial/serial.h"

using namespace std;

ofstream logFile("/tmp/serial.txt");
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

void intToHex(string bytesArray,int len) {
    logFile << "Hex " << " " << len << endl;
    logFile << "Read: ";
    for(int i = 0; i < len; i++) {
        char test[3];
        cout << (int) bytesArray[i];
        logFile << (int) bytesArray[i];
    }
    logFile << endl;
    printf("\n");
}

void boot() {
    bool done = false;
    int i = 0;
    while(!done) {
        try {
            string port = "/dev/ttyUSB" + to_string(i);
            logFile << "Selecting port... " << port << endl;
            serial_instance.setPort(port);
            serial_instance.setBaudrate(atoi(getenv("BAUD_RATE")));
            logFile << "Baudrate is set to ... " << atoi(getenv("BAUD_RATE")) << endl;
            serial::Timeout timeout = serial::Timeout::simpleTimeout(atoi(getenv("TIMEOUT")) * 100);
            serial_instance.setTimeout(timeout);
            logFile << "Timeout is set to ... " << atoi(getenv("TIMEOUT")) * 100 << endl;
            serial_instance.open();
            logFile << "Serial port is open now" << endl;
            done = true;
        } catch (serial::IOException exception) {
            i++;
            i = i  % 300;
        }
    }
}


int main(int argc, char **argv) {

    while(true) {
        try {
            boot();
            int read;
            int sizeOfData;
            logFile << "Ready for getting new input... " << endl;
            cin >> read;
            cin >> sizeOfData;
            while(true) {
                if(read == 0) {
                    char data[sizeOfData];
                    cin >> data;
                    uint8_t result[sizeOfData / 2];
                    hexToInt(data, sizeOfData, result);
                    logFile << "Writing " << data << endl;
                    serial_instance.write(result, sizeOfData / 2);
                    serial_instance.flush();
                } else if (read == 1) {
                    string toRead;
                    logFile << "Wanting to read No of bytes are " << sizeOfData << endl;
                    int dataRead = serial_instance.read(toRead, sizeOfData);
                    if(dataRead > 0) {
                        logFile << "Data read " << dataRead << endl;
                        int len = dataRead;
                        for(int i = 0; i < len; i++) {
                            char test[3];
                            if(((int) toRead[i] )< 0) {
                                cout << setfill('0') << setw(2) << hex<<((int) toRead[i]) + 256;
                                logFile<< setfill('0') << setw(2) << hex<<((int) toRead[i]) + 256;
                            } else {
                                cout << setfill('0') << setw(2) << hex<<(int) toRead[i];
                                logFile<< setfill('0') << setw(2) << hex<<(int) toRead[i];
                            }
                        }
                        logFile << endl;
                        printf("\n");
                    }
                } else if (read == 2) {
                    serial_instance.flushInput();
                    serial_instance.flushOutput();
                } else {
                    return 1;
                }
                logFile << "Ready for getting new input... " << endl;
                cin >> read;
                cin >> sizeOfData;
            }
        } catch (const std::bad_alloc& e) {
            logFile << "Bad Alloc" << endl;
        } catch (const serial::SerialException& e) {
            logFile << "Serial Exception" << endl;
	    boot();
            serial_instance.close();
        }
    }

    return 0;
}
