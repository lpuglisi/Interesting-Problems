# Money Changing
## Problem
Given a total dollar amount give the number of combinations possible to get to that total without any remainder along with the combinations themselves given a set of coin/dollar types (e.g. 0.25, 0.99, 1, 5, 5.37, etc.)

First, solve the problem recursively. Next, solve the problem utilizing dynamic programming, speeding up performance by at least two times.
## Examples
### To Run
On the command line run:
```
python MakingChange_part1.py 5 2 1
```
### Example 1
**Input:**

Total = 5

Units = [2,1]


**Output:**

There are 3 possible ways:

{1.0: 5}

{1.0: 3, 2.0: 1}

{1.0: 1, 2.0: 2}
### Example 2
**Input:**

Total = 2.25

Units = [1.0, 0.25, 0.1, 0.05]

**Output:**

There are 166 possible ways:

{0.25: 1, 1.0: 2}

{1.0: 2, 0.1: 2, 0.05: 1}

{1.0: 2, 0.1: 1, 0.05: 3}

{1.0: 2, 0.05: 5}

{0.25: 5, 1.0: 1}

{0.25: 4, 1.0: 1, 0.1: 2, 0.05: 1}

{0.25: 4, 1.0: 1, 0.1: 1, 0.05: 3}

...

...
