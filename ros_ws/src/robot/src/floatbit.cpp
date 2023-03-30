// /*
// https://forum.arduino.cc/t/float-over-serial-between-two-arduino-closed/583163/2
// */

// #include "iostream"
// #include "stdint.h"

// int8_t fByte[4];

// float keluaran;
// int main(int argc, char const *argv[])
// {
//     float x = 2.21;
//     float *fPtr = &x;
//     int8_t *bPtr = (int8_t *) fPtr;

//     for(int i = 0; i <= 3; i++){
//         fByte[i] = *bPtr + i;
//     }
//     keluaran = (fByte[3] << 24 | fByte[2] << 16 | fByte[1] << 8 | fByte[0]);
//     // keluaran = (fByte[3] >> 24 | fByte[2] >> 16 | fByte[1] >> 8 | fByte[0]);
//     // keluaran = (*bPtr + 3 | *bPtr + 2 | *bPtr + 1 | *bPtr);

//     std::cout << keluaran << std::endl;

//     return 0;
// }

/*
https://stackoverflow.com/questions/24420246/c-function-to-convert-float-to-byte-array
*/

#include <stdio.h>
#include "stdint.h"

float keluaran;

int main(void) {
  union {
    float nilai;
    uint8_t ytes[4];
  } thing;

  union {
    float nilai;
    uint8_t ytes[4];
  } eakw;

    thing.nilai = -1.234;
    for(int i = 0 ; i <= 3; i++){
        eakw.ytes[i] = thing.ytes[i];
    }
    // eakw.bytes = thing.bytes;
    printf("%f\n", eakw.nilai);

  return 0;
}
