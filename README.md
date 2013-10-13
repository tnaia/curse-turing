Turing curses!
==============

One night, having a good time with friends, suddenly, I have a bright idea.

"My friends, there is this wonderful thing I had tons of fun with!  It is
called *turing machine*. There are interpreters for it online, I am
sure. Let me just show you how this work, it will be enlightening, and you
will have yet another story of your exotic fun with geeks..."

What, these interpreters are provided in _binary_ format, and ony under 
demand? Thes others have to be used online, and gosh what creepy design!
I'd rather hack something in text mode...

Text mode! That's it!

Turing curses is my answer to precisely that dilemma. It has been hacked
one night after frustration on internet search.

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

The input format is *very* rigid. The characters of the tape are all ascii,
the states can only be integers, there mey not be more than 1000 states,
1000 transitions or 1000 characters. on the tape. I know, soo frustrating!

The good news is that those are constants in `#defined` in the first lines
of the _unique_ source file `tc.c`, which has just about 100 lines!

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
