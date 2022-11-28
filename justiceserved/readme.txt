Given n intervals (no two are equal), calculate for each i the high of a tower where the ith interval is on top.
A tower is a list of intervals where each interval lies inside the previous.

Solution:
We first change the problem to find a reversetower, where a reversetower is a list of intervals where each interval contains the previous.
To do this we transform each interval from [l, r] to [r, l+big number]. (the reversetower height after the transformation is equal to the
tower height before the transformation)

This problem can now be solved with a sweepline approach which maintains a max-segmenttree.
First we sort the transformed intervals [l, r] by r (in case of ties the shorter interval comes first).
When preocessing the interval [l, r] we query the best deepest nesting in [l, r] and store the result + 1 at position l in the segmenttree.
This is also the answere for the current interval.
Since intervals get processed at position r we only consider intervals which ended before the current interval started. Further, since we
only query values >= l all values we query start after our current. Which means they are contained inside the interval we are processing.

Difficulty:
65%

Note:
The story probabaly needs to be redone.