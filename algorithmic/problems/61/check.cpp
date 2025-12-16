#include "testlib.h"
#include <sstream>

using namespace std;

int main(int argc, char * argv[])
{
    setName("compare ordered sequences of signed int%d numbers", 8 * int(sizeof(long long)));

    registerTestlibCmd(argc, argv);

    int n = 0;
    string firstElems;

	double total_ratio = 0;
	double total_unbounded_ratio = 0;

    while (!ans.seekEof() && !ouf.seekEof())
    {
        n++;
        long long j = ans.readLong();
        long long p = ouf.readLong();
        if (p < j)
            quitf(_wa, "%d%s numbers differ - expected: '%s', found: '%s'", n, englishEnding(n).c_str(), vtos(j).c_str(), vtos(p).c_str());
        double ratio = min(1.0, p / j * 0.8);
        double unbounded_ratio = p / j * 0.8;
        
        total_ratio += ratio;
        total_unbounded_ratio += unbounded_ratio;
    }
    
    total_ratio /= n;
    total_unbounded_ratio /= n;
    double score = total_ratio * 100;
    double unbounded_score = total_unbounded_ratio * 100;

    int extraInAnsCount = 0;

    while (!ans.seekEof())
    {
        ans.readLong();
        extraInAnsCount++;
    }
    
    int extraInOufCount = 0;

    while (!ouf.seekEof())
    {
        ouf.readLong();
        extraInOufCount++;
    }

    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements", n + extraInAnsCount, n);
    
    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements", n + extraInOufCount, n);
    
    string msg = format(
                "Correct! Queries = %d (limit = %d). Ratio: %.6f (Score: %.2f). RatioUnbounded: %.6f (ScoreUnbounded: %.2f)",
                queries, limit, total_ratio, score, total_unbounded_ratio, unbounded_score);

    quitp(total_ratio, msg.c_str());
}
