//For sparse matrix
 
typedef struct QLNode 
{
    int iPos, jPos;        //非零元素的行列下标；
    int iElem;             //元素；
    struct QLNode *right, *down;    
}QLNode;
 
typedef struct QLNode* QLink;
typedef struct  
{
    QLink *rHead, *cHead;        //行列的头指针；
    int RowNum, ColNum, TotalNum;
}CrossList;
 
bool CreatCrossList(CrossList& CroLit)
{
    int row, coll, total;
    cin>>row>>coll>>total;
    CroLit.RowNum=row; CroLit.ColNum=coll; CroLit.TotalNum=total;
 
    CroLit.rHead= new QLink[row];        //创建行头指针表；
    CroLit.cHead= new QLink[coll];        //创建列头指针表；
 
    //初始化头指针表；
    for (int i=0; i<row; i++)
        CroLit.rHead[i]=NULL;
    for (int i=0; i<coll; i++)
        CroLit.cHead[i]=NULL;
    
    int i, j, elem;            //以三元组的形式输入
    for(cin>>i>>j>>elem; elem!=0; cin>>i>>j>>elem)
    {
        QLink pTem= new QLNode;
        pTem->right=pTem->down=NULL;
        pTem->iPos=i; pTem->jPos=j; pTem->iElem=elem;
 
        //直接插入：空，或者列坐标大于此行链表中的最大列坐标
        //    同一行里面，链表按照列的坐标排序，
        if( CroLit.rHead[i]==NULL || CroLit.rHead[i]->jPos>j )
        {
            pTem->right= CroLit.rHead[i];
            CroLit.rHead[i]=pTem;
        }
        else    //查寻在行表中的插入位置：
        {
            QLink  bg;
            for(bg=CroLit.rHead[i]; bg->right && bg->right->jPos<j; bg=bg->right);
            pTem->right=bg->right;    bg->right=pTem;
        }        //完成行插入。
        
        //直接插入：空，或者行坐标大于此列链表中的最大行坐标
        //    同一列里面，链表按照行的坐标排序，
        if( CroLit.cHead[j]==NULL || CroLit.cHead[j]->iPos>i )
        {
            pTem->down= CroLit.cHead[j];
            CroLit.cHead[j]=pTem;
        }
        else    //查寻在列表中的插入位置：
        {
            QLink  bg;
            for(bg=CroLit.cHead[j]; bg->down && bg->down->iPos<i; bg=bg->down);
            pTem->down=bg->down;    bg->down=pTem;
        }        //完成列插入。
    }
    return true;
}
//输出各行元素
void DisplayRow(CrossList dest)
{
    for (int i=0; i<dest.RowNum; i++)
    {
        QLink tem=dest.rHead[i];
        while (tem)
        {
            cout<<"( "<<tem->iPos<<", ";
            cout<<tem->jPos<<", ";
            cout<<tem->iElem<<" )";
            tem=tem->right;
        }
        cout<<endl;
    }
}
 
//对于有向图
const int MAX_VERTEX_NUM=20;
typedef struct ArcBox 
{
    int tailvex, headvex;
    ArcBox    *hlink, *tlink;
    int info;            //弧的相关信息，权值.
}ArcBox;
 
typedef struct VexNode 
{
    int data;
    ArcBox *firstIn, *firstOut;    //指向该顶点的第一个入弧，出弧
}VexNode;
 
typedef struct  
{
    VexNode xList[MAX_VERTEX_NUM];
    int vexNum, arcNum;
}OLGraph;        //十字链表:Orthogonal List;
 
int LocateVex(OLGraph& G, int& e) 
{
    for (int i=0; i<G.vexNum; i++)
        if(G.xList[i].data==e)
            return i;
}
bool CreatDG(OLGraph& G)
{
    //采用十字链表存储表示，构造有向图.
    cin>>G.vexNum>>G.arcNum;    //顶点数，弧数；
    for(int i=0; i<G.vexNum; i++)
    {
        cin>>G.xList[i].data;
        G.xList[i].firstIn=G.xList[i].firstOut=NULL;
    }
    for (int k=0; k<G.arcNum; k++)
    {
        int v1, v2, value;    //弧的起点，终点, 权值
        cin>>v1>>v2>>value;
        int i=LocateVex(G, v1);    int j=LocateVex(G, v2);
        ArcBox* ptem=new ArcBox;
        ptem->tailvex=i;    ptem->headvex=j; ptem->info=value;
        ptem->hlink=G.xList[j].firstIn;    ptem->tlink=G.xList[i].firstOut;    
        G.xList[j].firstIn=G.xList[i].firstOut=ptem;
    }
    return true;
}
//输出各行元素
void DisplayRow(OLGraph& dest)
{
    for (int i=0; i<dest.vexNum; i++)
    {
        ArcBox *tem;
        tem=dest.xList[i].firstIn;
        while (tem)
        {
            cout<<"( "<<tem->tailvex<<", ";
            cout<<tem->headvex<<", ";
            cout<<tem->info<<" )";
            tem=tem->hlink;
        }
        cout<<endl;
    }
}
