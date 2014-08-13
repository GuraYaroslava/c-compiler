### Simple Expression Grammar

```
<expression> ::= <term>
             | <expression> `+` <term>
             | <expression> `-` <term>
```

```
<term> ::= <factor>
         | <term> * <factor>
         | <term> / <factor>
```

```
<factor> ::= <constant>
           | <identifier>
           | `(` <expression> `)`
```