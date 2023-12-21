# postfixEvaluator
An extensible postfix notation evaluator.

This project provides a C++ class capable of evaluate a postfix-formated mathematical expression. This class is also capable to include new functions as plugins that can be added at runtime.

## Valid opcodes 
Although you can easiliy add your own opcodes, This postfix evaluator works with these predefined operands:
  * \+ Adds 2 operands in the stack: Ej 2 2 + = 2
  * \- Subs 2 operands in the stack: Ej 4 1 - = 3
  * \* Muiltiplies 2 operands in the stack: Ej 2 3 * = 6
  * / Divides one operand in the stack by other: Ej: 6 2 / = 3
  * print Prints n operands in the stack and pushes the lenght of printed operands: world hello 2 print   prints "helloworld" and return 10
  * read Puts user input into stack
  * dup Repeats stack n times: Ej: 1 4 dup = 1 1 1 1
  * pop Extracts n elements from the stack: Ej 2 1 1 1 3 pop = 2
  * swap Swaps the two last elements in the stack

## Valid operands
You can use these kinds of operands in this postfix Evaluator

### Numbers
Simply write the desired number: Ej. 1 3...

### Strings
You can write strings as is (if only one word) or quoted (If have symbols or spaces)
Ej:
* "Hello world"
* "jaime"

## Examples of postfix expression:

2 2 + = 4

2 2 + 3 * = 12

3 2 2 + * = 12
