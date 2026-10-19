
#include <iostream>
#include "dynamiczna.h"
#include<stdexcept>
#include <cstdlib>
#include<ctime>
#include<cmath>

template <typename T>
class Heap {
private:
    dynamic_array<T> arr;

    static int parent(int i) {
        return(i - 1) / 2;
    }
    static int left(int i) {
        return 2 * i + 1;
    }
    static int right(int i) {
        return 2 * i + 2;
    }
    void kopiecgora(int i) {
        if (i == 0){
            return;
        }
        int p = parent(i);
        if (arr.data[i] > arr.data[p]){
            T temp = arr.data[i];
            arr.data[i]=arr.data[p];
            arr.data[p] = temp;
            kopiecgora(p);
     }
        
    }
    void kopiecwdol(int i) {
        int l = left(i);
        int r = right(i);
        int n = arr.size;
        int  wiekszy = i;
        if (l < n && arr.data[l] >arr.data[wiekszy]) {
            wiekszy = l;
        }
        if (r<n && arr.data[r]>arr.data[wiekszy]) {
            wiekszy = r;
        }
        if (wiekszy != i) {
            T temp = arr.data[i];
            arr.data[i] = arr.data[wiekszy];
            arr.data[wiekszy] = temp;
            kopiecwdol(wiekszy);
        }
    }
public:
    void info() {
        arr.message();
    }
    void push(T value) {
        arr.push_back(value);
        int i = arr.size - 1;
        kopiecgora(i);
       
    }
    T poll() {
        if (arr.size == 0) throw std::out_of_range("pusty kopiec");
        else {
            T root = arr.data[0];
            T last = arr.data[arr.size - 1];
            arr.ielement(0, last);
            arr.size--;
            if (arr.size > 0) {
                kopiecwdol(0);
            }
            return root;

        }
    }
    void clear() {
        arr.clear();
    }
};
int main()
{
    srand(time(NULL));
    const int maxo = 1;
    Heap<int> b;
    for (int o = 1; o <= maxo; o++) {
        const int n = pow(10, o);
        std::cout << "Rozmiar danych: " << n << std::endl;
        clock_t t_start = clock();
        for (int i = 0; i < n; i++) {
            int v = ((rand() << 15) + rand()) % 5;
            b.push(v);
        }
        std::cout << "Po dodaniu:" << std::endl;
        b.info();
        clock_t t_end = clock();
        double totalczasdod = double(t_end - t_start) / CLOCKS_PER_SEC;
        double avgczasdod = totalczasdod / n;
        std::cout << "czas dodawania: " << totalczasdod << " s" << std::endl;
        std::cout << "sredni czas dodawania: " << avgczasdod << " s" << std::endl;
        t_start = clock();
        for (int i = 0; i < n; i++) {
            
            int wynik = b.poll();
            std::cout<< wynik<<std::endl;
        }
        
        t_end = clock();
        double pollczast = double(t_end - t_start) / CLOCKS_PER_SEC;
        double pollavg = pollczast / n;
        std::cout << "czas pobierania: " << pollczast << " s" << std::endl;
        std::cout << "sredni czas pobierania: " << pollavg << " s" << std::endl;
        b.info();
        b.clear();

    }
    return 0;
    /* Heap<int> h;
    h.push(10);
    h.push(50);
    h.push(20);
    h.push(70);
    h.push(30);
    h.push(16);
    h.push(59);
    h.push(24);
    h.push(78);
    h.push(33);
    h.push(12);
    h.push(56);
    h.push(21);
    h.push(67);
    h.push(39);
    h.info();
    std::cout << "Usuwanie roota" << std::endl;
    h.poll();
    h.info();
    std::cout << "dodaje jeszcze jedno" << std::endl;
    h.push(15);
    h.info();
    std::cout << "czyszczenie" << std::endl;
    h.clear();
    std::cout << "po czyscznieu" << std::endl;
    h.info();
    return 0;*/
}

