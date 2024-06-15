# CFG_Calculator
An implementation of a Context Free Grammar for a command-line-based calculator with variable storage, created in C++. Implementing a Lexer for tokenization, a Parser to construct an Abstract Syntax Tree and finally the calculator/interpreter which parses the tree and outputs the result of the equation.

# Usage
After running the program there should be some output to the terminal matching:
```bash
Welcome to the CFG Calculator!
Enter an expression to calculate
Type 'exit' at any time to quit
>
```

> [!NOTE] 
> ">" Here represents the user input


The user is then able to enter a mathematical expression, the parsed expression and the result will be displayed
```
> 2 + 2 * 2
Parsed expression: (2+(2*2))
Result: 6
```
## Setting Variables
To set a variable the input should start with a string followed by a "=" then the expression to set your variable to
```bash
> myVariable = 3 + 4 + 6 * (7 - 3)
Parsed expression: (myVariable=((3+4)+(6*(7-3))))
result: 31
```
Now if we want to access the value of `myVariable` we can just put it into our expressions, like it's a number.
```bash
> 3 / myVariable
Parsed expression: (3/myVariable)
Result: 0.0967742
```
## Clearing Variables
To clear the variables, and the terminal the user can simply type `clear`
```bash
> 3 / myVariable
Parsed expression: (3/myVariable)
Result: 0.0967742
> clear
```
This will clear the terminal and prompt the user to clear their variables
```bash
Would you like to clear the variables? (y/n)
> 
```

# Keywords
`clear` - Clears the terminal and will prompt user to also clear variables

`exit` - Exits the program

`vars` - Lists all set variables in the calculator

# Grammar

$$
\begin{align*}

\text{Expression <E>}&
\begin{cases}
    <T> <AO> <T>\\
    <I> = <E>\\
    <T>
\end{cases}\\
\\


\text{Term <T>}&
\begin{cases}
    <F> <MO> <F>\\
    <F>
\end{cases}\\
\\


\text{Factor <F>}&
\begin{cases}
    <P> <EO> <F>
    <P>
\end{cases}\\
\\


\text{Primary <P>}&
\begin{cases}
    <L>\\
    (<E>)\\
    <I>\\
    <UO> <P>
\end{cases}\\
\\

\text{Literal <L>}&
\begin{cases}
    \mathbb{R}
\end{cases}\\
\\


\text{Addition Operations <AO>}&
\begin{cases}
    +\\
    -
\end{cases}\\
\\

\text{Multiplication Operations <MO>}&
\begin{cases}
    *\\
    /
\end{cases}\\
\\

\text{Exponential Operations <EO>}&
\begin{cases}
    \char`\^

\end{cases}\\
\\
\text{Unary Operations <UO>}&
\begin{cases}
    sqrt
\end{cases}\\
\\

\text{Indetifier <I>}&
\begin{cases}
    \text{String literal}
\end{cases}

\end{align*}
$$
