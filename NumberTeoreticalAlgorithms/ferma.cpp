#include <iostream>
#include "numberAlgorithms.h"

using namespace std;

long ferma(long (*r)(long,long,long),long n){
    long x=(long)sqrt(n);
    cout<<n<<endl;
    cout<<x<<endl;
    long y=0;
    long t;
    long i=0;
    do{
        
        t=r(x,y,n);
        cout<<"x_"<<i<<" = "<<x<<endl;
        cout<<"y_"<<i<<" = "<<y<<endl;
        cout<<"r_"<<i<<" = "<<t<<endl<<endl;
        if(t>0){
            y+=1;
        }
        if(t<0){
            x+=1;
        }
        i++;
        
    }while(t!=0);
    cout<<"x-y = "<<x-y<<endl;
    cout<<"x+y = "<<x+y<<endl;
}

