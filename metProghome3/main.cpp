#include "GenScatterHierarchy.cpp"
#include<string>
#include<iostream>
template<class T>
struct Holder {
    T val;
};

template<> struct Holder<int> {
    int val = 7;
};

template<> struct Holder<double> {
    double val = 3.141592653;
};

template<> struct Holder<std::string> {
    std::string val = "Hello World!\n";
};
int main() {
    GenScatterHierarchy<Tuple<int, Tuple<double, Tuple<std::string, TailClass> > >, Holder> x;
    typedef GetValue<int, Holder> IntGetter;
    std::cout << (IntGetter::getVal(x)) << "\n";
    typedef GetValue<double, Holder> DoubleGetter;
    std::cout << (DoubleGetter::getVal(x)) << "\n";
    typedef GetValue<std::string, Holder> StringGetter;
    std::cout << (StringGetter::getVal(x)) << "\n";

    StringGetter::getVal(x) = "How does the compiler convert arguments in the recursieve part?";
    IntGetter::getVal(x) *= 10;
    DoubleGetter::getVal(x) *= 2.718281;

    std::cout << (IntGetter::getVal(x)) << "\n";
    std::cout << (DoubleGetter::getVal(x)) << "\n";
    std::cout << (StringGetter::getVal(x)) << "\n";
    return 0;
}
