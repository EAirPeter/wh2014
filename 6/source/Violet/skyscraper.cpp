#include <algorithm>
#include <cstdio>

using namespace std;

int N, M, D[ 18 ], X = 100;
bool V[ 18 ];

void dfs1( const int c, const int d );
void dfs2( const int c, const int d, const int e, const int f );

void dfs1( const int c, const int d ) {
	if( c == -1 ) {
		if( d < X )
			X = d;
		return;
	}
	V[ c ] = true;
	int i;
	for( i = c - 1; i > -1 && ( D[ c ] + D[ i ] > M || V[ i ] ); --i );
	dfs2( i, D[ c ], c, d );
	V[ c ] = false;
}

void dfs2( const int c, const int d, const int e, const int f ) {
	int i;
	for( i = e - 1; i > -1 && V[ i ]; --i );
	dfs1( i, f + 1 );
	if( c == -1 )
		return;
	if( d + D[ c ] <= M ) {
		V[ c ] = true;
		dfs2( c - 1, d + D[ c ], e, f );
		V[ c ] = false;
	}
}

int main() {
	freopen( "skyscraper.in", "r", stdin );
	freopen( "skyscraper.out", "w", stdout );
	scanf( "%d%d", &N, &M );
	for( int i = 0; i < N; ++i )
		scanf( "%d", D + i );
	sort( D, D + N );
	dfs1( N - 1, 0 );
	printf( "%d\n", X - 1 );
	return 0;
}

