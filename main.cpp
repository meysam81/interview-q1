/*
 * ============================================================================
 * In this revision we plan to reduce the big-O complexity from O(N ** 4) to
 * O(N ** 2) which is possible when we implement the following algorithm:
 * 1. Define two nested for-loops that will generate the possible pairs for
 *    either (a, b) or (c, d). Doesn't really matter which.
 * 2. Save the pairs and their summation in a hash table (map in c++).
 * 3. In another set of nested for-loops get the pairs and check if they are
 *    in their valid range (especially for smaller values such as a and b).
 *    Test the pairs against the formula placing the pair values in the place
 *    of all four variables.
 *
 * This algorithm runs in O(N ** 2) because only the first nested for-loops
 * which are 2 for-loops will take the most of the time. The second nested
 * for-loops will only is considerably smaller than first nested loops in
 * terms of time complexity.
 * ============================================================================
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <map>
#include <vector>

using namespace std;

#define A_MAX 100000
#define B_MAX 300000
#define C_MAX 500000
#define D_MAX 500000
#define BIGGEST 500000

bool prop(long int A, long int B, long int C, long int D)
{
    return (pow(A, 4) + pow(B, 4) + pow(C, 4) == pow(D, 4));
}

int main()
{
    long int a, b, c, d;

    map<int, vector<pair<int, int>>> result;

    for (auto i = 1; i <= BIGGEST; i++)
    {
        for (auto j = 1; j <= BIGGEST; j++)
        {
            auto sum = i + j;
            map<int, vector<pair<int, int>>>::iterator it = result.find(sum);
            if (it != result.end())
                result.insert(it, make_pair(i, j));
            else
            {
                vector<pair<int, int>> vec;
                vec.push_back(make_pair(i, j));
                result.insert(make_pair(sum, vec));
            }
        }
    }

    for (auto lst = result.begin(); lst != result.end(); lst++)
    {
        for (auto pair1 = lst->second.begin(); pair1 != lst->second.end(); pair1++)
        {
            a = pair1->first;
            b = pair1->second;
            if (!(a <= A_MAX && b <= B_MAX))
                continue;

            for (auto pair2 = lst->second.begin(); pair2 != lst->second.end(); pair2++)
            {
                c = pair2->first;
                d = pair2->second;

                if (prop(a, b, c, d))
                    printf("FOUND IT!\na = %ld\nb = %ld\nc = %ld\nd = %ld\n", a, b, c, d);
            }
        }
    }
}
