/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns 0 if the point is outside the polygon, 1 if
 * it is strictly inside the polygon, and 2 if it is on the polygon.
 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * int in = inPolygon(v, P{3, 3});
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

template<class P> int inPoly(vector<P> poly, P p) {
    bool good = false; int n = sz(poly);
    auto crosses = [](P s, P e, P p) { 
        return ((e.y >= p.y) - (s.y >= p.y)) * p.cross(s, e) > 0; 
    };
    for(int i = 0; i < n; i++){
        if(onSeg(poly[i], poly[(i+1)%n], p)) return 2;
        good ^= crosses(poly[i], poly[(i+1)%n], p);
    }
    return good;
}
