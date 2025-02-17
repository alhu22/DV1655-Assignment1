class Node:
    def __init__(self, value):
        self.value = value   # Value of the node (integer)
        self.children = []   # List to store child nodes

    def add_child(self, child_node):
        """Add a child node to the current node."""
        self.children.append(child_node)

    def __repr__(self):
        return f"Node({self.value})"


class Tree:
    def __init__(self, root_value):
        self.root = Node(root_value)  # The root of the tree

    def add_node(self, parent_node, child_value):
        """Add a node with a given value to a parent node."""
        child_node = Node(child_value)
        parent_node.add_child(child_node)
        return child_node


# Example Usage
if __name__ == "__main__":
    # Create a tree with root value 6
    tree = Tree(6)

    # Add child nodes to the root
    child_1 = tree.add_node(tree.root, 3)
    child_2 = tree.add_node(tree.root, 2)

    # Print the tree structure
    tree.print_tree()
