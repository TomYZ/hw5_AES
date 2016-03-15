//
//  keyexpand.c
//  hw5
//
//  Created by Zhen Yang on 3/13/16.
//
//

#include <stdio.h>
#include "tablecheck.c"
unsigned char hex_to_byte(char a,char b){
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

void print_byte_to_hex(unsigned char a){
    unsigned char mask1=15;//0x 0000 1111
    unsigned char mask2=240;//0x 1111 0000
    unsigned char a1=(a&mask2)>>4;
    unsigned char a2=(a&mask1);
    if(a1>=0&&a1<=9){
        printf("%c",a1+'0');
    }else{
        printf("%c",a1-10+'a');
    }
    if(a2>=0&&a2<=9){
        printf("%c",a2+'0');
    }else{
        printf("%c",a2-10+'a');
    }
}


void computeRcon(unsigned char * Rcon){//compute Rcon before keyexpand
    Rcon[1]=1;
    unsigned char a=2;
    int i=1;
    for(i=2;i<11;i++){
        Rcon[i]=mod(Rcon[i-1],a);
        //print_byte_to_hex(Rcon[i]);
    }
}


void keyexpand(char* key,FILE* table,unsigned char w[44][4]){
    
    int i=0,j;
    
    unsigned char Rcon[11];
    
    unsigned char S[256];
   
    unsigned char temp[4];
    
    unsigned char Rtemp;
    
    unsigned char R0=0;
    
    tablecheck(table,S,NULL,NULL,NULL);
    computeRcon(Rcon);
    
    
    for (i=0; i<4; i++) {
        printf("w[ %d]: ",i);
        for(j=0;j<4;j++){//w[i]=word()
            w[i][j]=hex_to_byte(key[8*i+2*j],key[8*i+2*j+1]);
            //printf("%c%c",key[8*i+2*j],key[8*i+2*j+1]);
            //printf(" %d ",w[i][j]);
            print_byte_to_hex(w[i][j]);
        }
        printf("\n");
    }
    
    
    for(i=4;i<44;i++){
        
        for(j=0;j<4;j++){//temp=w[i-1]
            temp[j]=w[i-1][j];
        }
        if(i%4==0){
            for(j=0;j<4;j++){//RotWord(temp)
                if(j==0){
                    Rtemp=temp[j];
                }
                if(j==3){
                    temp[j]=Rtemp;
                }
                else{
                    temp[j]=temp[j+1];
                }
                //SubWord()
                temp[j]=S[temp[j]];
                if(j==0){
                    temp[j]=temp[j]^Rcon[i/4];// XOR Rcon[i/NK]
                }else{
                    temp[j]=temp[j]^R0;
                }
                
            }
        }
        if(i<10)
            printf("w[ %d]: ",i);
        else
            printf("w[%d]: ",i);
        for(j=0;j<4;j++){
            w[i][j]=w[i-4][j]^temp[j];//w[i]=w[i-NK] XOR temp
            print_byte_to_hex(w[i][j]);
        }
        printf("\n");
    }
}