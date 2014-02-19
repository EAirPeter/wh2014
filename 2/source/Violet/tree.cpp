#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

int N, M, K, P, Q, S, C = 1;
int A[ 100001 ], B[ 100001 ], F[ 240001 ], L[ 100001 ], R[ 100001 ], T[ 100001 ];
int H[ 100001 ], I[ 240001 ], J[ 240001 ];

void adde( const int a, const int b ) {
	I[ C ] = b;
	J[ C ] = H[ a ];
	H[ a ] = C++;
}

void dfs() {
	B[ 0 ] = 0;
	B[ 1 ] = 1;
	T[ 1 ] = H[ 1 ];
	F[ L[ 1 ] = M++ ] = A[ 1 ];
	int p = 1;
	while( p ) {
		if( T[ p ] && I[ T[ p ] ] == B[ p - 1 ] )
			T[ p ] = J[ T[ p ] ];
		if( T[ p ] ) {
			B[ p + 1 ] = I[ T[ p ] ];
			T[ p ] = J[ T[ p ] ];
			++p;
			T[ p ] = H[ B[ p ] ];
			F[ L[ B[ p ] ] = M++ ] = A[ B[ p ] ];

		}
		else {
			F[ R[ B[ p ] ] = M++ ] = A[ B[ p ] ];
			--p;
		}
	}
}

struct qry {
	int n, s, l, r, x;
} D[ 100001 ];

bool operator < ( const qry & a, const qry & b ) {
	if( a.s != b.s )
		return a.s < b.s;
	return a.r < b.r;
}

bool cmpout( const qry & a, const qry & b ) {
	return a.n < b.n;
}

int main() {
	freopen( "tree.in", "r", stdin );
	freopen( "tree.out", "w", stdout );
	scanf( "%d%d", &N, &K );
	S = ( int ) sqrt( N );
	K <<= 1;
	for( int i = 1; i <= N; ++i ) {
		scanf( "%d", A + i );
		B[ i - 1 ] = A[ i ];
	}
	sort( B, B + N );
	P = ( int ) ( unique( B, B + N ) - B );
	for( int i = 1; i <= N; ++i )
		A[ i ] = ( int ) ( lower_bound( B, B + P, A[ i ] ) - B );
	for( int a, b, i = 1; i < N; ++i ) {
		scanf( "%d%d", &a, &b );
		adde( a, b );
		adde( b, a );
	}
	dfs();
	scanf( "%d", &Q );
	for( int a, i = 0; i < Q; ++i ) {
		scanf( "%d", &a );
		D[ i ].n = i;
		D[ i ].l = L[ a ];
		D[ i ].r = R[ a ];
		D[ i ].s = L[ a ] / S;
	}
	sort( D, D + Q );
	int cs = -1, ca = -1;
	for( int i = 0; i < Q; ++i ) {
		if( cs ^ D[ i ].s ) {
			cs = D[ i ].s;
			ca = 0;
			memset( T, 0, sizeof( T ) );
			for( int j = D[ i ].l; j <= D[ i ].r; ++j ) {
				ca -= T[ F[ j ] ] == K;
				++T[ F[ j ] ];
				ca += T[ F[ j ] ] == K;
			} 
		}
		else {
			for( int j = D[ i - 1 ].l; j < D[ i ].l; ++j ) {
				ca -= T[ F[ j ] ] == K;
				--T[ F[ j ] ];
				ca += T[ F[ j ] ] == K;
			}
			for( int j = D[ i ].l; j < D[ i - 1 ].l; ++j ) {
				ca -= T[ F[ j ] ] == K;
				++T[ F[ j ] ];
				ca += T[ F[ j ] ] == K;
			}
			for( int j = D[ i ].r; j > D[ i - 1 ].r; --j ) {
				ca -= T[ F[ j ] ] == K;
				++T[ F[ j ] ];
				ca += T[ F[ j ] ] == K;
			}
		}
		D[ i ].x = ca;
	}
	sort( D, D + Q, cmpout );
	for( int i = 0; i < Q; ++i )
		printf( "%d\n", D[ i ].x );
	return 0;
}

