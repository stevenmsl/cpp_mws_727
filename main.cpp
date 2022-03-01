#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol727;

/*
Input: S = “abcdebdde”, T = “bde”
Output: “bcde”
Explanation:
“bcde” is the answer because it occurs before “bdde” which has the same length.
“deb” is not a smaller window because the elements of T in the window must occur in order.
*/
tuple<string, string, string>
testFixture1()
{
  return make_tuple(string("abcdebdde"), string("bde"), string("bcde"));
}

void test1()
{
  auto f = testFixture1();
  auto s = get<0>(f);
  auto t = get<1>(f);
  cout << "Test 1 - exepct to see " << get<2>(f) << endl;
  auto result = Solution::minWindow(s, t);
  cout << "result: " << result << endl;
}

main()
{
  test1();
  return 0;
}