#include<iostream>
#include<random>
using namespace std;

int main(){
    std::random_device r;
    for (int i=0;i<100;i++){
        mt19937_64 mte(r());
        uniform_int_distribution<long int> unif(0,1);
        cout << unif(mte)<<endl;
    }
    return 0;
}