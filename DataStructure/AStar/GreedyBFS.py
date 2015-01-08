
def heuristic(a, b):
   # Manhattan distance on a square grid
   return abs(a.x - b.x) + abs(a.y - b.y)
  
def greedy_bfs(graph, start, goal):   
  frontier = PriorityQueue()
  frontier.put(start, 0)
  came_from = {}
  came_from[start] = None
  
  while not frontier.empty():
     current = frontier.get()
  
     if current == goal:
        break
     
     for next in graph.neighbors(current):
        if next not in came_from:
           priority = heuristic(goal, next)
           frontier.put(next, priority)
           came_from[next] = current
