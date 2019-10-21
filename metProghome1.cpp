#include<tuple>
#include<vector>
#include<string>
#include<iostream>
#include<cstdio>
using namespace std;

template<int N>
class tupleReader {
public:
    template<class T1, class ... otherClasses>
    static tuple<T1, otherClasses ...> readTuple(tuple<T1, otherClasses ...> *temp) {
        T1 a;
        cin >> a;
        tuple<otherClasses ...> new_temp;
        return (tuple_cat(make_tuple(a), tupleReader<N - 1>::readTuple(&new_temp)));
    }
};
template<>
class tupleReader<1> {
public:
    template<class T1>
    static tuple<T1> readTuple(tuple<T1> *temp) {
        T1 a;
        cin >> a;
        return make_tuple(a);
    }
};
template<class T1, class ... otherClasses>
vector<tuple<T1, otherClasses ...> > readCSV(char* filename) {
    freopen(filename, "r", stdin);
    vector<tuple<T1, otherClasses...> > ans;
    tuple<otherClasses ...> temp;
    while (1) {
        T1 a;
        if (!(cin >> a))
            break;
        ans.push_back(tuple_cat(make_tuple(a), tupleReader<tuple_size<tuple<T1, otherClasses ... > >::value- 1>::readTuple(&temp)));
    }
    return ans;
}
/*
tempalte<class T1>
vector<tuple<T1> > readCSV(char* filename) {
    freopen(filename, "r", stdin);
    vector<tuple<T1> > ans;
    T1 a;
    while (cin >> a) {
        ans.push_back(make_tuple<T1>(a));
    }
    return ans;
}*/
int main() {
    auto v = readCSV<double, string, int, string> ("input.txt");
    cout << v.size() << endl;
    cout << std::get<1>(v[2]);
    return 0;
}
