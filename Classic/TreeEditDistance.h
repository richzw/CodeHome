#include <string>
#include <vector>
#include <map>

#pragma once

#define BEGIN_GRAPH_CLUSTERING_NAMESPACE namespace GraphClustering {
#define END_GRAPH_CLUSTERING_NAMESPACE }

#define TEO_DELETE_COST 1
#define TEO_INSERT_COST 1
#define TEO_RENAME_COST 1

#define INVALID_NODE_INDEX    (-1)

//
//  return the max/min one from three values
//

#define TripleMin(v1, v2, v3) ( (v1) <= (v2) ) \
                                      ? ( ((v1) <= (v3)) ? (v1) : (v3) ) \
                                          : ( ((v2) <= (v3)) ? (v2) : (v3) )
#define TripleMax(v1, v2, v3) ( (v1) >= (v2) )  \
                                      ? ( ((v1) >= (v3)) ? (v1) : (v3) ) \
                                          : ( ((v2) >= (v3)) ? (v2) : (v3) )

//
//  return the index of max/min one of three values
//

#define TripleMinIndex(v1, v2, v3) ( (v1) <= (v2) ) \
                                      ? ( ((v1) <= (v3)) ? (1) : (3) ) \
                                          : ( ((v2) <= (v3)) ? (2) : (3) )
#define TripleMaxIndex(v1, v2, v3) ( (v1) >= (v2) )  \
                                      ? ( ((v1) >= (v3)) ? (1) : (3) ) \
                                          : ( ((v2) >= (v3)) ? (2) : (3) )

BEGIN_GRAPH_CLUSTERING_NAMESPACE

class PostOrderedTree;

class EditAction
{
public:
    enum ActionType
    {
        INSERT = 1,
        DELETE_T = 2,
        RELABLE = 3
    };

    //
    //  Delete source[idxDel]
    //
    EditAction(unsigned int idxDel)
        :m_edType(DELETE_T),
        m_this(idxDel),
        m_target(INVALID_NODE_INDEX),
        m_firstChild(INVALID_NODE_INDEX),
        m_lastChild(INVALID_NODE_INDEX)
    {};

    //
    //  Relable from source[idxRelFrom] to target[idxRelTo]
    //
    EditAction(unsigned int idxRelFrom, unsigned indxRelTo)
        :m_edType(RELABLE),
        m_this(idxRelFrom),
        m_target(indxRelTo),
        m_firstChild(INVALID_NODE_INDEX),
        m_lastChild(INVALID_NODE_INDEX)
    {};

    //
    //  Insert target[idxIns] in to source tree:
    //      - source[idxParent] is new parent
    //      - the node in source tree that corresponding to target[idxFirstChild] is the new first child
    //      - the node in source tree that corresponding to target[idxLastChild] is the new last child
    //
    EditAction(unsigned int idxIns, unsigned int idxParent, unsigned int idxFirstChild, unsigned int idxLastChild)
        :m_edType(INSERT),
        m_this(idxIns),
        m_target(idxParent),
        m_firstChild(idxFirstChild),
        m_lastChild(idxLastChild)
    {};

private:
    ActionType   m_edType;
    unsigned int m_this;

    /* for insert and relable */
    unsigned int m_target;

    /* only for insert */
    unsigned int m_firstChild;
    unsigned int m_lastChild;

    friend class EditScript;
};

class EditScript
{
public:
    EditScript() {};
    void AddAction(EditAction & action);
    void AddScript(EditScript & script);
    void Clear();
    unsigned int GetActionCount() 
    {   return m_vecAction.size();  };
    void ToString(std::string & outStr, PostOrderedTree & from, PostOrderedTree & to);

private:
    std::vector<EditAction> m_vecAction;
};

//
//  TreeNode of Ordered Tree (arbitary amount of children)
//
class TreeNode
{
public:
    TreeNode(std::string & nodeLable);
    void AddChild(TreeNode * pNode);
    std::string & GetLable() { return m_strLable; }

public:
    /* informational data */
    std::string     m_strLable;

    /* original tree info */
    TreeNode *      m_pParent;
    TreeNode *      m_pLeftMostChild;
    TreeNode *      m_pSibling;
    
    /* post ordered tree info */
    unsigned int    m_idxMe;
    unsigned int    m_idxParent;
    unsigned int    m_idxLeftMostChild;
    unsigned int    m_idxSibling;

    /* friend functions and classes */
    friend void LeftMostLeafDescendants(PostOrderedTree & poTree, unsigned int idxNode, std::map<unsigned int , unsigned int> & map);
    friend void KeyRoots(PostOrderedTree & poTree, unsigned int idxNode, std::vector<unsigned int> & vecKeyRoot);
    friend void BuildPostOrderVector(TreeNode * node, std::vector<TreeNode *> &vec);
    friend class PostOrderedTree;
};

//
//  Post Ordered Tree 
//

class PostOrderedTree
{
public:

    //
    //  Build the post order vector and also update related info in each node
    //

    void Build(TreeNode * root);

    TreeNode * GetNodeAt(unsigned int idx);
    TreeNode * GetRightMostChild(unsigned int idx);
    TreeNode * GetLeftMostChild(unsigned int idx);
    unsigned int GetRightMostChildIdx(unsigned int idx);
    unsigned int GetLeftMostChildIdx(unsigned int idx);
    unsigned int GetNodeCount();

private:
    std::vector<TreeNode *> m_vecPostOrderedNodes;
};

//
//      Find all the "left-most leaf descendant"s of descendants of node represented 
//  by idxNode in poTree.
//  
//      Caller will be the owner of the returned node vector.
//
//  NOTE: 
//      Each descendant of node idxNode only has one "left-most leaf descendant", 
//  so The size of the returned map is the count of descendants of node idxNode.
//
void LeftMostLeafDescendants(PostOrderedTree & poTree, unsigned int idxNode, std::map<unsigned int , unsigned int> & map);

//
//      Find all the "Key Root"s of the subtree rooted at idxNode of poTree.
//
//  NOTE:
//      "Key Root" is a node that either it is the root of the tree or it has
//  a left sibling.
//
void KeyRoots(PostOrderedTree & poTree, unsigned int idxNode, std::vector<unsigned int> & vecKeyRoot);


//
//      Compute Tree Edit Distance
//
//  Parameters:
//      fromTree    -   tree of the convertion source
//      toTree      -   tree of the conversion target
//      pTedMatrix  -   pointer of start element of tree edit distance matrix
//      pScriptMatrix   -   pointer to matrix of edit script: a vector of edit action
//
//  NOTE:
//      The algorithm used here is introduced in [Zhang-Shasha89] paper
//      Detailed description of this algorithm can be found at http://www.inf.unibz.it/dis/teaching/ATA
//
void TreeEditDistance(PostOrderedTree & fromTree, 
                      PostOrderedTree & toTree, 
                      unsigned int * pTedMatrix, 
                      EditScript * pScriptMatrix = NULL);

//
//      Compute Forest Distance
//
//  NOTE:
//      The algorithm used here is introduced in [Zhang-Shasha89] paper
//      Detailed description of this algorithm can be found at http://www.inf.unibz.it/dis/teaching/ATA
//  
void ForestEditDistance(PostOrderedTree & fromTree, 
                        PostOrderedTree & toTree,
                        unsigned int idxRootOfRighMostTreeInFromForest, 
                        unsigned int idxRootOfRightMostTreeInToForest,
                        std::map<unsigned int , unsigned int> & mapLmldOfFromForest,
                        std::map<unsigned int , unsigned int> & mapLmldOfToForest,
                        unsigned int * pTedMatrix,
                        unsigned int * pFedMatrix,
                        EditScript * pTreeEditDistanceMatrix,
                        EditScript * pForestEditDistanceMatrix);

END_GRAPH_CLUSTERING_NAMESPACE
