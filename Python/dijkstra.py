
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

def make_bidirectional(graph):
    new_graph = {node: neighbors.copy() for node, neighbors in graph.items()}
    for node in graph:
        for neighbor, weight in graph[node].items():
            if neighbor not in new_graph:
                new_graph[neighbor] = {}
            if node not in new_graph[neighbor]:
                new_graph[neighbor][node] = weight
    return new_graph


graph = {
    'A1':{'D1': 3},
    'B1': {'D1': 2},
    'C1': {'D1': 1},
    'D1': {'D2': 1},
    'E1': {'D1': 1},
    'F1': {'D1': 2}, 
    'A2': {'A3': 1},
    'B2': {'D2': 2, 'B3': 1},
    'C2': {'D2': 1, 'B2': 1},
    'D2': {'B2': 2, 'F2': 2},
    'E2': {'B2': 3, 'F2': 1},
    'F2': {'B2': 4, 'F4': 2},
    'A3': {'E3': 4},
    'B3': {'E3': 3, 'A3': 1},
    'C3': {'E3': 2, 'A3': 2},
    'D3': {'E3': 1, 'A3': 3},
    'E3': {'A3': 4, 'E4': 1},
    'F3': {'F2': 1, 'F4': 2},
    'A4': {'A6': 2, 'C4': 2},
    'B4': {'B5': 1, 'C4': 1, 'A4': 1},
    'C4': {'C5': 1, 'A4': 2},
    'D4': {'E4': 1, 'D5': 1},
    'E4': {'E3': 1, 'D4': 1},
    'F4': {'F2': 2},
    'A5': {'A4': 1, 'A6': 3},
    'B5': {'B4': 1},
    'C5': {'C4': 1, 'F5': 3},
    'D5': {'F5': 2, 'D4': 1, 'C5': 1},
    'E5': {'E6': 1, 'F5': 1, 'C5': 2},
    'F5': {'F6': 1, 'C5': 3},   
    'A6': {'E6': 4, 'A4': 1},
    'B6': {'E6': 3, 'A6': 1},
    'C6': {'E6': 2, 'A6': 2},
    'D6': {'A6': 3, 'E6':1},
    'E6': {'A6': 4, 'E5': 1},
    'F6': {'F5': 1}, 

}

print(dijkstra(graph,'A1','F6'))
