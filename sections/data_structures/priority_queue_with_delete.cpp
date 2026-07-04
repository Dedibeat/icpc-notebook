// Heap with lazy deletion. Only erase values that are currently in the heap.
// top()/pop() require nonempty heap (size() > 0). All ops O(log n).
// EDIT ONLY PQ: use priority_queue<int, vector<int>, greater<int>> for a
// min-heap (both queues MUST stay the same type).
struct Heap {
	using PQ = priority_queue<int>;
	PQ in, out;
	void push(int v) { in.push(v); }
	void erase(int v) { out.push(v); }
	int size() { return in.size() - out.size(); }
	int top() {
		while (out.size() && in.top() == out.top()) in.pop(), out.pop();
		return in.top();
	}
	void pop() { top(); in.pop(); }
};
