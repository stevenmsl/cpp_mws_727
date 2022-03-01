#include "solution.h"
#include "util.h"
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>

using namespace sol727;
using namespace std;

/*takeaways
  - the basic idea is that you have a window keeps sliding on S until the window can
    include T
  - S = abcdebdde, T = bde
    - step 1 - S: [a]bcdebdde T: bde
      - nothing happen on the T as [a] won't include any char from T
    - step 2 - S: a[b]cdebdde T: [b]de
      - [b] denotes a start of a new window
      - we abandon [a] as we want the smallest subsequence
    - step 3 - S: a[bc]debdde T: [b]de
      - c is not in the T. So the window on T reamins the same
    - step 4 - S: a[bcd]ebdde T: [bd]e
      - d is in the T. So the window on T grow
    - step 5 - S: a[bcde]bdde T: [bde]
      - found first candidate [bcde] the start index is 1, and the
        length is 4. Record these two things and we can generate
        substring from S later if needed

  - implementation:
        b  d  e   comment
    a  -1 -1 -1   abandoned once a new window started on S
    b   1 -1 -1   start a new window. start index is 1 and S[1] == T[0]
    c   1 -1 -1   c != d; nothing would change dp[2][1] = dp[2-1][1]
         \
    d   1  1 -1   d == d; dp[3][1] = dp[2][0]; copy the start index - extend the window on T
    e   1  1  1   e == e; dp[4][2] = dp[3][1]; copy the start index - extend the window on T
    b   5 -1 -1   new window
    d   5  5 -1
    d   5  5 -1
    e   5  5  5  second candidate
*/

string Solution::minWindow(string S, string T)
{
  const int m = S.size();
  const int n = T.size();
  auto start = -1, minLen = INT_MAX;

  /*represent windows on S and T
    - the value is the start index of the window
      on S
  */

  auto dp = vector<vector<int>>(m, vector<int>(n, -1));

  /*to simplify the logic inside the loop below */
  if (S[0] == T[0])
    dp[0][0] = 0;

  for (int i = 1; i < m; i++)
    /*same as the first character of T
      - you can start a new sliding window now
    */
    if (S[i] == T[0])
      dp[i][0] = i;
    /* within the same window as the previous char on S
     */
    else
      dp[i][0] = dp[i - 1][0];

  /*record how big the current window is */
  auto window = 1;

  /* the first row only includes 1 char from S, which
     has been taken care of from above. So i starts
     at 1
  */
  for (auto i = 1; i < m; i++)
  {
    if (dp[i][0] != dp[i - 1][0])
      window = 1;
    /*
       - we have compared each char in S to the first
         char in T already, so j starts at 1
       - if the window size is smaller than the size
         of T, there is no point to keep scanning
         for the rest of characters in T as the subsequence
         included in the windows won't have enough
         chars to cover T anyway
    */
    for (auto j = 1; j < min(window, n); j++)
      /* this is the key
         - if S[i] != T[j] we can't extend the window on T;
           just copy the start index from the same column
           in the previous row
               b  d  e
           b   1 -1 -1
                  |  |
           c   1 -1 -1 nothing changed;
         - if S[i] == T[J] we can extend the window on T;
           copy from the previous column from the previous
           row and hence extends the window on T
           c   1 -1 -1
                \
           d   1  1 -1  extend the window
      */
      dp[i][j] = S[i] == T[j] ? dp[i - 1][j - 1] : dp[i - 1][j];

    if (dp[i][n - 1] != -1)
    {
      auto len = i - dp[i][n - 1] + 1;
      if (len < minLen)
        minLen = len, start = dp[i][n - 1];
    }

    window++;
  }

  return (start != -1) ? S.substr(start, minLen) : "";
}
