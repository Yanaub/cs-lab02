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
