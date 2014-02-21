#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

#ifdef NAVIO
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

struct pnt {
	int x, y;
} D[ 501 ], E[ 501 ];

inline bool operator < ( const pnt & a, const pnt & b ) {
	if( a.x != b.x )
		return a.x < b.x;
	return a.y < b.y;
}

int gcd( const int a, const int b ) {
	return b ? gcd( b, a % b ) : a;
}

long long M, X, C;
int N, d, e;
int phi[ 4000001 ];
int pri[ 4000001 ], prc;
bool vpr[ 4000001 ];

priority_queue< int > h;

int ff( const pnt * f, const int l, int & p, const int g, const int o ) {
	while( p < l && f[ p ].x < g )
		++p;
	int t = p;
	while( p < l && f[ p ].x == g )
		++p;
	int k = phi[ g ];
	for( int i = t; i < p; ) {
		int r = i;
		while( i < p && f[ i ].y == f[ r ].y )
			++i;
		--k;
		h.push( o + r - i );
	}
	return k;
}

int main() {
	freopen( "shoot.in", "r", stdin );
	freopen( "shoot.out", "w", stdout );
	scanf( "%d" LLD, &N, &M );
	for( int i = 2; i <= N; ++i ) {
		if( !vpr[ i ] ) {
			pri[ prc++ ] = i;
			phi[ i ] = i - 1;
		}
		for( int j = 0; j < prc && i * pri[ j ] <= N; ++j ) {
			vpr[ i * pri[ j ] ] = true;
			if( i % pri[ j ] )
				phi[ i * pri[ j ] ] = phi[ i ] * ( pri[ j ] - 1 );
			else {
				phi[ i * pri[ j ] ] = phi[ i ] * pri[ j ];
				break;
			}
		}
	}
	--N;
	int a, b;
	int sx = N, sy = N, sz = N;
	while( scanf( "%d%d", &a, &b ) == 2 ) {
		int c = gcd( a, b );
		a /= c;
		b /= c;
		if( a == 0 )
			--sx;
		else if( b == 0 )
			--sy;
		else if( a == b )
			--sz;
		else if( a > b ) {
			D[ d ].x = a;
			D[ d++ ].y = b;
		}
		else {
			E[ e ].x = b;
			E[ e++ ].y = a;
		}
	}
	h.push( sx );
	h.push( sy );
	h.push( sz );
	sort( D, D + d );
	sort( E, E + e );
	a = b = 0;
	for( int g = 2; g <= N && C < M; ++g ) {
		int um = N / g;
		while( !h.empty() && h.top() > um && C < M ) {
			++C;
			X += h.top();
			h.pop();
		}
		long long k = ff( D, d, a, g, um ) + ff( E, e, b, g, um );
		if( C + k > M )
			k = M - C;
		C += k;
		X += k * um;
	}
	while( C < M && !h.empty() ) {
		++C;
		X += h.top();
		h.pop();
	}
	printf( LLD "\n", X );
	return 0;
}

