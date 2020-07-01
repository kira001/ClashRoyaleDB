#ifndef DEEPPTR_H
#define DEEPPTR_H

template<class T>
class DeepPtr {
private:
    T* pointer;

public:

    DeepPtr(T* ptr = nullptr);
    DeepPtr(const DeepPtr& deepPtr);
    ~DeepPtr();

    T* operator->() const;
    T& operator*() const;
    DeepPtr& operator=(const DeepPtr& deepPtr);
    bool operator==(const DeepPtr& deepPtr) const;
    bool operator!=(const DeepPtr& deepPtr) const;
    bool operator<(const DeepPtr& deepPtr) const;

};

template<class T>
DeepPtr<T>::DeepPtr(T* ptr): pointer(ptr) {}

template<class T>
DeepPtr<T>::DeepPtr(const DeepPtr& deepPtr) : pointer(deepPtr.pointer != nullptr ? deepPtr.pointer->clone() : nullptr) {}

template<class T>
DeepPtr<T>::~DeepPtr<T>() { if (pointer) delete pointer; }



template<class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& deepPtr) {
    if (this != &deepPtr) {
        if (pointer) delete pointer;
        pointer = deepPtr.pointer != nullptr ? deepPtr.pointer->clone() : nullptr;
    }
    return *this;
}
template<class T>
T* DeepPtr<T>::operator->() const { return pointer; }

template<class T>
T& DeepPtr<T>::operator*() const { return *pointer; }

template<class T>
bool DeepPtr<T>::operator==(const DeepPtr& deepPtr) const { return *pointer == *deepPtr; }

template<class T>
bool DeepPtr<T>::operator!=(const DeepPtr& deepPtr) const { return *pointer != *deepPtr; }

template<class T>
bool DeepPtr<T>::operator<(const DeepPtr &deepPtr) const { return *pointer < *deepPtr; }



#endif // DEEPPTR_H
