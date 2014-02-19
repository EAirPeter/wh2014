#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>

using namespace std;

inline double sqr( const double x ) {
	return x * x;
}

class pnt {
	friend double operator * ( const pnt & a, const pnt & b );
	friend bool operator < ( const pnt & a, const pnt & b );
	friend pnt operator + ( pnt a, const pnt & b );
	friend pnt operator - ( pnt a, const pnt & b );
	friend class seg;
public:
	pnt( const int px = 0, const int py = 0 ) : x( px ), y( py ) {
	}
	void read( const int m ) {
		scanf( "%d%d", &x, &y );
		n = m;
		g = atan2( y, x );
	}
	int getN() const {
		return n;
	}
	double getG() const {
		return g;
	}
	inline double dist2() const {
		return sqr( x ) + sqr( y );
	}
	inline double to( const pnt & m ) const {
		return sqrt( sqr( x - m.x ) + sqr( y - m.y ) );
	}
private:
	int x, y, n;
	double g;
} D[ 200000 ], *dp, op;

inline double operator * ( const pnt & a, const pnt & b ) {
	return a.x * b.y - a.y * b.x;
}

inline bool operator < ( const pnt & a, const pnt & b ) {
	if( a.g != b.g )
		return a.g < b.g;
	return a.dist2() < b.dist2();
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

class seg {
	friend bool operator < ( const seg & a, const seg & b );
public:
	void read( const int m, const int p ) {
		n = p;
		a.read( m );
		b.read( m );
		if( b < a )
			swap( a, b );
		int k = m << 1;
		D[ k ] = a;
		D[ k + 1 ] = b;
	}
	bool vld() const {
		return a.g != b.g;
	}
	bool crs() const {
		return a * b < 0;
	}
	int getN() const {
		return n;
	}
	double cro( const pnt & c, const pnt & d ) const {
		double s1 = ( d - a ) * ( b - a );
		double s2 = ( b - a ) * ( c - a );
		return s2 / ( s1 + s2 );
	}
private:
	int n;
	pnt a, b;
} E[ 100000 ];

inline bool operator < ( const seg & a, const seg & b ) {
	return a.cro( op, *dp ) < b.cro( op, *dp );
}

int N, M;
bool V[ 100000 ];
int W[ 100000 ];

set< seg > S;

int main() {
	freopen( "segment.in", "r", stdin );
	freopen( "segment.out", "w", stdout );
	scanf( "%d", &N );
	for( int i = 0; i < N; ++M, ++i ) {
		E[ M ].read( M, i );
		if( !E[ M ].vld() )
			--M;
	}
	sort( D, D + M * 2 );
	dp = new pnt( -1, 0 );
	for( int i = 0; i < M; ++i )
		if( E[ i ].crs() ) {
			S.insert( E[ i ] );
			W[ i ] = 2;
		}
	delete dp;
	for( int i = 0; i < M * 2; ) {
		dp = D + i;
		double g = D[ i ].getG();
		int j = i;
		for( i = j; i < M * 2 && D[ i ].getG() == g; ++i ) {
			int n = D[ i ].getN();
			if( W[ n ] == 0 ) {
				W[ n ] = 1;
				S.insert( E[ n ] );
			}
		}
		for( i = j; i < M * 2 && D[ i ].getG() == g; ++i ) {
			int n = D[ i ].getN();
			if( W[ n ] == 1 )
				W[ n ] = 2;
			else if( W[ n ] == 2 ) {
				W[ n ] = 0;
				S.erase( E[ n ] );
			}
		}
		if( !S.empty() )
			V[ S.begin()->getN() ] = true;
	}
	for( int i = 0; i < N; ++i )
		if( V[ i ] )
			printf( "%d\n", i );
	return 0;
}

