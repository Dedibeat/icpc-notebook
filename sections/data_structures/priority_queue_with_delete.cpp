// Heap with lazy deletion. Only erase values that are currently in the heap.
// top()/pop() require nonempty heap (size() > 0). All ops O(log n).
struct Heap {
	priority_queue<int> in, out;
	void push(int v) { in.push(v); }
	void erase(int v) { out.push(v); }
	int size() { return in.size() - out.size(); }
	int top() {
		while (out.size() && in.top() == out.top()) in.pop(), out.pop();
		return in.top();
	}
	void pop() { top(); in.pop(); }
};
