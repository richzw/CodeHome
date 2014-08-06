#http://www.redblobgames.com/pathfinding/a-star/introduction.html

'''
A* algorithm is like Dijkstra's algorithm in that it can be used to find a shortest path.
A* is like Greedy Best-First-Search in that it can use a heuristic to guide itself. 
https://github.com/prettymuchbryce/easystarjs

OPEN = priority queue containing START
CLOSED = empty set
while lowest rank in OPEN is not the GOAL:
  current = remove lowest rank item from OPEN
  add current to CLOSED
  for neighbors of current:
    cost = g(current) + movementcost(current, neighbor)
    if neighbor in OPEN and cost less than g(neighbor):
      remove neighbor from OPEN, because new path is better
    if neighbor in CLOSED and cost less than g(neighbor): **
      remove neighbor from CLOSED
    if neighbor not in OPEN and neighbor not in CLOSED:
      set g(neighbor) to cost
      add neighbor to OPEN
      set priority queue rank to g(neighbor) + h(neighbor)
      set neighbor's parent to current
'''
import heapq

def aStar(self, graph, current, end):
    closedList = set()
    path = []

    def retracePath(c):
        path.insert(0,c)
        if c.parent == None:
            return
        retracePath(c.parent)

    openList = [(-1, current)]
    heapq.heapify(openList)
    while openList:
        score, current = openList.heappop()
        if current == end:
            return retracePath(current)
        closedList.add(current)
        for tile in graph[current]:
            if tile not in closedList:
                tile.H = (abs(end.x-tile.x)+abs(end.y-tile.y))*10 
                if tile not in openList:
                    openList.heappush((tile.H, tile))
                tile.parent = current
    return path
