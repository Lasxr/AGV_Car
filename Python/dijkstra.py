
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
    'A1':{'B1': 1, 'A2': 1},
    'B1': {'A1': 1,},
    'C1': {'C2': 1, 'D1': 1, 'E1': 2},
    'D1': {'C1': 1, 'E1': 1},
    'E1': {'D1': 1, 'E2': 1},
    'F1': {'F5': 4}, 
    'A2':{'B2': 1},
    'B2': {'C2': 1, 'A2': 1},
    'C2': {'B2': 1, 'C1': 1},
    'D2': {'E2': 1, 'D3': 1},
    'E2': {'E1': 1, 'D2': 1},
    'F2': {'F5': 3,},
    'A3':{'A6': 3, 'A4': 1},
    'B3': {'D3': 2,'B6': 3, 'B4': 1},
    'C3': {'B3': 1, 'D3': 1},
    'D3': {'B3': 2, 'D2': 1},
    'E3': {'F3': 1, 'E5': 2},
    'F3': {'E3': 1, 'F5': 2},
    'A4':{'A3': 1, 'A6': 2},
    'B4': {'B3': 1, 'B6': 2},
    'C4': {'F4': 3,},
    'D4': {'F4': 2,},
    'E4': {'E3': 1, 'E5': 1, 'F4': 1},
    'F4': {'F5': 1, 'C4': 3},
    'A5':{'A6': 1, 'D5': 3},
    'B5': {'B3': 2, 'D5': 2, 'B4': 1},
    'C5': {'D5': 1, 'A5': 2},
    'D5': {'A5': 3, 'D6': 1},
    'E5': {'E3': 2, 'F5': 1},
    'F5': {'F1': 4, 'E5': 1},   
    'A6':{'A3': 3, 'B6':1},
    'B6': {'B3': 3,},
    'C6': {'F6': 3},
    'D6': {'D5': 1, 'F6':2},
    'E6': {'F6': 1,},
    'F6': {'C6': 3,}, 

}

graph = make_bidirectional(graph)
print(dijkstra(graph,'A1','F6'))
