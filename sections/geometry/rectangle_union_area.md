Maintain a data structure for the active cross-section while events are visited
in coordinate order. Compute the contribution from $x_{prev}$ to $x$ using the
**old** active state, then apply all events at $x$ as one group.

### Rectangle union

$$
area\mathrel{+}=covered_y\,(x-x_{prev}).
$$

- Start at $x_1$: add $[y_1,y_2)$.
- End at $x_2$: remove $[y_1,y_2)$.

Coordinate-compress all $y$ endpoints. A segment-tree node stores a cover count:

- `cover > 0`: covered length is $ys_r-ys_l$.
- `cover == 0`: sum its children, or use zero at a leaf.

Grouping equal $x$ avoids arbitrary start/end tie order. In sweeps with point
queries, tie order is semantic: decide the open/closed boundaries before placing
add, query, and remove events.

Skip zero-area rectangles, keep half-open intervals consistent, and use
`__int128` if coordinate difference times covered length may overflow.
