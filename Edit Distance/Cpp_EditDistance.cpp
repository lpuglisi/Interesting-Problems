#include <Rcpp.h>
#include <iostream>
#include <string>
#include <cmath>
using namespace Rcpp;
using namespace std;

//This function is only used in C++, not an Rcpp function
//The input for this function is the following:
// > s1 : The first (reference) string to align
// > s2 : The second (alternative) string to align
// > cost : A matrix to contain cost to each node (negative if not stored)
// > move : A matrix to contain the optimal move to each node (negative if not stored)
// > r : row index (0..s1.size()), indicating the position in s1
// > c : column index (0..s1.size()), indicating the position in s2
// > mcost : cost of single letter mismatch
// > icost : cost of single latter insertion/deletion

int editDistance(string& s1, string& s2, IntegerMatrix& cost, IntegerMatrix& move, int r, int c, int mcost, int icost) {
  if (cost(r,c) < 0) {
    if (r==0) {
      if (c==0) {
        cost(r,c)=0;
        move(r,c) = 0;
      }
      else {
        cost(r,c) = editDistance(s1,s2,cost,move,r,c-1,mcost,icost)+icost;
        move(r,c) = 1;
      }
    }
  else if (c==0) {
    cost(r,c) = editDistance(s1,s2,cost,move,r-1,c,mcost,icost)+icost;
    move(r,c) = 3;
  }
  else {
    int iDist = editDistance(s1, s2, cost,move, r, c-1,mcost,icost) + icost;
    int dDist = editDistance(s1, s2, cost,move, r-1, c,mcost,icost) + icost;
    int x = (s1[r-1] != s2[c-1]);
    int mDist = editDistance(s1,s2,cost,move,r-1,c-1,mcost,icost) + x*mcost;
    if ( iDist < dDist ) {
      if (iDist < mDist) {
        cost(r,c) = iDist;
        move(r,c) = 1;
      }
      else {
        cost(r,c) = mDist;
        move(r,c) = 2;
      }
    }
    else {
      if (dDist < mDist) {
        cost(r,c) = dDist;
        move(r,c) = 3;
      }
      else {
        cost(r,c) = mDist;
        move(r,c) = 2;
      }
    }
  }
  }
  return cost(r,c);
}


// [[Rcpp::export]]
List alignWords(string s1, string s2, int mcost, int icost) {
  string alignment ="";
  int r = (int)s1.size();
  int c = (int)s2.size();
  IntegerMatrix cost(r+1,c+1);
  IntegerMatrix move(r+1,c+1);
  fill(cost.begin(), cost.end(), -1.0);
  fill(move.begin(), move.end(), -1.0);
  int distance = editDistance(s1, s2, cost, move, r, c, mcost, icost);
  //Define the alignment variable based off of the move matrix
  while ((r>0) || (c>0)) {
    if (move(r,c)==2) {
      if (s1[r-1] != s2[c-1]) {
        alignment="*"+alignment;
        r--;
        c--;
      }
      else {
        alignment="."+alignment;
        r--;
        c--;
      }
    }
    else if (move(r,c)==1) {
      alignment = "I"+alignment;
      c--;
    }
    else {
      alignment = "D"+alignment;
      r--;
    }
  }
  //Create the first and second outputs based on the alignment produced
  string tmp1 = s1;
  string tmp2 = s2;
  for (int i=0; i < alignment.length(); i++) {
    char c = alignment[i];
    char z = 'I';
    char z2 = 'D';
    if (c == z) {
      tmp1 = tmp1.insert(i, "-");
    }
    else if (c == z2) {
      tmp2 = tmp2.insert(i,"-");
    }
  }
  string first = tmp1;
  string second = tmp2;
  return List::create(Named("distance")=distance,Named("first")=first,Named("alignment")=alignment,Named("second")=second);
}
