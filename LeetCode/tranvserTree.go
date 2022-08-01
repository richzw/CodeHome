// https://fanlv.wiki/2021/08/12/post-order/
func PreOrderInteractive(root *TreeNode) {
	if root == nil {
		return
	}
	stack := make([]*TreeNode, 0)
	stack = append(stack, root)
	for len(stack) > 0 {
		node := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		fmt.Printf("%d, ", node.Val)

		if node.Right != nil {
			stack = append(stack, node.Right)
		}
		if node.Left != nil {
			stack = append(stack, node.Left)
		}
	}
}

func inOrderInteractive(root *TreeNode) {
	if root == nil {
		return
	}
	stack := make([]*TreeNode, 0)
	node := root

	for node != nil || len(stack) > 0 {
		if node != nil {
			stack = append(stack, node)
			node = node.Left
			continue
		}

		node = stack[len(stack)-1]
		fmt.Printf("%d, ", node.Val)
		stack = stack[:len(stack)-1]
		node = node.Right
	}
}

func postOrderInteractive(root *TreeNode) {
	if root == nil {
		return
	}
	stack := make([]*TreeNode, 0)
	node := root
	var prev *TreeNode

	for node != nil || len(stack) > 0 {
		if node != nil {
			stack = append(stack, node)
			node = node.Left
			continue
		}

		node = stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		if node.Right == nil || node.Right == prev {
			fmt.Printf("%d, ", node.Val)
			prev = node
			node = nil
		} else {
			stack = append(stack, node)
			node = node.Right
		}
	}
}

func postOrderInteractive2(root *TreeNode) {
	if root == nil {
		return
	}
	inp := make([]*TreeNode, 0)
	out := make([]int, 0)
	inp = append(inp, root)

	for len(inp) > 0 {
		node := inp[len(inp)-1]
		inp = inp[:len(inp)-1]

		out = append(out, node.Val)

		if node.Left != nil {
			inp = append(inp, node.Left)
		}
		if node.Right != nil {
			inp = append(inp, node.Right)
		}
	}

	for l := len(out) - 1; l >= 0; l-- {
		fmt.Printf("%d, ", out[l])
	}
}

func PostOrder(root *TreeNode) {
	if root == nil {
		//fmt.Println("nil")
		return
	}
	PostOrder(root.Left)
	PostOrder(root.Right)
	fmt.Printf("%d, ", root.Val)
}

type IterNode struct {
	line int
	node *TreeNode
}

func postOrderInteractive3(root *TreeNode) {
	if root == nil {
		return
	}
	stack := make([]*IterNode, 0)
	stack = append(stack, &IterNode{node: root, line: 0})

	for len(stack) > 0 {
		cur := stack[len(stack)-1]
		if cur.line == 0 {
			if cur.node == nil {
				stack = stack[:len(stack)-1]
				continue
			}
		} else if cur.line == 1 {
			stack = append(stack, &IterNode{node: cur.node.Left, line: 0})
		} else if cur.line == 2 {
			stack = append(stack, &IterNode{node: cur.node.Right, line: 0})
		} else if cur.line == 3 {
			fmt.Printf("%d, ", cur.node.Val)
			stack = stack[:len(stack)-1]
		}

		cur.line++
	}
}
