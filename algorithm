#include <iostream>
#include <random>

using namespace std;

template<typename T>
void swap(T&, T&);

template<typename T>
void qsort(T* feature, int* samples, int left, int right);

template<typename T>
int partition(T* feature, int* samples, int left, int right);


void shuffle(int* samples, int dim0);

void generate_samples_index(int*, int);

template<typename T>
void generate_feature(T*, int);

template<typename T>
void print(T*, int);

/////////////////////////////////////////////////////////////

void generate_samples_index(int* samples, int dim0){
    for(int i=0; i<dim0; i++){
        samples[i] = i;
    }
}

template<typename T>
void generate_feature(T* feature, int dim0){
    random_device rd;
    mt19937 gen(rd());
    
    uniform_real_distribution<T> dist(0, 20.0);
    for(int i=0; i<dim0; i++){
        feature[i] = dist(gen);
    }
}

template<typename T>
void print(T* arr, int dim0){
    if(dim0<=10){
         for(int i=0; i<dim0; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else{
        for(int i=0; i<5; i++){
            cout << arr[i] << " ";
        }

        cout << "..." << " ";

        for(int i=5; i>0; i--){
            cout << arr[dim0-i] << " ";
        }
        cout << endl;
    }
   
}

void shuffle(int* samples, int dim0){
    // Fisher–Yates_shuffle
    random_device sd;
    mt19937 gen(sd());
    
    for(int j=dim0-1; j>0; j--){
        uniform_int_distribution<> dist(0, j-1);
        int random_index = dist(gen);
        ::swap<int>(samples[random_index], samples[j]);
    }
}


template<typename T>
void qsort(T* feature, int* samples, int left, int right){
    if(right > left){
        int pivot_index = partition<T>(feature, samples, left, right);
        qsort<T>(feature, samples, left, pivot_index-1);
        qsort<T>(feature, samples, pivot_index+1, right);
    }
}


template<typename T>
int partition(T* feature, int* samples, int left, int right){
    T pivot_value = feature[right];
    int cur_index = left;
    for(int i=left; i<right; i++){
        if(feature[i] < pivot_value){
            ::swap<T>(feature[i], feature[cur_index]);
            ::swap<int>(samples[i], samples[cur_index]);
            cur_index++;
        }
        
    }
    ::swap<T>(feature[cur_index], feature[right]);
    ::swap<int>(samples[cur_index], samples[right]);
    return cur_index;
}


template<typename T>
void swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}



int main(){
    int dim0 = 90000000;
    int* samples = new int[dim0];
    generate_samples_index(samples, dim0);
    print(samples, dim0);


    float* feature = new float[dim0];
    generate_feature(feature, dim0);
    print(feature, dim0);

    // quick sort 
    qsort<float>(feature, samples, 0, dim0-1);
    cout << "feature values after quick sort." << endl;
    print(feature, dim0);
    cout << "samples index vlaues after quick sort." << endl;
    print(samples, dim0);


    // shuffle 
    int size = 10;
    int* samples1 = new int[size];
    generate_samples_index(samples1, size);
    print(samples1, size);
    shuffle(samples1, size);
    cout << "samples1 index vlaues after shuffle." << endl;
    print(samples1, size);
}
