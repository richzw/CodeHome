[Source](http://jordanorelli.com/post/32665860244/how-to-use-interfaces-in-go)

Remember the following:

- create abstractions by considering the functionality that is common between datatypes, instead of the fields that are common between datatypes
- an `interface{}` value is not of any type; it is of `interface{}` type
- interfaces are two words wide; schematically they look like `(type, value)`
- it is better to accept an `interface{}` value than it is to return an `interface{}` value
- a pointer type may call the methods of its associated value type, but not vice versa
- everything is pass by value, even the receiver of a method
- an interface value isn’t strictly a pointer or not a pointer, it’s just an interface
- if you need to completely overwrite a value inside of a method, use the `*` operator to manually dereference a pointer

Real-world interfaces: getting an object out of an http request
------

Let’s wrap up by seeing how we might design an interfaces to solve a common web development problem: we wish to parse the body of an HTTP request into some object data. At first, this is not a very obvious interface to define. We might try to say that we’re going to get a resource from an HTTP request like this:

`GetEntity(*http.Request) (interface{}, error)`

because an interface{} can have any underlying type, so we can just parse our request and return whatever we want. This turns out to be a pretty bad strategy, the reason being that we wind up sticking too much logic into the GetEntity function, the GetEntity function now needs to be modified for every new type, and we’ll need to use a type assertion to do anything useful with that returned interface{} value. In practice, functions that return interface{} values tend to be quite annoying, and as a rule of thumb you can just remember that it’s typically better to take in an interface{} value as a parameter than it is to return an interface{} value. (Postel’s Law, applied to interfaces)

We might also be tempted to write some type-specific function like this:

`GetUser(*http.Request) (User, error)`

This also turns out to be pretty inflexible, because now we have different functions for every type, but no sane way to generalize them. Instead, what we really want to do is something more like this:

```go
type Entity interface {
    UnmarshalHTTP(*http.Request) error
}
func GetEntity(r *http.Request, v Entity) error {
    return v.UnmarshalHTTP(r)
}
```

Where the GetEntity function takes an interface value that is guaranteed to have an UnmarshalHTTP method. To make use of this, we would define on our User object some method that allows the User to describe how it would get itself out of an HTTP request:

```go
func (u *User) UnmarshalHTTP(r *http.Request) error {
   // ...
}
```

in your application code, you would declare a var of User type, and then pass a pointer to this function into GetEntity:

```go
var u User
if err := GetEntity(req, &u); err != nil {
    // ...
}
```

That’s very similar to how you would unpack JSON data.  This type of thing works consistently and safely because the statement var u User will automatically zero the User struct.  Go is not like some other languages in that declaration and initialization occur separately, and that by declaring a value without initializing it you can create a subtle pitfall wherein you might access a section of junk data; when declaring the value, the runtime will zero the appropriate memory space to hold that value.  Even if our UnmarshalHTTP method fails to utilize some fields, those fields will contain valid zero data instead of junk.


