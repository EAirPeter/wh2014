#include <algorithm>
#include <cstdio>

using namespace std;

struct pnt {
	pnt() : x(), y() {
	}
	pnt( const double a, const double b ) : x( a ), y( b ) {
	}
	pnt & operator *= ( const double f ) {
		x *= f;
		y *= f;
		return *this;
	}
	double x, y;
} D[ 50000 ], E[ 4 ];

int N, C;
bool V[ 50000 ];
int S[ 50000 ], p, e;

bool operator < ( const pnt & a, const pnt & b ) {
	if( a.x != b.x )
		return a.x < b.x;
	return a.y < b.y;
}

pnt operator + ( pnt a, const pnt & b ) {
	a.x += b.x;
	a.y += b.y;
	return a;
}

pnt operator - ( pnt a, const pnt & b ) {
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

double operator * ( const pnt & a, const pnt  & b ) {
	return a.x * b.y - b.x * a.y;
}

inline double cx( const pnt & a, const pnt & b, const pnt & c ) {
	return ( b - a ) * ( c - a );
}

inline bool chk( const pnt & a, const pnt & b, const pnt & c ) {
	return cx( a, b, c ) > 0;
}

inline bool chk( const int a, const int b, const int c ) {
	return chk( D[ a ], D[ b ], D[ c ] );
}

bool cross( const pnt & a1, const pnt & b1, const pnt & a2, const pnt & b2 ) {
	return ( cx( a1, a2, b1 ) * cx( a1, b1, b2 ) >= 0 ) && ( cx( a2, b1, b2 ) * cx( a2, b2, a1 ) >= 0 );
}

bool cross( const pnt & a1, const pnt & b1, const pnt & a2, const pnt & b2, pnt & c ) {
	if( !cross( a1, b1, a2, b2 ) )
		return false;
	double s1 = ( a2 - a1 ) * ( b1 - a1 );
	double s2 = ( b1 - a1 ) * ( b2 - a1 );
	pnt v = b2 - a2;
	v *= s1 / ( s1 + s2 );
	c = a2 + v;
	return true;
}

void f3() {
	sort( D, D + N );
	V[ S[ p++ ] = 0 ] = true;
	for( int i = 1; i < N; ++i ) {
		while( p > 1 ) {
			if( chk( S[ p - 2 ], S[ p - 1 ], i ) )
				break;
			else
				V[ S[ --p ] ] = false;
		}
		V[ S[ p++ ] = i ] = true;
	}
	V[ 0 ] = false;
	int k = p;
	for( int i = N - 1; i > -1; --i )
		if( !V[ i ] ) {
			while( p > k ) {
				if( chk( S[ p - 2 ], S[ p - 1 ], i ) )
					break;
				else
					V[ S[ --p ] ] = false;
			}
			V[ S[ p++ ] = i ] = true;
		}
	for( int i = 1; i < p; ++i ) {
		pnt a( C, min( D[ S[ i - 1 ] ].y, D[ S[ i ] ].y ) - 1 );
		pnt b( C, max( D[ S[ i - 1 ] ].y, D[ S[ i ] ].y ) + 1 );
		if( cross( D[ S[ i - 1 ] ], D[ S[ i ] ], a, b, E[ e ] ) )
			++e;
	}
	sort( E, E + e );
	printf( "%.3lf %.3lf\n", E[ 0 ].y, E[ e - 1 ].y );
}

int main() {
	freopen( "minmax.in", "r", stdin );
	freopen( "minmax.out", "w", stdout );
	scanf( "%d%d", &N, &C );
	for( int i = 0; i < N; ++i )
		scanf( "%lf", &D[ i ].x );
	for( int i = 0; i < N; ++i )
		scanf( "%lf", &D[ i ].y );
	if( N > 2 )
		f3();
	else {
		pnt a( C, min( D[ 0 ].y, D[ 1 ].y ) - 1 );
		pnt b( C, max( D[ 0 ].y, D[ 1 ].y ) + 1 );
		cross( D[ 0 ], D[ 1 ], a, b, E[ 0 ] );
		printf( "%.3lf %.3lf\n", E[ 0 ].y, E[ 0 ].y );
	}
	return 0;
}

