#include <iostream>
#include <unordered_set>
#include <time.h>
#include <limits.h>


using namespace std;

class Hasher{
private:
    int n,p,a,b;
    int randomAB(int Min,int Max)
    {
    return Min+rand()%(Max-Min+1);
    }
public:
    Hasher(int arr_size){
    n=arr_size;
    p=(n%2==0) ? n+1 : n+2;
    while (true){
        bool isPrime=true;
        for (int i=2;i<=p;++i)
        {
            if (p%i==0){
                isPrime=false;
                break;
            }
            if (isPrime=true) break;
            else p+=2;
        }
    }
    srand(time(NULL));
    a=randomAB(1,p);
    b=randomAB(1,p);
    }

     int hash(int x){
    return (((a*x+b)%p)%n);}
};



int main()
{
    int n;
    cin>>n;
    long long* arr=new long long[n];
    for(int i=0;i<n;i++)
    {
        a[i]=INT_MIN;
    }
    Hasher h(n);
    long long temp;
    for(int i=0;i<n;i++){
    cin>>temp;
    int idx=h.hash(temp);
    while(arr[idx]!=INT_MIN && arr[idx]!=temp)
    {
        idx++;
        if (idx=n) idx=0;
    }
    arr[idx]=temp;
    }
    int cntr;
    for(int i=0;i<n;i++)
    {
        if (arr[i]!=INT_MIN)
        cntr++;
    }
    cout<<cntr;


    return 0;
}