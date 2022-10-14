#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton
{
public:
    static T* instance()
    {
        static tInstance a;
        return &a;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton &&) = delete;
    Singleton& operator=(Singleton&&) = delete;
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
private:
    struct tInstance : public T {};
};

#endif // SINGLETON_H
