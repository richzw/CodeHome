####Graph Search algorithm
'''
One Source, one destination:
- Greedy Best First Search
- A START
One source, all destinations, or all sources, one destination:
- Breadth First Search - unweighted edges
- Dijkstra’s Algorithm - adds weights to edges
- Bellman-Ford - supports negative weights
All sources, all destinations:
- Floyd-Warshall
- Johnson’s Algorithm

http://www.redblobgames.com/pathfinding/tower-defense/
'''

def BFS(start):
	open = Queue()
	open.put(start)
	start.visited = True
	#start.parent = None
	## start.distance = 0

	while not open.empty():
		current = open.get()
		for next in current.neighbors():
			if not next.visited:
				next.visited = True
				#next.parent = current
				## next.distance = current.distance + 1
				open.put(next)
