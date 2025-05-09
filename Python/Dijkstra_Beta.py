def Graph_gen(walls):
    rows, cols = 6, 6
    graph = {}

    directions = {
        'U': (-1, 0),
        'D': (1, 0),
        'L': (0, -1),
        'R': (0, 1)
    }

    for i in range(rows):
        for j in range(cols):
            node = chr(ord('A') + i) + str(j + 1)
            graph[node] = {}
            blocked = walls.get(node, '')
            for d, (di, dj) in directions.items():
                if d not in blocked:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < rows and 0 <= nj < cols:
                        neighbor = chr(ord('A') + ni) + str(nj + 1)
                        graph[node][neighbor] = 1
    return graph


def dijkstra(graph, start, end):
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0
    previous_node = {node: None for node in graph}
    visited = set()

    while len(visited) < len(graph):
        current_node = None
        for node in distances:
            if node not in visited:
                if current_node is None or distances[node] < distances[current_node]:
                    current_node = node
        if distances[current_node] == float('infinity'):
            break
        visited.add(current_node)

        for neighbor, weight in graph[current_node].items():
            distance = distances[current_node] + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous_node[neighbor] = current_node

    path = []
    current_node = end
    while previous_node[current_node] is not None:
        path.insert(0, current_node)
        current_node = previous_node[current_node]
    if path:
        path.insert(0, start)

    return path, distances[end]


walls = {
    'A1': 'R',  'B1': 'R',   'C1': 'D',  'D1': 'U',  'E1': 'D',  'F1': 'U',
    
    'A2': 'LD',  'B2': 'LUR',  'C2': '',  'D2': 'D',  'E2': 'UR',  'F2': '',
    
    'A3': '',  'B3': 'LD',  'C3': 'UD',  'D3': 'U',  'E3': 'LD',  'F3': 'U',
    
    'A4': 'R',  'B4': '',  'C4': 'R',  'D4': '',  'E4': '',  'F4': '',
    
    'A5': 'L',  'B5': 'R',  'C5': 'LR',  'D5': 'D',  'E5': 'UR',  'F5': '',
    
    'A6': 'D',  'B6': 'UL',  'C6': 'L',  'D6': '',  'E6': 'LD',  'F6': 'U'
}

graph = Graph_gen(walls)

print(dijkstra(graph,'A1','F6'))