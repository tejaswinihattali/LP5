#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Structure to store final results
struct Result {
    int minVal;
    int maxVal;
    long long sumVal;
    double avgVal;
};

class ArrayStatistics {

private:

    vector<int> arr;
    int size;

public:

    // Constructor
    ArrayStatistics(int n) {

        size = n;

        arr.resize(size);

        // Initialize array
        for(size_t i = 0; i < arr.size(); i++) {
            arr[i] = i + 1;
        }
    }


    // Sequential stats
    Result sequentialStats() {

        Result res;

        res.minVal = arr[0];
        res.maxVal = arr[0];
        res.sumVal = 0;

        for(size_t i = 0; i < arr.size(); i++) {

            if(arr[i] < res.minVal)
                res.minVal = arr[i];

            if(arr[i] > res.maxVal)
                res.maxVal = arr[i];

            res.sumVal += arr[i];
        }

        res.avgVal = (double)res.sumVal / arr.size();

        return res;
    }


    // Parallel stats
    Result parallelStats() {

        Result res;

        int globalMin = arr[0];
        int globalMax = arr[0];
        long long globalSum = 0;

        #pragma omp parallel num_threads(8) \
        reduction(min:globalMin) \
        reduction(max:globalMax) \
        reduction(+:globalSum)
        {

            #pragma omp for schedule(static)
            for(size_t i = 0; i < arr.size(); i++) {

                if(arr[i] < globalMin)
                    globalMin = arr[i];

                if(arr[i] > globalMax)
                    globalMax = arr[i];

                globalSum += arr[i];
            }
        }

        res.minVal = globalMin;
        res.maxVal = globalMax;
        res.sumVal = globalSum;
        res.avgVal = (double)globalSum / arr.size();

        return res;
    }

};

int main() {

    const int SIZE = 1000000;

    // Object creation
    ArrayStatistics obj(SIZE);

    double start, end;


    // Sequential execution
    start = omp_get_wtime();

    Result seq = obj.sequentialStats();

    end = omp_get_wtime();

    cout << "\nSequential Results:\n";
    cout << "Min = " << seq.minVal << endl;
    cout << "Max = " << seq.maxVal << endl;
    cout << "Sum = " << seq.sumVal << endl;
    cout << "Average = " << seq.avgVal << endl;
    cout << "Time = " << (end - start) << " sec\n";


    // Parallel execution
    start = omp_get_wtime();

    Result par = obj.parallelStats();

    end = omp_get_wtime();

    cout << "\nParallel Results:\n";
    cout << "Min = " << par.minVal << endl;
    cout << "Max = " << par.maxVal << endl;
    cout << "Sum = " << par.sumVal << endl;
    cout << "Average = " << par.avgVal << endl;
    cout << "Time = " << (end - start) << " sec\n";

    return 0;
}


