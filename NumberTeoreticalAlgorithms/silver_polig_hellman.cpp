#include <iostream>
#include "numberAlgorithms.h"

using namespace std;

//a^х=b (mod p), p - prime
long silver_polig_hellman(long a,long b,long p){
    map<long,long> factors=factorize(p-1);
    long *r;
    long x=0;//future result,x=x_1*((p-1)/q_1^alpha_1)*((p-1)/q_1^alpha_1)^(-1)+
            //                x_2*((p-1)/q_2^alpha_2)*((p-1)/q_2^alpha_2)^(-1)+
            //                +...+
            //                x_n*((p-1)/q_n^alpha_n)*((p-1)/q_n^alpha_n)^(-1)
    long x_i;//x_i , i=1,...,n
    for(auto q:factors){
        x_i=0;
        r=new long[q.first];// precalculated values
        for (long i = 0; i < q.first; i++) {
            r[i]=modPow(a,i*(p-1)/q.first,p);
        }
        for(long k=0;k<q.second;k++){
            long c;//x_i=c_0*b^((p-1)/q)+c_1*(b*a^(-result))^((p-1)/q^2)+...+c_{n-1}*(b*a^(-result))^((p-1)/q^{n-1})
            long h;//h=b^((p-1)/q) , h= (b*a^(-result))^((p-1)/q^2)
            long a_inv=mod_inverse(a,p);
            if(k==0){
                h=modPow(b,(p-1)/q.first,p); 
            }else{
                h=modPow(b*modPow(a_inv,x_i,p),(p-1)/pow(q.first,k+1),p);
            }
            for (long j = 0; j < q.first; j++){
                if(h==r[j]){
                    c=j;
                    break;
                }
            }
            x_i+=c*modPow(q.first,k,pow(q.first,q.second));
        }
        long g=((p-1)/pow(q.first,q.second));
        long g_inv=mod_inverse(g,pow(q.first,q.second));
        x+=(x_i*g*g_inv)%(p-1);
        delete r;
    }
    cout<<x<<endl;
    return x;
}