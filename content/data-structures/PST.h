/**
 * Author: Sachin Sivakumar
 * Date: 2023-09-04
 * Description: Persistent segment tree with laziness
 * Time: $O(\log N)$ per query, $O((n + q) \log n)$ memory
 * Status: Works but not stress-tested
 */

#pragma once

struct PST {
	PST *l = 0, *r = 0;
	int lo, hi;
	ll val = 0, lzadd = 0;
	PST(vl& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new PST(v, lo, mid); r = new PST(v, mid, hi);
		}
		else val = v[lo];
	}
	ll query(int L, int R) {
		if (R < lo || hi < L) return 0; // idempotent
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	PST * add(int L, int R, ll v) {
		if (R <= lo || hi <= L) return this;
		PST *n;
		if (L <= lo && hi <= R) {
			n = new PST(*this);
			n->val += v;
			n->lzadd += v;
		} else {
			push();
			n = new PST(*this);
			n->l = l->add(L, R, v);
			n->r = r->add(L, R, v);
		}
		return n;
	}
	void push() {
		if(lzadd == 0) return;
		l = l->add(lo, hi, lzadd);
		r = r->add(lo, hi, lzadd);
		lzadd = 0;
	}
};
