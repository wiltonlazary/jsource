NB. x,y Append in place -------------------------------------------------

f=: 3 : 0
 z=. i.0
 for_i. i.y do.
  z=. z,i
 end.
)

(i. -: f)"0 ?2 10$2e3

f=: 3 : 0
 z=. i.0
 for_i. i.y do.
  z=. i ,~ z
 end.
)

(i. -: f)"0 ?2 10$2e3


f1=: 3 : 0
 z=. i.0 0
 for_i. i.y do.
  z=. z,i. i
 end.
)

(i."0@i. -: f1)"0 ?2 10$100

f1=: 3 : 0
 z=. i.0 0
 for_i. i.y do.
  z=. (i. i) ,~ z
 end.
)

(i."0@i. -: f1)"0 ?2 10$100

f2=: 3 : 0
 z=. ''
 for_x. y do.
  z=. z,x
 end.
)

(] -: f2) 'only Hugh can prevent florist friars'
(] -: f2) u:'only Hugh can prevent florist friars'
(] -: f2) 10&u:'only Hugh can prevent florist friars'
(] -: f2) s:@<"0 'only Hugh can prevent florist friars'
(] -: f2) ?1000$1e6

f2=: 3 : 0
 z=. ''
 for_x. y do.
  z=. x ,~ z
 end.
)

(] -: f2) 'only Hugh can prevent florist friars'
(] -: f2) u:'only Hugh can prevent florist friars'
(] -: f2) 10&u:'only Hugh can prevent florist friars'
(] -: f2) s:@<"0 'only Hugh can prevent florist friars'
(] -: f2) ?1000$1e6

global=: i.7
f3=: 3 : 'global=. global,y'
((i.7),999 888) -: f3 999 888
NB. global -: i.7

f4=: 3 : 0
 a =: 4 27$'a'
 a1=: 4 27$'a'
 b =: 3 17$(10$'b'),'1234567'
 a =: a,b
 assert. a -: a1,b
 a =: 4 27$u:'a'
 a1=: 4 27$u:'a'
 b =: 3 17$(10$u:'b'),u:'1234567'
 a =: a,b
 assert. a -: a1,b
 a =: 4 27$10&u:'a'
 a1=: 4 27$10&u:'a'
 b =: 3 17$(10$10&u:'b'),10&u:'1234567'
 a =: a,b
 assert. a -: a1,b
 a =: 4 27$s:@<"0 'a'
 a1=: 4 27$s:@<"0 'a'
 b =: 3 17$(10$s:@<"0 'b'),s:@<"0 '1234567'
 a =: a,b
 assert. a -: a1,b
 1
)

f4 ''

global=: ;: 'zero one two three four'

f5=: 3 : 0
 txt=. 1 2 { global
 txt=. txt ,each 'x'
)

('onex';'twox') -: f5 ''

global=: (u:&.>) ;:'zero one two three four'

f5=: 3 : 0
 txt=. 1 2 { global
 txt=. txt ,each u:'x'
)

((u:'onex');u:'twox') -: f5 ''

global=: (10&u:&.>) ;:'zero one two three four'

f5=: 3 : 0
 txt=. 1 2 { global
 txt=. txt ,each 10&u:'x'
)

((10&u:'onex');10&u:'twox') -: f5 ''

global -: ;: 'zero one two three four'

f6=: 3 : 0
 g=. ;: 'zero one two three four'
 t=. 1 2 { g
 t=. t ,each 'x'
 assert. t -: ;:'onex twox'
 assert. g -: ;: 'zero one two three four'
 g=. (u:&.>) ;:'zero one two three four'
 t=. 1 2 { g
 t=. t ,each u:'x'
 assert. t -: (u:&.>) ;:'onex twox'
 assert. g -: (u:&.>) ;:'zero one two three four'
 g=. (10&u:&.>) ;:'zero one two three four'
 t=. 1 2 { g
 t=. t ,each 10&u:'x'
 assert. t -: (10&u:&.>) ;:'onex twox'
 assert. g -: (10&u:&.>) ;:'zero one two three four'
 1
)

f6 ''

f7=: 3 : 0
 g=. ;: 'zero one two three four'
 t=. 1 2 { g
 t=. t ,&.> 'x'
 assert. t -: ;:'onex twox'
 assert. g -: ;: 'zero one two three four'
 g=. (u:&.>) ;:'zero one two three four'
 t=. 1 2 { g
 t=. t ,&.> u:'x'
 assert. t -: (u:&.>) ;:'onex twox'
 assert. g -: (u:&.>) ;:'zero one two three four'
 g=. (10&u:&.>) ;:'zero one two three four'
 t=. 1 2 { g
 t=. t ,&.> 10&u:'x'
 assert. t -: (10&u:&.>) ;:'onex twox'
 assert. g -: (10&u:&.>) ;:'zero one two three four'
 1
)

f7 ''

global=: '01234'

f8=: 3 : 0
 a=. y
 a=. a,'x'
)

'01234x' -: f8 global
global -: '01234'

'01234x' -: f8 '01234'

global=: u:'01234'

f8=: 3 : 0
 a=. y
 a=. a,u:'x'
)

'01234x' -: f8 global
global -: '01234'

'01234x' -: f8 u:'01234'

global=: 10&u:'01234'

f8=: 3 : 0
 a=. y
 a=. a,10&u:'x'
)

'01234x' -: f8 global
global -: '01234'

'01234x' -: f8 10&u:'01234'

f9=: 3 : 0
 a=. '01234'
 a=. a,'x'
)

'01234x' -: f9 ''

f9=: 3 : 0
 a=. u:'01234'
 a=. a,u:'x'
)

'01234x' -: f9 ''

f9=: 3 : 0
 a=. 10&u:'01234'
 a=. a,10&u:'x'
)

'01234x' -: f9 ''

test=: 4 : 0
 q=. x, y
 x=. x, y
 assert. q -: x
 1
)

5 6     test 2 3 4
5 6     test 2 3 4
(i.4 3) test 10 20 30
5 6 7 8 test 0 1 0
5 6 7.8 test 0 1 0
5 6 7.8 test 0 3 4
5 6 7.8 test 0 3.4
5 6 7j8 test 0 1 0
5 6 7j8 test 0 3 4
5 6 7j8 test 0 3.4
5 6 7j8 test 0 3j4

(<5 6 ) test&>~ (i.10 25)$&.> <2 3 4
(<'12') test&>~ (i.10 25)$&.> <'abc'

testa=: 4 : 0
 (a.{~x ?@$ 256) test a.{~y ?@$ 256
 (    x ?@$ 2e9) test     y ?@$ 2e9
 (    x ?@$ 0  ) test     y ?@$ 0
)

67       testa&> '';,&.> 3 5 7 11 13 67 71
(<4 5  ) testa&> '';3;5;7
(<6 4 5) testa&> '';3;5;7; 4 5;2 3;4 3;2 5; 2 3 4;2 4 5;2 7

NB. Verify no local-to-global aliasing
f10 =: 3 : 'a =. a , 8'
f11 =: 3 : 'a =: a , 8'
f12 =: 3 : 'a =: a , a =. 2 3'
f13 =: 3 : 'a =. a , a =. 2 3'
a =: i. 4
0 1 2 3 8 -: f10''
0 1 2 3 -: a
0 1 2 3 8 -: f11''
0 1 2 3 8 -: a
'domain error' -: f12 etx ''
2 3 2 3 -: f13''

NB. Verify constants not corrupted in unassigned verbs
f =: 3 : 0"0 '123'
'abc' , (2#y) , 'd'
)
('abc11d' , 'abc22d' ,: 'abc33d') -: f

NB. Verify inplacing works in forks, including nvv forks
1120000 > 7!:2 '(i. , ]) 100000'
'lrlr' -: (1 {. 'l') (, , ,) (1 {. 'r')
(10000 # 'lrlr') -: (10000 # 'l') (, , ,) (10000 # 'r')
24000 > 7!:2 '(10000 # ''l'') (, , ]) (1000 # ''r'')'
(10000 2000 # 'lr') -: (10000 # 'l') (, , ]) (1000 # 'r')
24000 > 7!:2 '(10000#''l'') ([: ] ,) (1000#''r'')'
0 7 14 21 28 -: (({.7)"_ * ])"0 i. 5  NB. ensure constant function not overwritten
0 7 14 21 28 -: (({.7) * ])"0 i. 5  NB. ensure n in nvv not overwritten
b =: 7
0 7 14 21 28 -: (b * ])"0 i. 5  NB. ensure name in nvv not overwritten
b -: 7
a =: 10000#'a'
3000 > 7!:2 'a =: (''b'' ,~ [) a'   NB. NVV with Usecount=1 still inplace
3000 > 7!:2 'a =: (({.''b'') ,~ [) a'  NB. Usecount -1 too
nb =: ('b' ,~ [)
3000 > 7!:2 'a =: nb a'  NB. usecount=1 inside the name, still inplace
a -: (10000#'a'),'bbb'
b =: 'c'
3000 > 7!:2 'a =: (b ,~ ]) a'  NB. different name, still inplace assignment
b -: 'c'
a -: (10000#'a'),'bbbc'
3000 < 7!:2 'a =: (a ,~ ]) a'  NB. same name, not inplace
a -: ((10000#'a'),'bbbc'),((10000#'a'),'bbbc')
NB. Boxed values should cause no trouble, but we don't have anything that inplaces boxed arrays yet

NB. Repeat the tests in an explicit definition - twice, to ensure no corruption of stored sentences
ipexp =: 3 : 0
0 7 14 21 28 -: (({.7)"_ * ])"0 i. 5  NB. ensure constant function not overwritten
0 7 14 21 28 -: (({.7) * ])"0 i. 5  NB. ensure n in nvv not overwritten
b =. 7
0 7 14 21 28 -: (b * ])"0 i. 5  NB. ensure name in nvv not overwritten
b -. 7
a =. 10000#'a'
3000 > 7!:2 'a =. (''b'' ,~ [) a'   NB. NVV with Usecount=1 still inplace
3000 > 7!:2 'a =. (({.''b'') ,~ [) a'  NB. Usecount -1 too
nb =. ('b' ,~ [)
3000 > 7!:2 'a =. nb a'  NB. usecount=1 inside the name, still inplace
a -: (10000#'a'),'bbb'
b =. 'c'
3000 > 7!:2 'a =. (b ,~ ]) a'  NB. different name, still inplace assignment
b -: 'c'
a -: (10000#'a'),'bbbc'
3000 < 7!:2 'a =. (a ,~ ]) a'  NB. same name, not inplace
a -: ((10000#'a'),'bbbc'),((10000#'a'),'bbbc')
)
ipexp''
ipexp''

a =: 'abc'
'abcbabcb' -: a (, , ,) 'b'
a =: a (, , ,) 'b'
'abcbabcb' -: a
'abcbabcb' -: ('a','bc') (, , ,) {.'b'
a =: 'abc'
a =: 'abc' (, , (, , ,)) 'b'
a -: 'abcbabcbabcb'
a =: 'abc'
a =: 'abc' (, , (, , [)) 'b'
a -: 'abcbabcbabc' 

            


NB. hook
('c' ,~ 999 $ 'abc') -: (, {:) 999 $ 'abc'
3000 > 7!:2 '(, {:) 888 $ ''abc'''
('c' ,~ 1000 # 'a') -: (1000 # 'a') (, ]) 'c'
4000 > 7!:2 '(1000 # ''a'') (, ]) ''c'''

NB. u@v
'b' -: (10000#'a') {:@, 'b'
20000 > 7!:2 '(10000#''a'') {:@, ''b'''         
a =: 10000#'c'
3000 > 7!:2 'a =: {.@(({.''b'') ,~ ]) a'

NB. u&v
a =: i. 1000
0 1 2 3 4 -: ($0) {.&(5 ,~ ]) a
a =: i. 1000
3000 > 7!:2 'a =: ($0) {.&(5 ,~ ]) a'

NB. u@:v
'b' -: (10000#'a') {:@:, 'b'
20000 > 7!:2 '(10000#''a'') {:@:, ''b'''         
a =: 10000#'c'
3000 > 7!:2 'a =: {.@:(({.''b'') ,~ ]) a'

NB. u&n
20000 > 7!:2 ',&''a'' 10000#''b'''
a =: 10000#'a'
('c' ,~ 10000#'a') -: a =: ,&'c' a
2000 > 7!:2 'a =: ,&({.''c'') a'

NB. m&v
(5,.i.4) -: (6-1)&,"0 i. 4  NB. Verify constant not overwritten

NB. u&.v
20000 > 7!:2 ',&''b''&.] 10000#''a'''
a =: 10000#5
(6 ,~ 10000#5) -: a =: ,&6&.] a
3000 > 7!:2 'a =: ,&6&.] a'
3000 > 7!:2 '{. a =: ,&6&.] a'  NB. Verify assignment need not be first word
a =: 10000#'a'
22000 > 7!:2 'a =: ]&.(,&({.''b'')) a'

NB. u&.:v
20000 > 7!:2 ',&''b''&.:] 10000#''a'''
a =: 10000#5
(6 ,~ 10000#5) -: a =: ,&6&.:] a
3000 > 7!:2 'a =: ,&6&.:] a'
3000 > 7!:2 '{. a =: ,&6&.:] a'  NB. Verify assignment need not be first word
22000 > 7!:2 ',&''b''&.:(,&''c'' :. (,&''d'')) 10000#''a'''  NB. all verbs inplaceable
a =: 10000#'a'
22000 > 7!:2 'a =: ]&.:(,&({.''b'')) a'



4!:55 ;:'a a1 b f f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13 global ipexp local nb test testa'


