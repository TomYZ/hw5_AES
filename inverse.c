//
//  inverse.c
//  hw5
//
//  Created by Zhen Yang on 3/14/16.
//
//

#include <stdio.h>
#include "modprod.c"



void XOR(unsigned char *a,unsigned char *b,unsigned char *sum){
    int i=0;
    for(i=0;i<4;i++){
        sum[i]=(a[i]^b[i]);
    }
}


void modify(unsigned char *a,unsigned char *b,unsigned char *pro){
    modprod(NULL,NULL,a,b,pro);
}

void divide(unsigned char *a,unsigned char *b,unsigned char *rem,,unsigned char *quo,unsigned char *S){
    int i=0;
    if(a[0]<b[0]){
        quo[0]=0;
        quo[1]=0;
        quo[2]=S[b[0]];
        for(i=0;i<3;i++){
            rem[i]=mod(b[i+1],quo[2]);
        }
        rem[3]=1;
        quo[3]=mod(rem[0],S[b[0]]);
        rem[0]=0;
        for(i=1;i<4;i++){
            rem[i]=(rem[i]^quo[3]);
        }
    }else{
        
    }
}

void computeInv(unsigned char *S){
    unsigned char i=0,j=0,k=1;
    for(i=0;i<256;i++){
        for(j=0;j<256;j++){
            if(mod(i,j)==k){
                S[i]=j;
                break;
            }
        }
    }
}


void inverse(char *p){
    unsigned char S[256];
    computeInv(S);
}