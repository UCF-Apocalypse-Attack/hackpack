/**
 * Author: Tyler marks
 * Date: 2024-04-29
 * Description:
\\\begin{minipage}{75mm}
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
*/
#pragma once

#include "Point.h"

template<class P> vector<P> convexHull(vector<P> poly){
    int n = sz(poly);
    vector<P> hull(n+1);
    sort(all(poly));
    int k = 0;
    for(int i = 0; i < n; i++){
        while(k >= 2 && hull[k-2].cross(hull[k-1], poly[i]) <= 0) k--;
        hull[k++] = poly[i];
    }
    for(int i = n-1, t = k+1; i > 0; i--){
        while(k >= t && hull[k-2].cross(hull[k-1], poly[i-1]) <= 0) k--;
        hull[k++] = poly[i-1];
    }
    hull.resize(k-1);
    return hull;
}
