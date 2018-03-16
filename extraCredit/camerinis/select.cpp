#include<algorithm>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
using namespace std;

//finds the k-th element in the vector v using O(n)-time
//start is the starting index in the range in v
//fin is the last index in the range in v
//Initially, start = 0, fin = v.size()-1
int select(vector<int> &v, int start, int fin, int k);
//initializes v with integers from standard input cin
void init(vector<int> &v);

int main(){
    vector<int> v;   
    init(v);
    int vsize = v.size();
    int mid = vsize >> 1;//divide by 2
    if(vsize % 2 == 0)
        mid--;
    int find_median = select(v, 0, v.size()-1, mid);
    cout << "found median is " << find_median << ", " 
        << mid << "-th element of v" << endl;
}//main
int select(vector<int> &v, int start, int fin, int k){

    int vsize = fin - start + 1;
    if(start == fin)
        return v[start];
    else if(start > fin)
        return -1;
    int msize = ceil((double)vsize/5);

    vector<int> medians(msize, 0);
    int med_ind = 0;
    for(int i = start; i <= fin; i = i + 5){
        vector<int> temp(5, 0);
        int j = 0;
        for(; j < 5 && (i + j)<= fin; j++){
            temp[j] = v[i+j];
        }//for j
        if(j < 5)
            temp.resize(j);
        sort(temp.begin(), temp.end());
        if(j == 5)
            medians[med_ind++] = temp[2];
        else{
            int jmid = j >> 1;//divide by 2
            if(j % 2 == 0)
                jmid--;
            medians[med_ind++] = temp[jmid];

            }
    }//for i
    //so far we selected medians of n/5 groups of 5 elem
    int mid = msize >> 1; //divide by 2
    if((msize % 2) == 0)
        mid--;
    int x = select(medians, 0, msize - 1, mid);
    //partition v's elements around x
    //find x
    int indx = -1;
    for(int i = start; i <= fin; i++){
        if(v[i] == x){
            indx = i;
            break;
            }
    }//for i
    if(indx == -1)
        return -2;
    int t = v[start];
    v[start] = x;
    v[indx] = t;
    int i = start + 1, j = fin;
    while(i < j){
        if(v[i] > x && v[j] <= x){
            t = v[j];
            v[j] = v[i];
            v[i] = t;
            i++;
            j--;
        }//if
        else if(v[i] <= x){
            i++;
            if(i > fin){
                i--;
                break;
            }
            }
        else{
            j--;
            if(j == 0){
                j++;
                break;
            }
            }
    }//while partition
    int last = i;
    if(v[i] > x)
        last--;
//count how many elements are equal to x
    int count_equal = 0;
    for(int u = start; u <= last; u++){
        if(v[u] == x)
            count_equal++;
    }//for u
    
    if(k > (last - count_equal) && k <= last)
        return x;
    else if(last < k)
        return select(v, last + 1, fin, k);
    else
        return select(v, start, last, k);
}//select
void init(vector<int> &v){
    int x;
    while(cin >> x)
        v.push_back(x);

}
