prolog './g602.ijs'
NB. ":y on non-empty numeric array y ------------------------------------

sprintf =: ":
real    =: {.@+.
imag    =: {:@+.

minus   =: $&'_'@('-'&=@{.)
ubar    =: >@({&(<;._1 ' _ _ _. _.'))@('iInN'&i.@{.)
afte    =: minus , (i.&0@(e.&'-+0') }. ])
efmt    =: >:@(i.&'e') ({. , afte@}.) ]
finite  =: ]`efmt@.('e'&e.)
massage =: finite`ubar@.(e.&'iInN'@{.)
fmtD    =: (minus,massage@(e.&'-+'@{.}.])) @ sprintf

cleanZ  =: (* ] >&| (2^_44)"_ * |.)&.+.
fmtZ1   =: fmtD@real , 'j'&,@fmtD@imag`(''"_)@.(0&=@imag)
fmtZ    =: fmtZ1 NB. @ cleanZ

fmtB    =: {&'01'
fmtI    =: sprintf
fmt     =: (fmtB&.>)`(fmtI&.>)`(fmtD&.>)`(fmtZ&.>) @. (1 4 8&i.@(3!:0))

sh      =: (*/@}:,{:@(1&,))@$ ($,) ]
width   =: (<:@{. 0} ])@:>:@(>./)@sh@:(#&>)
th      =: (-@width ;@:({.&.>)"1 ]) @ fmt

f =: ": -: th

f x=:1=?2 3 4$2
f x=:_50+?2 3 4$100
f x=:o._50+?2 3 4$100
f x=:r.?4 3 2$100

f x=:1=?2
f x=:_50+?100
f x=:o._50+?100
f x=:r.?100
f x=:r.0

f x=:_3.1415e_76 _3.1415e76
f x=:_3.1415e_76j_3.1415e76

f _
f __
f _.
f 3 7$ _ 3 __ 4 _. 6

(":_3.1415e_76) -: fmtD '-3.1415e-76'
(":_3.1415e76 ) -: fmtD '-3.1415e+076'
(": _) -: fmtD 'INF'
(": _) -: fmtD 'inf'
(":__) -: fmtD '-INF'
(":__) -: fmtD '-inf'
(":_.) -: fmtD 'NAN'
(":_.) -: fmtD 'nan'
(":_.) -: fmtD '+NAN01'
(":_.) -: fmtD '+nan01'

(,'_' ) -: ": _
'__' -: ": __
'_.' -: ": _.

(":x) -: }. ; ' ',&.>":&.>x=: 4 5,imax,1 _2 3
(":x) -: }. ; ' ',&.>":&.>x=: 4 5,imin,1 _2 3

(":imax) -: ": <:2x^IF64{31 63
(":imin) -: ": - 2x^IF64{31 63

sqz=: #"1~ -.@(1 1&E.)@(*./)@(' '&=)
(":x) -: sqz _3 }.@,\' ',.":,., x=: 2 3$imax,1 2 _3
(":x) -: sqz _3 }.@,\' ',.":,., x=: 2 3$imin,1 2 _3

NB. Unicodes not emulated by th
'abcd' -: ": u: 'abcd'
'abcd' -: ": 10&u: 'abcd'
(224 160 128 224 160 129{a.) -: ": 4 u: 2048 2049

NB. ": on unboxed literal
(a.{~i.16 16) -: ": 16 16$a.
(":x) -: ":("1) x=: 3 4$ 97 224 176 157 98{a.
(":x) -: ":("1) x=: 3 4$ u: 16b61 16bd800 16bdc00
(":x) -: ":("1) x=: 3 4$ 10&u: 16b61 16bd800 16bdc00

NB. ": on unboxed literal should have no extra null
({.a.) -.@e. 8 u: }. u: i.16bd800
({.a.) -.@e. ": }. u: i.16bd800
(8 u: x) -: ":x=: u: i.16bd800
(8 u: x) -: ":x=: u: 0 0 0,~ 16be000 + i.16b2000
(8 u: x) -: ":x=: 10&u: 0 0 0,~ 16b10000 + i.16b2000
NB. literal2
(8 u: x) -: ":x=: u: i.128                 NB. ascii
(8 u: x) -: ":x=: u: 128+i.128             NB. literal2
(8 u: y) -: ":x=: 7 u: y=: 16bd800 + i.8   NB. lone surrogate
(8 u: y) -: ":x=: 7 u: y=: 16b10000 + i.8  NB. non-bmp
NB. literal4
(8 u: x) -: ":x=: 10&u: i.128               NB. ascii
(8 u: x) -: ":x=: 10&u: 128+i.128           NB. literal4
(8 u: y) -: ":x=: 10&u: y=: 16b10000 + i.8  NB. non-bmp
(a.{~256|y) -: ": 10&u: y=: 16b110000 + i.1000 NB. demoting unboxed illegal utf32

bc =: 9!:6 ''
9!:7  '+++++++++|-'
a =: <;.(_1) 32 195 171 195 171 195 171 32 97 98 99 100 101 102{a.
(a.{~3 15$ 43 45 45 45 43 45 45 45 45 45 45 43 32 32 32 124 195 171 195 171 195 171 124 97 98 99 100 101 102 124 43 45 45 45 43 45 45 45 45 45 45 43 32 32 32) -: ": a
NB. display width of extended Latin
6 = # ' ' -.~ {. ": <u:200+i.4
6 = # ' ' -.~ {. ": <8&u: u:200+i.4
NB. display width of CJK
10 = # ' ' -.~ {. ": <u:30000+i.4
10 = # ' ' -.~ {. ": <8&u: u:30000+i.4
NB. display width of mixed character sets
18 = # ' ' -.~ {. ": <8&u: u:(40+i.4),(200+i.4),30000+i.4
NB. display width of non-bmp pane
6 = # ' ' -.~ {. ": <10&u: 16b10000+i.4
10 = # ' ' -.~ {. ": <10&u: 16b20000+i.4
9!:7 bc


NB. ":y print precision -------------------------------------------------

pi=:o.1
'3.14159' -: ":pi
'3.14159' -: ":!.6 pi
'3.141592653589793' -: ":!.16 pi

ppq =: 9!:10
pp  =: 9!:11

6 -: ppq ''
x=:7^_4+i.14

(": -: ":!. 6) x
(": -: ":!. 4) x [ pp 4
(": -: ":!. 8) x [ pp 8
(": -: ":!.12) x [ pp 12
(": -: ":!. 6) x [ pp 6

'domain error' -: pp etx 'a'
'domain error' -: pp etx <7
'domain error' -: pp etx 7.5
'domain error' -: pp etx 7j5
'domain error' -: pp etx _6

'rank error'   -: pp etx 5 6

'limit error'  -: pp etx 41


NB. ":y on boxed array y ------------------------------------------------

boxed   =: 32 = 3!:0
mt      =: 0 e. $
boxc    =: 9!:6 ''
tcorn   =: 2  0{boxc
tint    =: 1 10{boxc
bcorn   =: 8  6{boxc
bint    =: 7 10{boxc

sh      =: (*/@}: , {:)@(1&,)@$ $ ,
rows    =: */\.@}:@$
bl      =: }.@(,&0)@(+/)@(0&=)@(|/ i.@{.@(,&1))
mask    =: 1&,. #&, ,.&0@>:@i.@#
mat     =: mask@bl@rows { ' ' , sh

edge    =: ,@(1&,.)@[ }.@# +:@#@[ $ ]
left    =: edge&(3 9{boxc)@>@(0&{)@[ , "0 1"2 ]
right   =: edge&(5 9{boxc)@>@(0&{)@[ ,~"0 1"2 ]
top     =: 1&|.@(tcorn&,)@(edge&tint)@>@(1&{)@[ ,"2  ]
bot     =: 1&|.@(bcorn&,)@(edge&bint)@>@(1&{)@[ ,"2~ ]
perim   =: [ top [ bot [ left right

topleft =: (4{boxc)&((<0 0)}) @ ((_2{boxc)&,.) @ ((_1{boxc)&,)
inside  =: 1 1&}. @: ; @: (,.&.>/"1) @: (topleft&.>)
take    =: {. ' '"_^:mt
frame   =: [ perim {@[ inside@:(take&.>)"2 ,:^:(1 = #@$)@]
rc      =: (>./@sh&.>) @: (,.@|:"2@:(0&{"1);1&{"1) @: ($&>)

thorn1  =: ":`thbox @. boxed
thbox   =: (rc frame ]) @: (mat@thorn1&.>)

f =: ": -: thorn1

y =: 2 3$(i.2 3);'abc';(i.4 1);(2 2$'ussr');12;<+&.>i.2 2 3
f y

f <'abc'
f <''
f <2 0 3$'abc'
f <2 3 4 2$'abc'

f ;:'Cogito, ergo sum.'
f (?3$20)?&.>30

f <i.2 3
f 3;<o.i.2 3
f <<3;<r.?1 1 2 3$100
f <<'';i.2 0 3 4 2
f +&.>i.2 3 4
f (<i.3 4) (<0 0 0)} +.&.>i.2 3 4

NB. ascii
f < 'abc'
f < u: 'abc'
f < 10&u: 'abc'
f 'abc';(u: 'abc');(10&u: 'abc')
f (32}.128{.a.);(u: 32}.i.128);(10&u: 32}.i.128)

NB. NUL removed
0 -.@e. , ": < a.
0 -.@e. , ": < u: 0 0, 0 0,~ 128+i.128
0 -.@e. , ": < 10&u: 0 0, 0 0,~ 128+i.128
0 -.@e. , ": (128{.a.);(u: 0 0, 0 0,~ 128+i.128)
0 -.@e. , ": (128}.a.);(10&u: 0 0, 0 0,~ 128+i.128)
0 -.@e. , ": (u: 0 0, 0 0,~ 128+i.128);(10&u: 0 0, 0 0,~ 128+i.128)
0 -.@e. , ": (128}.a.);(u: 0 0, 0 0,~ 128+i.128);(10&u: 0 0, 0 0,~ 128+i.128)

NB. x":y ----------------------------------------------------------------

sp =: +./@(0&>)@+.@[ >:@*. 0&<:@]
f0 =: (-.&' ') @ (((* * 20&+@|)@{. j. {:)@+.@[ ": ])
f  =: 4 : 0
 ((*./0<:+.x)*x sp {.y)}. ; ((x sp y)$&.>' ') ,&.> x <@f0"0 y
)
f  =: 4 : 0
 }.;' ' ,&.> x <@f0"0 y
)

NB. Boolean
t=:(,.  15 j.i.10) <@": 0
t -: (1+(*k)+k=:i.10) <&(_15&{.)@{."0 1 '0.',9$'0'
t=:(,.- 15 j.i.10) <@": 0
t -: (2+(*k)+k=:i.10) <&(15&{.)&(,&'e0')@{."0 1 ' 0.',9$'0'
(0j4  f t) -: 0j4  ": t=:1=?9$2
(0j_4 f t) -: 0j_4 ": t=:1=?9$2
(0 ": t) -: 0 ": (2-2)+t=:?10 10$2
'*****' -: 5j6":0

NB. integer
t=:(,.15 j. i.10) <@": 3
t -: (1+(*k)+k=:i.10) <&(_15&{.)@{."0 1 '3.',9$'0'
t=:(,.15 j. i.10) <@": _3
t -: (2+(*k)+k=:i.10) <&(_15&{.)@{."0 1 '_3.',9$'0'
t=:(,.-15 j. i.10) <@": 3
t -: (2+(*k)+k=:i.10) <&(15&{.)&(,&'e0')@{."0 1 ' 3.',9$'0'
t=:(,.-15 j. i.10) <@": _3
t -: (2+(*k)+k=:i.10) <&(15&{.)&(,&'e0')@{."0 1 '_3.',9$'0'
(0j4  f t) -: 0j4  ": t=:_50+?9$100
(0j_4 f t) -: 0j_4 ": t=:_50+?9$100
'*****' -: 5j3":12
imax -: 0 ". 25 ": imax
imin -: 0 ". 25 ": imin

NB. floating point
t=:(,. 15 j. i.10) <@": 3.2
t -: (1+(*k)+k=:i.10) <&(_15&{.)@{."0 1 '3.2',8$'0'
t=:(,. 15 j. i.10) <@": _3.2
t -: (2+(*k)+k=:i.10) <&(_15&{.)@{."0 1 '_3.2',8$'0'
t=:(,.-15 j. i.10) <@": 3.2
t -: (2+(*k)+k=:i.10) <&(15&{.)&(,&'e0')@{."0 1 ' 3.2',8$'0'
t=:(,.-15 j. i.10) <@": _3.2
t -: (2+(*k)+k=:i.10) <&(15&{.)&(,&'e0')@{."0 1 '_3.2',8$'0'
(0j4  f t) -: 0j4  ": t=:o._50+?9$100
(0j_4 f t) -: 0j_4 ": t=:o._50+?9$100
'*****' -: 5j3":_1.2
(];._2 (0 : 0)) -: 0j_4 ": 2 2 $ 0.12 0.12 _0.1 _1.1
 1.2000e_1  1.2000e_1
_1.0000e_1 _1.1000e0
)


NB. complex
t=:(,. 15 j. i.10) <@": 3.2j4
t -: (1+(*k)+k=:i.10) <&(_15&{.)@{."0 1 '3.2',8$'0'
t=:(,. 15 j. i.10) <@": _3.2j4
t -: (2+(*k)+k=:i.10) <&(_15&{.)@{."0 1 '_3.2',8$'0'
t=:(,.-15 j. i.10) <@": 3.2j4
t -: (2+(*k)+k=:i.10) <&(15&{.)&(,&'e0')@{."0 1 ' 3.2',8$'0'
t=:(,.-15 j. i.10) <@": _3.2j4
t -: (2+(*k)+k=:i.10) <&(15&{.)&(,&'e0')@{."0 1 '_3.2',8$'0'
'*****' -: 5j3":_1.2j4

(;_1 _2 _3<@{."0 t{'01') -: 1 2 3": t=:1=?3$2
(;_1 _2 _3<@{."0 t{'0123456789') -: 1 2 3": t=:?3$10

(9 {."1 '  _',:' __') -: 0 _1 { _9j2 ": ,. _ , (i: 5) , __
(9 {."1 '  _',:' __') -: 0 _1 { 9j_2 ": ,. _ , (i: 5) , __

test =: 4 : '((}:$z)-:}:$y),(#$z)-:1>.#$y [ z=: x ": y'

9j4 test 50
9j4 test ,12
9j4 test 1 2 3
9j4 test i.1 3
9j4 test i.3 1
9j4 test i.3 4
9j4 test i.2 3 4
9j4 test i.2 3 4 5

0j4 test 50
0j4 test ,12
0j4 test 1 2 3
0j4 test i.1 3
0j4 test i.3 1
0j4 test i.3 4
0j4 test i.2 3 4
0j4 test i.2 3 4 5

9j4 test i.0
9j4 test i.5 0
9j4 test i.0 5
9j4 test i.2 0 4

0j4 test i.0
0j4 test i.5 0
0j4 test i.0 5
0j4 test i.2 0 4

(_12{.'1234.57') -: 12j2 ": 1234.567

-:/ 10   ": ,. 3.33e_16 _3.33e_16
-:/ 10j4 ": ,. 3.33e_16 _3.33e_16
'  0' -: 3 ": _3.33e_12j_4.44e_14

'domain error' -: 9.2     ": etx 12
'domain error' -: 9j2     ": etx '3 4'
'domain error' -: 9j2     ": etx <123
'domain error' -: 'ab'    ": etx 4 5
'domain error' -: (<21)   ": etx 4 5

'length error' -: 1 2     ": etx 4
'length error' -: 1 2     ": etx 4 5 6
'length error' -: 1 2     ": etx i.2 3
'length error' -: 1 2     ": etx i.2 3 4


NB. x":y on boxed arrays ------------------------------------------------

(0 0 ": x) -: ": x=: ,. ;: 'Cogito, ergo sum.'

(' *'{~0=i.3 3) -: 3 3{.1 1}.0 0":x=:x,:|.x=:(1 1$'*');3 3$'*'
(' *'{~1=i.3 3) -: 3 3{.1 1}.0 1":x
(' *'{~2=i.3 3) -: 3 3{.1 1}.0 2":x
(' *'{~3=i.3 3) -: 3 3{.1 1}.1 0":x
(' *'{~4=i.3 3) -: 3 3{.1 1}.1 1":x
(' *'{~5=i.3 3) -: 3 3{.1 1}.1 2":x
(' *'{~6=i.3 3) -: 3 3{.1 1}.2 0":x
(' *'{~7=i.3 3) -: 3 3{.1 1}.2 1":x
(' *'{~8=i.3 3) -: 3 3{.1 1}.2 2":x

f =: 4 : 0
 old=.9!:16 ''
 9!:17 x
 z=.":y
 9!:17 old
 z
)

0 0 (f -: ":) x=:i.&.>i.2 3 4
0 1 (f -: ":) x
0 2 (f -: ":) x
1 0 (f -: ":) x
1 1 (f -: ":) x
1 2 (f -: ":) x
2 0 (f -: ":) x
2 1 (f -: ":) x
2 2 (f -: ":) x

0 0 (f -: ":) x=:i.&.><"1 >:7 7#:?4 3$49
0 1 (f -: ":) x
0 2 (f -: ":) x
1 0 (f -: ":) x
1 1 (f -: ":) x
1 2 (f -: ":) x
2 0 (f -: ":) x
2 1 (f -: ":) x
2 2 (f -: ":) x

'domain error' -: 'ab'      ": etx 1;2;3
'domain error' -: 1.2 0     ": etx 1;2;3
'domain error' -: 1 2j3     ": etx 1;2;3
'domain error' -: (1;2)     ": etx 1;2;3

'length error' -: 0 1 2 3   ": etx 1;2;3
'length error' -: (i.0)     ": etx 1;2;3


NB. x":y on extended integers -------------------------------------------

20j4 (": -: (": x:)) x=: _5e8+?20$1e9
20j4 (": -: (": x:)) ,.x
20j4 (": -: (": x:)) 5 4$x
20j0 (": -: (": x:)) x
20j0 (": -: (": x:)) ,.x
20j0 (": -: (": x:)) 5 4$x
0j4  (": -: (": x:)) x
0j4  (": -: (": x:)) ,.x
0j4  (": -: (": x:)) 5 4$x
0    (": -: (": x:)) x
0    (": -: (": x:)) ,.x
0    (": -: (": x:)) 5 4$x

0j_4 (": -: (": x:)) 123454
0j_4 (": -: (": x:)) 123455
0j_4 (": -: (": x:)) 123456
0j_4 (": -: (": x:)) 123496
0j_4 (": -: (": x:)) 123996
0j_4 (": -: (": x:)) 129996
0j_4 (": -: (": x:)) 199996
0j_4 (": -: (": x:)) 999996

_14  (": -: (": x:)) 123454
_14  (": -: (": x:)) 123455
_14  (": -: (": x:)) 123456
_14  (": -: (": x:)) 123496
_14  (": -: (": x:)) 123996
_14  (": -: (": x:)) 129996
_14  (": -: (": x:)) 199996
_14  (": -: (": x:)) 999996

0j_6 (": -: (": x:)) 1234
0j_6 (": -: (": x:)) 1235
0j_6 (": -: (": x:)) 1236
0j_6 (": -: (": x:)) 1239
0j_6 (": -: (": x:)) 1299
0j_6 (": -: (": x:)) 1999
0j_6 (": -: (": x:)) 9999

0j3  (": -: (": x:^:_1)) 12344x 12346 12347 % 10000x
0j3  (": -: (": x:^:_1)) 12349x 12399 12999 19999 99999 % 10000x
0j3  (": -: (": x:^:_1)) x=: %/x: (+ 0&=) _4e8+?2 20 5$1e9

12j3 (": -: (": x:^:_1)) 12344x 12346 12347 % 10000x
12j3 (": -: (": x:^:_1)) 12349x 12399 12999 19999 99999 % 10000x
12j3 (": -: (": x:^:_1)) x=: %/x: (+ 0&=) _4e8+?2 20 5$1e9

'0.0000e0' -: 0j_4 ": 0r1
'0.0000'   -: 0j4  ": 0r1

2 50027 -: $ 0j25 ": ,. 10 ^ 0 50000x


4!:55 ;:'a afte bc bcorn bint bl bot boxc boxed cleanZ edge efmt '
4!:55 ;:'f f0 finite fmt fmtB fmtD fmtI fmtZ fmtZ1 frame ' 
4!:55 ;:'imag inside k left mask massage mat minus mt perim '
4!:55 ;:'pi pp ppq rc real right rows sh sp sprintf '        
4!:55 ;:'sqz t take tcorn test th thbox thorn1 tint top '
4!:55 ;:'topleft ubar width x y z ' 


epilog''

