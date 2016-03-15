//
//  hw5.c
//  hw5
//
//  Created by Zhen Yang on 3/13/16.
//
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "encrypt.c"

int main(int argc,char *argv[]){
    FILE * f;
    FILE * m;
    unsigned char w[44][4];
    
    //char *s="0123456789abcdef";
    if (argc<3) {
        fprintf(stderr,"malformed command\n");
        return 0;
    }else{
        if (strcmp(argv[1],"tablecheck")==0) {//tablecheck
            f=fopen(argv[2]+3,"r");
            if(f==NULL){
                fprintf(stderr,"can not open file\n");
                return 0;
            }
            if(tablecheck(f,NULL,NULL,NULL,NULL)==false){//only for tablechek, not for retreive data
                fprintf(stderr,"malformed tablefile\n");
                return 0;
            }
            fclose(f);
        }else if(strcmp(argv[1],"modprod")==0){
            modprod(argv[2]+4,argv[3]+4,NULL,NULL,NULL);
        
        }else if(strcmp(argv[1],"keyexpand")==0){
            f=fopen(argv[3]+3,"r");
            if(f==NULL){
                fprintf(stderr,"can not open file\n");
                return 0;
            }
            keyexpand(argv[2]+3,f,w);
            
        }else if(strcmp(argv[1],"encrypt")==0){
            f=fopen(argv[3]+3,"r");
            m=fopen(argv[4],"r");
            if(f==NULL){
                fprintf(stderr,"can not open file\n");
                return 0;
            }
            encrypt(argv[2]+3,f,m);
            
        }else{
            fprintf(stderr,"malformed command\n");
        }
    }
    return 0;
}
