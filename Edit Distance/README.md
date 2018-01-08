# Edit Distance 
## Problem
Utilize dynamic programming and C++ (Rcpp) to find the edit distance between two strings, along with information about the alignment between the two strings. Specifically, the Rcpp function should take two strings along with two integer costs (one cost for the insertions/deletions and another cost for a mismatch) and output the following:
1. Edit Distance: Optimal edit distance between string 1 and string 2
2. String 1: First string with a '-' at the optimal split to align the two strings
3. Alignment: Alignment between both of the strings with a '.', '*', 'I', or 'D' for each character corresponding to a match, mismatch, insertion, or deletion, respectively
4. String 2: Second string with a '-' at the optimal split to align the two strings

## Examples
### Example 1
Running function alignWords() in R:
```
alignWords("ALGORITHM","ALTRUISTIC",1,1)
```
and the output:
```
$distance
[1] 6
$first
[1] "ALGORI-THM"
$alignment
[1] "..***.I.**"
$second
[1] "ALTRUISTIC"
```
### Example 2
Running function alignWords() in R:
```
alignWords("ALGORITHM","ALTRUISTIC",2,1)
```
and the output:
```
$distance
[1] 9
$first
[1] "ALGOR-I-THM"
$alignment
[1] "..D*.I.I.**"
$second
[1] "AL-TRUISTIC"
```
