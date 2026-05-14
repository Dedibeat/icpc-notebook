struct Heap {
	PQ<int> qi,qo;
	void ins(int v,int o) { (o>0?qi:qo).push(v); }
	int top() {
		while(qo.size()&&qi.top()==qo.top()) qi.pop(),qo.pop();
		return qi.top();
	}
};
