#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include<string>
#include <vector>
using namespace std;
struct Input {
vector<double> numbers;
size_t bin_count;
vector<string>colors;
};
vector<size_t> make_histogram(Input input);
void find_minmax(vector<double> numbers, double& min, double& max);



#endif // HISTOGRAM_H_INCLUDED
