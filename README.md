# Binary Search Tree (BST) Operations

This program demonstrates the basic operations of a Binary Search Tree (BST) implemented in C++. The operations covered include inserting nodes, removing nodes using different strategies, and performing an inorder traversal.

## Features
1. **Insertion**: Insert new elements (books) into the BST.
2. **Removal**: Remove nodes from the tree using two strategies:
   - **Strategy 1**: Always remove the leftmost node in the left subtree or the rightmost node in the right subtree.
   - **Strategy 2**: Alternate between removing the leftmost node in the left subtree and the rightmost node in the right subtree.
3. **Inorder Traversal**: Traverse the tree and print the nodes in sorted order.

## Files

- **books.txt**: A text file containing a list of book titles. These are read and inserted into the binary search tree. The file should be formatted with one book title per line.

## Functions

### 1. `insert(struct node* root, std::string val)`
Inserts a new node with the given book title (`val`) into the binary search tree, maintaining the BST property.

### 2. `removeNode(struct node* root, std::string val, bool left = true)`
Removes a node with the given book title (`val`). The `left` parameter specifies whether to remove from the left or right subtree. It follows these cases:
- Case 1: The node is a leaf node (no children).
- Case 2: The node has only a right child.
- Case 3: The node has only a left child.
- Case 4: The node has both left and right children.

### 3. `getLeftMax(struct node* root)`
Returns the maximum node in the left subtree of the given root node.

### 4. `getRightMin(struct node* root)`
Returns the minimum node in the right subtree of the given root node.

### 5. `strategy1(struct node* root, std::string book)`
Removes a node following **Strategy 1**, which always removes the leftmost node in the left subtree or the rightmost node in the right subtree.

### 6. `strategy2(struct node* root, std::string book)`
Removes a node following **Strategy 2**, which alternates between removing the leftmost node in the left subtree and the rightmost node in the right subtree.

### 7. `inorder(struct node* root)`
Performs an inorder traversal of the BST and prints the keys (book titles) in sorted order.

## Compilation and Execution

### Compilation
To compile the code, use the following command:
