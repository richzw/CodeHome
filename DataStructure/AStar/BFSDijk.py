
 def bfs_dijk(graph, start, goal):
	frontier = Queue.PriorityQueue()
	frontier.put(start, 0)
	came_from = {}
	cost_so_far = {}
	came_from[start] = None
	cost_so_far[start] = 0
	while not frontier.empty():
		current = frontier.get()
		if current == goal:
			break
		for neighbor in graph.neighbors(current):
			new_cost = cost_so_far[current] + graph.cost(current, neighbor)
			if neighbor not in cost_so_far or new_cost < cost_so_far[neighbor]:
				cost_so_far[neighbor] = new_cost
				frontier.put(neighbor, new_cost)
				came_from[neighbor] = current
