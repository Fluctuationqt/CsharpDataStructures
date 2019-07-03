#include<iostream>
#include<queue>
#include<iomanip>
using namespace std;
int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    double* arr = new double[n];
    for(int i = 0; i<n;i++){
        cin>>arr[i];
    }
    double median = arr[0];
    priority_queue<double,vector<double>, less<double>> smaller;
    priority_queue<double,vector<double>,greater<double>> bigger;
    smaller.push(arr[0]);
    cout<<fixed<<setprecision(1);
    cout<<median<<endl;
    for (int i=1; i < n; i++)
    {
        double curr = arr[i];
        if (smaller.size() > bigger.size())        {
            if (curr < median){
                bigger.push(smaller.top());
                smaller.pop();
                smaller.push(curr);
            }
            else{
                bigger.push(curr);
            }
            median = (smaller.top()+bigger.top()) / 2.0;
        }
        else if (smaller.size() == bigger.size())
        {
            if (curr > median){
                bigger.push(curr);
                median = (double)bigger.top();
            } else {
                smaller.push(curr);
                median = (double)smaller.top();
            }
        } else {
            if (curr > median) {
                smaller.push(bigger.top());
                bigger.pop();
                bigger.push(curr);
            }
            else
                smaller.push(curr);
            median = (smaller.top()+bigger.top()) / 2.0;
        }
        cout << median << endl;
    }
    return 0;
}