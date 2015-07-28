Asynchronous in JavaScript
============

- 1**CallBack**

  - **Pros**:
    - They are a very well know pattern, so they are familiar thus easy to understand.
    - Very easy to implement in your own libraries / functions
  - **Cons**:
    - Nested callbacks will form the infamous pyramid of doom as shown above, which can get hard to read when you have multiple nested levels. But this is quite easy to fix by splitting the functions also as shown above.
    - You can only pass one callback for a given event, this can be a big limitation in many cases.

- 2**Event (Pub/Sub)**

  - **Pros**:
    - This is another well understood pattern.
    - The big advantage is that you are not limited to one listener per object, you can add as many listeners as you want.
  - **Cons**:
    - A bit more difficult to setup than callbacks in your own code, you will probably want to use a library
    
- 3**Flow Control Library**

  - **Pros**:
    - Usually code using a control flow library is easier to understand because it follows a natural order (from top to bottom). This is not true with callbacks and listeners.
  - **Cons**:
    - If the signatures of the functions don’t match as in the second example then you can argue that the flow control library offers little in terms of readability.

- 4**Promise**

  - **Pros**
    - Really powerful, you can aggregate promises, pass them around, or add listeners when already resolved.
  - **Cons**
    - The least understood of all these tools.
    - They can get difficult to track when you have lots of aggregated promises with added listeners along the way.

