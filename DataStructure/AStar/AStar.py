'''
simple version
'''
def floodfill(graph, start):
	frontier = Queue()
	frontier.put(start)
	visited = {}
	visited[start] = True
	while not frontier.empty():
		current = frontier.get()
		for neighbor in graph.neighbors(current):
			if neighbor not in visited:
				frontier.put(neighbor)
				visited[neighbor] = True

'''
Get path
'''
def floodfill(graph, start):
	frontier = Queue()
	frontier.put(start)
	paths = {}
	paths[start] = None
	while not frontier.empty():
		current = frontier.get()
		for neighbor in graph.neighbors(current):
			if neighbor not in paths:
				frontier.put(neighbor)
				paths[neighbor] = current
				
'''
Get Distance
'''
def floodfill(graph, start):
	frontier = Queue()
	frontier.put(start)
	distance = {}
	distance[start] = 0
	while not frontier.empty():
		current = frontier.get()
		for neighbor in graph.neighbors(current):
			if neighbor not in distance:
				frontier.put(neighbor)
				distance[neighbor] = 1 + distance[current]
				
