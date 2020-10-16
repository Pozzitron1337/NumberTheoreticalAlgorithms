#include "numberAlgorithms.h"
class ElipticCurve
{
private:
    long a;
    long b;
    long n;
public:
    ElipticCurve(long a,long b,long n){
        this->a=a;
        this->b=b;
        this->n=n;
    }
    long getN(){
        return n;
    }
    long getA(){
        return a;
    }
    ~ElipticCurve(){}
};

class ElipticCurvePoint
{
private:
    ElipticCurve* curve;
    long a;
    long x;
    long y;
    long n;
public:
    ElipticCurvePoint(ElipticCurve* curve,long x,long y){
        this->curve=curve;
        this->x=x;
        this->y=y;
        this->n=curve->getN();
        this->a=curve->getA();
    }
    ~ElipticCurvePoint(){
        //delete curve;
    }
    void printPoint(){
        cout<<"("<<x<<" , "<<y<<")"<<endl;
    }
    long inverse(long element){
        if(gcd_not_verbose(element,n)!=1){
            return 0;
        }
        long a=element;
        long b=n;
        long r=0;
        long p=1;
        long x;//future inverse element;
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
            x+=n;
        }
        return x;
    }
    
    //P+Q=R
    ElipticCurvePoint operator+(ElipticCurvePoint& Q){
        if (this->x==Q.x && this->y==Q.y){

            long Y=y*2%n;
            if(gcd_not_verbose(Y,n)==1){
                long Y_inv=inverse(Y);
                long numerator=(3*x*x+a)%n;
                long fraction=(numerator*Y_inv)%n;
                long square=(fraction*fraction)%n;
                long t1=(2*x)%n;
                long x_result=square-t1;
                if(x_result<0){
                    x_result+=n;
                }
                long t2=(x-x_result);
                if(t2<0){
                    t2+=n;
                }
                long t3=(fraction*t2)%n;
                long y_result=t3-y;
                if(y_result<0){
                    y_result+=n;
                }
                return ElipticCurvePoint(curve,x_result,y_result);
            }
            else{
                cout<<"Y = "<<Y<<endl;
                cout<<"gcd("<<Y<<" , "<<n<<") = "<<gcd_not_verbose(Y,n)<<endl;
                exit(1);
                //return ElipticCurvePoint(curve,0,0);
            }
        }
        else
        {
            long sub_x=Q.x - this->x;
            if(sub_x<0){
                sub_x+=n;
            }
            if(gcd_not_verbose(sub_x,n)==1){
                long sub_x_inv=inverse(sub_x);
                long sub_y=Q.y-this->y;
                if(sub_y<0){
                    sub_y+=n;
                }
                long fraction=(sub_y*sub_x_inv)%n;
                long square=(fraction*fraction)%n;
                long t1=square-this->x;
                if(t1<0){
                    t1+=n;
                }
                long x_result=t1-Q.x;
                if(x_result<0){
                    x_result+=n;
                }
                long t2=this->x-x_result;
                if(t2<0){
                    t2+=n;
                }
                long t3=(fraction*t2)%n;
                long y_result=t3-this->y;
                if(y_result<0){
                    y_result+=n;
                }
                return ElipticCurvePoint(curve,x_result,y_result);
            }else{
                cout<<"sub_x = "<<sub_x<<endl;
                cout<<"gcd("<<sub_x<<" , "<<n<<") = "<<gcd_not_verbose(sub_x,n)<<endl;
                exit(1);
                //return ElipticCurvePoint(curve,0,0);
            }
        }
        
    }
};

void task_3_lenstra(long n){
    ElipticCurve *curve=new ElipticCurve((long)5,(long)-5,n);
    ElipticCurvePoint P{curve,1,1};
    long f=8*7*6*5*4*3*2;
    //3P=P+P+P
    auto R=P+P;
    for (size_t i = 1; i <= f-1; i++)
    {
        R=R+P;
    }
    R.printPoint();
    delete curve;

}