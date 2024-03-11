import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
n = int(input().split(' ')[0])
list_of_edges = []
for i in range(1, n):
    list_of_edges.append([int(input()), i+1])
G.add_edges_from(list_of_edges)

nx.draw(G, with_labels=True)
plt.show()