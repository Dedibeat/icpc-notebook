#include <iostream>
#include <functional>

using namespace std;
using ll = long long;

struct T {
	int s;
	T* n;
	array<T*, 26> c;
	bool t, v;
	ll r;
};

int main(){
	string s;
	ll k;
	cin >> s >> k;
	
	T* q0 = new T{0}, *t = q0;
	t->n = t;
	
	for(char c : s){
		T* p = t;
		t = new T{p->s + 1};
		
		for(; !p->c[c - 'a']; p = p->n)
			p->c[c - 'a'] = t;
		
		T* q = p->c[c - 'a'];
		
		if(q == t)
			t->n = q0;
		else if(q->s == p->s + 1)
			t->n = q;
		else {
			T* u = new T{p->s + 1, q->n, q->c};
			
			t->n = q->n = u;
			
			for(; p and p->c[c - 'a'] == q; p = p->n)
				p->c[c - 'a'] = u;
		}
	}
	
	for(; t != q0; t = t->n)
		t->t = 1;
	
	int j = 0;
	
	function<void(T*)> f = [&](T* a){
		if(a->v)
			return;
		
		a->v = 1;
		a->s = a->t;
		a->r = 0;
		
		for(int c = 0; c < 26; c++)
			if(a->c[c]){
				f(a->c[c]);
				a->s += a->c[c]->s;
				a->r += a->c[c]->r;
			}
		
		a->r += a->s;
	};
	
	f(q0);
	
	k += s.size();
	s = "";
	
	for(;;){
		k -= q0->s;
		
		if(k <= 0)
			break;
		
		for(int c = 0; c < 26; c++)
			if(T* b = q0->c[c]; b){
				if(b->r >= k){
					q0 = b;
					s += char(c + 'a');
					break;
				}
				
				k -= b->r;
			}
	}
	
	cout << s;
}