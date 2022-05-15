Turing curses!
==============

One night, at a small friendly gathering with, erm, friends, suddenly, 
someone exclaims:

"My friends, there is this wonderfully entertaing thing I know...  It is
called a *turing machine*. We can download a simulator  online, I am
sure. Let me just show you how this works, it will be enlightening, and you
will have yet another story of exotic geeky fun..."

A little browsing later, though:

"What, these interpreters are provided in _binary_ format, and ony under
demand? These others must to be used online, and gosh what creepy design!
I'd rather hack something in text mode..."

At which point the voiceover from the narrator takes over...

Text mode! That's it!

Turing curses is my answer to the sketchy dillema (masterfully portrayed
in the previous paragraphs). It has been hacked one night after frustration 
on internet search.

This software is distributed under the GPLv3 license. See COPYING file.

# Current status and usage

Minimum working simulator of a turing machine which runs in a tape infinite
to the "right". The only way of halting it is trying to advance beyond the
finite end of the tape. Say you compile it as `tc`. Then you run it using
the line below

    tc rules-file.txt 'tape text'
    
where `rules-file.txt` is something like this

    A,0,a,0,R
    +,0,a,0,R
     ,0, ,1,L
    a,1, ,2,L
    a,2,A,2,L

The machine states are always integers, and the initial state is always
`0`.  The line `a,1, ,2,L` describes the transition `(a,1) --> ( ,2,L)`,
which in english means if in state `1` the tape reads `a`, then the machine
writes ` ` in place of `a`, change to state `2` and go to the left.

Yes, `L` stands for "left" and `R` for right.

## 1000 Idiosyncrasies

The input format is *very* rigid. 

- Characters of the tape must be ASCII;
- States can only be integers;
- There may be at most 1000 states, 1000 transitions and 1000 characters on the tape

I know, frustrating!

The good news (for item 3) is that the limits are constants `#defined`
in the first lines of the _unique_ source file `tc.c`. And that has
just about 100 lines!

## Example

Here is a run of the program (`$` is my imaginary prompt).

    $ tc rules-file.txt 'AAA+AA'
    Reading the machine...
     got transition 0:  (A,0) --> (a,0,R)
     got transition 1:  (+,0) --> (a,0,R)
     got transition 2:  ( ,0) --> ( ,1,L)
     got transition 3:  (a,1) --> ( ,2,L)
     got transition 4:  (a,2) --> (A,2,L)
    [ done reading machine ]
    Simulating machine on tape.
    tape: AAA+AA
    s  0  ^
    tape: aAA+AA
    s  0   ^
    tape: aaA+AA
    s  0    ^
    tape: aaa+AA
    s  0     ^
    tape: aaaaAA
    s  0      ^
    tape: aaaaaA
    s  0       ^
    tape: aaaaaa
    s  0        ^
    tape: aaaaaa
    s  1       ^
    tape: aaaaa
    s  2      ^
    tape: aaaaA
    s  2     ^
    tape: aaaAA
    s  2    ^
    tape: aaAAA
    s  2   ^
    tape: aAAAA
    s  2  ^
    tape: AAAAA
    s  2 ^
    [ machine halted ]

## Suggestions of challenges

A couple of warming-up turing-machines you may want to write.
They'll be more fun to code when we have ascii-named states, I know.

- unary adder `11+111` --> `11111`
- erasor `blabla` -->  ` ` (clear tape)
- unary product `111x11` --> `111111`
- complement of DNA sequence `ATGC` --> `TACG`
- reverse binary sequence `1010111` --> `1110101`
- binary to hexadecimal `1010` --> `A`
- add one (binary)  `1111` --> `10000`
- evaluate unary expression (multiplication precedes sum) `11+111*11` --> `11111111`
- evaluate unary expression (with parenthesis!) `(11+111)*11` --> `1111111111`
