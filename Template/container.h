#ifndef CONTAINER_H
#define CONTAINER_H

template<class T>
class Container {
private:
    unsigned int capacity;
    unsigned int size;
    T* array;

    void resizeArray();

public:

    Container();
    Container(const Container& container);
    ~Container();

    unsigned int getCapacity() const;
    unsigned int getSize() const;

    Container& operator=(const Container& container);
    T& operator[](unsigned int i) const;
    bool operator==(const Container& container) const;
    bool operator!=(const Container& container) const;

    void clear();
    void insert(const T& obj);
    void remove(const T& obj);
    int search(const T& obj) const;
    void remove(int pos);
};


template<class T>
Container<T>::Container() : capacity(0), size(0), array(nullptr) {}

template<class T>
Container<T>::Container(const Container& container) : capacity(container.capacity), size(container.size), array(new T[capacity]) {
    for (unsigned int i = 0; i < size; ++i)
        array[i] = container.array[i];
}

template<class T>
Container<T>::~Container<T>() { if (array) delete[] array; }



template<class T>
unsigned int Container<T>::getCapacity() const { return capacity; }

template<class T>
unsigned int Container<T>::getSize() const { return size; }



template<class T>
Container<T>& Container<T>::operator=(const Container& container) {
    if(!container.getCapacity()&&!container.getSize())
        clear();
    else if(this!= &container){
        delete[] array;
        capacity=container.getCapacity();
        size=container.getSize();
        array= new T[capacity];
        for(unsigned int i=0; i<size;i++)
            array[i]=container[i];
    }
    return *this;
}

template<class T>
T& Container<T>::operator[](unsigned int i) const { return array[i]; }

template<class T>
bool Container<T>::operator==(const Container& container) const {
    if (array && container.array) {
        if (size == container.size) {
            for (unsigned int i = 0; i < size; ++i) {
                if (array[i] != container.array[i])
                    return false;
            }
            return true;
        }
    }
    return false;
}

template<class T>
bool Container<T>::operator!=(const Container& container) const {
    return !(*this == container);
}



template<class T>
void Container<T>::clear() {
    delete [] array;
    array=nullptr;
    capacity=0;
    size=0;
}

template<class T>
void Container<T>::resizeArray() {
    if(!capacity) {capacity= 1; array= new T[capacity];}
    else{
        capacity=capacity*2;
        T* tmp= new T[capacity];
        for(unsigned int i=0; i<size; i++)
            tmp[i]=array[i];
        delete[] array;
        array=tmp;
    }
}

template<class T>
void Container<T>::insert(const T& obj) {
    if (size + 1 > capacity) resizeArray();
    size++;
    array[size-1] = obj;
}

template<class T>
void Container<T>::remove(const T& obj) {
    if (size > 0) {
        int pos = search(obj);
        if (pos != -1) {
            unsigned int u_pos = static_cast<unsigned int>(pos);
            T* tmp = new T[capacity];
            unsigned int j = 0;
            for (unsigned int i = 0; i < size; ++i) {
                if (i != u_pos) {
                    tmp[j] = array[i];
                    j++;
                }
            }
            size--;
            delete[] array;
            array = tmp;
        }
    }
}

template<class T>
int Container<T>::search(const T& obj) const {
    for (unsigned int i = 0; i < size; ++i) {
        if (array[i] == obj)
            return static_cast<int>(i);
    }
    return -1;
}



template<class T>
void Container<T>::remove(int pos) {
    if (pos >=0 && pos < static_cast<int>(size)) {
        unsigned int u_pos = static_cast<unsigned int>(pos);
        T* tmp = new T[capacity];
        unsigned int j = 0;
        for (unsigned int i = 0; i < size; ++i) {
            if (i != u_pos) {
                tmp[j] = array[i];
                j++;
            }
        }
        size--;
        delete[] array;
        array = tmp;
    }
}

#endif // CONTAINER_H
