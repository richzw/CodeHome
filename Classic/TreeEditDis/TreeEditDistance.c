#include <windows.h>
#include "treeeditdist.h"

BEGIN_GRAPH_CLUSTERING_NAMESPACE

////////////////////////////////////////////////////////////////////////////////
//          implementation for class - EditScript
////////////////////////////////////////////////////////////////////////////////

void EditScript::AddAction(EditAction & action)
{
    m_vecAction.push_back(action);
}

void EditScript::AddScript(EditScript & script)
{
    if (script.m_vecAction.size() != 0)
    {
        m_vecAction.insert(m_vecAction.end(), script.m_vecAction.begin(), script.m_vecAction.end());
    }
}

void EditScript::Clear()
{
    m_vecAction.clear();
}

void EditScript::ToString(std::string & outStr, PostOrderedTree & from, PostOrderedTree & to)
{
    char buf[1024];
    for (std::vector<EditAction>::const_iterator iter = m_vecAction.begin();
        iter != m_vecAction.end();
        ++iter)
    {
        if (iter->m_edType == EditAction::INSERT)
        {
            sprintf_s(buf, 1024, "INSERT [%d]-th node in target to source tree : parent[%d](in source tree), left most child[%d](in target tree), right most child[%d](in target tree)\n",
                iter->m_this,
                iter->m_target,
                iter->m_firstChild,
                iter->m_lastChild);
            outStr.append(buf);
        }
        else if (iter->m_edType == EditAction::DELETE_T)
        {
            sprintf_s(buf, 1024, "DELETE [%d]-th node in source tree\n", iter->m_this);
            outStr.append(buf);
        }
        else if (iter->m_edType == EditAction::RELABLE)
        {
            sprintf_s(buf, 1024, "RELABLE [%d]-th node in source from [%s] to [%s] as the [%d]-th node in target tree\n",
                iter->m_this,
                from.GetNodeAt(iter->m_this)->m_strLable.c_str(),           
                to.GetNodeAt(iter->m_target)->m_strLable.c_str(),
                iter->m_target);
            outStr.append(buf);
        }
        else
        {
            // assert(false)
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//          implementation for class - TreeNode
////////////////////////////////////////////////////////////////////////////////

TreeNode::TreeNode(std::string & nodeLable)
    :m_strLable(nodeLable),

    m_pParent(NULL),
    m_pLeftMostChild(NULL),
    m_pSibling(NULL),

    m_idxMe(INVALID_NODE_INDEX),
    m_idxParent(INVALID_NODE_INDEX),
    m_idxLeftMostChild(INVALID_NODE_INDEX),
    m_idxSibling(INVALID_NODE_INDEX)
{}

void TreeNode::AddChild(TreeNode * pNode)
{
    //assert (pNode != NULL)
    pNode->m_pParent = this;

    if (m_pLeftMostChild == NULL)
        // not child yet
    {
        m_pLeftMostChild = pNode;
    }
    else
    {
        TreeNode * tailNode = m_pLeftMostChild;
        while (tailNode->m_pSibling != NULL)
        {   
            tailNode = tailNode->m_pSibling; 
        }
        tailNode->m_pSibling = pNode;
    }
}

////////////////////////////////////////////////////////////////////////////////
//          implementation for class - PostOrderedTree
////////////////////////////////////////////////////////////////////////////////

void BuildPostOrderVector(TreeNode * root, std::vector<TreeNode *> &vec)
{
    //
    // traverse subtree first
    //
    TreeNode * curNode = root->m_pLeftMostChild;
    if (curNode != NULL)
    {
        do
        {
            BuildPostOrderVector(curNode, vec);
            curNode = curNode->m_pSibling;
        } while (curNode != NULL);
    }

    //
    // visit me
    //
    vec.push_back(root);
    root->m_idxMe = vec.size() - 1;
};

void PostOrderedTree::Build(TreeNode * node)
{
    //
    // put it in vector first
    //
    BuildPostOrderVector(node, m_vecPostOrderedNodes);

    //
    // update vector index info
    //
    for (std::vector<TreeNode *>::iterator iter = m_vecPostOrderedNodes.begin();
        iter != m_vecPostOrderedNodes.end();
        ++iter)
    {
        (*iter)->m_idxParent  = ((*iter)->m_pParent == NULL) ? INVALID_NODE_INDEX : (*iter)->m_pParent->m_idxMe;
        (*iter)->m_idxLeftMostChild = ((*iter)->m_pLeftMostChild == NULL) ? INVALID_NODE_INDEX : (*iter)->m_pLeftMostChild->m_idxMe;
        (*iter)->m_idxSibling = ((*iter)->m_pSibling == NULL) ? INVALID_NODE_INDEX : (*iter)->m_pSibling->m_idxMe;
    }
}

TreeNode * PostOrderedTree::GetNodeAt(unsigned int idx)
{
    TreeNode * nodeRet = NULL;
    if (idx < m_vecPostOrderedNodes.size())
    {
        nodeRet = m_vecPostOrderedNodes.at(idx);
    }

    return nodeRet;
}

TreeNode * PostOrderedTree::GetRightMostChild(unsigned int idx)
{
    TreeNode * node = GetNodeAt(idx);
    if (node != NULL)
    {
        node = node->m_pLeftMostChild;
        while (node != NULL && node->m_pSibling != NULL)
        {
            node = node->m_pSibling;
        }
    }

    return node;
}

unsigned int PostOrderedTree::GetRightMostChildIdx(unsigned int idx)
{
    TreeNode * node = GetNodeAt(idx);
    if (node != NULL)
    {
        node = node->m_pLeftMostChild;
        while (node != NULL && node->m_pSibling != NULL)
        {
            node = node->m_pSibling;
        }
    }

    return (node == NULL) ? INVALID_NODE_INDEX : node->m_idxMe;
}

TreeNode * PostOrderedTree::GetLeftMostChild(unsigned int idx)
{
    TreeNode * node = GetNodeAt(idx);
    return ((node == NULL) ? NULL : node->m_pLeftMostChild);
}

unsigned int PostOrderedTree::GetLeftMostChildIdx(unsigned int idx)
{
    TreeNode * node = GetNodeAt(idx);
    return ((node == NULL || node->m_pLeftMostChild == NULL) ? INVALID_NODE_INDEX : node->m_pLeftMostChild->m_idxMe);
}

unsigned int PostOrderedTree::GetNodeCount()
{
    return m_vecPostOrderedNodes.size();
}

void LeftMostLeafDescendants(PostOrderedTree & poTree, unsigned int idxNode, std::map<unsigned int , unsigned int> & outMap)
{
    if (poTree.GetNodeAt(idxNode)->m_idxLeftMostChild == -1)
        // leaf node - my left-most leaf descendant is myself
    {
        outMap[poTree.GetNodeAt(idxNode)->m_idxMe] = poTree.GetNodeAt(idxNode)->m_idxMe;
    }
    else
        // inner node
    {
        // recursive process
        for (unsigned int idx = poTree.GetNodeAt(idxNode)->m_idxLeftMostChild; idx != -1; idx = poTree.GetNodeAt(idx)->m_idxSibling)
        {
            LeftMostLeafDescendants(poTree, idx, outMap);
        }

        // my left-most leaf descendant is the same as that of my left-most child
        outMap[poTree.GetNodeAt(idxNode)->m_idxMe] = outMap[poTree.GetNodeAt(idxNode)->m_idxLeftMostChild];
    }
}

void KeyRoots(PostOrderedTree & poTree, unsigned int idxNode, std::vector<unsigned int> & vecKeyRoot)
{
    // find the left most leaf child of idxNode.
    unsigned int idxLeftMostDesc = idxNode;
    while (poTree.GetNodeAt(idxLeftMostDesc)->m_idxLeftMostChild != -1)
    {
        idxLeftMostDesc = poTree.GetNodeAt(idxLeftMostDesc)->m_idxLeftMostChild;
    }

    // each node that is pointed by left sibling is a key root
    for (unsigned int idx  =  idxLeftMostDesc; idx < idxNode; ++idx)
    {
        if (poTree.GetNodeAt(idx)->m_idxSibling != -1)
        {
            vecKeyRoot.push_back(poTree.GetNodeAt(idx)->m_idxSibling);
        }
    }

    // root of current subtree is a key root
    vecKeyRoot.push_back(idxNode);
}

//
//  Algorithm Skeleton:
//  
//  td[1..|T1|, 1..|T2|] : empty array for tree distances;
//  l1 = lmld(root(T1)); kr1 = kr(l1, |leaves(T1)|);
//  l2 = lmld(root(T2)); kr2 = kr(l2, |leaves(T2)|);
//  for x = 1 to |kr1| do
//      for y = 1 to |kr2| do
//          forest-dist(kr1[x], kr2[y], l1, l2, td);
//

void TreeEditDistance(PostOrderedTree & fromTree, PostOrderedTree & toTree, unsigned int * pTedMatrix, EditScript * pTreeEditScriptMatrix)
{
    //
    // compute Left-Most Leaf Descendant of all nodes of two tree
    //

    std::map<unsigned int, unsigned int> mapLmldFrom, mapLmldTo;
    LeftMostLeafDescendants(fromTree, fromTree.GetNodeCount() - 1, mapLmldFrom);
    LeftMostLeafDescendants(toTree, toTree.GetNodeCount() - 1, mapLmldTo);

    //
    // compute Key Root of the two tree
    //

    std::vector<unsigned int> vecKeyRootFrom, vecKeyRootTo;
    KeyRoots(fromTree, fromTree.GetNodeCount() - 1, vecKeyRootFrom);
    KeyRoots(toTree, toTree.GetNodeCount() - 1, vecKeyRootTo);

    //
    // allocate forest distance & edit script(if needed) matrix
    //

    unsigned int * pFdMatrix = new unsigned int[(fromTree.GetNodeCount() + 1) * (toTree.GetNodeCount() + 1)];
    ZeroMemory(pFdMatrix, sizeof(unsigned int) * (fromTree.GetNodeCount() + 1) * (toTree.GetNodeCount() + 1));
    EditScript * pForestEditScriptMatrix = NULL;
    if (pTreeEditScriptMatrix != NULL)
    {
        pForestEditScriptMatrix = new EditScript[(fromTree.GetNodeCount() + 1) * (toTree.GetNodeCount() + 1)];
    }

    //
    // compute forest edit distance and tree edit distance now
    //

    for (size_t i = 0; i < vecKeyRootFrom.size(); ++i)
    {
        for (size_t j = 0; j < vecKeyRootTo.size(); ++j)
        {
            ForestEditDistance(fromTree, toTree, vecKeyRootFrom[i], vecKeyRootTo[j], mapLmldFrom, mapLmldTo, 
                    pTedMatrix, pFdMatrix, pTreeEditScriptMatrix, pForestEditScriptMatrix);
        }
    }

    delete [] pFdMatrix;
    if (pForestEditScriptMatrix != NULL)
    {
        delete [] pForestEditScriptMatrix;
    }
}

//
//  Algorithm Skeleton:  
//
//  FOREST-DIST(i, j, l1, l2, td)
//
//    fd[l1[i] - 1 ... i , l2[j] - 1 ... j] : empty array;
//    fd[l1[i] - 1, l2[j] - 1] = 0;
//
//    for di = l1[i] to i do 
//      fd[di , l2[j] - 1] = fd[di - 1, l2[j] - 1] + Wdel ;
//
//    for dj = l2[j] to j do 
//      fd[l1[i] - 1, dj ] = fd[l1[i] - 1, dj - 1] + Wins ;
//
//    for di = l1[i] to i do
//      for dj = l2[j] to j do
//          if l [di] = l [i] and l [dj] = l [j] then
//              fd[di , dj] = min(fd[di - 1, dj] + Wdel,
//                      fd[di , dj - 1] + Wins,
//                      fd[di - 1, dj - 1] + Wren);
//              td[di , dj] = f [di , dj];
//          else 
//              fd[di , dj] = min(fd[di - 1, dj] + Wdel,
//                      fd[di , dj - 1] + Wins,
//                      fd[l [di] - 1, l [dj] - 1] + td[di , dj]);
//

void ForestEditDistance(PostOrderedTree & treeFrom,
                        PostOrderedTree & treeTo,
                        unsigned int idxFrom, /*index of the Root Of Right-Most Tree In FromForest*/ 
                        unsigned int idxTo,   /*index of the Root Of Right-Most Tree In ToForest*/
                        std::map<unsigned int , unsigned int> & mapLmldFrom,
                        std::map<unsigned int , unsigned int> & mapLmldTo,
                        unsigned int * pTedMatrix,
                        unsigned int * pFdMatrix,
                        EditScript * pTreeEditScriptMatrix,
                        EditScript * pForestEditScriptMatrix)
{
    //
    // NOTE: The forest distance matrix sub starts from 1 rather 0. The 0-th column and 0-th row
    //      is used for some sentinal purpose. But in outter representation and input parameter
    //      all sub value starts from 0.
    //

    //
    // this round of computation only uses part of the pFdMatrix
    //

    unsigned int nMatrixRowSize = idxTo + 2;
    unsigned int nMatrixColSize = idxFrom + 2;

    //
    // compute init matrix elements - top and left edge of the matrix
    //

    pFdMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + mapLmldTo[idxTo]] = 0;

    if (pForestEditScriptMatrix != NULL)
    {
        pForestEditScriptMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + mapLmldTo[idxTo]].Clear();
    }

    for (unsigned int idx = mapLmldFrom[idxFrom]; idx <= idxFrom; ++idx)
    {
        pFdMatrix[(idx + 1) * nMatrixRowSize + mapLmldTo[idxTo]] =
                pFdMatrix[idx * nMatrixRowSize + mapLmldTo[idxTo]] + TEO_DELETE_COST;     /*cost of delete operation*/

        if (pForestEditScriptMatrix != NULL)
        {
            pForestEditScriptMatrix[(idx + 1) * nMatrixRowSize + mapLmldTo[idxTo]].Clear();
            pForestEditScriptMatrix[(idx + 1) * nMatrixRowSize + mapLmldTo[idxTo]].AddScript(pForestEditScriptMatrix[idx * nMatrixRowSize + mapLmldTo[idxTo]]);
            EditAction deleteAction(idx);
            pForestEditScriptMatrix[(idx + 1) * nMatrixRowSize + mapLmldTo[idxTo]].AddAction(deleteAction);
        }
    }

    for (unsigned int idx = mapLmldTo[idxTo]; idx <= idxTo; ++idx)
    {
        pFdMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + (idx + 1)] =
                pFdMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + idx] + TEO_INSERT_COST; /*cost of insert operation*/

        if (pForestEditScriptMatrix != NULL)
        {
            pForestEditScriptMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + (idx + 1)].Clear();
            pForestEditScriptMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + (idx + 1)].AddScript(pForestEditScriptMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + idx]);
            EditAction insertAction(idx, treeTo.GetNodeAt(idx)->m_idxParent, treeTo.GetLeftMostChildIdx(idx), treeTo.GetRightMostChildIdx(idx));
            pForestEditScriptMatrix[mapLmldFrom[idxFrom] * nMatrixRowSize + (idx + 1)].AddAction(insertAction);
        }
    }

    //
    // compute other matrix elements buttom up using dynamic programming technique
    //
    for (unsigned int di = mapLmldFrom[idxFrom]; di <= idxFrom; ++di)
    {
        for (unsigned int dj = mapLmldTo[idxTo]; dj <= idxTo; ++dj)
        {
            if ((mapLmldFrom[di] == mapLmldFrom[idxFrom]) && (mapLmldTo[dj] == mapLmldTo[idxTo]))
                // *from* & *to* are both tree, not forest
            {
                unsigned int nRenameCost = (treeFrom.GetNodeAt(di)->GetLable().compare(treeTo.GetNodeAt(dj)->GetLable()) == 0) ? 0 : TEO_RENAME_COST;
                pFdMatrix[(di + 1) * nMatrixRowSize + (dj + 1)] = TripleMin(pFdMatrix[di * nMatrixRowSize + (dj + 1)] + TEO_DELETE_COST,
                        pFdMatrix[(di + 1) * nMatrixRowSize + dj] + TEO_INSERT_COST,
                        pFdMatrix[di * nMatrixRowSize + dj] + nRenameCost);
                pTedMatrix[di * treeTo.GetNodeCount() + dj] = pFdMatrix[(di + 1) * nMatrixRowSize + (dj + 1)];

                if (pForestEditScriptMatrix != NULL)
                {
                    pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].Clear();
                    int actionIdx = TripleMinIndex(pFdMatrix[di * nMatrixRowSize + (dj + 1)] + TEO_DELETE_COST,
                        pFdMatrix[(di + 1) * nMatrixRowSize + dj] + TEO_INSERT_COST,
                        pFdMatrix[di * nMatrixRowSize + dj] + nRenameCost);
                    if (actionIdx == 1)
                        // delete
                    {
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddScript(pForestEditScriptMatrix[di * nMatrixRowSize + (dj + 1)]);
                        EditAction deleteAction(di);
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddAction(deleteAction);
                    }
                    else if (actionIdx == 2)
                        // insert
                    {
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddScript(pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + dj]);
                        EditAction insertAction(dj, treeTo.GetNodeAt(dj)->m_idxParent, treeTo.GetLeftMostChildIdx(dj), treeTo.GetRightMostChildIdx(dj));
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddAction(insertAction);
                    }
                    else if (actionIdx == 3)
                        // relable
                    {
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddScript(pForestEditScriptMatrix[di* nMatrixRowSize + dj]);
                        if (nRenameCost != 0) /*don't record action if the lable is the same*/
                        {
                            EditAction relableAction(di, dj);
                            pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddAction(relableAction);
                        }
                    }
                    else
                    {
                        // assert(fale)
                    }
                }

                if (pTreeEditScriptMatrix != NULL)
                {
                    pTreeEditScriptMatrix[di * treeTo.GetNodeCount() + dj].Clear();
                    pTreeEditScriptMatrix[di * treeTo.GetNodeCount() + dj].AddScript(pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)]);
                }
            }
            else
                // at least one of *from* & *to* is forest, not tree
            {
                pFdMatrix[(di + 1) * nMatrixRowSize + (dj + 1)] = TripleMin(pFdMatrix[di * nMatrixRowSize + (dj + 1)] + TEO_DELETE_COST,
                        pFdMatrix[(di + 1) * nMatrixRowSize + dj] + TEO_INSERT_COST,
                        pFdMatrix[di * nMatrixRowSize + dj] + pTedMatrix[di * treeTo.GetNodeCount() + dj]);

                if (pForestEditScriptMatrix != NULL)
                {
                    pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].Clear();
                    int actionIdx = TripleMinIndex(pFdMatrix[di * nMatrixRowSize + (dj + 1)] + TEO_DELETE_COST,
                        pFdMatrix[(di + 1) * nMatrixRowSize + dj] + TEO_INSERT_COST,
                        pFdMatrix[di * nMatrixRowSize + dj] + pTedMatrix[di * treeTo.GetNodeCount() + dj]);
                    if (actionIdx == 1)
                        // delete
                    {
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddScript(pForestEditScriptMatrix[di * nMatrixRowSize + (dj + 1)]);
                        EditAction deleteAction(di);
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddAction(deleteAction);
                    }
                    else if (actionIdx == 2)
                        // insert
                    {
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddScript(pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + dj]);
                        EditAction insertAction(dj, treeTo.GetNodeAt(dj)->m_idxParent, treeTo.GetLeftMostChildIdx(dj), treeTo.GetRightMostChildIdx(dj));
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddAction(insertAction);
                    }
                    else if (actionIdx == 3)
                        // combine two parts
                    {
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddScript(pForestEditScriptMatrix[di* nMatrixRowSize + dj]);
                        pForestEditScriptMatrix[(di + 1) * nMatrixRowSize + (dj + 1)].AddScript(pTreeEditScriptMatrix[di * treeTo.GetNodeCount() + dj]);
                    }
                    else
                    {
                        // assert(fale)
                    }
                }
            }
        }
    }
}

END_GRAPH_CLUSTERING_NAMESPACE

