def reconstruct_tree_in_pre(inorder: list, preorder: list, parent: dict):
    """
    Given the inorder and preorder traversals of a tree, reconstructs it

    :param inorder: list
    :param preorder: list
    :param parent: dict which tells for a vertex (int) who is their parent
    :return: the root of the tree
    """
    if len(inorder) == 0:
        return -1
    if len(inorder) == 1:
        return inorder[0]

    root = preorder[0]
    idx_root_inorder = 0
    while inorder[idx_root_inorder] != root:
        idx_root_inorder += 1

    left_child = reconstruct_tree_in_pre(inorder[0:idx_root_inorder], preorder[1:idx_root_inorder + 1], parent)
    right_child = reconstruct_tree_in_pre(inorder[idx_root_inorder + 1:], preorder[idx_root_inorder + 1:], parent)

    if left_child != -1:
        parent[left_child] = root
    if right_child != -1:
        parent[right_child] = root
    return root


def reconstruct_tree_in_post(inorder: list, postorder: list, parent: dict):
    """
    Given the inorder and postorder traversals of a tree, reconstructs it

    :param inorder: list
    :param postorder: list
    :param parent: dict which tells for a vertex (int) who is their parent
    :return: the root of the tree
    """
    if len(inorder) == 0:
        return -1
    if len(inorder) == 1:
        return inorder[0]

    root = postorder[-1]
    idx_root_inorder = 0
    while inorder[idx_root_inorder] != root:
        idx_root_inorder += 1

    left_child = reconstruct_tree_in_post(inorder[:idx_root_inorder], postorder[:idx_root_inorder], parent)
    right_child = reconstruct_tree_in_post(inorder[idx_root_inorder + 1:], postorder[idx_root_inorder:-1], parent)

    if left_child != -1:
        parent[left_child] = root
    if right_child != -1:
        parent[right_child] = root
    return root
