// find approximate point minimizing max distance
// find point with best score
// optimize non-convex function
P cur = start;
double step = initial_step;

while (step > 1e-9) {
    P nxt = cur + random_direction() * step;
    if (score(nxt) < score(cur))
        cur = nxt;
    step *= 0.98;
}