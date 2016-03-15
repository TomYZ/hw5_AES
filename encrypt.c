//
//  encrypt.c
//  hw5
//
//  Created by Zhen Yang on 3/14/16.
//
//

#include <stdio.h>
#include "keyexpand.c"



void print_state(unsigned char state[4][4]){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            print_byte_to_hex(state[j][i]);
        }
    }
    printf("\n");
}



void ShiftRow(unsigned char s[4],int time){
    int i,j;
    unsigned char temp;
    for(i=0;i<time;i++){
        for(j=0;j<4;j++){
            if(j==0){
                temp=s[j];
            }
            if(j==3){
                s[j]=temp;
            }else{
                s[j]=s[j+1];
            }
        }
    }
}

void encrypt(char* key,FILE* table,FILE *in){
    unsigned char S[256];
    unsigned char P[4];
    unsigned char state[4][4];
    unsigned char input[16];
    unsigned char w[44][4];
    unsigned char p1[4],p2[4],p3[4];
    int cc,count=0,i,j,round;
    
    
    p1[0]=3;
    p1[1]=1;
    p1[2]=1;
    p1[3]=2;
    
    if (tablecheck(table,S,P,NULL,NULL)==false) {
        fprintf(stderr,"malformed tablefile\n");
        return;
    }
    keyexpand(key,table,w);
    while ((cc=fgetc(in))!=EOF) {
        input[count]=cc;
        count++;
        if(count==16){
            for(i=0;i<16;i++){
                state[i%4][i/4]=input[i];//state = in
            }
            print_state(state);
            for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                    state[j][i]=(state[j][i]^w[i][j]);//AddRoundKey w[0-3]
                }
            }
            print_state(state);
            for(round=1;round<10;round++){
                
                for(i=0;i<4;i++){
                    for(j=0;j<4;j++){
                        state[j][i]=S[state[j][i]];//SubBytes(state)
                    }
                }
                print_state(state);
                for(i=1;i<4;i++){
                    ShiftRow(state[i],i);//ShiftRow(state)
                }
                print_state(state);
                for(i=0;i<4;i++){
                    for(j=0;j<4;j++){
                        p2[j]=state[3-j][i];
                    }
                    modprod(NULL,NULL,p1,p2,p3);//MixColumn[state]
                    for(j=0;j<4;j++){
                        state[j][i]=p3[3-j];
                    }
                }
                print_state(state);
                for(i=0;i<4;i++){
                    for(j=0;j<4;j++){
                        state[j][i]=(state[j][i]^w[round*4+i][j]);
                        
                        //AddRoundKey w[round*4-round*4+3]
                    }
                }
                print_state(state);
                
            }
            for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                    state[j][i]=S[state[j][i]];//SubBytes(state)
                }
            }
            print_state(state);
            for(i=1;i<4;i++){
                ShiftRow(state[i],i);//ShiftRow(state)
            }
            print_state(state);
            for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                    state[j][i]=(state[j][i]^w[40+i][j]);//AddRoundKey w[40-43]
                }
            }
            print_state(state);
        }
    }
    
}