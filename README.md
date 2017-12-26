# C++11 - Rvalue Reference & Move Constructor

## 0: References in C++

In C++, references were created to represent an alias of existing memory location referred by a name.
for example, we can create the reference of a variable as 

```
int first = 100;

int & refFirst = first;

```

Here `first` and `refFirst` refers to the same memory location and `refFirst` is stored as an alias without having its own memory. 

Since references were used to refer something which already exists, it wasn't allowed to refer `Temporaries` as a reference. For example the code

```
int & refTemp = 10;
```
will not compile, because `10` is a `Temporary` variable and will go off memory after the execution of this line, hence referring it after the line is not allowed. However, there was one exception to this rule is that we can refer temporaries using the const reference.

```
const int &refTemp = 10;
```

## 1: RValue reference in C++11 onwards

C++11 added rvalue reference to handle exactly the same scenario with temporaries. With `rvalue` reference it's possible not only to provide temporaries a name but also to act on it. For example, the code below is a valid code in C++11 onwards

```
int && rvalFirst = 100;

rvalFirst++;

```

With `rvalue` its possible to overload functions with two types of signatures, one with reference and another with `rvalue` reference. The `rvalue` reference function signature shall be automatically called by compiler for 'Temporaries'  For example

```
void fn(int & refVal); 

void fn(int && rvalueVal);

int val = 100;
fn(val);  // Will call void fn(int & refVal); 

fn(200); // Will call void fn(int && rvalueVal);

```

## 2: What's the use of rvalue reference ?

With `rvalue` reference we can transfer the ownership without copying. To properly understand it let's visit the old C++ `Copy Constructor` mechanism. For example, let's write a class with a copy constructor and the main function which uses this class as a vector

```
class A {
public:
    int * ptr;
    A(int val) {
           ptr = new int; *ptr = val;
    }
    // Copy Constructor
    A(const A & a1) {
        this->ptr = new int;
        *this->ptr = (*a1.ptr);
    }
int main(){
    vector<A> v1;
    v1.push_back(A(100));
  
    return 0;
}
```

In the code above, the line ` v1.push_back(A(100));` will create a temporary and invokes the copy constructor. As part of the copy construction, we allocate a new memory and let the temporary die after the execution of this line.

`RValue` reference allows us to reuse the memory allocated by the temporary and avoid reallocation of memory. This is done by declaring something called `move constructor`. 

The move constructor is defined as 

```
 A( A && a1) {
        this->ptr = a1.ptr;
        a1.ptr = nullptr;
    }

```

Instead of allocating new pointer, we reassign the existing pointer and change the original pointer to `nullptr` so that it's not deallocated by the destructor of the class.  

That's the reason we don't declare A as `const` in `move constructor` as oppose to doing the same in `copy constructor`. That's why we need a new one

## NOTE:

It's a good practice to declare `move constructor` as `noexpecpt`

