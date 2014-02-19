#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

#define fimp() { \
	fout << "impossible" << endl; \
	return; \
}

#define fine() { \
	fout << "inestimable" << endl; \
	return; \
}

class pnt;
class cir;
class pol;
class gra;

typedef double tvl;
typedef vector< pnt > vpn;
typedef vector< cir > vci;
typedef vector< pol > vpo;
typedef vector< tvl > vtv;
typedef vpn::iterator ipn;
typedef vci::iterator ici;
typedef vpo::iterator ipo;
typedef vtv::iterator itv;
typedef vpn::const_iterator cpn;
typedef vci::const_iterator cci;
typedef vpo::const_iterator cpo;
typedef vtv::const_iterator ctv;

const tvl epo = 1e-3;
const tvl eps = 1e-8;
const tvl pi = acos( -1.0 );

inline tvl sqr( const tvl x ) {
	return x * x;
}

inline bool feq( const tvl a, const tvl b ) {
	return fabs( a - b ) < eps;
}

class pnt {
public:
	pnt() : x(), y() {
	}
	pnt( const tvl px, const tvl py ) : x( px ), y( py ) {
	}
	inline tvl len2() const {
		return sqr( x ) + sqr( y );
	}
	inline tvl len() const {
		return sqrt( sqr( x ) + sqr( y ) );
	}
public:
	tvl x, y;
} tpn;

inline istream & operator >> ( istream & is, pnt & pn ) {
	return is >> pn.x >> pn.y;
}

inline bool operator == ( const pnt & a, const pnt & b ) {
	return feq( a.x, b.x ) && feq( a.y, b.y );
}

inline pnt operator - ( pnt a, const pnt & b ) {
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

inline tvl operator * ( const pnt & a, const pnt & b ) {
	return a.x * b.y - a.y * b.x;
}

class lne {
public:
	lne() : a(), b(), c() {
	}
	lne( const tvl pa, const tvl pb, const tvl pc ) : a( pa ), b( pb ), c( pc ) {
	}
	lne( const pnt & pa, const pnt & pb ) {
		sp2( pa, pb );
	}
	inline void sp2( const pnt & pa, const pnt & pb ) {
		a = pb.y - pa.y;
		b = pa.x - pb.x;
		c = -pa.x * a - pa.y * b;
		if( a ) {
			x = fy( -20000 );
			y = fy( 20000 );
		}
		else {
			x = fx( -20000 );
			y = fx( 20000 );
		}
	}
	inline tvl dis( const pnt & p ) const {
		return fabs( a * p.x + b * p.y + c ) / sqrt( sqr( a ) + sqr( b ) );
	}
private:
	inline pnt fx( const tvl & p ) const {
		return pnt( ( -c - a * p ) / b, p );
	}
	inline pnt fy( const tvl & p ) const {
		return pnt( ( -c - b * p ) / a, p );
	}
public:
	tvl a, b, c;
	pnt x, y;
} tln;

class gra {
public:
	virtual tvl gin( const cir & g ) const = 0;
public:
	tvl c;
};

class cir : public gra {
public:
	cir() : r(), o() {
	}
	cir( const tvl pr, const pnt & po ) : r( pr ), o( po ) {
	}
	inline lne gci( const cir & g ) const {
		return lne( ( g.o.x - o.x ) * 2, ( g.o.y - o.y ) * 2, o.len2() - g.o.len2() + sqr( g.r ) - sqr( r ) );
	}
	inline tvl gin( const cir & g ) const {
		tvl d = ( g.o - o ).len();
		if( d <= g.r - r )
			return c;
		if( d <= r - g.r )
			return 0;
		if( d >= g.r + r )
			return 0;
		lne e = gci( g );
		tvl a = acos( e.dis( o ) / r );
		if( d < e.dis( g.o ) )
			a = pi - a;
		return a / pi * c;
	}
public:
	tvl r;
	pnt o;
} tci;

inline istream & operator >> ( istream & is, cir & ci ) {
	is >> ci.o >> ci.r;
	ci.c = ci.r * pi * 2;
	return is;
}

inline tvl segv( pnt a, pnt b, const cir & g ) {
	tvl r2 = sqr( g.r );
	tvl a2 = ( g.o - a ).len2();
	tvl b2 = ( g.o - b ).len2();
	tvl d = ( a - b ).len();
	tvl h2 = sqr( fabs( ( a - g.o ) * ( b - g.o ) ) / d );
	tvl da = sqrt( a2 - h2 );
	tvl db = sqrt( b2 - h2 );
	tvl dr = sqrt( r2 - h2 );
	if( a2 <= r2 && b2 <= r2 )
		return d;
	if( h2 >= r2 )
		return 0;
	if( b2 < a2 ) {
		swap( a2, b2 );
		swap( a, b );
		swap( da, db );
	}
	if( a2 >= r2 ) {
		if( feq( db - da, d ) )
			return 0;
		return dr * 2;
	}
	return dr - da;
}

class pol : public gra {
public:
	inline tvl gin( const cir & g ) const {
		tvl v = 0;
		for( cpn i = p.begin() + 1; i < p.end(); ++i )
			v += segv( *( i - 1 ), *i, g );
		return v;
	}
public:
	vpn p;
} tpo;

inline istream & operator >> ( istream & is, pol & po ) {
	int n;
	is >> n;
	po.p.clear();
	for( int i = 0; i < n; ++i ) {
		is >> tpn;
		po.p.push_back( tpn );
	}
	po.p.push_back( po.p.front() );
	po.c = 0;
	for( cpn i = po.p.begin() + 1; i < po.p.end(); ++i )
		po.c += ( *i - *( i - 1 ) ).len();
	return is;
}

ifstream fin( "invasion.in" );
ofstream fout( "invasion.out" );

int N;
tvl M;

pnt NG;
vci VC;
vpo VP;
vtv VT;

inline tvl gcr( const cir & pci ) {
	tvl v = 0;
	for( cci i = VC.begin(); i < VC.end(); ++i )
		v += i->gin( pci );
	for( cpo i = VP.begin(); i < VP.end(); ++i )
		v += i->gin( pci );
	return v;
}

inline void wrk( const tvl pL, const tvl pR, bool & pB ) {
	tvl L = pL, R = pR;
	if( gcr( cir( L, NG ) ) > M || gcr( cir( R, NG ) ) < M )
		return;
	while( R - L > epo ) {
		tvl t = ( L + R ) / 2;
		tvl v = gcr( cir( t, NG ) );
		if( v > M )
			R = t;
		else
			L = t;
	}
	pB = false;
	fout << fixed << setprecision( 2 ) << L << endl;
}

inline void Main() {
	if( !( fin >> N >> M ) )
		return;
	char s[ 4 ];
	for( int i = 0; i < N; ++i ) {
		fin >> s;
		if( s[ 0 ] == 'C' ) {
			fin >> tci;
			VC.push_back( tci );
		}
		else {
			fin >> tpo;
			VP.push_back( tpo );
		}
	}
	fin >> NG;
	tvl c = 0;
	for( cci i = VC.begin(); i < VC.end(); ++i )
		c += i->c;
	for( cpo i = VP.begin(); i < VP.end(); ++i )
		c += i->c;
	if( c < M )
		fimp();
	if( feq( c, M ) )
		fine();
	VT.push_back( 0 );
	VT.push_back( 30000 );
	for( cci i = VC.begin(); i < VC.end(); ++i )
		if( i->o == NG )
			VT.push_back( i->r );
	sort( VT.begin(), VT.end() );
	bool bx = true;
	for( ctv i = VT.begin() + 1; i < VT.end() && bx; ++i )
		wrk( *( i - 1 ), *i - eps, bx );
	if( bx )
		fimp();
}

int main() {
	while( !fin.eof() ) {
		VC.clear();
		VP.clear();
		VT.clear();
		Main();
	}
	return 0;
}

