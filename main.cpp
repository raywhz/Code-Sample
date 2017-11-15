/**  
    code_sample
    main.cpp
    Created by Haozhou Wu on 8/23/17.
 
    A range filter and a median filter are created respectively.
    Both filters are tested in main function.
*/

#include <iostream>
#include <vector>

using namespace std;

/*
    The Range filer crops all the values that are below or above the detection range.
    Input: vector pointer
    Output: the same vector pointer
*/
class Rangefilter{
public:
    Rangefilter(int N, float max, float min){
        array_length = N;
        range_max = max;                        // Detection range
        range_min = min;
    };
    
    void filter1(vector<float>& nums){
        for(int i = 0; i < array_length; i++){
            if(nums[i] < range_min)
                nums[i] = range_min;
            if(nums[i] > range_max)
                nums[i] = range_max;
        }
    
    };
private:
    int array_length;
    float range_max, range_min;
};


/*
    Tha median filter returns a pointer to a 2-D vector called "table".
    "table" is N*D. N is array length. D is the number of previous scans.
    Medians are stored in table[i][0], i ~ [0, N).
    Previous scan inputs are stored in table[i][j], j ~ [1, D+1]
        i.e. last input scans are stored in table[i][1]
             input scans before last scan are in table[i][2]...
*/
class Medianfilter{
public:
    Medianfilter(int N = 0, int D = 0){         // N array length, D #of prev scans
        array_length = N;
        prev_scan = D;
    };
    
    void filter2(vector<vector<float>>&table, vector<float>&data){
        // have to know if it's the first D scans
        size_t scan_times = table[0].size();
        if (scan_times == 0){
            for (int i = 0; i < array_length; i++){
                table[i].insert(table[i].begin(), data[i]);
                GetMedian(table[i]);
            }
        }
        else {
            if (scan_times <= prev_scan+1){
                for (int i = 0; i < array_length; i++){
                    table[i][0] = data[i];
                    GetMedian(table[i]);
                }
            }
            else{
                for (int i = 0; i < array_length; i++){
                    table[i][0] = data[i];
                    table[i].resize(prev_scan+1);   // store only previous D inputs
                    GetMedian(table[i]);
                    
                }
            }
        }
    };

    // Calculate the median and insert into the begining of the table
    void GetMedian(vector<float>&data){
        float median;
        size_t size = data.size();
        vector<float> temp(size);
        
        for (int i = 0; i < size; i++){
            temp[i] = data[i];
        }

        sort(temp.begin(), temp.end());
        if (size%2 == 0)
            median = (temp[size/2-1] + temp[size/2])/2;
        else
            median = temp[size/2];
        
        data.insert(data.begin(), median);
    };
    
    
private:
    int prev_scan, array_length;
    
};



int main(int argc, const char * argv[]) {
    int N = 5, D = 3;                                       // array length, prev scans
    float range_max = 50, range_min = 0.03;                 // detection range
    Rangefilter f1(N, range_max, range_min);
    
    // tests with values out of range
    vector<float> data = {0.001,0.02,3,400,55};
    f1.filter1(data);
    cout << "Range filter testing"<<endl;
    cout << "Output of data {0.001,0.02,3,400,55} is: " << endl;
    for (int n = 0; n<data.size(); n++)
        cout<<data[n]<<" ";
    
    cout << endl << endl << "Median filter testing" << endl;
    
    // create a table to store medians and inputs
    vector<vector<float>>table(N,vector<float>(0));
    Medianfilter f2(N, D);


    // Testing by the given example
    vector<vector<float>>test(N,vector<float>(5));
    test[0] = {0,1,2,1,3};
    test[1] = {1,5,7,1,3};
    test[2] = {2,3,4,1,0};
    test[3] = {3,3,3,1,3};
    test[4] = {10,2,4,0,0};
    for (int i = 0; i<5; i++){
        f2.filter2(table, test[i]);
        cout << "Median: ";
        for(int j = 0; j<N; j++){
            cout << table[j][0] << " ";
        }
        cout << endl;
    }
    
    return 0;
}

















