#include "histogram.h"
vector<size_t> make_histogram(Input input){
    double min, max;
    find_minmax(input.numbers, min, max);
    vector<size_t> bins(input.bin_count);
    double bin_size = (max - min) / input.bin_count;
    for (size_t i = 0; i < input.numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < input.bin_count - 1) && !found; j++) {
           auto lo = min + j * bin_size;
           auto hi = min + (j + 1) * bin_size;
           if ((lo <= input.numbers[i]) && (input.numbers[i] < hi)) {
                bins[j]++;
                found = true;
           }
        }
        if (!found) {
           bins[input.bin_count - 1]++;
        }
   }
   return bins;
}

void find_minmax(vector<double>numbers, double &min, double &max) {
    if (numbers.size()>0){
    min = numbers[0];
    for (double x : numbers) {
       if (x < min) {
           min = x;
       }
       else if (x > max) {
           max = x;
       }
  }
    }
}
void show_histogram_text(const vector<size_t> &bins){
    const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
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
            cout<<" ";}
        cout <<bins[i]<<"|";
        if(max_count>MAX_ASTERISK){
                height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
                for(size_t j=0;j<height;j++){
                    cout<<"*";}}
        else{
            for(int j=0;j<bins[i];j++){
                    cout<<"*";}}
        cout<<endl;
    }
}
