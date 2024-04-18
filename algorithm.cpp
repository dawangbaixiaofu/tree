#include <iostream>
#include <random>
#include <stack>
#include <math.h>


using namespace std;

////////////////////////////////////////////////////////////////
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



// interface for building a tree
struct node{
    float threshold;
    float impurity;
    int feature;
    node* left = nullptr;
    node* right = nullptr;
};

struct StackRecord{
    int parent;
    bool is_left;
    int start;
    int end;
    int depth;
    float impurity;
    

};

struct SplitRecord{
    int feature;
    int pos;
    float threshold;
    float improvement;
    float impurity_left;
    float impurity_right;

};

class object{
    // matrix 
};

class DepthFirstTreeBuild{
    public:
    int node_count = 0;
    int capacity = 2047;
    node* nodes = new node[capacity];
    int node_count = 0;

    SplitRecord split;
    
    int tree_leaf = -1;
    int tree_undefined = -2;
    int* samples;
    

    float X[100][10];
    float* y;
    
    void build();
    int add_node();
    void node_split(StackRecord* record, SplitRecord* split, float impurity);
    float node_impurity(int* samples, int start, int end);
    void bfs();
    void dfs();
};


/////////////////////////////////////////////////////////////

void DepthFirstTreeBuild::node_split(StackRecord* record, SplitRecord* split, float impurity){
    // find a best feature and corresponding threshold
    int n_features;
    int* features; // 0, 1, 2, ..., n_features-1
    
    int start = record->start;
    int end = record->end;
    float impurity = record->impurity;
    int random_subscript;
    int n_samples = (end-start);
    float feature_value[n_samples];
    int* features = new int[n_features];
    int* samples = new int[n_samples];

    SplitRecord best_record;

    random_device sd;
    mt19937 gen(sd());
    // shuffle features 
    for(int i=n_features-1; i>0; i--){
        uniform_int_distribution<> dist(0, i);
        random_subscript = dist(gen);
        ::swap<int>(features[i], features[random_subscript]);
        // generate features, reset feature_values 
        for(int i=start; i<end; i++){
            feature_value[i] = X[samples[i]][random_subscript];
        }
        // sort feature and samples
        ::qsort(feature_value, samples, start, end-1);

        // search best threshold
        // refresh sum_total which holds impurity information and compute sum_left and sum_right
        // seperatly to calculate information gain.
        


    }   



}




float DepthFirstTreeBuild::node_impurity(int* samples, int start, int end){
    // caculate impurity
    float impurity;
    int n_outputs;
    int n_classes;
    int n_node_samples = (end-start);
    float sum_total[n_outputs][n_classes]; // 二维数组
    
    int c;
    float count_k;


    for(int i = start; i<end; i++){
        int index = samples[i];
        for(int k=0; k<n_outputs; k++){
            c = y[index, k];
            sum_total[k][c] += 1;
        }
    }

    for(int k=0; k<n_outputs; k++){
        for(int c=0; c<n_classes; c++){
            count_k = sum_total[k][c];
            if(count_k>0.0){
                count_k /= n_node_samples;
                impurity -= count_k*log(count_k);
            }
        }
    }
    impurity /= n_outputs;
    return impurity;
}



void DepthFirstTreeBuild::build(){
    int dim0 = 100;
    int* samples;
    StackRecord record;

    // local var needed 
    float impurity;
    bool first = 1;
    bool is_leaf = 0;
    float EPSILON = 1.1920929e-07;
    float min_impurity_decrease = 0.01;


    
    stack<StackRecord> build_stack;
    build_stack.push({
        parent:tree_undefined,
        is_left:0,
        start:0,
        end:dim0,
        impurity:INFINITY
    }
    );
    

    while(!build_stack.empty()){
        record = build_stack.top();
        

        build_stack.pop();  
        // 1. current node whether is leaf node
        // current node samples, depth, 2*min_samples_leaf

        // root node 
        if(first){
            impurity = node_impurity(samples, record.start, record.end);
            first = 0;
        }
        else{
            impurity = record.impurity;
        }

        // 2. current node whether is leaf node
        // impurity < EPSILON
        is_leaf = (is_leaf or impurity < EPSILON);
        if(!is_leaf){
            // node split 
            node_split(&record, &split, impurity);

            // 3. current node whether is leaf node 
            // split.pos >= end or split.improvement + EPSILON < min_impurity_decrease

        }

        // add current node to tree, and return current node id
        // caculate current node id
        // if parent is undefined, then current node is root node
        // if parent exists, and is_left is true, then current node is nodes[parent].left = current node id
        // else nodes[parent].right = current node id
        int node_id = add_node();

        
        if(!is_leaf){
            // push splitted right node information on build_stack
            build_stack.push({
                parent:node_id,
                is_left:0,
                start:split.pos,
                end:record.end,
                depth:record.depth+1,
                impurity:split.impurity_right
            });

            // push splitted left node information on build_stack
            build_stack.push({
                parent:node_id,
                is_left:1,
                start:record.start,
                end:split.pos,
                depth:record.depth+1,
                impurity:split.impurity_left
            });
        }

    }
    
}



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
        uniform_int_distribution<> dist(0, j);
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
