
def dijkstra(graph,start,end):
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0

    previous_node = {node: None for  node in graph}
    visited = set()
    while len(visited)<len(graph):
        current_node = None
        for node in distances:
            if node not in visited:
                if current_node is None:
                    current_node=node
                elif distances[node]<distances[current_node]:
                    current_node=node
        if distances[current_node]== float('infinity'):
            break
        visited.add(current_node)
        for neighbor,weight in graph[current_node].items():
            distance = distances[current_node]+weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous_node[neighbor]=current_node
    path = []
    current_node = end
    while previous_node[current_node] is not None:
        path.insert(0,current_node)
        current_node=previous_node[current_node]
    if path:
        path.insert(0,start)

    return path,distances[end]

graph = {
    'A':{'D':1},
    'B': {'C': 1, "E": 1},
    'C': {'B': 1, "F": 1, "I": 2},
    'D': {'A': 1, "E": 1},
    'E': {'D': 1, "B": 1},
    'F': {'I': 1, "C": 1},
    'G': {'H': 1, "I": 1},
    'H': {'G': 1, "I": 1},
    'I': {'G': 2, "H": 1, "F": 1, "C": 2}
}

print(dijkstra(graph,'A','G'))