#include <Arduino.h>

// Prototipes
int myShiftOut(int, int,int*);
int superShiftOut(int (*matrix)[8], int, int*, int*, int, int,int);
int separateMatrix(int (*matrix)[8], int (*m1)[8], int (*m2)[8]);
int superShiftOut2(int (*matrix)[8], int, int ,int);



/*-------------------------------------------------------myShiftOut  -> for bonus <- ------------------------------------------
    function that writes multiple bits serially to be subsequently multiplexed by the 74HC595

    @param data_Pin | arduino phisical pin for write
    @param clock_Pin | arduino phisical pin for controll the clock 
    @param data | pointer to an array who contains the data to upload

    @return 0 if everything is okay
-----------------------------------------------------------------------------------------------------------------------------*/
int myShiftOut(int data_Pin, int clock_Pin,int* data ){
    for(int i=7;i>=0;i--){
      digitalWrite(data_Pin,*(data+i));
      digitalWrite(clock_Pin,HIGH);
      digitalWrite(clock_Pin,LOW);
    }
  return 0;
  }

/*-------------------------------------------------------superShiftOut-----------------------------------------------------------
    function that separete the main array in rows and call the funcion myShiftOut to upload
    row by row

    @param matrix | pointer to main matrix 
    @param columnM1 | pointer to array who contains the columns of the phisical matrix 1
    @param columnM2 | pointer to array who contains the columns of the phisical matrix 2
    @param controlRow |  pointer to array who contains the rows of the phisical matrix 1 and 2
    @param data | arduino phisical pin for write
    @param clock_Pin | arduino phisical pin for controll the clock 
    @param latch | arduino phisical pin for control the latch clock

    @return 0 if everything is okay
-------------------------------------------------------------------------------------------------------------------------------*/
int superShiftOut2(int (*matrix)[8], int data, int clock,int latch){
    int auxM1[8][8];
    int auxM2[8][8];
    int columnM1[8]; 
    int columnM2[8];
    int controlRow[8];

    separateMatrix(matrix, auxM1, auxM2);

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            columnM1[j]  = auxM1[i][j];
            columnM2[j]  = auxM2[i][j];
            *(controlRow +j) = 1;
        }
        *(controlRow +i) = 0;
        digitalWrite(latch,HIGH);
        myShiftOut(data, clock, columnM2);
        myShiftOut(data, clock, controlRow);
        myShiftOut(data, clock, columnM1);
        myShiftOut(data, clock, controlRow);
        digitalWrite(latch,LOW);
    }
return 0;
}
/*-------------------------------------------------------separateMatrix--------------------------------------------------------
    function that split the main matrix 16x8 in two matrices 8x8

    @param matrix | a pointer to the main matrix 16x8
    @param m1 | a pointer to a matrix 8x8
    @param m2 | a pointer to a matrix 8x8

    @return 0 if everything is okay
-----------------------------------------------------------------------------------------------------------------------------*/
int separateMatrix(int (*matrix)[8], int (*m1)[8], int (*m2)[8]){

    for(int i=0; i<16; i++){
        for(int j=0; j<8; j++){
            if(i>=0 && i<8)
                *(*(m1 +i)+j) = *(*(matrix +i)+j);
            else if(i>=8 && i<16)
                *(*(m2 +i-8)+j) = *(*(matrix +i)+j);
        }
    }
return 0;
}
