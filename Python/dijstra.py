def dijkstra(graph, start,end):
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0

    previous_nodes = {node: None for node in graph}
    