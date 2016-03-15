//
//  modprod.c
//  hw5
//
//  Created by Zhen Yang on 3/13/16.
//
//

#include <stdio.h>
unsigned char hex_to_char(char a,char b){
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
void char_to_hex(unsigned char a){
    unsigned char mask1=15;
    unsigned char mask2=240;
    unsigned char a1=(a&mask2)>>4;
    unsigned char a2=a&mask1;
    if(a1>=0&&a1<=9){
        printf("{%c",a1+'0');
    }else{
        printf("{%c",a1-10+'a');
    }
    if(a2>=0&&a2<=9){
        printf("%c}",a2+'0');
    }else{
        printf("%c}",a2-10+'a');
    }
}
unsigned char xtime(unsigned char p){
    unsigned char b=p>>7;
    unsigned char m=27; //0x 0001 1011  {1B}
    if(b==0){
        return (p<<1);
    }
        p=(p<<1);
        return p^m;
    
    
}
unsigned char mod(unsigned char p1,unsigned char p2){
    int i;
    unsigned char p2temp=0,p1temp=0,xtemp;
    unsigned char mask=0x00000001;
    xtemp=p1;
    for(i=0;i<8;i++){
        p2temp=((p2&mask)>>i);
        mask=(mask<<1);
        
        if(p2temp==1){
            p1temp=(p1temp^xtemp);
            //printf(" xtime:%d ",xtemp);
        }
        xtemp=xtime(xtemp);
    }
    return p1temp;
}
bool modprod(char* p1,char* p2,unsigned char*m1,unsigned char*m2,unsigned char* p){
    unsigned char mm0=0;
    unsigned char mm1=1;
    unsigned char d[4],a[4],b[4];
    int i;
    for(i=0;i<4;i++){
        if(p1!=NULL){
            a[i]=hex_to_char(*p1,*(p1+1));
            printf("{%c%c}",*p1,*(p1+1));
            p1+=2;
        }else{
            a[i]=m1[i];
        }
    }
    printf(" CIRCLEX ");
    for(i=0;i<4;i++){
        if (p2!=NULL) {
            b[i]=hex_to_char(*p2,*(p2+1));
            printf("{%c%c}",*p2,*(p2+1));
            p2+=2;
        }else{
            b[i]=m2[i];
        }
    }
    printf(" = ");
    //printf("%d",mod(a[0],b[3]));
    d[0]=(mod(a[0],b[3])^mod(a[1],b[2])^mod(a[2],b[1])^mod(a[3],b[0]));
    d[1]=(mod(a[1],b[3])^mod(a[2],b[2])^mod(a[3],b[1])^mod(a[0],b[0]));
    d[2]=(mod(a[2],b[3])^mod(a[3],b[2])^mod(a[0],b[1])^mod(a[1],b[0]));
    d[3]=(mod(a[3],b[3])^mod(a[0],b[2])^mod(a[1],b[1])^mod(a[2],b[0]));
    
    for(i=0;i<4;i++){
        char_to_hex(d[i]);
        if(p1==NULL){
            p[i]=d[i];
        }
    }
    printf("\n");
    for(i=0;i<4;i++){
        if(i==3){
            if(d[i]!=mm1) return false;
        }else{
            if(d[i]!=mm0) return false;
        }
    }
    return true;
}