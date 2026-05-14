## Ordered Set / Ordered Map (PBDS)

Header:


**Ordered Set**



**Ordered Map**



**Supported operations**



Time complexity: $O(\log n)$

---

## Ordered Multiset

PBDS does not support duplicates directly.  
Trick: store pairs.



Alternative trick (less clean):


---

## Rope

Header:


Rope is useful for fast string modifications.



Time complexity:
$$
\text{insert / erase / substring } = O(\log n)
$$

Common use cases:

- Editor simulation
- Large string modifications
- Persistent-like behavior
