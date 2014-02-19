#include <cstdio>

using namespace std;

struct tnode {
	int s, d;
	long long v;
	tnode *c[ 2 ], *p;
	void update() {
		s = c[ 0 ]->s + c[ 1 ]->s + 1;
	}
} T[ 2000000 ], *nil;

int C = 1, M;
int N;

tnode * newnode( tnode * p, const int d, const long long v ) {
	T[ C ].p = p;
	T[ C ].d = d;
	T[ C ].v = v;
	T[ C ].s = 1;
	T[ C ].c[ 0 ] = T[ C ].c[ 1 ] = nil;
	return T + C++;
}

tnode * build( tnode * p, const int d, const int l, const int r ) {
	if( l > r )
		return nil;
	int m = ( l + r ) >> 1;
	tnode * O = newnode( p, d, m );
	if( l ^ r ) {
		O->c[ 0 ] = build( O, 0, l, m - 1 );
		O->c[ 1 ] = build( O, 1, m + 1, r );
		O->update();
	}
	return O;
}

tnode * rotate( tnode * R, const int d ) {
	tnode * O = R->c[ d ^ 1 ];
	R->c[ d ^ 1 ] = O->c[ d ];
	R->c[ d ^ 1 ]->p = R;
	R->c[ d ^ 1 ]->d = d ^ 1;
	O->c[ d ] = R;
	O->p = R->p;
	O->d = R->d;
	R->p = O;
	R->d = d;
	R->update();
	O->update();
	return O;
}

tnode * getk( tnode * R, int k ) {
	while( R != nil ) {
		if( R->c[ 0 ]->s + 1 == k )
			break;
		if( R->c[ 0 ]->s < k ) {
			k -= R->c[ 0 ]->s + 1;
			R = R->c[ 1 ];
		}
		else
			R = R->c[ 0 ];
	}
	return R;
}

tnode * next( tnode * R ) {
	if( R->c[1] != nil )
		return getk( R->c[1], 1 );
	while( R->p != nil && R->d == 1 )
		R = R->p;
	return R->p;
}

void splay( tnode *R, tnode * & root ) {
	while( R->p != nil ) {
		if( R->p == root ) {
			rotate( root, R->d ^ 1 );
			break;
		}
		if( R->d ^ R->p->d )
			R->p->p->c[ R->p->d ] = rotate( R->p, R->d ^ 1 );
		else
			R->p->p->p->c[ R->p->p->d ] = rotate( R->p->p, R->p->d ^ 1 );
		R->p->p->c[ R->p->d ] = rotate( R->p, R->d ^ 1 );
	}
	root = R;
}

tnode * split( tnode * & R, const int k ) {
	tnode *O = getk( R, k );
	splay( O, R );
	O = R->c[ 1 ];
	O->p = nil;
	O->d = 0;
	R->c[ 1 ] = nil;
	R->update();
	return O;
}

void merge( tnode * & R, tnode * O ) {
	splay( getk( R, R->s ), R) ;
	R->c[ 1 ] = O;
	O->p = R;
	O->d = 1;
	R->update();
}

int main() {
	tnode *s, *t, *u;
	int p, l, r, o;
	long long x;
	freopen( "card.in", "r", stdin );
	freopen( "card.out", "w", stdout );
	nil = T;
	nil->p = nil->c[ 0 ] = nil->c[ 1 ] = nil;
	nil->v = nil->s = 0;
	nil->d = 0;
	scanf( "%d%d", &N, &M );
	s = build( nil, 0, 0, N - 1 );
	while( M-- ) {
		scanf( "%d%d%d", &p, &l, &r );
		if( l == 0 )
			continue;
		o = p + l;
		p = p * r % o;
		if( p == 0 )
			continue;
		l = o - p;
		t = split( s, p );
		u = split( t, l );
		merge( t, s );
		merge( t, u );
		s = t;
	}
	t = getk( s, 1 );
	x = t->v;
	while( t != nil )
		x += ( t = next( next( t ) ) )->v;
	printf( "%lld\n", x );
	return 0;
}

