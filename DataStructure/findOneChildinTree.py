//Q: 给定二叉树，求只有一个child的节点数

def count_one_child_node(btree):
    count = 0
    queue = []
    if btree != None:
        queue.append(btree)

        while queue:
            current = queue.pop(0)
            #print current.data
            if current.left_node != None and current.right_node == None:
                count += 1
                queue.append(current.left_node)
            elif current.left_node == None and current.right_node != None:
                count += 1
                queue.append(current.right_node)
            elif current.left_node and current.right_node:
                queue.append(current.left_node)
                queue.append(current.right_node)

    return count
