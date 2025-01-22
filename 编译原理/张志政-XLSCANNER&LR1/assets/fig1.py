import matplotlib.pyplot as plt
import networkx as nx

# Create a directed graph
G = nx.DiGraph()

# Add nodes with positions
positions = {
    0: (0, 0),
    1: (2, 2),
    2: (4, 2),
    3: (2, -2),
    4: (4, -2),
    5: (6, -2),
    6: (2, -4),
    7: (0, -4),
    8: (-2, -4),
    9: (0, -6),
    10: (-2, -6),
    11: (-2, 0),
    12: (2, 0)
}

# Add nodes
G.add_nodes_from(positions.keys())

# Add labeled edges
edges = [
    (0, 1, '+'), (0, 1, '*'), (0, 2, '+'), (0, 2, '*'), 
    (1, 1, '+'), (2, 2, '*'), (0, 3, '<'), (0, 3, '>'), 
    (3, 4, '='), (3, 4, '!'), (4, 5, '='), (5, 5, '='), 
    (0, 11, ''), (11, 12, '='), (12, 12, '='),
    (0, 6, ','), (6, 6, ';'),
    (0, 7, ''), (7, 8, 'a-z,A-Z'), (8, 8, 'a-z,A-Z,0-9'),
    (0, 9, ''), (9, 9, '0-9'),
]

for edge in edges:
    G.add_edge(edge[0], edge[1], label=edge[2])

# Draw the graph
plt.figure(figsize=(12, 8))
nx.draw(
    G, positions, with_labels=True, node_size=2000, node_color="lightblue", font_size=10,
    font_weight="bold", arrowsize=20
)

# Draw edge labels
edge_labels = {(u, v): d['label'] for u, v, d in G.edges(data=True)}
nx.draw_networkx_edge_labels(G, positions, edge_labels=edge_labels, font_size=8)

plt.title("NFA Diagram", fontsize=16)
plt.show()
