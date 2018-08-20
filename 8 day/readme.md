 # 7 segments of hell
I did it probably the wrong way but okay.
<hr>
<h3>Count the unambiguous ones</h3>
(after separator)

`be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb `|` dgacbe cefdb cefbgd gcbe`

`edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec `|` fcgedb cgb dgebacf gc`

eg. there are    
`fdgacbe` only way for 8   
`gcbe`   ____only way for 4   
`cgb `   _____only way for 7   
`gc`   _______only way for 1   

```
  0:      1:      2:      3:      4:
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....

  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg
 ```

<hr>
<h3> Translate from left side left ones</h3>    

based on all 0-9 `be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb` |find for: `fdgacbe cefdb cefbgd gcbe` : 8394

(and sum them up)
 

.... steps:

Filtering with set theory operators `A ∪ B` and  `A ∩ B` 

rules:

`t{Y}` any combinationf of Y lit up segments    
`+ -` are set operations union/intersect

```
0step:
    t{2} => 1
    t{3} => 7
    t{4} => 4
    t{7} => 8
1step:
    t{5} - get(4) => if{7} => 2
    t{5} - get(7) => if{2} => 3
    t{6} - get(4) => if{2} => 9
2step:
    t{6} - get(1) => if{4} - get(4) => if{3} => 0
    t{5} - get(1) => if{4} - get(4) => if{2} => 5
    ```
