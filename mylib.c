//
// Created by Mazzi on 03/04/2021.
//

#include "mylib.h"

void QuickSortB(Building* B, int NN){
    int lt=0, rt=NN-1;
    QuickSortBR(B, lt, rt);
}

void QuickSortBR(Building* B, int lt, int rt ){
    int q;
    if (rt <= lt) return;
    q = partitionB(B, lt, rt);
    QuickSortBR(B, lt, q-1);
    QuickSortBR(B, q+1, rt);
}

void swapB(Building* B1, Building *B2){
    Building tmp = *B1;
    *B1=*B2;
    *B2=tmp;
}

int partitionB(Building* B, int lt, int rt ){
    int i, j;
    int x = B[rt].bc;
    i = lt-1;
    j = rt;
    for ( ; ; ) {
        while(B[++i].bc>x);
        while(B[--j].bc< x);
        if (j == lt) break;
        if (i >= j) break;
        swapB(&B[i],&B[j]);
    }
    swapB(&B[i],&B[rt]);
    return i;
}

void QuickSortA(Antenna* A, int NN){
    int lt=0, rt=NN-1;
    QuickSortAR(A, lt, rt);
}

void QuickSortAR(Antenna* A, int lt, int rt ){
    int q;
    if (rt <= lt) return;
    q = partitionA(A, lt, rt);
    QuickSortAR(A, lt, q-1);
    QuickSortAR(A, q+1, rt);
}

int partitionA (Antenna* A, int lt, int rt){
    int i, j;
    int x = A[rt].ac;
    i = lt-1;
    j = rt;
    for ( ; ; ) {
        while(A[++i].ac>x);
        while(A[--j].ac< x);
        if (j == lt) break;
        if (i >= j) break;
        swapA(&A[i],&A[j]);
    }
    swapA(&A[i],&A[rt]);
    return i;
}

void swapA(Antenna* A1, Antenna* A2){
    Antenna tmp = *A1;
    *A1=*A2;
    *A2=tmp;
}

int calcolaPoints(int **map, Antenna A, Building* B){
    int i,j, idB, tot = 0, p;
    int startX = A.ax-A.ar>0 ? A.ax-A.ar : 0;
    int endX   = A.ax+A.ar<W ? A.ax+A.ar : W-1;
    int startY = A.ay-A.ar>0 ? A.ay-A.ar : 0;
    int endY   = A.ay+A.ar<H ? A.ay+A.ar : H-1;

    for(j=startX; j<=endX; j++){
        for(i=startY; i<=endY; i++){
            if(abs(i-A.ay)+abs(j-A.ax)<=A.ar){
                idB = map[i][j]-1;
                if(idB>=0 && !B[idB].used){
                    p=(B[idB].bc*A.ac) - (B[idB].bl*(abs(i-A.ay)+abs(j-A.ax)));
                    tot+=p;
                    //B[idB].used=1;
                }
            }
        }
    }
    return tot;
}

void togliB(int **map,int** map2, Antenna A, Building* B){
    int i,j, idB;
    int startX = A.ax-A.ar>0 ? A.ax-A.ar : 0;
    int endX   = A.ax+A.ar<W ? A.ax+A.ar+1 : W;
    int startY = A.ay-A.ar>0 ? A.ay-A.ar : 0;
    int endY   = A.ay+A.ar<H ? A.ay+A.ar+1 : H;
    map2[A.ay][A.ax]=-(A.id+1);
    for(j=startX; j<endX; j++){
        for(i=startY; i<endY; i++){
            if(abs(i-A.ay)+abs(j-A.ax)<=A.ar){
                idB = map[i][j]-1;
                if(idB>=0 && !B[idB].used){
                    B[idB].used=1;
                }
            }
        }
    }
}




