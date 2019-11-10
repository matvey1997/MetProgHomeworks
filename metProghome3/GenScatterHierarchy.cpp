struct TailClass {
};

template<class T, class H>
struct Tuple {
    typedef H head;
    typedef T tail;
};

template<class TList, template<class> class Unit>
class GenScatterHierarchy;

template<class T1, class T2, template<class> class Unit>
class GenScatterHierarchy<Tuple<T1, T2>, Unit> : public GenScatterHierarchy<T1, Unit>,
                                                 public GenScatterHierarchy<T2, Unit> {
public:
        using TList = Tuple<T1, T2>;
        using LeftBase = GenScatterHierarchy<T1, Unit>;
        using RightBase = GenScatterHierarchy<T2, Unit>;
};
template<class AtomicType, template<class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType>{
public:
    using LeftBase = Unit<AtomicType>;
};
template<template<class> class Unit>
class GenScatterHierarchy<TailClass, Unit> {
};


template<class Key, class TList, class H, template<class> class Unit>
struct GetValueRecursieve {
    static Key& getVal(TList& x) {
        return GetValueRecursieve<Key, typename TList::RightBase, typename TList::LeftBase, Unit>::getVal(x);
    }
};

template<class Key, class TList, template<class> class Unit>
struct GetValueRecursieve<Key, TList, GenScatterHierarchy<Key, Unit>, Unit> {
    static Key& getVal(Unit<Key>& x) {
        return x.val;
    }
};

template<class Key, class TList, template<class> class Unit>
struct GetValueRecursieve<Key, TList, GenScatterHierarchy<TailClass, Unit>, Unit> {
    static Key& getVal(TList& x) {
        return new Key();
    }
};
template<class Key, template<class> class Unit>
struct GetValue {
    template<class TList>
    static Key& getVal(TList& x) {
        return GetValueRecursieve<Key, typename TList::RightBase, typename TList::LeftBase, Unit>::getVal(x);
    }
};
