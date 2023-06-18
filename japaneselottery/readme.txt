Statement:
A game of Amida-Kuji is described by n (<=20 vertical bars at
postions 1,2,...n. And q (10^5) horizontal bars. In the game
you start at the top of one vertical bar and follow it to the
bottom but every time you encounter an horizontal bar you have
to follow it. This actually describes a permutation.

You are given such a game where horizontal bars are added one
by one. The question is after each bar added, how many would
you need to remove to make the permutation the identity.

Solution:
The answere only depends on the permutation and not on the
actual positions of the horizontal bars. Thus we can keep
track of the final permutation with a segment tree which
holds permutations (A Horizontal bar is a swap which we can
encode in a permutation).
Given the final permutation p we can observe that the answer
is always n - | cycles(p)|. The reason is that a bar can only
change the number of cycles by 1, and we can always find a bar
which increases the number of cycles. And we want to obtain
a permutation with n cycles i.e. the identity permutation.

Difficulty:
90%
