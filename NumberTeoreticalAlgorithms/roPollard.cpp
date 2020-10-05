#include <iostream>
#include <vector>
#include <math.h>
#include "numberAlgorithms.h"

using namespace std;

long roPolard_2_in_power_h_(long (*F)(long,long),long n, long x_0=1){
    cout<<"ro-Pollard function :"<<__func__<<" , n = "<<n<<" , x_0 = "<<x_0<<endl<<endl;
    long gcd_result;
    vector<long> x;//we dont know how much iterations will be
    x.push_back(x_0);
    size_t j=1;
    size_t k;
    do{
        k=get_hight_bit(j)-1;
        
        for(int i=x.size();i<=j;i++){
            x.push_back(F(x[i-1],n));
        }
        cout<<"x_"<<k<<" = "<<x[k]<<endl;
        cout<<"x_"<<j<<" = "<<x[j]<<endl;
        cout<<"|x_"<<k<<"-x_"<<j<<"|="<<abs(x[k]-x[j])<<endl;
        gcd_result=gcd(abs(x[k]-x[j]),n);
       
        
        j++;
    }while (gcd_result==1||gcd_result>n);
    
    cout<<"result is "<< gcd_result<<endl;
    return gcd_result;
}


long roPolard_j_equals_2k(long (*F)(long,long),long n, long x_0=1){
    cout<<"ro-Pollard function :"<<__func__<<" , n="<<n<<" , x_0 = "<<x_0<<endl<<endl;

    long gcd_result;
    vector<long> x;//we dont know how much iterations will be
    x.push_back(x_0);
    size_t k=1;
    do{
        //this for cycle on k>1 always do 2 iteration
        for(size_t i=x.size()-1;i<=2*k;i++){
            x.push_back(F(x[i],n));
        }
        cout<<"x_"<<k<<" = "<<x[k]<<endl;
        cout<<"x_"<<2*(k)<<" = "<<x[2*k]<<endl;
        cout<<"|x_"<<k<<"-x_"<<2*k<<"|="<<abs(x[k]-x[2*k])<<endl;
        gcd_result=gcd(abs(x[k]-x[2*k]),n);
        cout<<"gcd = "<<gcd_result<<endl<<endl;
        k++;
    }while (gcd_result==1);
    cout<<"result is "<< gcd_result<<endl;
    return gcd_result;
}

long roPolard_classic(long (*F)(long,long),long n, long x_0=1){
    cout<<"ro-Pollard function :"<<__func__<<" , n = "<<n<<" , x_0 = "<<x_0<<endl<<endl;

    long gcd_result;
    vector<long> x;//we dont know how much iterations will be
    x.push_back(x_0);
    do{
        x.push_back(F(x[x.size()-1],n));
        for(int k=0;k<x.size()-1;k++){
            cout<<"Looking at the pair:"<<endl;
            cout<<"    x_"<<k<<" = "<<x[k]<<endl;
            cout<<"    x_"<<x.size()-1<<" = "<<x[x.size()-1]<<endl;
            cout<<"|x_"<<x.size()-1<<"-x_"<<k<<"|="<<abs(x[k]-x[x.size()-1])<<endl;
            gcd_result=gcd(abs(x[k]-x[x.size()-1]),n);
            if(gcd_result!=1){
                break;
            }
            
        }
    }while(gcd_result==1);
    
    cout<<"result is "<< gcd_result<<endl;
    return gcd_result;
}