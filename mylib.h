//
// Created by Mazzi on 03/04/2021.
//

#ifndef REPLY2021_V3_MYLIB_H
#define REPLY2021_V3_MYLIB_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>



//ANTENNE
typedef struct Antenna{
    int ar;
    int ac;
    int ax;
    int ay;
    int id;
    int points;
    int used;

}Antenna;
//BUILDINGS
typedef struct Building{
    int bx;
    int by;
    int bl;
    int bc;
    int id;
    int used;
}Building;

FILE *r , *w;
int W,H,N,M,R;
int **map, **map2;
Building* buildings;
Antenna* antennas;

void QuickSortB(Building* B, int NN);
void QuickSortBR(Building* B, int lt, int rt );
int partitionB (Building* B, int lt, int rt );
void swapB(Building* B1, Building *B2);
void QuickSortA(Antenna* A, int NN);
void QuickSortAR(Antenna* A, int lt, int rt );
int partitionA (Antenna* A, int lt, int rt );
void swapA(Antenna* A1, Antenna* A2);
int calcolaPoints(int **map, Antenna A, Building* B);
void togliB(int** map,int** map2, Antenna A, Building* B);

#endif //REPLY2021_V3_MYLIB_H
