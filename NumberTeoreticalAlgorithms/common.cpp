#include <iostream>
#include <map>
#include <cmath>
#include <bitset>
#include "numberAlgorithms.h"

using namespace std;

long gcd (long a, long b) {
    cout<<"gcd( "<<a<<" , "<<b<<" )"<<endl;
    
    while (a!=0 && b!=0) {
        cout<<"    a!=0 and b!=0? yes"<<endl;
        cout<<"         a>b?"<<endl;
        if (a>b) {
            cout<<"             yes: a:="<<a<<"mod"<<b<<" = ";
            a=a%b;
            cout<<a<<endl;
        }
        else{ 
            cout<<"             no: b:="<<b<<"mod"<<a<<" = ";
            b=b%a;
             cout<<b<<endl;
        }
    }
    cout<<"    a!=0 and b!=0? no"<<endl;
    cout<<"gcd is "<<a+b<<endl;
    return a+b;
}

long gcd_not_verbose (long a, long b) {
    while (a!=0 && b!=0) {  
        if (a>b) {      
            a=a%b;
        }
        else{ 
            b=b%a;
        }
    }
    return a+b;
}

long mod_inverse(long element, long mod){
        if(gcd_not_verbose(element,mod)!=1){
            return 0;
        }
        long a=element;
        long b=mod;
        long r=0;
        long p=1;
        long x;
        while (a!=0 && b!=0) {
            if (a>=b) {
                a -= b;
                p -= r;
            } else {
                b -= a;
                r -= p;
            }
        }
        if (a!=0) {
            x = p;

        }else {
            x = r;
        }
        if(x<0){
            x+=mod;
        }
        return x;//x=element^(-1) (mod p)
}

long get_hight_bit(long x){
    //if input is 0b11010101,the return is 0b10000000
    long t = 1;
    if (x >= t << 32) t <<= 32;
    if (x >= t << 16) t <<= 16;
    if (x >= t << 8) t <<= 8;
    if (x >= t << 4) t <<= 4;
    if (x >= t << 2) t <<= 2;
    if (x >= t << 1) t <<= 1;
    return t;
}


long f_1(long x,long n){
    return (x*x+1)%n;
}
long f_2(long x,long n){
    return (x*x-1)%n;
}
long f_3(long x,long n){
    return (x*x+x+1)%n;
}
long f_4(long x,long y,long n){
    return x*x-y*y-n;
}

//prime->ammount of primes
map<long, long> factorize(long n){
    map<long, long> factors;

    for (long i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }

    if (n != 1) {
        factors[n]++;
    }

    return factors;
}

long pow(long a,long exp){
    long y=1;
    long exp_len=log2(get_hight_bit(exp));
    for (long i = exp_len; i >-1; i--){
        y=y*y;
        if((exp>>i)&0x1){
            y=(y*a);
        }
    }
    return y;
}

long modPow(long a,long exp,long mod){
    long y=1;
    long exp_len=log2(get_hight_bit(exp));
    for (long i = exp_len; i >-1; i--){
        y=(y*y)%mod;
        if((exp>>i)&0x1){
            y=(y*a)%mod;
        }
    }
    return y;    
}