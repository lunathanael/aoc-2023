import networkx as nx

# Sample input data
data = open('input25.txt').strip().split('\n')

# Create a graph from the input data
G = nx.Graph()
for line in data:
    parts = line.split(': ')
    node = parts[0]
    connected_nodes = parts[1].split()
    for cn in connected_nodes:
        G.add_edge(node, cn)

