from treelib import Node, Tree

tree = Tree()
n = int(input().split(' ')[0])
tree.create_node(1, 1)
for i in range(1, n):
    tree.create_node(i+1, i+1, parent=int(input()))
tree.show()
