**C++98 and C++03**

This answer is for the older versions of the C++ standard. The C++11 and C++14 versions of the standard do not formally 
contain 'sequence points'; operations are 'sequenced before' or 'unsequenced' or 'indeterminately sequenced' instead. 
The net effect is essentially the same, but the terminology is different.

-------------------------------------------------------

**What are Sequence Points?**

The Standard says

> At certain specified points in the execution sequence called sequence points, all side effects of previous evaluations
> shall be complete and no side effects of subsequent evaluations shall have taken place. (§1.9/7)

**Side effects? What are side effects?**

Evaluation of an expression produces something and if in addition there is a change in the state of
the execution environment it is said that the expression (its evaluation) has some side effect(s).

For example:

    int x = y++; //where y is also an int
    
In addition to the initialization operation the value of `y` gets changed due to the side effect of `++` operator.

So far so good. Moving on to sequence points. An alternation definition of seq-points given by 
the comp.lang.c author `Steve Summit`:

> Sequence point is a point in time at which the dust has settled and all side effects which have been seen so far
> are guaranteed to be complete.

----------------------------------

**What are the common sequence points listed in the C++ Standard ?**

Those are:

- at the end of the evaluation of full expression (§1.9/16) (A full-expression is an expression that is not a subexpression of another expression.)1

Example :

    int a = 5; // ; is a sequence point here
    
- in the evaluation of each of the following expressions after the evaluation of the first expression(§1.9/18) 2

  - `a && b` (§5.14)
  - `a || b` (§5.15)
  - `a ? b : c` (§5.16)
  - `a , b` (§5.18) (in func(a,a++) , is not a comma operator, it's merely a separator between the arguments a and a++. The behaviour is undefined in that case if a is considered to be a primitive type) 

- at a function call (whether or not the function is inline), after the evaluation of all function arguments (if any) which takes place before execution of any expressions or statements in the function body (§1.9/17).

> 1 : Note : the evaluation of a full-expression can include the evaluation of subexpressions that are not lexically part of the full-expression. For example, subexpressions involved in evaluating default argument expressions (8.3.6) are considered to be created in the expression that calls the function, not the expression that defines the default argument

> 2 : The operators indicated are the built-in operators, as described in clause 5. When one of these operators is overloaded (clause 13) in a valid context, thus designating a user-defined operator function, the expression designates a function invocation and the operands form an argument list, without an implied sequence point between them.

--------------

**What is Undefined Behaviour?**

The Standard defines Undefined Behaviour in Section §1.3.12 as

- behaviour, such as might arise upon use of an erroneous program construct or erroneous data, for which this International Standard imposes no requirements 3.

- Undefined behaviour may also be expected when this International Standard omits the description of any explicit definition of behavior.

> 3 : permissible undefined behavior ranges from ignoring the situation completely with unpredictable results, to behaving during translation or program execution in a documented manner characteristic of the environment (with or with- out the issuance of a diagnostic message), to terminating a translation or execution (with the issuance of a diagnostic message).

In short, undefined behaviour means anything can happen from daemons flying out of your nose to your girlfriend getting pregnant.

-----------

**What is the relation between Undefined Behaviour and Sequence Points?**

Before I get into that you must know the difference(s) between `Undefined Behaviour`, `Unspecified Behaviour` and `Implementation Defined Behaviour`.

You must also know that `the order of evaluation of operands of individual operators and subexpressions of individual expressions, and the order in which side effects take place, is unspecified.`

For example:

```c
int x = 5, y = 6;
int z = x++ + y++; //it is unspecified whether x++ or y++ will be evaluated first.
```

------------

Now the Standard in §5/4 says

- 1) **Between the previous and next sequence point a scalar object shall have its stored value modified at most once by the evaluation of an expression.**

What does it mean?

Informally it means that between two sequence points a variable must not be modified more than once. In an expression statement, the next sequence point is usually at the terminating semicolon, and the previous sequence point is at the end of the previous statement. An expression may also contain intermediate sequence points.

From the above sentence the following expressions invoke Undefined Behaviour.

```c
i++ * ++i; // i is modified more than once
i = ++i    // same as above
++i = 2;   // same as above
i = ++i +1 // same as above
++++++i;   //parsed as (++(++(++i)))

i = (i,++i,++i); // Undefined Behaviour because there's no sequence point between `++i`(right most) and assignment to `i` (`i` gets modified more than once b/w two SP)
```

But the following expressions are fine

```c
i = (i, ++i, 1) + 1; //well defined (AFAIK)
i = (++i,i++,i) // well defined 
int j = i;
j = (++i, i++, j*i); // well defined
```

---------------------

- 2) **Furthermore, the prior value shall be accessed only to determine the value to be stored.**

What does it mean?

It means if an object is written to within a full expression, any and all accesses to it within the same expression **must be directly involved in the computation of the value to be written.**

For example in `i = i + `1 all the access of `i` (in L.H.S and in R.H.S) are directly involved in computation of the value to be written. So it is fine.

This rule effectively constrains legal expressions to those in which the accesses demonstrably precede the modification.

Example 1:

     std::printf("%d %d", i,++i); // invokes Undefined Behaviour because of Rule no 2

Example 2:

     a[i] = i++ // or a[++i] = i or a[i++] = ++i etc

is disallowed because one of the accesses of i (the one in a[i]) has nothing to do with the value which ends up being stored in i (which happens over in i++), and so there's no good way to define--either for our understanding or the compiler's--whether the access should take place before or after the incremented value is stored. So the behaviour is undefined.

Example 3 :

     int x = i + i++ ;// Similar to above

-------------

**Is it true that there are no Sequence Points in C++11**

**Yes!** This is very true.

Sequence Points have been replaced by the more clear Sequenced Before and Sequenced After (and Unsequenced and Indeterminately Sequenced) relations in C++11.

-------------

**What exactly is this 'Sequenced before' thing?**

Sequenced Before(§1.9/13) is a relation which is:

- **Asymmetric**
- **Transitive**

between evaluations executed by a single thread and induces a **strict partial order1**

Formally it means given any two evaluations(See below) A and B, if A is sequenced before B, then the execution of A shall precede the execution of B. If A is not sequenced before B and B is not sequenced before A, then A and B are **unsequenced 2.**

Evaluations A and B are indeterminately sequenced when either A is sequenced before B or B is sequenced before A, but it is **unspecified** which3.

> [NOTES] 
> 1 : A strict partial order is a binary relation "<" over a set P which is asymmetric, and transitive, i.e., for all a, b, and c in P, we have that:

> ........(i). if a < b then ¬ (b < a) (asymmetry);

> ........(ii). if a < b and b < c then a < c (transitivity).

> 2 : The execution of unsequenced evaluations can overlap.

> 3 : Indeterminately sequenced evaluations cannot overlap, but either could be executed first.

------------



