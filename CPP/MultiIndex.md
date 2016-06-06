
// http://www.codesynthesis.com/~boris/blog/2012/09/11/emulating-boost-multi-index-with-std-containers/

```cpp
struct person_set
{
  typedef std::map<key<std::string>, person> email_map;
  typedef map_iterator_adapter<email_map::const_iterator> iterator;
 
  typedef std::map<key<std::string>, iterator> name_map;           // <--
 
  std::pair<iterator, bool>
  insert (const person& v)
  {
    // First check that we don't have any collisions in
    // the secondary indexes.
    //
    {
      auto i (name_map_.find (&v.name));                           // <--
      if (i != name_map_.end ())                                   // <--
        return std::make_pair (i->second, false);                  // <--
    }
 
    auto r (email_map_.insert (email_map::value_type (&v.email, v)));
    iterator i (r.first);
 
    if (r.second)
    {
      r.first->first.p = &i->email;
      name_map_.insert (name_map::value_type (&i->name, i));       // <--
    }
 
    return std::make_pair (i, r.second);
  }
 
  iterator                                                         // <--
  find_email (const std::string& email) const                      // <--
  {                                                                // <--
    return email_map_.find (&email);                               // <--
  }                                                                // <--
 
  iterator
  find_name (const std::string& name) const
  {
    auto i (name_map_.find (&name));
    return i != name_map_.end () ? i->second : end ();
  }
 
  iterator begin () const {return email_map_.begin ();}
  iterator end () const {return email_map_.end ();}
 
private:
  email_map email_map_;
  name_map name_map_;                                              // <--
};
```
