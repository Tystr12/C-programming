#include <stdio.h>

int main(void) // no parameters
{
    printf("hello, world\n");
}
// This function is completely fine in C99 standard and later versions, including C17.
// If this was compiled with an earlier standard like C89, the lack of a return type for main would cause a warning or error.
// The message would say something like this: 'warning: control reaches end of non-void function [-Wreturn-type]'

// int main (void) is the correct way to define the main function
// leaving it as int main() is also acceptable in C99 and later but this means 
// that the function can take any number of arguments, which is not the intended use for main in this context.
// This is NOT like Java where () means no arguments. In C, it is better to use (void) to explicitly indicate no parameters.

// In modern C, 'int main(void)' is the preferred declaration because it explicitly
// states that the function takes no parameters. 'int main()' is allowed but means
// an unspecified number of parameters (old-style declaration).
