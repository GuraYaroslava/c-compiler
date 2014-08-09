# Grammar

# Notation

To describe the grammar are used
the [Backus-Naur Form](http://en.wikipedia.org/wiki/Backus–Naur_Form).
The meta-symbols of BNF are:

- `< >` angle brackets used to surround category names
- `::=` meaning "is defined as"
- `|`   meaning "or"

Optional items enclosed in square brackets: `[` and `]`. That is, everything
that is set within the square brackets may be present just once, or not at all.
Literal words and character set members (terminals) are indicated by enclosing
in grave accent `` ` `` to distinguish them from meta-symbols.

# Table of Contents

- [Grammar](#grammar)
- [Notation](#notation)
- [Lexical Conventions](#lexical-conventions)
    - [Tokens](#tokens)
    - [Comments](#comments)
    - [Identifiers](#identifiers)
    - [Constants](#constants)
        - [Integer Constants](#integer-constants)
        - [Floating Constants](#floating-constants)
        - [Character Constants](#character-constants)
    - [String Literals](#string-literals)
- [Expressions](#expressions)
    - [Primary Expressions](#primary-expressions)
    - [Postfix Expressions](#postfix-expressions)
    - [Unary Operators](#unary-operators)
    - [Multiplicative Operators](#multiplicative-operators)
    - [Additive Operators](#additive-operators)
    - [Shift Operators](#shift-operators)
    - [Relational Operators](#relational-operators)
    - [Equality Operators](#equality-operators)
    - [Bitwise AND Operator](#bitwise-and-operator)
    - [Bitwise Exclusive OR Operator](#bitwise-exclusive-or-operator)
    - [Bitwise Inclusive OR Operator](#bitwise-inclusive-or-operator)
    - [Logical AND Operator](#logical-and-operator)
    - [Logical OR Operator](#logical-or-operator)
    - [Conditional Operator](#conditional-operator)
    - [Assignment Expressions](#assignment-expressions)
    - [Comma Operator](#comma-operator)
- [Declarations](#declarations)
    - [Type Specifiers](#type-specifiers)
    - [Structure Declarations](#structure-declarations)
    - [Declarators](#declarators)
        - [Function Declarators](#function-declarators)
    - [Initialization](#initialization)
    - [Type names](#type-names)
- [Statements](#statements)
    - [Expression Statement](#expression-statement)
    - [Compound Statement](#compound-statement)
    - [Selection Statements](#selection-statements)
    - [Iteration Statements](#iteration-statements)
    - [Jump Statements](#jump-statements)

# Lexical Conventions

## Tokens

```
<token> ::= <identifier>
          | <constant>
          | <keyword>
          | <string-literal>
          | <operator>
          | <separators>
```

Blanks, horizontal and vertical tabs, newlines, formfeeds and comments as
described below (collectively, "white space") are ignored except as they
separate tokens.

## Comments

Comments are treated as whitespace. The characters `/*` start a comment, which
terminates with the characters `*/`. These comments do not nest.
The characters `//` start a comment, which terminates with the next new-line character.

## Identifiers

```
<identifier> ::= <nondigit>
               | <identifier> <digit>
               | <identifier> <nondigit>
```

```
<digit> ::= `0` | `1` | `2` | `3` | `4` | `5` | `6` | `7` | `8` | `9`
```

```
<nondigit> ::= `a` | `b` | `c` | `d` | `e` | `f` | `g` | `h` | `i` | `j` | `k` | `l` | `m`
             | `n` | `o` | `p` | `q` | `r` | `s` | `t` | `u` | `v` | `w` | `x` | `y` | `z`
             | `A` | `B` | `C` | `D` | `E` | `F` | `G` | `H` | `I` | `J` | `K` | `L` | `M`
             | `N` | `O` | `P` | `Q` | `R` | `S` | `T` | `U` | `V` | `W` | `X` | `Y` | `Z` | `_`
```

## Keywords

```
<keyword> ::= `break`    | `char`   | `const`
            | `continue` | `do`     | `else`
            | `float`    | `for`    | `if`
            | `int`      | `return` | `struct`
            | `void`     | `while`
```

## Constants

```
<constant> ::= <integer-constant>
             | <floating-constant>
             | <character-constant>
``` 

### Integer Constants

```
<integer-constant> ::= <decimal-constant>
                     | <octal-constant>
                     | <hexadecimal-constant>
```

```
<decimal-constant> ::= <nonzero-digit>
                     | <decimal-constant> <digit>
```

```
<octal-constant> ::= `0`
                   | <octal-constant> <octal-digit>
```

```
<hexadecimal-constant> ::= <hexadecimal-prefix> <hexadecimal-digit>
                         | <hexadecimal-constant> <hexadecimal-digit>
```

```
<nonzero-digit> ::= `1` | `2` | `3` | `4` | `5` | `6` | `7` | `8` | `9`
```

```
<octal-digit> ::= `0` | `1` | `2` | `3` | `4` | `5` | `6` | `7`
```

```
<hexadecimal-prefix> ::= `0x` | `0X`
```

```
<hexadecimal-digit> ::= `0` | `1` | `2` | `3` | `4` | `5` | `6` | `7` | `8` | `9`
                      | `a` | `b` | `c` | `d` | `e` | `f`
                      | `A` | `B` | `C` | `D` | `E` | `F`
``` 

### Floating Constants

```
<floating-constant> ::= <fractional-constant> [<exponent-part>]
                      | <degit-sequence> <exponent-part>
```

```
<fractional-constant> ::= [<degit-sequence>] `.` <degit-sequence>
                        | <degit-sequence> `.`
```

```
<exponent-part> ::= `e` [<sign>] <degit-sequence>
                  | `E` [<sign>] <degit-sequence>
```

```
<degit-sequence> ::= <digit>
                   | <degit-sequence> <digit>
```

```
<sign> := `-` | `+`
```

### Character Constants

```
<character-constant> ::= `'` <c-char-sequence> `'`
```

```
<c-char-sequence> ::= <c-char>
                    | <c-char-sequence> <c-char>
```                    

```
<c-char> ::= <escape-sequence>
            | `any member of the source character set except
              the single-quote ', backslash \, or new line character`
```

```
<escape-sequence> ::= <simple-escape-sequence>
```

```
<simple-escape-sequence> ::= `\'` | `\"`| `\?` | `\\` | `\a` | `\b` | `\f` | `\n` | `\r` | `\t` | `\v`
```

## String Literals

```
<sring-literal> ::= `"` <s-char-sequence> `"`
```

```
<s-char-sequence> ::= <s-char>
                    | <s-char-sequence> <s-char>
```

```
<s-char> ::= <escape-sequence>
            | `any member of the source character set except
              the single-quote ", backslash \, or new line character`
```

# Expressions

## Primary Expressions

```
<primary-expression> ::= <identifier>
                       | <constant>
                       | <sring-literal>
                       | `(` <expression> `)`
```

## Postfix Expressions

```
<postfix-expression> ::= <primary-expression>
                       | <postfix-expression> `[` <expression> `]`
                       | <postfix-expression> `(` [<argument-expression-list>] `)`
                       | <postfix-expression> `.` <identifier>
                       | <postfix-expression> `->` <identifier>
                       | <postfix-expression> `++`
                       | <postfix-expression> `--`
```

```
<argument-expression-list> ::= <assignment-expression>
                             | <argument-expression-list> `,` <assignment-expression>
```

## Unary Operators

```
<unary-expression> ::= <postfix-expression>
                    | `++` <unary-expression>
                    | `--` <unary-expression>
                    | <unary-operator> <unary-expression>
```

```
<unary-operator> ::= `&` | `*` | `+` | `-` | `~` | `!`
```

## Multiplicative Operators

```
<multiplicative-expression> ::= <multiplicative-expression> `*` <unary-expression>
                              | <multiplicative-expression> `/` <unary-expression>
                              | <multiplicative-expression> `%` <unary-expression>
```

## Additive Operators

```
<additive-expression> ::= <multiplicative-expression>
                        | <additive-expression> `+` <multiplicative-expression>
                        | <additive-expression> `-` <multiplicative-expression>
```

## Shift Operators

```
<shift-expression> ::= <additive-expression>
                     | <shift-expression> `<<` <additive-expression>
                     | <shift-expression> `>>` <additive-expression>
```

## Relational Operators

```
<relational-expression> ::= <shift-expression>
                          | <relational-expression> `<` <shift-expression>
                          | <relational-expression> `>` <shift-expression>
                          | <relational-expression> `<=` <shift-expression>
                          | <relational-expression> `>=` <shift-expression>
```

## Equality Operators

```
<equality-expression> ::= <relational-expression>
                        | <equality-expression> `==` <relational-expression>
                        | <equality-expression> `!=` <relational-expression>
```

## Bitwise AND Operator

```
<and-expression> ::= <equality-expression>
                   | <and-expression> `&` <equality-expression>
```

## Bitwise Exclusive OR Operator

```
<exclusive-or-expression> ::= <and-expression>
                            | <exclusive-or-expression> `^` <and-expression>
```

## Bitwise Inclusive OR Operator

```
<inclusive-or-expression> ::= <exclusive-or-expression>
                            | <inclusive-or-expression> `|` <exclusive-or-expression>
```

## Logical AND Operator

```
<logical-and-expression> ::= <inclusive-or-expression>
                           | <logical-and-expression `&&` <inclusive-or-expression>
```

## Logical OR Operator

```
<logical-or-expression> ::= <logical-and-expression>
                          | <logical-or-expression `||` <logical-and-expression>
```

## Conditional Operator

```
<conditional-expression> ::= <logical-or-expression>
```

## Assignment Expressions

```
<assignment-expression> ::= <conditional-expression>
                          | <unary-expression> <assigment-operator> <assignment-expression>
```

```
<assignment-operator> ::= `=` | `*=` | `/=` | `%=` | `+=` | `-=` | `<<=` | `=>>` | `&=` | `^=` | `|=`
```

## Comma Operator

```
<expression> ::= <assignment-expression>
               | <expression> `,` <assignment-expression>
```

# Declarations

```
<declaration> ::= <declaration-specifiers> [<init-declarator-list>] `;`
```

```
<declaration-specifiers> ::= <type-specifier> [<declaration-specifiers>] `;`
```

```
<init-declarator-list> ::= <init-declarator>
                         | <init-declarator-list> `,` <init-declarator>
```

```
<init-declarator> ::= <declarator>
                    | <declarator> `=` initializer
```

## Type Specifiers

```
<type-specifier> ::= `void`
                   | `char`
                   | `int`
                   | `float`
                   | <struct-specifier>
```

## Structure Declarations

```
<struct-specifier> ::= `struct` [<identifier>] `{` <struct-declaration-list> `}`
                     | `struct` <identifier>
```

```
<struct-declaration-list> ::= <struct-declaration>
                            | <struct-declaration-list> <struct-declaration>
```

```
<struct-declaration> ::= <specifier-qualifier-list> [<struct-declarator-list>] `;`
```

```
<specifier-qualifier-list> ::= <type-specifier> [<specfier-qualifier-list>] `;`
```

```
<struct-declarator-list> ::= <declarator>
                           | <struct-declarator-list> `,` <declarator>
```

## Declarators

```
<declarator> ::= [<pointer>] <direct-declarator>
```

```
<direct-declarator> ::= <identifier>
                      | `(` <declarator> `)`
                      | <direct-declarator> `[` [<conditional-expression>] `]`
                      | <direct-declarator> `(` <parameter-list> `)`
                      | <direct-declarator> `(` [<identifier-list>] `)`
```

```
<pointer> ::= `*`
            | `*` <pointer>
```

### Function Declarators

```
<parameter-list> ::= <parameter-declaration>
                   | <parameter-list> `,` <parameter-declaration>
```

```
<parameter-declaration> ::= <declaration-specifiers> <declarator>
                          | <declaration-specifiers> [<abstract-declarator>]
```

```
<identifier-list> ::= <identifier>
                    | <identifier-list> `,` <identifier>
```

## Type names

```
<abstract-declarator> ::= <pointer>
                        | [<pointer>] <direct-abstract-declarator>
```

```
<direct-abstract-declarator> ::= `(` <abstract-declarator> `)`
                               | [<direct-abstract-declarator>] `[` [<conditional-expression>] `]`
                               | [<direct-abstract-declarator>] `(` [<parameter-list>] `)`
```

## Initialization

```
<initializer> ::= <assignment-expression>
                | `{` <initializer-list> `}`
                | `{` <initializer-list> `,` `}`
```

```
<initializer-list> ::= <initializer>
                     | <initializer-list> `,` <initializer>
```

# Statements

```
<statment> ::= <expression-statment>
             | <compound-statment>
             | <selection-statment>
             | <iteration-statment>
             | <jump-statment>
```

## Expression Statement

```
<expression-statment> ::= [<expression>] `;`
```

## Compound Statement

```
<compound-statement> ::= `{` [<declaration-list>] [<statement-list>] `}`
```

```
<declaration-list> ::= <declaration>
                     | <declaration-list> <declaration>
```

```
<statement-list> ::= <statement>
                   | <statment-list> <statement>
```

## Selection Statements

```
<selection-statment> ::= `if` `(` <expression> `)` <statement>
                       | `if` `(` <expression> `)` <statement> else <statment>
```

## Iteration Statements

```
<iteration-statment> ::= `while` `(` <expression> `)` <statement>
                       | `do` <statment> `while` `(` <expression> `)`
                       | `for` `(` [<expression>] `;` [<expression>] `;` [<expression>] `)` <statment>
```

## Jump statements

```
<jump-statment> ::= `continue` `;`
                  | `breake` `;`
                  | `return` [<expression>] `;`
```