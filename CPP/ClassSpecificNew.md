
// https://www.relisoft.com/book/tech/9new.html

```cpp
class FreeList
{
public:
    FreeList () : _p (0) {}
    ~FreeList ();
    void Purge ();
    void * NewLink ();
    void Recycle (void * link);
private:
    Link * _p;
};

class Link
{
    friend class FreeList;
public:
    Link (Link * pNext, int id)
    : _pNext (pNext), _id (id) {}

    Link *  Next () const { return _pNext; }
    int     Id () const { return _id; }
    // allocator
    void * operator new (size_t size)
    {
        assert (size == sizeof (Link));
        return _freeList.NewLink ();
    }
    void operator delete (void * mem)
    {
        if (mem)
            _freeList.Recycle (mem);
    }
    static void Purge () { _freeList.Purge (); }
private:
    static    FreeList _freeList;

    Link *  _pNext;
    int     _id;
};

class List
{
public:
    List ();
    ~List ()
    {
        while (_pHead != 0)
        {
            Link * pLink = _pHead;
            _pHead = _pHead->Next();
            delete pLink;
        }
    }
    void Add (int id)
    {
        Link * pLink = new Link (_pHead, id);
        _pHead = pLink;
    }
    Link const * GetHead () const { return _pHead; }
private:
    Link * _pHead;
};


void * FreeList::NewLink ()
{
    if (_p != 0)
    {
        void * mem = _p;
        _p = _p->_pNext;
        return mem;
    }
    else
    {
        // use global operator new
        return ::new char [sizeof (Link)];
    }
}

void FreeList::Recycle (void * mem)
{
    Link * link = static_cast<Link *> (mem);
    link->_pNext = _p;
    _p = link;
}

FreeList::~FreeList ()
{
    Purge ();
}

void FreeList::Purge ()
{
    while (_p != 0)
    {
        // it was allocated as an array of char
        char * mem = reinterpret_cast<char *> (_p);
        _p = _p->Next();
        ::delete [] mem;
    }
}


```
