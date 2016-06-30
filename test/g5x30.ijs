NB. 5!:30 ---------------------------------------------------------------

9!:17 (0 0)
cr  =: 13{a.
lf  =: 10{a.
crlf=: 13 10{a.

f   =: 5!:30

dtb =: -@(+/"1)@(*./\."1)@(' '&=) <@}."_1 ]
g   =: ; @: (,&lf&.>) @: dtb @: (1 1&}.) @: (_1 _1&}.) @: ": @: <

t=: 0 250 _ _ f x=: i.4 5
t -: ,(":i.4 5),.lf

t=: 0 250 5 10 f x=: i.300
t -: (250{.":x),'...',lf

t=: 0 _ _ _ f x=: ?2 3 4 5 3$1e6
t -: g x

t=: 0 250 5 10 f i.40 1
16 = +/ t=lf
t -: (,' ',.'01234',.lf),'...',lf,,(2":30+i.10 1),.lf

t=: 0 _ 5 10 f x=: lf (100?2000)}2000$'x'
16 = +/ t=lf
i =: 1 i.~ '...' E. t
t -: (i{.x),'...',lf,(((5+i)-#t){.x),lf

('a',LF,LF,'b',LF,'c',LF) -: (0 40 1 1) 5!:30 'a',LF,LF,'b',LF,'c'
('a',LF,LF,'bc',LF,'c',LF) -: (0 40 1 1) 5!:30 'a',LF,LF,'bc',LF,'c'
('a',LF,'...',LF,'c',LF) -: (0 40 1 1) 5!:30 'a',LF,LF,'bcd',LF,'c'
('a',CR,LF,CR,LF,'b',CR,LF,'c',CR,LF) -: (1 40 1 1) 5!:30 'a',LF,LF,'b',LF,'c'
('a',CR,LF,'...',CR,LF,'c',CR,LF) -: (1 40 1 1) 5!:30 'a',LF,LF,'bc',LF,'c'
u1 =. (u: 16b03c0),'r2'
u2 =. 'abc'
(207 128 114 50 10 97 98 99 10 { a.) -: (0 40 20 20)  5!:30 u1,:u2
(207 128 114 50 10 97 32 32 10 97 98 99 10 10 98 10{a.) -: 0 40 20 20 (5!:30) (u1,LF,'a') ,: u2,CR,CRLF,'b'

bc =: 9!:6 ''
9!:7 (16+i.11) { a.
u1=: (u: 16b03c0),'r2'
(0 : 0) -: (0 40 20 20)  5!:30 <u1
┌───┐
│πr2│
└───┘
)
(0 : 0) -: (0 40 20 20)  5!:30  ,.~(<'abcdéf'),:<>'ab';'aéé';'asdf'
┌──────┬──────┐
│abcdéf│abcdéf│
├──────┼──────┤
│ab    │ab    │
│aéé   │aéé   │
│asdf  │asdf  │
└──────┴──────┘
)
(0 : 0) -: (0 40 20 20)  5!:30  ,.~(<'aéf'),:<>'ab';'aéé';'asdf'
┌─────┬─────┐
│aéf  │aéf  │
├─────┼─────┤
│ab   │ab   │
│aéé  │aéé  │
│asdf │asdf │
└─────┴─────┘
)
(0 : 0) -: (0 40 20 20)  5!:30  ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│é    │
├──────┼─────┤
│aéc   │ab   │
│aéc   │aéé  │
│      │asdf │
│      │é    │
│      │é    │
└──────┴─────┘
)
   9!:17 (1 0)

(0 : 0) -: (0 40 20 20)  5!:30     ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│é    │
├──────┼─────┤
│      │ab   │
│aéc   │aéé  │
│aéc   │asdf │
│      │é    │
│      │é    │
└──────┴─────┘
)
   9!:17 (2 0)

(0 : 0) -: (0 40 20 20)  5!:30     ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│é    │
├──────┼─────┤
│      │ab   │
│      │aéé  │
│      │asdf │
│aéc   │é    │
│aéc   │é    │
└──────┴─────┘
)
   9!:17 (0 1)

(0 : 0) -: (0 40 20 20)  5!:30     ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│  é  │
├──────┼─────┤
│ aéc  │ab   │
│ aéc  │aéé  │
│      │asdf │
│      │é    │
│      │é    │
└──────┴─────┘
)
   9!:17 (0 2)

(0 : 0) -: (0 40 20 20)  5!:30     ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│    é│
├──────┼─────┤
│   aéc│ab   │
│   aéc│aéé  │
│      │asdf │
│      │é    │
│      │é    │
└──────┴─────┘
)
   9!:17 (1 1)

(0 : 0) -: (0 40 20 20)  5!:30     ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│  é  │
├──────┼─────┤
│      │ab   │
│ aéc  │aéé  │
│ aéc  │asdf │
│      │é    │
│      │é    │
└──────┴─────┘
)
   9!:17 (2 2)

(0 : 0) -: (0 40 20 20)  5!:30     ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│    é│
├──────┼─────┤
│      │ab   │
│      │aéé  │
│      │asdf │
│   aéc│é    │
│   aéc│é    │
└──────┴─────┘
)
   9!:17 (1 2)

(0 : 0) -: (0 40 20 20)  5!:30     ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌──────┬─────┐
│abcdéf│    é│
├──────┼─────┤
│      │ab   │
│   aéc│aéé  │
│   aéc│asdf │
│      │é    │
│      │é    │
└──────┴─────┘
)
9!:17 (0 0)
(0 : 0) -: (0 40 20 20)  (5!:30)        1 ; (i. 4 2) ;< ('abcdéf';2 4$'aéc'),.(<'é'),:<>'ab';'aéé';'asdf';'é';,'é'
┌─┬───┬──────────────┐
│1│0 1│┌──────┬─────┐│
│ │2 3││abcdéf│é    ││
│ │4 5│├──────┼─────┤│
│ │6 7││aéc   │ab   ││
│ │   ││aéc   │aéé  ││
│ │   ││      │asdf ││
│ │   ││      │é    ││
│ │   ││      │é    ││
│ │   │└──────┴─────┘│
└─┴───┴──────────────┘
)




9!:7 bc

'domain error' -: 'abc'       5!:30 etx 4 5 6
'domain error' -: (1 2 3 4.5) 5!:30 etx 4 5 6
'domain error' -: (1 2 3 4j5) 5!:30 etx 4 5 6
'domain error' -: (1 2 3 4r5) 5!:30 etx 4 5 6
'domain error' -: (1;2;3;455) 5!:30 etx 4 5 6

'domain error' -: (0 _1 9 9 ) 5!:30 etx 4 5 6
'domain error' -: (0 9 _1 9 ) 5!:30 etx 4 5 6
'domain error' -: (0 9 9 _1 ) 5!:30 etx 4 5 6

'rank error'   -: (1        ) 5!:30 etx 4 5 6
'rank error'   -: (,:1 2 3 4) 5!:30 etx 4 5 6

'length error' -: (i.5      ) 5!:30 etx 4 5 6
'length error' -: (i.3      ) 5!:30 etx 4 5 6

'index error'  -: (3 10 10 9) 5!:30 etx 4 5 6


4!:55 ;:'bc cr crlf dtb f g i lf t u1 u2 x'


