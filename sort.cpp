/*#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubbleSortParallel(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        #pragma omp parallel for
        for (int j = (i % 2); j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool isSwapped = false;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]), isSwapped = true;
        }

        if (!isSwapped)
            break;
    }
}

void merge1(vector<int> &arr, int left, int mid, int right)
{
    vector<int> temp(right - left + 1); 
    int ptr = 0, i = left, j = mid + 1;

    while(i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
            temp[ptr++] = arr[i++];
        else 
            temp[ptr++] = arr[j++];
    }

    while(i <= mid)
        temp[ptr++] = arr[i++];
    
    while(j <= right)
        temp[ptr++] = arr[j++];

    for (int i = 0; i < right - left + 1; i++)
    {
        arr[i + left] = temp[i];
    }
}

void mergeSortUtil(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortUtil(arr, left, mid);
    mergeSortUtil(arr, mid + 1, right);
    merge1(arr, left, mid, right);
}

void mergeSortUtilParallel(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    if (right - left < 1000)
    {
        mergeSortUtil(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr, left, mid);

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr, mid + 1, right);

    #pragma omp taskwait
    merge1(arr, left, mid, right);
}

void mergeSort(vector<int> &arr)
{
    int n = arr.size();
    mergeSortUtil(arr, 0, n - 1);
}

void mergeSortParallel(vector<int> &arr)
{
    int n = arr.size();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSortUtilParallel(arr, 0, n - 1);
        }
    }
}

void printArray(const vector<int> &arr)
{
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

int main() 
{
    int n = 100000;
    vector<int> arr(n);

    srand(time(0));

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;

    double t1, t2;

    t1 = omp_get_wtime();
    vector<int> arrCopy1 = arr;
    bubbleSort(arrCopy1);
    t2 = omp_get_wtime();
    // printArray(arrCopy1);
    cout << "Time taken by sequential bubble sort: " << t2 - t1 << " seconds" << endl;

    t1 = omp_get_wtime();
    vector<int> arrCopy2 = arr;
    bubbleSortParallel(arrCopy2);
    t2 = omp_get_wtime();
    // printArray(arrCopy2);
    cout << "Time taken by parallel bubble sort: " << t2 - t1 << " seconds" << endl;

    t1 = omp_get_wtime();
    vector<int> arrCopy3 = arr;
    mergeSort(arrCopy3);
    t2 = omp_get_wtime();
    // printArray(arrCopy3);
    cout << "Time taken by sequential merge sort: " << t2 - t1 << " seconds" << endl;

    t1 = omp_get_wtime();
    vector<int> arrCopy4 = arr;
    mergeSortParallel(arrCopy4);
    t2 = omp_get_wtime();
    // printArray(arrCopy4);
    cout << "Time taken by parallel merge sort: " << t2 - t1 << " seconds" << endl;
}*/


#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubbleSort(vector<int> &arr){
    int n = arr.size();
    for(int i=0; i<n-1; i++){
        bool isSwapped = false;
        for(int j=0; j<n-1-i;j++){
            if(arr[j]>arr[j+1])
                swap(arr[j],arr[j+1]); isSwapped=true;
        }
        if (!isSwapped)
            break;
    }
}

void bubbleSortParallel(vector<int>& arr){
    int n = arr.size();
    for(int i = 0; i<n; i++){
        #pragma omp parallel for
        for(int j = (i%2); j<n-1; j+=2){
            if (arr[j] > arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }
}

void merge1(vector<int> &arr, int left, int mid, int right){
    vector<int> temp(right-left+1);
    int ptr = 0, i = left, j=mid+1;

    while (i<=mid && j<=right){
        if (arr[i] < arr[j])
            temp[ptr++] = arr[i++];
        else
            temp[ptr++] = arr[j++];
    }

    while (i<=mid){
        temp[ptr++] = arr[i++];
    }

    while (j<=right){
        temp[ptr++] = arr[j++];
    }

    for (int i=0; i<(right-left+1);i++){
        arr[i+left] = temp[i];
    }
}

void mergeSortUtil(vector<int> &arr, int left, int right){
    if (left>= right)
        return;

    int mid = left + (right-left)/2;
    mergeSortUtil(arr,mid,left);
    mergeSortUtil(arr,mid+1,right);
    merge1(arr,left,mid,right);
}

void mergeSortUtilParallel(vector<int> &arr, int left, int right){
    if (left>=right)
        return;

    if (right-left < 1000){
        mergeSortUtil(arr,left,right);
        return;
    }

    int mid = left + (right-left)/2;

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr,mid,left);

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr,mid+1,right);

    #pragma omp taskwait
    merge1(arr,left,mid,right);
}

void mergeSort(vector<int> &arr){
    int n = arr.size();
    mergeSortUtil(arr, 0 ,n-1);
}

void mergeSortParallel(vector<int> &arr){
    int n= arr.size();;
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortUtilParallel(arr,0,n-1);
    }
}

void printArray(const vector<int> &arr){
    for(int i:arr){
        cout<<i<<" ";
    cout<<endl;
    }
}

int main(){
    int n = 1000000;
    vector<int> arr(n);

    srand(time(0));

    for(int i=0; i<n;i++){
        arr[i] = rand() % 10000;
    }

    double t1,t2;

    t1=omp_get_wtime();
    vector<int> arrCopy1=arr;
    bubbleSort(arrCopy1);
    t2=omp_get_wtime();
    cout<<"Time taken by Sequential Bubble Sort: "<<t2-t1<<"seconds"<<endl;

    t1=omp_get_wtime();
    vector<int> arrCopy2=arr;
    bubbleSortParallel(arrCopy2);
    t1=omp_get_wtime();
    cout<<"Time taken by Parallel Bubble Sort: "<<t2-t1<<"seconds"<<endl;

    t1=omp_get_wtime();
    vector<int> arrCopy3=arr;
    mergeSort(arrCopy3);
    t1=omp_get_wtime();
    cout<<"Time taken by Sequential Merge Sort: "<<t2-t1<<"seconds"<<endl;

    t1=omp_get_wtime();
    vector<int> arrCopy4=arr;
    mergeSortParallel(arrCopy4);
    t1=omp_get_wtime();
    cout<<"Time taken by Parallel Merge Sort: "<<t2-t1<<"seconds"<<endl;
    return 0;
}


/*#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubbleSortParallel(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        #pragma omp parallel for
        for (int j = (i % 2); j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool isSwapped = false;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]), isSwapped = true;
        }

        if (!isSwapped)
            break;
    }
}

void merge1(vector<int> &arr, int left, int mid, int right)
{
    vector<int> temp(right - left + 1); 
    int ptr = 0, i = left, j = mid + 1;

    while(i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
            temp[ptr++] = arr[i++];
        else 
            temp[ptr++] = arr[j++];
    }

    while(i <= mid)
        temp[ptr++] = arr[i++];
    
    while(j <= right)
        temp[ptr++] = arr[j++];

    for (int i = 0; i < right - left + 1; i++)
    {
        arr[i + left] = temp[i];
    }
}

void mergeSortUtil(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortUtil(arr, left, mid);
    mergeSortUtil(arr, mid + 1, right);
    merge1(arr, left, mid, right);
}

void mergeSortUtilParallel(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    if (right - left < 1000)
    {
        mergeSortUtil(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr, left, mid);

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr, mid + 1, right);

    #pragma omp taskwait
    merge1(arr, left, mid, right);
}

void mergeSort(vector<int> &arr)
{
    int n = arr.size();
    mergeSortUtil(arr, 0, n - 1);
}

void mergeSortParallel(vector<int> &arr)
{
    int n = arr.size();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSortUtilParallel(arr, 0, n - 1);
        }
    }
}

void printArray(const vector<int> &arr)
{
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

int main() 
{
    int n = 100000;
    vector<int> arr(n);

    srand(time(0));

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;

    double t1, t2;

    t1 = omp_get_wtime();
    vector<int> arrCopy1 = arr;
    bubbleSort(arrCopy1);
    t2 = omp_get_wtime();
    // printArray(arrCopy1);
    cout << "Time taken by sequential bubble sort: " << t2 - t1 << " seconds" << endl;

    t1 = omp_get_wtime();
    vector<int> arrCopy2 = arr;
    bubbleSortParallel(arrCopy2);
    t2 = omp_get_wtime();
    // printArray(arrCopy2);
    cout << "Time taken by parallel bubble sort: " << t2 - t1 << " seconds" << endl;

    t1 = omp_get_wtime();
    vector<int> arrCopy3 = arr;
    mergeSort(arrCopy3);
    t2 = omp_get_wtime();
    // printArray(arrCopy3);
    cout << "Time taken by sequential merge sort: " << t2 - t1 << " seconds" << endl;

    t1 = omp_get_wtime();
    vector<int> arrCopy4 = arr;
    mergeSortParallel(arrCopy4);
    t2 = omp_get_wtime();
    // printArray(arrCopy4);
    cout << "Time taken by parallel merge sort: " << t2 - t1 << " seconds" << endl;
}

/*

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubbleSort(vector<int> &arr){
    int n = arr.size();
    for(int i=0; i<n-1; i++){
        bool isSwapped = false;
        for(int j=0; j<n-1-i;j++){
            if(arr[j]>arr[j+1])
                swap(arr[j],arr[j+1]); isSwapped=true;
        }
        if (!isSwapped)
            break;
    }
}

void bubbleSortParallel(vector<int>& arr){
    int n = arr.size();
    for(int i = 0; i<n; i++){
        #pragma omp parallel for
        for(int j = (i%2); j<n-1; j+=2){
            if (arr[j] > arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }
}

void merge1(vector<int> &arr, int left, int mid, int right){
    vector<int> temp(right-left+1);
    int ptr = 0, i = left, j=mid+1;

    while (i<=mid && j<=right){
        if (arr[i] < arr[j])
            temp[ptr++] = arr[i++];
        else
            temp[ptr++] = arr[j++];
    }

    while (i<=mid){
        temp[ptr++] = arr[i++];
    }

    while (j<=right){
        temp[ptr++] = arr[j++];
    }

    for (int i=0; i<(right-left+1);i++){
        arr[i+left] = temp[i];
    }
}

void mergeSortUtil(vector<int> &arr, int left, int right){
    if (left>= right)
        return;

    int mid = left + (right-left)/2;
    mergeSortUtil(arr,mid,left);
    mergeSortUtil(arr,mid+1,right);
    merge1(arr,left,mid,right);
}

void mergeSortUtilParallel(vector<int> &arr, int left, int right){
    if (left>=right)
        return;

    if (right-left < 1000){
        mergeSortUtil(arr,left,right);
        return;
    }

    int mid = left + (right-left)/2;

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr,mid,left);

    #pragma omp task shared(arr)
    mergeSortUtilParallel(arr,mid+1,right);

    #pragma omp taskwait
    merge1(arr,left,mid,right);
}

void mergeSort(vector<int> &arr){
    int n = arr.size();
    mergeSortUtil(arr, 0 ,n-1);
}

void mergeSortParallel(vector<int> &arr){
    int n= arr.size();;
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortUtilParallel(arr,0,n-1);
    }
}

void printArray(const vector<int> &arr){
    for(int i:arr){
        cout<<i<<" ";
    cout<<endl;
    }
}

int main(){
    int n = 1000000;
    vector<int> arr(n);

    srand(time(0));

    for(int i=0; i<n;i++){
        arr[i] = rand() % 10000;
    }

    double t1,t2;

    t1=omp_get_wtime();
    vector<int> arrCopy1=arr;
    bubbleSort(arrCopy1);
    t2=omp_get_wtime();
    cout<<"Time taken by Sequential Bubble Sort: "<<t2-t1<<"seconds"<<endl;

    t1=omp_get_wtime();
    vector<int> arrCopy2=arr;
    bubbleSortParallel(arrCopy2);
    t1=omp_get_wtime();
    cout<<"Time taken by Parallel Bubble Sort: "<<t2-t1<<"seconds"<<endl;

    t1=omp_get_wtime();
    vector<int> arrCopy3=arr;
    mergeSort(arrCopy3);
    t1=omp_get_wtime();
    cout<<"Time taken by Sequential Merge Sort: "<<t2-t1<<"seconds"<<endl;

    t1=omp_get_wtime();
    vector<int> arrCopy4=arr;
    mergeSortParallel(arrCopy4);
    t1=omp_get_wtime();
    cout<<"Time taken by Parallel Merge Sort: "<<t2-t1<<"seconds"<<endl;
    return 0;
}

/*
#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

using namespace std;

// ---------------- SEQUENTIAL BUBBLE SORT ----------------
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- PARALLEL BUBBLE SORT ----------------
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {

        #pragma omp parallel for
        for (int j = (i % 2); j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- MERGE FUNCTION ----------------
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// ---------------- SEQUENTIAL MERGE SORT ----------------
void sequentialMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ---------------- PARALLEL MERGE SORT ----------------
void parallelMergeSort(vector<int>& arr, int left, int right) {  // add int depth = 0 if want to limit depth of parallelism

    if (left < right) {

        int mid = (left + right) / 2;
        // if (depth < 4) { // optional depth check to limit parallelism, cause generally system has limited thread so 4 cores is like 2^4 = 16 threads, so we can limit to that
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, right);
        }
        // else {
        //     sequentialMergeSort(arr, left, mid);
        //     sequentialMergeSort(arr, mid + 1, right);    
        // }    

        merge(arr, left, mid, right);
    }
}

int main() {

    int SIZE;

    cout << "Enter array size: ";
    cin >> SIZE;

    vector<int> original(SIZE);

    // Random array generation
    for (int i = 0; i < SIZE; i++) {
        original[i] = rand() % 1000; // OR cin >> original[i] if want to input manually
    }

    vector<int> a1 = original;
    vector<int> a2 = original;
    vector<int> a3 = original;
    vector<int> a4 = original;

    double start, end;

    // ---------------- SEQUENTIAL BUBBLE SORT ----------------
    start = omp_get_wtime();
    sequentialBubbleSort(a1);
    end = omp_get_wtime();
    cout << "\nSequential Bubble Sort Time: " << (end - start) * 1000 << " ms" << endl;

    // ---------------- PARALLEL BUBBLE SORT ----------------
    start = omp_get_wtime();
    parallelBubbleSort(a2);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << (end - start) * 1000 << " ms" << endl;

    // ---------------- SEQUENTIAL MERGE SORT ----------------
    start = omp_get_wtime();
    sequentialMergeSort(a3, 0, SIZE - 1);
    end = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << (end - start) * 1000 << " ms" << endl;

    // ---------------- PARALLEL MERGE SORT ----------------
    start = omp_get_wtime();
    parallelMergeSort(a4, 0, SIZE - 1);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << (end - start) * 1000 << " ms" << endl;

    return 0;  
}



COMPILATION:
g++ -fopenmp hpc2.cpp -o hpc2

SET THREADS:
export OMP_NUM_THREADS=4

RUN:
./hpc2

*/

/*
#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

using namespace std;

// ---------------- Sequential Bubble Sort ----------------
void sequentialBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- Parallel Bubble Sort ----------------
// Odd-Even Transposition Sort
void parallelBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n; i++) {

        // Even Phase
        if (i % 2 == 0) {

            #pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2) {

                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }

        // Odd Phase
        else {

            #pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2) {

                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

// ---------------- Merge Function ----------------
void merge(vector<int>& arr, int low, int mid, int high) {

    vector<int> temp;

    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {

        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= high) {
        temp.push_back(arr[j]);
        j++;
    }

    for (int k = low; k <= high; k++) {
        arr[k] = temp[k - low];
    }
}

// ---------------- Sequential Merge Sort ----------------
void sequentialMergeSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int mid = (low + high) / 2;

        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// ---------------- Parallel Merge Sort ----------------
void parallelMergeSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

// ---------------- Print Array ----------------
void printArray(vector<int>& arr) {

    for (int x : arr) {
        cout << x << " ";
    }

    cout << endl;
}

int main() {

    vector<int>arr;
    int bubbleN=5000;

    for(int i=0;i<bubbleN;i++)
    {
        arr.push_back(rand()%bubbleN);
        //cout<<arr[i]<<" ";
    }

    // Copies of original array
    vector<int> bubbleSeq = arr;
    vector<int> bubblePar = arr;

    vector<int>arr1;
    int mergeN=1900000;

    for(int i=0;i<mergeN;i++)
    {
        arr1.push_back(rand()%mergeN);
        //cout<<arr[i]<<" ";
    }
    vector<int> mergeSeq = arr1;
    vector<int> mergePar = arr1;

    // Sequential Bubble Sort
    double start = omp_get_wtime();

    sequentialBubbleSort(bubbleSeq,bubbleN);

    double end = omp_get_wtime();

    double seqBubbleTime = end - start;

    cout << "\nSequential Bubble Sort:\n";

    cout << "Time Taken: "<< seqBubbleTime<< " seconds\n";

    // Parallel Bubble Sort
    start = omp_get_wtime();

    parallelBubbleSort(bubblePar, bubbleN);

    end = omp_get_wtime();

    double parBubbleTime = end - start;

    cout << "\nParallel Bubble Sort:\n";

    cout << "Time Taken: "<< parBubbleTime<< " seconds\n";

    cout << "Speedup: "<< seqBubbleTime / parBubbleTime<< endl;

    // Sequential Merge Sort
    start = omp_get_wtime();

    sequentialMergeSort(mergeSeq, 0, mergeN- 1);

    end = omp_get_wtime();

    double seqMergeTime = end - start;

    cout << "\nSequential Merge Sort:\n";

    cout << "Time Taken: "<< seqMergeTime<< " seconds\n";

    // Parallel Merge Sort
    start = omp_get_wtime();

    parallelMergeSort(mergePar, 0, mergeN - 1);

    end = omp_get_wtime();

    double parMergeTime = end - start;

    cout << "\nParallel Merge Sort:\n";

    cout << "Time Taken: "<< parMergeTime<< " seconds\n";

    cout << "Speedup: "<< seqMergeTime / parMergeTime<< endl;

    return 0;
}*/
