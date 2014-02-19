#include <algorithm>
#include <cstdio>

using namespace std;

int N1, N2, N3, N;
bool W[ 20 ];

int dfs( const int c, const int d ) {
	if( c == N ) {
		return 0;
	}
	int x = dfs( c + 1, d );
	W[ c ] = true;
	x = max( x, dfs( c + 1, d + 1 ) );
	W[ c ] = false;
	return x;
}

int main() {
	freopen( "clear.in", "r", stdin );
	freopen( "clear.out", "w", stdout );
	scanf( "%d%d%d", &N1, &N2, &N3 );
	N = min( N1, min( N2, N3 ) );
	printf( "%d\n", dfs( 0, 0 ) );
	return 0;
}
