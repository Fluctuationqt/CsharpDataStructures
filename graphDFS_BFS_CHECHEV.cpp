void dfs(int v, bool visited[], list<int>[] *adj ) {
 visited[v] = true;
 //TODO: обхождането в дълбочина е с някаква цел. Например търсене на
 // определена характеристика. Да се добави в зависимост от задачата.

 list<int>::iterator i;
	for (auto i : adj[v]){ // i = adj[v].begin(); i != adj[v].end(); ++i
		if (!visited[*i]){
			dfs(*i, visited,adj);
		}
	}
}

void BFS(int s,list<int>[] *adj) {
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++){
	 visited[i] = false;
	}
	list<int> queue;
	queue.push_back(s);
	visited[s] = true;
	list<int>::iterator i;
	while(!queue.empty()) {
		 s = queue.front();
		 queue.pop_front();
		 // TODO:обхождането в ширина е с някаква цел.
		 for (auto i : adj[s]) {
			 if (!visited[*i]) {
				 visited[*i] = true;
				 queue.push_back(*i);
			 }
		 }
	}
}

/*

    TOP SORT:
	L <- Empty list that will contain the sorted nodes
	while there are unmarked nodes do
	  select an unmarked node n
	  visit(n)

	function visit(node n)
	  if n has a permanent mark then return
	  if n has a temprorary mark then stop
	  mark n temporarily
	  for each node m with an edge from n to m do
		visit(m)
	  mark n permanently
	  add n to head of L

	  Example:
	  0 - > NULL
	  1 - > NULL
	  2 - > 3
	  3 - > 1
	  4 - > 0, 1
	  5 - > 0, 2
	  
	  DFS of the shown graph is “5 2 3 1 0 4”, 
	  but it is not a topological sorting
	  
	  True output:
	  5 4 2 3 1 0 is a topological sorting
	  and it's not the only one 
*/