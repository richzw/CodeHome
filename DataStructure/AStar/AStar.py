'''
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
