#ifndef __MARCDRACO_PACK24__ARDUINO
#define __MARCDRACO_PACK24__ARDUINO

/***********************************************************************************
  Copyright 2020, Marc Draco
  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or other
   materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
  DAMAGE.
************************************************************************************/

/**
 * @brief 
 * 
 * @param X First 16 bit number range +/- 4095 
 * @param Y Second 16 bit number  +/- 4095
 * @param U8 unsigned char packed value
 * @param L16 unsigned word packed value
 * @brief pack 32 bits into 24 bits 
 */

void pack24(uint16_t X, uint16_t Y, uint8_t* U8, uint16_t* L16)
{
    *U8  = ((X & 0x0F00) >> 4) | ((Y & 0x0F00) >> 8);
    *L16 = ((X & 0x00FF) << 8) |  (Y & 0x00FF);
}

/**
 * @brief Unpack a previously packed 16 bit pair
 * 
 * @param U8 Packed char from pack routine 
 * @param L16 Packed word from pack routine
 * @param X Address of var to return "X"
 * @param Y Address of var to return "Y"
 */
void unpack24(uint8_t U8, uint16_t L16, uint16_t* X, uint16_t* Y)
{
    *X  = ((U8 & 0x0F) << 8) |  (L16 & 0x00FF);
    *Y  = ((U8 & 0xF0) << 4) | ((L16 & 0xFF00) >> 8) ;
}

/**
 * @brief Pack 32 bits from two signed variables into 24 bits
 * 
 * @param X First variable - +/- 2047
 * @param Y Second variable - +/- 2047
 * @param U8 Address to store 8 bit variable
 * @param L16 Address to store 16 bit variable
 */
void packSigned24(int16_t X, int16_t Y, uint8_t* U8, uint16_t* L16)
{

    uint8_t sX = ( (X & 0x8000) >> 8);
    uint8_t sY = ( (Y & 0x8000) >> 8);

    if (sX)
    {
        X = (X ^ 0xFFFF) + 1;
    }

    if (sY)
    {
        Y = (Y ^ 0xFFFF) + 1;
    }

    *U8  =  ((X & 0x0700) >> 4) | 
            ((Y & 0x0700) >> 8) | 
              sX | 
              sY >> 4;

    *L16 =  ((X & 0x00FF) << 8) |  
             (Y & 0x00FF);

}

/**
 * @brief Unpack a previously packed signed 16 bit pair
 * 
 * @param U8 Packed char from pack routine 
 * @param L16 Packed word from pack routine
 * @param X Address of var to return "X"
 * @param Y Address of var to return "Y"
 */
void unpackSigned24(uint8_t U8, uint16_t L16, int16_t* X, int16_t* Y)
{
    uint8_t sX = (U8 & 0x80) >> 4; // Sign bit for X
    uint8_t sY = (U8 & 0x08);      // Sign bit for Y

    *X  = (L16 >> 8) | ((U8 & 0x70) << 4);
    *Y  = (L16 & 0xFF) | ((U8 & 0x07) << 8);

    if (sX)
    {
        *X = (*X ^ 0xFFFF) + 1;
    }

    if (sY)
    {
        *Y = (*Y ^ 0xFFFF) + 1;
    }
}

#endif
