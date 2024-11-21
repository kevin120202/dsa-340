class BTreeNode:
    def __init__(self, t, is_leaf):
        """
        Initialize a B-tree node.
        :param t: Minimum degree of the B-tree.
        :param is_leaf: Boolean indicating if the node is a leaf.
        """
        self.t = t  # Minimum degree
        self.leaf = is_leaf  # True if leaf node
        self.keys = []  # List to hold keys
        self.children = []  # List to hold children pointers


class BTree:
    def __init__(self, t):
        """
        Initialize the B-tree.
        :param t: Minimum degree of the B-tree.
        """
        self.t = t
        self.root = BTreeNode(t, is_leaf=True)

    def search(self, node, key):
        """
        Search for a key in the B-tree starting at the given node.
        :param node: Current node.
        :param key: Key to search for.
        :return: Tuple of (node, index) if found, else None.
        """
        pass  # Fill in the search logic here

    def insert(self, key):
        """
        Insert a key into the B-tree.
        :param key: Key to insert.
        """
        pass  # Fill in the insert logic here

    def insert_non_full(self, node, key):
        """
        Insert a key into a node that is not full.
        :param node: The node to insert into.
        :param key: Key to insert.
        """
        pass  # Fill in the insert_non_full logic here

    def split_child(self, parent, index):
        """
        Split the child of a node that is full.
        :param parent: Parent node containing the child to split.
        :param index: Index of the child to split.
        """
        pass  # Fill in the split_child logic here

    def traverse(self, node):
        """
        Traverse the B-tree and print all keys in sorted order.
        :param node: Node to start traversal from.
        """
        pass  # Fill in the traverse logic here
