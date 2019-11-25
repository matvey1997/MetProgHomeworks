template<typename T>
T* ConvertToPtr(T& t) {
    return &t;
}

template<typename T>
T* ConvertToPtr(T* t) {
    return t;
}

template<typename T>
T& ConvertToRef(T& t) {
    return t;
}

template<typename T>
T& ConvertToRef(T* t) {
    return *t;
}

template<typename ...Tail>
class ArgsPack;
template<>
class ArgsPack<> {
public:
    ArgsPack() {}
    template<class Deligate, typename... Args>
    auto Call(const Deligate& deligate, Args&&... args) -> decltype(deligate(args...)) {
        return deligate(args...);
    }
};

template<typename Head, typename ...Tail>
class ArgsPack<Head, Tail...> : ArgsPack<Tail...> {
private:
    Head m_Param;
public:
    typedef ArgsPack<Tail...> __base;
    ArgsPack(Head&& head, Tail&&... tail) :
        __base(std::forward<Tail>(tail)...), m_Param(std::forward<Head>(head)) {}

    template<class Deligate, typename... Args>
    auto Call(const Deligate& deligate, Args&&... args)
            -> decltype(this->__base::Call(deligate, args..., ConvertToPtr(m_Param))) {
        return __base::Call(deligate, args..., ConvertToPtr(m_Param));
    }
    template<class Deligate, typename... Args>
    auto Call(const Deligate& deligate, Args&&... args)
            -> decltype(this->__base::Call(deligate, args..., ConvertToRef(m_Param))) {
        return __base::Call(deligate, args..., ConvertToRef(m_Param));
    }
};

template<class TObject, typename TCE>
struct SimpleDeligate {
private:
    TObject& m_Object;
    TCE m_CollableEntity;
public:
    SimpleDeligate(TObject& object, const TCE& ptr)
        : m_Object(object), m_CollableEntity(ptr) {}

    template<typename... Params2>
    auto operator()(Params2... args) const
            -> decltype((m_Object.*m_CollableEntity)(args...)) {
        return (m_Object.*m_CollableEntity)(args...);
    }
};

template<class TCE>
struct CEWrapper {
private:
    TCE m_CollableEntity;
public:
    CEWrapper(const TCE& ptr) : m_CollableEntity(ptr) {}

    template<typename... Params2>
    auto operator()(Params2... args)const -> decltype(m_CollableEntity(args...)) {
        return m_CollableEntity(args...);
    }
};

template <class TCollableEntity, typename... Args>
class Functor : ArgsPack<Args...> {
private:
    TCollableEntity m_CollableEntity;
public:
    typedef ArgsPack<Args...> __base;
    Functor(TCollableEntity collable_entity, Args... args) : __base(std::forward<Args>(args)...), m_CollableEntity(collable_entity) {}

    template<class TCE = TCollableEntity>
    auto Call() -> decltype(this -> __base::Call(CEWrapper<TCE>(m_CollableEntity))) const {
        return __base::Call(CEWrapper<TCE>(m_CollableEntity));
    }

    template<class Object>
    auto Call(Object& object)
            -> decltype(this->__base::Call(SimpleDeligate<Object, TCollableEntity>(object, m_CollableEntity))) const {
        return __base::Call(SimpleDeligate<Object, TCollableEntity>(object, m_CollableEntity));
    }
};

template<class TCollableEntity, typename... Params>
Functor<TCollableEntity, Params...> make_functor(const TCollableEntity& collable_entity, Params&&... given_params) {
    return Functor<TCollableEntity, Params...>(collable_entity, std::forward<Params>(given_params)...);
}
