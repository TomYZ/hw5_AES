//
//  tablecheck.c
//  hw5
//
//  Created by Zhen Yang on 3/12/16.
//
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "modprod.c"
unsigned char hex_to_dec(char a,char b){
    unsigned char temp;
    if(a>='0'&&a<='9'){
        temp=a-'0';
    }else{
        temp=a-'a'+10;
    }
    if(b>='0'&&b<='9'){
        temp=temp*16+(b-'0');
    }else{
        temp=temp*16+(b-'a'+10);
    }
    return temp;
}
bool tablecheck(FILE *table,unsigned char* S,unsigned char* P,unsigned char* INVP,unsigned char* INVS){
    // check whether S is a permutation of 00-ff
    int t[256];
    int i=0,j=0,k;
    unsigned char temp;
    char* buf=(char*)malloc(1024);
    char* buf1=(char*)malloc(128);
    char* buf2=(char*)malloc(128);
    fgets(buf,1024,table);
    buf+=2;
    for (i=0; i<256; i++) {//initialize S permutation table to 0
        t[i]=0;
    }
    //printf("S: ");
    for (i=0; i<256; i++) {
        temp=hex_to_dec(*buf,*(buf+1));//printf("%c,",temp);
        if(S!=NULL){
            S[i]=temp;
        }
        if(t[temp]==0){
            t[temp]=1;
        }else{
            fprintf(stderr,"S is not valid\n");
            return false;// repeat, S is not a permutation
        }
        buf+=2;
    }
    fgets(buf1,1024,table);
    buf1+=2;
    fgets(buf2,1024,table);
    buf2+=5;
    if(modprod(buf1,buf2,NULL,NULL,NULL)==false)
    {
        fprintf(stderr,"P and INVP are not valid\n");
        return false;
    }
    fseek(table,0,SEEK_SET);
    return true;
}
