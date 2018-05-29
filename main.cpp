#include <iostream>
#include "vector.h"
#include <vector>

using std::cout;

int main() {

    Vector<int> b(3, 3);
    Vector<int> c(b);
    Vector<std::string> a(3, "LUL");
   // a.push_back();
    const double g=15;

    for (auto i = 0; i <c.size() ; ++i) {
       // cout<<c[i]<<'\n';

    }
    Vector<int> d{0,1,2,3,4,5};
   int *second=&d[2];
    int *forth=&d[4];

    int *p=d.erase(second, forth);
    for (auto i = 0; i <d.size() ; ++i) {
      //  cout<<d[i]<<'\n';

    }
    Vector<int> e{0,1,2,3,4,5};

    second=&e[2];
    e.erase(second);
    for (auto i = 0; i <e.size() ; ++i) {
       //cout<<e[i]<<'\n';

    }

    Vector<int> in{0,1,2,3,4,5,6};

    second= &in[2];
    //cout<<second;
            const int s=10;
    in.insert(second, 10);
    for (auto i = 0; i <in.size() ; ++i) {
      // cout<<in[i]<<'\n';

    }

    Vector<int> in2{0,1,2,3,4,5,6,7};
    second= &in2[2];
     in2.emplace_back(1);
     cout<<in2[8];

    return 0;
}