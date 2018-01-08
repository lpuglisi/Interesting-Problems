library(Rcpp)

#Load in C++ functions for EM algorithm
sourceCpp('Algo_TwoWays.cpp')

#Setup test data for functions
# Data is from a normal distribution with a mean of 0 and 10, and a SD of 1 in both cases
x = c(rnorm(1000), rnorm(500)+10)

#Run EM algorithm for the both the full and univariate cases
gmm615emFull(x, 2, 1000, 1e-8)
gmm615emUniVar(x, 2, 1000, 1e-8)
