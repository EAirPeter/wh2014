#include <algorithm>
#include <cstdio>

using namespace std;

#ifdef NAVIO
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

int N;

int main() {
	freopen( "game.in", "r", stdin );
	freopen( "game.out", "w", stdout );
	scanf( "%d", &N );
	long long x, s = 0, t = 0;
	for( int i = 0; i < N; ++i ) {
		scanf( LLD, &x );
		s += x;
		t = max( x, t );
	}
	printf( LLD "\n", max( ( s - 1 ) / ( N - 1 ), t ) );
	return 0;
}

