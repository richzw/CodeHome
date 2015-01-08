"""
"""
# previous path solution

current = goal
path = [current]
while current != start:
   current = came_from[current]
   path.append(current)
