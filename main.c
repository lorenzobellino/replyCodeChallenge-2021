#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mylib.h"




void Solve();
void Lettura();
void scrivi();
void compute();
int main(int argc, char **argv){
    int i;
    char solution[25];
    if(argc == 1){
        fprintf(stderr,"usage : ./solve file1.txt, file2.txt ... , filen.txt\n");
        exit(-1);
    }
    for(i=1;i<argc;i++){
        fprintf(stdout,"%s\n",argv[i]);
        r = fopen(argv[i],"r");
        if(r==NULL) printf("NULL");
        sprintf(solution,"solution_%s",argv[i]);
        w = fopen(solution,"w+");
        Solve();
        fclose(r);
        fclose(w);
    }
    return 0;
}

void Solve(){
    Lettura();
    compute();
    scrivi();
}

void Lettura(){
    int i,j;
    fscanf(r,"%d %d",&W,&H);
    fscanf(r,"%d %d %d",&N,&M,&R);
    antennas = malloc(M*sizeof(Antenna));
    solution = malloc(M*sizeof(Sol));
    buildings = malloc(N*sizeof(Building));
    for(i=0;i<M;i++){
        antennas[i].ac=-1;
        buildings[i].bc=-1;
    }
    for(i=M;i<N;i++){
        buildings[i].bc=-1;
    }
    map = malloc(H*sizeof(int *));
    map2 = malloc(H*sizeof(int *));
    for(i=0;i<H;i++){
        map[i] = malloc(W*sizeof(int));
        map2[i] = malloc(W*sizeof(int));
        for(j=0;j<W;j++){
            map[i][j]=0;
            map2[i][j]=0;
        }
    }
    fprintf(stdout,"lettura buildings\n");
    for(i=0;i<N;i++){
        fscanf(r,"%d %d %d %d\n",&buildings[i].bx,&buildings[i].by,&buildings[i].bl,&buildings[i].bc);
        buildings[i].id = i;
        buildings[i].used = 0;
    }
    fprintf(stdout,"lettura antennas\n");
    for(i=0;i<M;i++){
        fscanf(r,"%d %d\n",&antennas[i].ar,&antennas[i].ac);
        antennas[i].id = i;
        antennas[i].points = 0;
        antennas[i].ax = -1;
        antennas[i].ay = -1;
    }
    fprintf(stdout,"ordina building\n");
    QuickSortB(buildings,N);
    for(i=0;i<N;i++){
        map[buildings[i].by][buildings[i].bx] = i+1;
    }
    fprintf(stdout,"ordina antennas\n");
    QuickSortA(antennas,M);
}

void scrivi(){
    fprintf(stdout,"scrittura\n");
    fprintf(w,"%d\n",M);
    for(int i=0;i<M;i++){
        fprintf(w,"%d %d %d\n",antennas[i].id, antennas[i].ax,antennas[i].ay);
    }
}

void compute(){
    fprintf(stdout,"calcola\n");
    int i,j,sx,sy,ex,ey,x,y,points;
    for(i=0;i<M;i++){
        points = 0;
        j=0;
        while(buildings[j].used==1) j++;
        sx = buildings[j].bx-antennas[i].ar >0 ? buildings[j].bx-antennas[i].ar:0;
        ex = buildings[j].bx+antennas[i].ar <W ? buildings[j].bx+antennas[i].ar:W-1;
        sy = buildings[j].by-antennas[i].ar >0 ? buildings[j].by-antennas[i].ar:0;
        ey = buildings[j].by+antennas[i].ar <H ? buildings[j].by+antennas[i].ar:H-1;
        for(x=sx;x<=ex;x++){
            for(y=sy;y<=ey;y++){
                if(map2[y][x]==0){
                    Antenna a;
                    a.ax=x;
                    a.ay=y;
                    a.ar=antennas[i].ar;
                    points = calcolaPoints(map,a,buildings);
                    if(points>=antennas[i].points){
                        antennas[i].points = points;
                        antennas[i].ax = x;
                        antennas[i].ay = y;
                        antennas[i].used=1;
                    }
                }
            }
        }
        togliB(map,map2,antennas[i],buildings);
    }
}
