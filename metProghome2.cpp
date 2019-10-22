#include<iostream>
using std::cout;

class TailClass {
};

template<class H, class T>
class TupleType {
public:
    typedef H head;
    typedef T tail;
};

template <class key, class H, class T>
class indexRecursiveGetter {
public:
    static int get(int level) {
        return indexRecursiveGetter<key, class T::head, class T::tail>::get(level + 1);
    }
};

template<class key, class T>
class indexRecursiveGetter<key, key, T> {
public:
    static int get(int level) {
        return level;
    }
};

template<class key, class T>
class indexRecursiveGetter<key, TailClass, T> {
public:
    static int get(int level) {
        return -1;
    }
};

template<class key, class T>
class indexRecursiveGetter<key, T, TailClass> {
public:
    static int get(int level) {
        return -1;
    }
};

template<class key>
class indexRecursiveGetter<key, key, TailClass> {
public:
    static int get(int level) {
        return level;
    }
};

template<class key, class TupleType>
int getIndexOf() {
    return indexRecursiveGetter<key, class TupleType::head, class TupleType::tail>::get(0);
}
int main() {
    cout << getIndexOf<std::pair<int, double>, TupleType<bool, TupleType<double, TupleType<std::string, TupleType<char*, TupleType<int, TupleType<std::pair<int, int>, TupleType<double, TailClass> > > > > > > >();
    return 0;
}
