library(Rcpp)

#Load in function from C++
sourceCpp("Cpp_EditDistance.cpp")

#Run test case
alignWords("ALGORITHM","ALTRUISTIC",2,1)
