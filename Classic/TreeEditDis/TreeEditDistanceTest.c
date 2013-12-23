#include <stdio.h>
#include <windows.h>
#include <queue>
#include <time.h>
#include "TreeEditDist.h"

using namespace GraphClustering;

#define test_assert_true(expr)  if (!(expr)) { printf("Error - should be true at line[%d].\n", __LINE__);  }
#define test_assert_false(expr) if (expr)    { printf("Error - should be false at line[%d].\n", __LINE__); }

TreeNode * GenRandomTree(int nodeCount, std::string & prefix)
{
    const int MAX_CHILDREN = 4;

    std::queue<TreeNode *> nodeQ;
    srand(GetTickCount());

    // root node
    std::string nodeLable(prefix);
    nodeLable.append("A");
    TreeNode * root = new TreeNode(nodeLable);
    nodeQ.push(root);

    for (int nCount = 1; nCount < nodeCount; )
    {
        TreeNode * curNode = nodeQ.front();
        nodeQ.pop();
        int nChildren = rand() % MAX_CHILDREN;
        for (int i = 0; i <= nChildren && nCount < nodeCount; ++i, ++nCount)
        {
            // new lable
            std::string nodeLable(prefix);
            int idx = nCount;
            while (idx >= 26)
            {
                nodeLable.push_back('A' + idx % 26);
                idx /= 26;
            }
            nodeLable.push_back('A' + idx);

            TreeNode * node = new TreeNode(nodeLable);
            curNode->AddChild(node);
            nodeQ.push(node);
        }
    }

    return root;
}

void GenGraphVizScript(TreeNode * root, TreeNode * parent, std::string & script)
{
    char buf[64];
    if (parent != NULL && root != NULL)
    {
        sprintf_s(buf, sizeof(buf), "\"%s(%d)\" -> \"%s(%d)\";\n", 
            parent->m_strLable.c_str(),
            parent->m_idxMe,
            root->m_strLable.c_str(),
            root->m_idxMe);
        script.append(buf);
    }

    TreeNode * node = root->m_pLeftMostChild;
    if (node  != NULL)
    {
        while (node != NULL)
        {
            GenGraphVizScript(node, root, script);
            node = node->m_pSibling;
        }
    }
}

void EditScriptStressTest(int nSourceTreeNode, int nTargetTreeNode)
{
    //
    //  generate two random trees
    //

    TreeNode * rootSrc = GenRandomTree(nSourceTreeNode, std::string("tree_"));
    Sleep(1000);
    TreeNode * rootTar = GenRandomTree(nTargetTreeNode, std::string("tree_"));

    //
    //  build post ordered tree and compute diff
    //

    PostOrderedTree treeSource;
    treeSource.Build(rootSrc);

    PostOrderedTree treeTarget;
    treeTarget.Build(rootTar);

    // visualize the two trees

    std::string scriptSrc;
    scriptSrc.append("digraph s { ");
    GenGraphVizScript(rootSrc, NULL, scriptSrc);
    scriptSrc.append(" }");

    std::string scriptTar;
    scriptTar.append("digraph t { ");
    GenGraphVizScript(rootTar, NULL, scriptTar);
    scriptTar.append(" }");

    // do the computing

    unsigned int nMatrixSize = treeSource.GetNodeCount() * treeTarget.GetNodeCount();
    unsigned int * pTedMatrix = new unsigned int[nMatrixSize];
    ZeroMemory(pTedMatrix, sizeof(unsigned int) * nMatrixSize);
    EditScript * pTreeEditScriptMatrix = new EditScript[nMatrixSize];

    printf("Begin stress test ...\n");

    FILETIME ftBegin, ftEnd;
    GetSystemTimeAsFileTime(&ftBegin);
    //TreeEditDistance(treeSource, treeTarget, pTedMatrix, pTreeEditScriptMatrix);
    TreeEditDistance(treeSource, treeTarget, pTedMatrix, NULL);
    GetSystemTimeAsFileTime(&ftEnd);

    ULARGE_INTEGER uiBegin, uiEnd;
    uiBegin.HighPart = ftBegin.dwHighDateTime;
    uiBegin.LowPart  = ftBegin.dwLowDateTime;
    uiEnd.HighPart = ftEnd.dwHighDateTime;
    uiEnd.LowPart  = ftEnd.dwLowDateTime;

    printf("End stress test..\n");
    printf("Test with [%d] source nodes, [%d] target nodes, cost [%d] steps, using [%f] seconds...\n", 
        nSourceTreeNode,
        nTargetTreeNode,
        pTedMatrix[nSourceTreeNode * nTargetTreeNode - 1],
        (uiEnd.QuadPart - uiBegin.QuadPart) / (10 * 1000 * 1000 + 0.0));

    int nTedMatrixRowSize = nTargetTreeNode;
    int nTedMatrixColSize = nSourceTreeNode;
    //for (int i = 0; i < nTedMatrixColSize; ++i)
    //{
    //    for (int j = 0; j < nTedMatrixRowSize; ++j)
    //    {
    //        test_assert_true(pTreeEditScriptMatrix[i * nTedMatrixRowSize + j].GetActionCount() == pTedMatrix[i * nTedMatrixRowSize + j]);
    //    }
    //}
    
    std::string editActionString;
    pTreeEditScriptMatrix[nTedMatrixRowSize * nTedMatrixColSize - 1].ToString(editActionString, treeSource, treeTarget);

    delete [] pTedMatrix;
    delete [] pTreeEditScriptMatrix;

    printf("== stress tree edit distance & script test done! ==\n");

    return;
}

void BasicEditDistanceAndScriptTest()
{
    //
    //  basic edit distance value test.
    //
    //  [the ground truth is from http://www.inf.unibz.it/dis/teaching/ATA]
    //

    //
    //      [source tree]       [target tree]
    //          f6                  f6       
    //          /\                  /\
    //         /  \                /  \
    //        d4  e5              c4  e5
    //        /\                  |
    //       /  \                 |
    //      a1  c3                d3
    //           |                /\ 
    //           |               /  \
    //           b2             a1  b2
    //

    // build source and target tree

    TreeNode sa(std::string("a")), sb(std::string("b")), sc(std::string("c")), sd(std::string("d")), se(std::string("e")), sf(std::string("f"));
    sc.AddChild(&sb);
    sd.AddChild(&sa);
    sd.AddChild(&sc);
    sf.AddChild(&sd);
    sf.AddChild(&se);
    PostOrderedTree treeSource;
    treeSource.Build(&sf);

    TreeNode ta(std::string("a")), tb(std::string("b")), tc(std::string("c")), td(std::string("d")), te(std::string("e")), tf(std::string("f"));
    td.AddChild(&ta);
    td.AddChild(&tb);
    tc.AddChild(&td);
    tf.AddChild(&tc);
    tf.AddChild(&te);
    PostOrderedTree treeTarget;
    treeTarget.Build(&tf);

    // do the computing

    unsigned int nMatrixSize = treeSource.GetNodeCount() * treeTarget.GetNodeCount();
    unsigned int * pTedMatrix = new unsigned int[nMatrixSize];
    ZeroMemory(pTedMatrix, sizeof(unsigned int) * nMatrixSize);
    EditScript * pTreeEditScriptMatrix = new EditScript[nMatrixSize];
    TreeEditDistance(treeSource, treeTarget, pTedMatrix, pTreeEditScriptMatrix);

    // check results:

    unsigned int trueMatrix[] = 
    {
        0, 1, 2, 3, 1, 5,
        1, 0, 2, 3, 1, 5,
        2, 1, 2, 2, 2, 4,
        3, 3, 1, 2, 4, 4,
        1, 1, 3, 4, 0, 5,
        5, 5, 3, 3, 5, 2
    };
    int nTedMatrixRowSize = 6;
    int nTedMatrixColSize = 6;
    for (int i = 0; i < nTedMatrixColSize; ++i)
    {
        for (int j = 0; j < nTedMatrixRowSize; ++j)
        {
            test_assert_true(pTedMatrix[i * nTedMatrixRowSize + j] == trueMatrix[i * nTedMatrixRowSize + j]);
            test_assert_true(pTreeEditScriptMatrix[i * nTedMatrixRowSize + j].GetActionCount() == trueMatrix[i * nTedMatrixRowSize + j]);
        }
    }
    
    delete [] pTedMatrix;
    delete [] pTreeEditScriptMatrix;

    printf("== basic tree edit distance & script test done! ==\n");
}

void UtilTest()
{
    //
    //  test min
    //
    test_assert_true(1 == TripleMin(1, 1 + 1, 3));
    test_assert_true(1 == TripleMin(1, 3, 1 + 1));
    test_assert_true(1 == TripleMin(1 + 1, 1, 3));
    test_assert_true(1 == TripleMin(1 + 1, 3, 1));
    test_assert_true(1 == TripleMin(3, 1 + 1, 1));
    test_assert_true(1 == TripleMin(3, 1, 1 + 1));
    printf("== triple max test done! ==\n");

    //
    //  test max
    //
    test_assert_true(3 == TripleMax(1, 1 + 1, 3));
    test_assert_true(3 == TripleMax(1, 3, 1 + 1));
    test_assert_true(3 == TripleMax(1 + 1, 1, 3));
    test_assert_true(3 == TripleMax(1 + 1, 3, 1));
    test_assert_true(3 == TripleMax(3, 1 + 1, 1));
    test_assert_true(3 == TripleMax(3, 1, 1 + 1));
    printf("== triple max test done! ==\n");
}

int main(int argc, char** argv)
{
    UtilTest();

    BasicEditDistanceAndScriptTest();

    EditScriptStressTest(50, 50);
    EditScriptStressTest(100, 100);
    EditScriptStressTest(500, 500);
    EditScriptStressTest(1000, 1000);

    return 0;
}
