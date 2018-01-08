#include <Rcpp.h>
#include <cmath>
#include <algorithm>
using namespace Rcpp;
using namespace std;

// Function to shuffle vector from the beginning until k, to be used in EM Algorithms
NumericVector shufflevect(NumericVector x, int k) {
  for (int i=0; i<k; i++) {
    double ind1 = R::runif(0.0,1.0);
    double n = x.size();
    double nv = ind1*n;
    int ind2 = (int) nv;
    double temp = x[i];
    x[i] = x[ind2];
    x[ind2] = temp;
  }
  return(x[seq(0,k-1)]);
}

// A full E-M algorithm for Gaussian mixture model (GMM)
//
// This function performs a full k-component E-M algorithm, learning 3*k-1 free parameters,
// (k-1) for priors, k for means, and k for sds. The time complexity should be
// O(nkr) where n is the size of input and r is the number of iteration.
// The input is:
//   x : A vector containing observed data for H
//   k : The number of mixture components. Must be integer of 2 or greater
//   maxiter : Maximum number of E-M iterations allowed.
//   tol : The precision of tolernace (in terms of stepwise likelihood improvement) to stop iteration

// Returns a list containing the following items:
//  maxllk : Maximum log-likelihood values
//  pis : A vector of size k, containing MLE parameters of mixing proportions
//  mus : A vector of size k, containing MLE parameters of means
//  sds : A vector of size k, containing MLE parameters of standard deviations
//  iter: The number of E-M iterations performed until convergence (or to reach maxiter)

// [[Rcpp::export]]
List gmm615emFull(NumericVector x, int k, int maxiter=1000, double tol=1e-8) {
  NumericVector pis(k);
  fill(pis.begin(), pis.end(),1/(double)k);
  NumericVector mus(k);
  mus = shufflevect(x,k);
  int n = x.size();
  double ss = sd(x)*sqrt(((double)n-1)/(double)n);
  NumericVector sds(k,ss);
  double prevLLK = -1e300;
  double maxllk = 0;
  int iter = 0;
  for (int i=0; i <= maxiter; i++) {
    iter = i;
    double llk = 0;
    NumericVector wsum(k);
    NumericVector wxsum(k);
    NumericVector wxxsum(k);
    for (int j=0; j <= n; j++) {
      NumericVector tmp(k);
      //C++ dnorm is not vectorized, loop through each value
      for (int z=0; z < k; z++) {
        tmp[z] = R::dnorm(x[j], mus[z], sds[z], FALSE);
      }
      NumericVector w = pis * tmp;
      double s = accumulate(w.begin(),w.end(), 0.0);
      w = w/s;
      llk = llk + log(s);
      wsum = wsum + w;
      wxsum = wxsum + w * x[j];
      wxxsum = wxxsum + w * x[j] * x[j];
    }
    if (llk - prevLLK < tol) { break; }
    prevLLK = llk;
    //M-Step
    pis = wsum / n;
    mus = wxsum / n / pis;
    sds = sqrt(wxxsum / n / pis - mus * mus);
  }
  maxllk = prevLLK;
  return( List::create(Named("maxllk")=maxllk,
    Named("pis")=pis,
    Named("mus")=mus,
    Named("sds")=sds,
    Named("iter")=iter));
}



//A constrained (identical variance) E-M algorithm for Gaussian mixture model (GMM)

// This function performs a constrained k-component E-M algorithm, learning 2*k free parameters,
// (k-1) for priors, k for means, and 1 for sds. The model assumes that each component has identical
// variance terms. The time complexity should be
// O(nkr) where n is the size of input and r is the number of iteration.

// The input is:
//   x : A vector containing observed data for H
//   k : The number of mixture components. Must be integer of 2 or greater
//   maxiter : Maximum number of E-M iterations allowed.
//   tol : The precision of tolerance (in terms of stepwise likelihood improvement) to stop iteration

// Returns a list containing the following items:
//  maxllk : Maximum log-likelihood values
//  pis : A vector of size k, containing MLE parameters of mixing proportions
//  mus : A vector of size k, containing MLE parameters of means
//  sd : A numeric value containing MLE parameter of pooled standard deviation
//  iter: The number of E-M iterations performed until convergence (or to reach maxiter)

// [[Rcpp::export]]
List gmm615emUniVar(NumericVector x, int k, int maxiter=1000, double tol=1e-8) {
  NumericVector pis(k);
  NumericVector mus(k);
  double sd2;   //Renamed this since the std dev function is named 'sd'
  double maxllk = 0;
  int iter = 0;
  sd2 = sd(x);
  mus = shufflevect(x,k);
  fill(pis.begin(), pis.end(),1/(double)k);
  int n = x.size();
  double prevLLK = -1e300;
  for (int i=0; i <= maxiter; i++) {
    iter = i;
    double llk = 0;
    NumericVector wsum(k);
    NumericVector wxsum(k);
    NumericVector wxxsum(k);
    NumericVector unifsum(k); // To be used later for uniform sigma assumption
    for (int j=0; j <= n; j++) {
      NumericVector tmp(k);
      //C++ dnorm is not vectorized, loop through each value
      for (int z=0; z < k; z++) {
        tmp[z] = R::dnorm(x[j], mus[z], sd2, FALSE);
      }
      NumericVector w = pis * tmp;
      double s = accumulate(w.begin(),w.end(), 0.0);
      w = w/s;
      llk = llk + log(s);
      wsum = wsum + w;
      wxsum = wxsum + w * x[j];
      wxxsum = wxxsum + w * x[j] * x[j];
    }
    if (llk - prevLLK < tol) { break; }
    prevLLK = llk;
    //M-Step
    pis = wsum / n;
    mus = wxsum / n / pis;
    //New steps for uniform variance assumption
    unifsum = (mus * mus) * pis;
    double sm = accumulate(unifsum.begin(),unifsum.end(), 0.0);
    double wxxsm = accumulate(wxxsum.begin(),wxxsum.end(), 0.0);
    sd2 = sqrt((wxxsm / n) - sm); // Updated equation based on mathematical derivation
  }
  maxllk = prevLLK;
  return( List::create(Named("maxllk")=maxllk,
    Named("pis")=pis,
    Named("mus")=mus,
    Named("sd")=sd2,
    Named("iter")=iter));
}
