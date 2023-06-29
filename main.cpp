#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void del_povt(vector<double> &v)
{
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            if(v[i]==v[j]){
                v.erase(v.begin() + j);
                j--;
            }
        }
    }
}
int main()
{   const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    size_t number_count;
    size_t bin_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers(number_count);
    cerr << "Enter numbers: ";
    for(size_t i=0;i<number_count;i++){
        cin >> numbers[i];
    }
    cerr << "Enter bin count: ";
    cin >> bin_count;
    del_povt(numbers);
    number_count=numbers.size();


    double min = numbers[0];
    double max = numbers[0];
    for (double x : numbers) {
       if (x < min) {
           min = x;
       }
       else if (x > max) {
           max = x;
       }
  }

    vector<size_t> bins(bin_count);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
           auto lo = min + j * bin_size;
           auto hi = min + (j + 1) * bin_size;
           if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
           }
        }
        if (!found) {
           bins[bin_count - 1]++;
        }
   }
  double max_count=0;
  for (int i=0;i<bins.size();i++){

        if(max_count<bins[i]){
            max_count=bins[i];
        }
  }

  size_t height ;

  for(int i=0;i<bins.size();i++){
        if(bins[i]<100){
            cout<<" ";
        }
        if(bins[i]<10){
            cout<<" ";
        }

        cout <<bins[i]<<"|";
        if(max_count>MAX_ASTERISK){
                height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
                for(size_t j=0;j<height;j++){
                    cout<<"*";
        }}
        else{
            for(int j=0;j<bins[i];j++){
                    cout<<"*";
        }
        }

        cout<<endl;
    }


}
