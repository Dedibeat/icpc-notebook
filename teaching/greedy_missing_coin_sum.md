# Greedy lesson: Missing Coin Sum

**Problem:** [CSES 2183 — Missing Coin Sum](https://cses.fi/problemset/task/2183/), Sorting and Searching.

**Audience:** General audience. Approximately 10 minutes. Use coin cards or write the values on a board.

**Learning goal:** Understand how a greedy solution can maintain a simple guarantee, and why the next choice preserves it.

## 1. Start with a puzzle — 2 minutes

> You have five coins worth **1, 2, 2, 7, and 9**. Each coin can be used at most once. What is the smallest positive amount you cannot pay exactly?

Let the audience try amounts:

- 1: use 1.
- 2: use either 2.
- 3: use 1 + 2.
- 4: use 2 + 2.
- 5: use 1 + 2 + 2.
- 6: the three small coins total only 5, and every other coin is already too large.

The answer is **6**.

Ask: “Can we find that gap without trying every subset or every amount?”

## 2. Discover the useful guarantee — 2 minutes

Sort the coins from smallest to largest.

Keep the coins in two groups: **checked coins** and **coins we have not checked yet**.

Let **R be the total value of the checked coins**. We will maintain this promise:

> With the checked coins, we can pay every whole-number amount from 0 through R.

Each amount is a separate payment: we can choose a different subset of coins for each amount. We are not trying to pay all those amounts at once.

Initially there are no checked coins. Their total is R = 0, and paying 0 means taking no coins.

| Next coin | What we can make before it | Decision | What we can make afterward |
|---|---|---|---|
| 1 | 0 | Include it | 0 through 1 |
| 2 | 0 through 1 | Include it | 0 through 3 |
| 2 | 0 through 3 | Include it | 0 through 5 |
| 7 | 0 through 5 | Stop: 6 is missing | Answer: 6 |

Emphasize both facts: **the checked coins total R**, and **every amount up to R is possible**. Knowing their total alone would not guarantee that every smaller payment is possible.

## 3. Explain why the greedy step works — 3 minutes

### Begin with the concrete example

Our checked coins are **1, 2, 2**. They total **5**, and we have shown how to pay each amount from 0 through 5.

Suppose the next coin is **4**. Every old payment is still possible. For the new amounts, use the new coin and pay the rest with the old coins:

| New amount | Use the new coin | Pay the rest using old coins |
|---|---|---|
| 6 | 4 | 2 |
| 7 | 4 | 1 + 2 |
| 8 | 4 | 2 + 2 |
| 9 | 4 | 1 + 2 + 2 |

So we can now pay every amount from 0 through 9, the new total.

But suppose the next coin is **7** instead. We cannot pay 6:

- Without an unchecked coin, even taking every checked coin gives only 5.
- With an unchecked coin, even the smallest one is already worth 7.

There is no third possibility. The answer is 6.

### The same reasoning for any set of coins

The checked coins total **R**, and can pay every whole-number amount from 0 through R. Let **c be the smallest unchecked coin**.

**If c is greater than R + 1, stop.**

To pay R + 1, we would have to either use an unchecked coin or use none:

- Using none gives at most R, even if we take all the checked coins.
- Using one or more gives at least c, which is too much. All coin values are positive.

Therefore R + 1 is impossible. Every smaller positive amount is already possible, so it is the smallest missing amount.

**If c is at most R + 1, add it to the checked coins.**

All payments up to R are still possible by ignoring the new coin. Consider any new whole-number amount **A from R + 1 through R + c**:

1. Use the new coin c once.
2. The remaining amount is A − c.
3. That remainder is at least 0: A is at least R + 1, and c is at most R + 1.
4. It is at most R: A is at most R + c.
5. We already know how to pay every remainder from 0 through R using only the old coins.

Thus every new amount is possible too. The promise still holds, with the new total R + c.

If we check every coin without finding a gap, all amounts up to the final total R are possible. R + 1 exceeds the value of all our coins combined, so it is the answer.

## 4. State the algorithm — 1 minute

1. Sort the coin values.
2. Start with R = 0.
3. For each coin c, from smallest to largest:
   - If c > R + 1, return R + 1.
   - Otherwise, increase R by c.
4. If every coin was included, return R + 1.

Sorting takes **O(n log n)** time; the scan takes **O(n)** time and **O(1)** additional working space beyond the sorted array.

For a C++ implementation, R must be `long long`: the constraints allow a total coin value of 2 × 10^14.

## 5. Check understanding — 2 minutes

Ask the audience to explain each answer using the range guarantee:

| Coins | Smallest missing amount | Teaching point |
|---|---|---|
| 2, 3, 4 | 1 | The first coin can already reveal a gap. |
| 1, 1, 1 | 4 | Equal-valued coins are separate usable coins. |
| 1, 2, 3 | 7 | Sometimes the answer is one more than the total. |
| 1, 2, 4, 8 | 16 | A coin equal to R + 1 extends coverage perfectly. |
| 1, 2, 5 | 4 | Later, larger coins cannot repair an earlier gap. |

Final audience question:

> Why must we sort the coins before stopping at a gap?

Expected explanation: only sorting guarantees that no remaining coin is small enough to fill it. For example, stopping immediately at 5 in the unsorted list [5, 1, 2] would incorrectly report 1.

## Presenter notes

- Keep “each coin at most once” visible throughout the lesson.
- The stopping condition is strictly c > R + 1; equality is safe.
- Use positive integer coin values, as required by the problem.
- Ask the audience to describe the guarantee before introducing the word “invariant.”
- No graph terminology or advanced data structure is needed.
