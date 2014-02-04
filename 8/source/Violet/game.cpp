#include <algorithm>
#include <cstdio>

using namespace std;

int N;

int main() {
	freopen( "game.in", "r", stdin );
	freopen( "game.out", "w", stdout );
	scanf( "%d", &N );
	long long x, s = 0, t = 0;
	for( int i = 0; i < N; ++i ) {
		scanf( "%lld", &x );
		s += x;
		t = max( x, t );
	}
	printf( "%lld\n", max( ( s - 1 ) / ( N - 1 ), t ) );
	return 0;
}

