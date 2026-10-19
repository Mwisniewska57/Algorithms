
#include <iostream>
#include <cstdlib>

template <typename T>
struct dynamic_array {
    int size;
    int capacity;   //maks liczba elementow ktore sie mieszcza bez realokacji
    T* data;

    dynamic_array() {  //konstruktor
        size = 0;
        capacity = 2;
        data = new T[capacity]; //tablica t
    }

    ~dynamic_array() {  ///dekonstruktor
        delete[] data;  //zwalnianie pamieci zaalok w konstukt
    }
    void resize(int newcapacity) {
        T* new_data = new T[newcapacity];
        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = newcapacity;

    }
    void push_back(T val) {    //dodawanie na koncu
        if (size < capacity) {
            data[size] = val;
            size++;
        }
        else {
            resize(capacity * 2);
            data[size] = val;
            size++;
        }
    }

    T at(int index) {  //zwracanie elementu na danym indeksie
        if (index < 0 || index >= size) {
            throw std::out_of_range("index out of range");
        }

        return data[index];
    }
    void clear() {
        delete[] data;
        size = 0;
        capacity = 2;
        data = new T[capacity];
    }
    void ielement(int index,T new_data) {   ///podmiana i elementu 
        if (index < 0 || index >= size) {
            throw std::out_of_range("index out of range");
        }
        else {
            data[index] = new_data;
        }
    }

    void bubble_sort(bool (*cmp)(const T& a, const T& b)) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                if (!cmp(data[j], data[j + 1])) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
    void message() {
        std::cout <<"size: "<<size<< std::endl;
        std::cout <<"capacity: "<<capacity<<std::endl;
        if (size == 0) {
            std::cout << "nie ma elementow" << std::endl;
        }
        else if(size> 5) {
            for (int i = 0; i < 5; i++) {
                std::cout << "element nmr" << i << " " << data[i] << std::endl;
            }
        }
        else 
            for (int i = 0; i < size; i++) {
                std::cout << "element nmr" << i << " " << data[i] << std::endl;
            }

        
    }
};

struct Person {
    int age;
    std::string name;
};
bool cmpint(const int& a, const int& b) {
    return a < b;
}

bool compare(const Person& lhs, const Person& rhs) {
    return lhs.age < rhs.age;
}

int main() {
    srand(time(NULL));
    double max_time = 0;
    const int n = pow(10, 1);
    dynamic_array<int> d;
    clock_t t_start = clock();
    for (int i = 0; i < n; i++) {
        int v = rand() % 10000;
        clock_t t1 = clock();
        d.push_back(v);
        clock_t t2 = clock();
        double timepe = double(t2 - t1) / CLOCKS_PER_SEC;
        if (timepe > max_time) {
            max_time = timepe;
            std::cout << "nowy najgorszy czas dodawania: " << i << ": " << max_time << "s" << std::endl;
        }

    }
    clock_t t_end = clock();
    double ttime = (double(t_end) - double(t_start)) / CLOCKS_PER_SEC;
    double average = ttime / n;
    std::cout << "liczba elementow: " << n << std::endl;
    std::cout << "czas calkowity:" << ttime << " s" << std::endl;
    std::cout << "sredni czas " << average << " s" << std::endl;
    std::cout << "najgorszy czas" << max_time << " s" << std::endl;
    d.message();
    
    dynamic_array<int> arr;
    for (int i = 0; i < 10; i++) {
        arr.push_back(rand() % 100);
    }
    std::cout << "przed sortowaniem:"<<std::endl;
    for (int i = 0; i < arr.size; i++) {
        std::cout << arr.at(i) << " ";
    }
    arr.bubble_sort(cmpint);
    std::cout << "po sortowaniu";
    for (int i = 0; i < arr.size; i++) {
        std::cout << arr.at(i) << " ";
    }
    //dynamic_array<Person> arr;
    //for (int i = 10; i >= 0; i--) {
    //    arr.push_back({ i, "imie" });
    //        std::cout << "nowy element: "<< arr.at(i) << std::endl;
    //        std::cout << "size: " << arr.size << std::endl;
    //        std::cout << "capacity: " << arr.capacity << std::endl;
    //}

    //arr.bubble_sort(compare);

    //for (int i = 0; i < 11; i++) {
    //    std::cout << arr.at(i).age << ' ' << arr.at(i).name << std::endl;
    //}

 /*   const int n = pow(10, 5);
    dynamic_array<int> d;
    for (int i = 0; i < n; i++) {

    }
}*/
}