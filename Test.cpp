/**
 * Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
 *
 * For example:
 *
 * Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.
 *
 * Follow up:
 * Could you do it without any loop/recursion in O(1) runtime?
 *
 * solution approach:
 * Look at the pattern which emerges when we sum the values and eventually reduce it to single digit. By observing carefully, we will see a pattern.
 *
 * This is calculating digital root of a number (https://en.wikipedia.org/wiki/Digital_root)
 * The formula is:
 * dr(n) = 0 if n = 0,
 * 		   9 if n != 0 and  (n % 9 == 0)
 * 		   n % 9
 *
 */

#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <vector>
#include <set>

using namespace std;

