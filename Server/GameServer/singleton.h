#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

template<class T>
class Singleton {
public:
    static T* Instance();

private:
    Singleton();
    Singleton(Singleton<T> const&);
    Singleton<T>& operator= (const Singleton<T>& t);
    virtual ~Singleton();
    static T* instance;
};

template<class T>
T* Singleton<T>::instance = nullptr;

template<class T>
T* Singleton<T>::Instance()
{
    if (instance == nullptr) {
        instance = new T;
    }
    return instance;
}

#endif /* SINGLETON_H_ */
