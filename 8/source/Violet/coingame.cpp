#include <algorithm>
#include <cstdio>

using namespace std;

int N, K, C;

int main() {
	freopen( "coingame.in", "r", stdin );
	freopen( "coingame.out", "w", stdout );
	scanf( "%d%d%d", &N, &K, &C );
	printf( "%d\n", C + max( N - ( K / ( ( C - 1 ) / N + 1 ) ), 0 ) );
	return 0;
}

