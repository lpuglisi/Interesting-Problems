#include <Rcpp.h>
#include <iostream>
#include <algorithm>
using namespace Rcpp;
using namespace std;
// [[Rcpp::export]]
NumericVector insertion_sort(NumericVector x) {
  int n = x.size();
  for(int i=1; i < n; ++i) {
    double key = x[i];
    int j = i-1;
    while(j >= 0) {
      if ( x[j] < key ) {
        break;
      }
      x[j+1] = x[j];
      --j;
    }
    x[j+1] = key;
  }
  return x;
}


// [[Rcpp::export]]
NumericVector bubble_sort(NumericVector x) {
  int n = x.size();
  double tmp;
  for(int i=1; i < n; ++i) {
    for(int j=0; j < i; ++j) {
      if ( x[j] > x[i] ) {
        tmp = x[j];
        x[j] = x[i];
        x[i] = tmp;
      }
    }
  }
  return x;
}

// [[Rcpp::export]]
void merge_sort(NumericVector x, int l, int r) {
  if ( l + 2 > r ) return;
  else {
    int m = (l+r)/2;
    if ( l < m ) { merge_sort(x, l, m); }
    if ( m < r ) { merge_sort(x, m, r); }
    // combine each part
    if ( l < m ) {
      NumericVector tmp(x.begin()+l, x.begin()+m);
      int i=0, j=m, k = l;
      while( ( i + l < m ) || ( j < r ) ) {
        if ( i+l == m ) {
          x[k++] = x[j++];
        }
        else if ( ( j == r ) || ( tmp[i] < x[j] ) ) {
          x[k++] = tmp[i++];
        }
        else {
          x[k++] = x[j++];
        }
      }
    }
  }
}

// [[Rcpp::export]]
NumericVector merge_sort(NumericVector x) {
merge_sort(x, 0, (int)x.size());
return x;
}
// [[Rcpp::export]]
NumericVector std_sort(NumericVector x) {
// Including std::sort() as a benchmark for other sorting algorithms
sort(x.begin(), x.end());
return x;
}
