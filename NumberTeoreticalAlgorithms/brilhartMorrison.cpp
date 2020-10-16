#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <bitset>
#include "numberAlgorithms.h"

long brilhart_morrison(long n,size_t iterations=5){
    cout<<"n = "<<n<<endl;
    cout<<"iterations = "<<iterations<<endl;
    long v[iterations];
    double alpha[iterations];
    long a[iterations];
    long u[iterations];
    v[0]=1;
    alpha[0]=sqrt(n);
    a[0]=(long)alpha[0];
    u[0]=alpha[0];
    for(size_t k=0;k<iterations-1;k++){
        v[k+1]=(n-(u[k]*u[k]))/v[k];
        alpha[k+1]=(alpha[0]+(double)u[k])/(double)v[k+1];
        a[k+1]=(long)alpha[k+1];
        u[k+1]=a[k+1]*v[k+1]-u[k];
    }
    for(size_t i=0;i<iterations;i++){
        cout<<"a_"<<i<<" = "<<a[i]<<endl;
    }
    for(size_t i=0;i<iterations;i++){
        cout<<"v_"<<i<<" = "<<v[i]<<endl;
    }
    for(size_t i=0;i<iterations;i++){
        cout<<"u_"<<i<<" = "<<u[i]<<endl;
    }
    for(size_t i=0;i<iterations;i++){
        cout<<"alpha_"<<i<<" = "<<alpha[i]<<endl;
    }
    long b[iterations+1];
    b[0]=1;
    b[1]=a[0];
    for(size_t k=1;k<iterations;k++){
        b[k+1]=a[k]*b[k]+b[k-1];
        
    }
    for (size_t i = 0; i <= iterations; i++)
    {
        cout<<"b_"<<i<<" = "<<b[i]<<endl;
    }
    
    long m[iterations+1];
    for(size_t k=0;k<=iterations;k++){
        m[k]=(b[k]*b[k])%n;
        if(m[k]>abs(m[k]-n)){
            m[k]=(m[k]-n);
        }
        cout<<"m_"<<k-1<<" = "<<m[k]<<endl;
    }
    //filling the factorBase and m_factorized
    set<long> factorBase;
    map<long,long> m_factorized[iterations+1];
    for(size_t i=0;i<=iterations;i++){
        long t;
        if(m[i]<0){
            m_factorized[i]=factorize(-m[i]);
            m_factorized[i].insert(std::pair<long,long>(-1,1));
            factorBase.insert(-1);
            
        }else {
            m_factorized[i]=factorize(m[i]);
        }
        for(auto it=m_factorized[i].begin();it!=m_factorized[i].end();++it){
                factorBase.insert(it->first);
        }
    }
    for (size_t i = 0; i <= iterations; i++){
        for(auto it=factorBase.begin();it!=factorBase.end();++it){
            if(m_factorized[i].find(*it)==m_factorized[i].end()){
                m_factorized[i].insert(std::pair<long,long>(*it,0));
            }
            
        }
        
    }
    cout<<"B={";
    for (auto it = factorBase.begin(); it!=factorBase.end(); ++it)
    {
        if(it!=factorBase.end()){
            cout<<*it<<",";
        }
        else{
            cout<<*it;
        }
        
    }
    cout<<"}"<<endl;
    for (size_t i = 0; i <= iterations; i++){
        if(i==0){
            cout<<"(m_"<<"-1"<<")^2 mod(n) = ";
        }else
        {
            cout<<"(m_"<<i-1<<")^2 mod(n) = ";
        }
        
        printf("%3ld = ",m[i]);
        for(auto it=m_factorized[i].begin();it!=m_factorized[i].end();++it){
            cout<<it->first<<"^"<<it->second<<" * ";
        }    
        cout<<endl;
    }

    vector<long> epsilon[iterations];
    for (size_t i = 1; i <=iterations ; i++){
       for (auto it=m_factorized[i].begin();it!=m_factorized[i].end();++it){
               epsilon[i-1].push_back(it->second%2); 
       }
    }

    for(int i=0;i<iterations;i++){
        cout<<"epsilon_"<<i<<" = ( ";
        for (auto it = epsilon[i].begin(); it!=epsilon[i].end(); ++it){
            cout<<*it<<" "; 
        }
         cout<<")"<<endl;
    }
    
    //finding the (x_1,...,x_n)
    vector<long> canditate;
    long x_iterator=1;
    bitset<64> x(x_iterator);
    long sum;
    for (size_t i = 0; i < factorBase.size(); i++) {
        sum=0;
        for (size_t j = 0; j < iterations; j++){
            sum+=epsilon[j][i]*x[j];
        }
        if(sum%2==1){
            x_iterator++;
            x=x_iterator;
            i=-1;
            continue;
        }else{
            if(i==factorBase.size()-1){
                canditate.push_back(x_iterator);
                if(x_iterator<(long)1<<iterations){
                    x_iterator++;
                    x=x_iterator;
                    i=-1;
                    continue;
                }
            }
        }
    }
    for (size_t i = 0; i < iterations-1; i++){
        cout<<"x_"<<i<<"*epsilon_"<<i<<"+";
    }
    cout<<"x_"<<iterations-1<<"*epsilon_"<<iterations-1<<" = 0"<<endl;
    cout<<"candidates: ";
    for(auto it=canditate.begin();it!=canditate.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
    bitset<64> bitCandidate;
    for(auto it=canditate.begin();it!=canditate.end();++it){
        bitCandidate=*it;
        cout<<"candidate:"<<*it<<" = "<<bitCandidate<<endl;
        x=*it;
        for(size_t i=0;i<iterations;i++){
            cout<<"     x_"<<i<<" = "<<x[i]<<endl;
        }

        //counting X,Y
        long X=1;
        long Y=1;
        long t;
        for(size_t i=0;i<iterations;i++){
            if(x[i]==1){
                X*=b[i+1];
                X%=n;
                Y*=(b[i+1]*b[i+1])%n;
                Y%=n;
            }   
        }
        Y=sqrt(Y);
        cout<<"     X = "<<X<<endl;
        cout<<"     Y = "<<Y<<endl;
        cout<<"     gcd(X-Y,n) = "<<gcd_not_verbose(abs(X-Y),n)<<endl;
        cout<<"     gcd(X+Y,n) = "<<gcd_not_verbose(abs(X+Y),n)<<endl;
    }
}   
