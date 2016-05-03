### Source

[gcc optimizer](http://stackoverflow.com/questions/36893251/why-does-the-enhanced-gcc-6-optimizer-break-practical-c-code)
[compare this to null](http://www.viva64.com/en/b/0226/)

### In summary

It's a bad idea to rely on calling a nonstatic method through a null-pointer. If you want to enable a method to be executed for
a null pointer, you should make the method static and explicitly pass the pointer to the object as a parameter.

### samples

```c++
class Class {
public:
    void DontAccessMembers()
    {
        ::Sleep(0);
    }
};

int main()
{
    Class* object = 0;
    object->DontAccessMembers();
}

class Class {
public:
    static void DontAccessMembers(Class* currentObject)
    {
        ::Sleep(0);
    }
};

int main()
{
    Class* object = 0;
    Class::DontAccessMembers(object);
}
```

One more sample

```cpp
class FirstBase {
    int firstBaseData;
};

class SecondBase {
public:
    void Method()
    {
        if( this == 0 ) {
            printf( "this == 0");
        } else {
            printf( "this != 0 (value: %p)", this );
        }
    }
};

class Composed1 : public FirstBase, public SecondBase {
};

int main()
{
    Composed1* object = 0;
    object->Method();
}
```

```cpp
struct Node
{
  Node* left;
  Node* right;
  void process();
  void traverse_in_order() {
    traverse_in_order_impl(this);
  }
private:
  static void traverse_in_order_impl(Node * n)
    if (!n) return;
    traverse_in_order_impl(n->left);
    n->process();
    traverse_in_order_impl(n->right);
  }
};
```
