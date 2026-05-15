struct Heap {
	// NOTE: top() assumes heap is nonempty and deletes were previously inserted.
	priority_queue<int> qi, qo;
	void ins(int v,int o) { (o>0?qi:qo).push(v); }
	int top() {
		while(qi.size() && qo.size() && qi.top()==qo.top()) qi.pop(),qo.pop();
		return qi.top();
	}
};
