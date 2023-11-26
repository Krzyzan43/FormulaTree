# FormulaTree
Program allows entering mathematical formulas with variables in postfix notation, evaluating and joining them. Postfix notation is a notation, where operators follow their operands (i.e. (1+3)*(12-9/2) translates to * + 1 3 - 12 / 9 2). Each character in a formula has to be seperated by a space. Entered formulas are automatically corrected if they have any errors.

# Possible Commands
  * enter <formula> - Creates a tree with a given formula and corrects errors if any. Then prints generated tree. Following operations will work on the generated tree
  * vars - Prints out all variables found in current formula (any symbol with a letter in it is considered a variable, except sin and cos)
  * print - Prints out current tree in postfix notation
  * comp <var0> <var1> ... <varN> - Computes current formula, substituting the variables with given values. Values need to be entered in the same order as 'vars' prints them out
  * join <formula> - Creates formula from the argument and joins it at the end of current tree

# Example
```
enter + - a 10 * sin b 5

print
+ - a 10 * sin b 5

vars
a
b

comp 12 1
6.20735

join * a 2
Current tree: 
+ - a 10 * sin b * a 2

comp 12 1
22.1953
```

# Error correction
  * Operators - If argument for an operator is missing, for example - 2, then program will try to create another neutral argument. I.e. [- Fixed: - 0 0],  [+ 2 sin Fixed: + 2 sin 0] and so on
  * Variables - Anything that has a letter in it will be considered a variable, unless it is a sin or cos. Fixing variable removes all illegal characters that aren't number or letters from it. I.e [var1$%-4 Fixed: var14]
  * Numbers - Anything that isn't either operator or variable will be considered a number. Fixing a number removes all characters that aren't digits. If no characters are left, number is evaluated to be 0. I.e [501(*$3 Fixed: 5013], [$#@%! Fixed: 0]
