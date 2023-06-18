Statement:
you are given an integer x mod 10^9+7 and need to find
a 2x200 rectangle with some dominos placed on it such
that there are x ways to completely fill the rectangle
with dominos.

For example, given a 2x3 rectangle (all other squares
filled) we can observe that there are 3 possible ways
to place 3 dominos:

123
123

113
223

122
133

Difficulty: 95%

Solution:
Note that the answer 0 can be obtained by this:
##.
.##
Since a single field can not be filled with a domino.

Further, observe that if the answere is not 0 an halfempty
row is never helpfull i.e. if we place a domino horizontally
we can place a second domino in the other row at the same
position without changing the number of possible placements.
Thus we only need to find a solution where the free areas
are rectangles.
Now take a look at the the number of possible placements for
a 2xN rectangle:

N | #placements
--+-------------
0 | 1
1 | 1
2 | 2
3 | 3
4 | 5
5 | 8
6 | 13
x | fib(x)

Thus the problem boils down to: can you find fibonacci numbers
f(y_i) such that the sum of y_i is < 200 and the product of
f(y_i) is x. To solve this we use some kind of meet in the
middle strategy:
generate K random solutions with sum <= 100 and any product.
After we did this we can check for each solution if we
generated another solution such that there product is x in
log(K).
This approach is equal to generating K^2 random solutions but
requires only O(K*log(K)) operations. For large K we find a
solution with high porbability for a fixed x.
