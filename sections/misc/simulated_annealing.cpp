// Local search with shrinking step (hill climbing / pattern search).
// Good for: approximate geometric optimization (e.g. point minimizing max
// distance), unimodal-ish continuous functions. Tune step count to time limit.
// For true simulated annealing also accept worse moves with probability
// exp((score(cur)-score(nxt))/temp), temp decaying like step.
P cur = start;
double step = initial_step; // e.g. max coordinate range

while (step > 1e-9) {
    P nxt = cur + random_direction() * step;
    if (score(nxt) < score(cur))
        cur = nxt;
    step *= 0.98; // slower decay (0.999) = better quality, more time
}
