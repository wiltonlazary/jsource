prolog './gtdot.ijs'
NB. T. t. ------------------------------------------------------------------

NB. **************************************** threads & tasks **********************************
NB. j904 64-bit only

NB. wait until there are y free threads
wthr=: {{ while. y ~: {. 2 T.'' do. 6!:3]0.001 end. 1 }}

N=: <: 9!:56'maxtasks'
N > 0
N1=: <.@%: N
N1 > 0
N >: N1*N1
N2=: 32 <. <.@%: 20 * N+2
N2 > 0

NB. create all available threads
1: 0&T."1^:(0 < #) ''$~ (0 >. N-1 T. ''),0
N = 1 T.''
wthr N

NB. no more thread can be created
'limit error' -: 0&T. etx ''

f=: 4 : 0
echo^:ECHOFILENAME 'test ',(":1),' f ',(":y),' start: ',":6!:0''
pyx=. g t. (<'worker';x) "0 i.y
while. do.
 r=. 4 T. pyx               NB. echo r for debug
 if. *./0>r do. break. end.
 6!:3[0.001
end.
assert. r e. _1000 _1001    NB. _1001 if run on the main thread
echo^:ECHOFILENAME 'test ',(":1),' f ',(":y),' finish: ',":6!:0''
]&> pyx
)

f1=: 4 : 0
if. 0 [ x*.GITHUBCI*.IFWIN do. y=. 10 <. y end.    NB. temp workaround
echo^:ECHOFILENAME 'test ',(":1),' f1 ',(":y),' start: ',":6!:0''
pyx=. x&g1@y t. (<'worker';x) "0 i.y
while. do.
 r=. 4 T. pyx               NB. echo r for debug
 if. *./0>r do. break. end.
 6!:3[0.001
end.
assert. r e. _1000 _1001    NB. _1001 if run on the main thread
echo^:ECHOFILENAME 'test ',(":1),' f1 ',(":y),' finish: ',":6!:0''
]&> pyx
)

f2=: 4 : 0
if. 0 [ x*.GITHUBCI*.IFWIN do. y=. 10 <. y end.    NB. temp workaround
echo^:ECHOFILENAME 'test ',(":1),' f2 ',(":y),' start: ',":6!:0''
pyx=. x&g1@y t. (<'worker';x) "0 i.y
pyx0=. g t. (<'worker';x) "0 i.y
while. do.
 r=. 4 T. pyx,pyx0               NB. echo r for debug
 if. *./0>r do. break. end.
 6!:3[0.001
end.
assert. r e. _1000 _1001    NB. _1001 if run on the main thread
echo^:ECHOFILENAME 'test ',(":1),' f2 ',(":y),' finish: ',":6!:0''
(,]&> pyx), ]&>pyx0
)

g=: 3 : 0
9!:1[(7^5)+3 T.''  NB. random per thread
6!:3[0.001*?0      NB. arbitrary delay
1
)

g1=: 4 : 0
9!:1[(7^5)-3 T.''  NB. random per thread
for_i. i.y do.
 6!:3[0.001*?0     NB. arbitrary delay
 pyx=. g t. (<'worker';x) "0 i.y
end.
]&> pyx
)

N = 1 T.''
wthr N

NB. number of tasks < number of worker threads

0 f N            NB. run in master thread

N = 1 T.''
wthr N

1 f N            NB. queued job

N = 1 T.''
wthr N

0 f1 N1          NB. run in master thread

N = 1 T.''
wthr N

1 f1 N1          NB. queued job

N = 1 T.''
wthr N

0 f2 N1          NB. run in master thread

N = 1 T.''
wthr N

1 f2 N1          NB. queued job

N = 1 T.''
wthr N

NB. number of tasks > number of worker threads

0 f 2*N          NB. run in master thread

N = 1 T.''
wthr N

1 f 2*N          NB. queued job

N = 1 T.''
wthr N

0 f1 N1          NB. run in master thread

N = 1 T.''
wthr N

1 f1 N1          NB. queued job

N = 1 T.''
wthr N

0 f2 N1          NB. run in master thread

N = 1 T.''
wthr N

1 f2 N1          NB. queued job

N = 1 T.''
wthr N

0 f1 N2          NB. run in master thread

N = 1 T.''
wthr N

1 f1 N2          NB. queued job stress test

N = 1 T.''
wthr N

1 f1 40          NB. queued job stress test

N = 1 T.''
wthr N

1 f1 45          NB. queued job stress test

N = 1 T.''
wthr N

1 f1 50          NB. queued job stress test

N = 1 T.''
wthr N

NB. too long on Windows hhr 1 f1 55          NB. queued job stress test

N = 1 T.''
wthr N

NB. too long on Windows hhr 1 f1 60          NB. queued job stress test

N = 1 T.''
wthr N

0 f2 N2          NB. run in master thread

N = 1 T.''
wthr N

1 f2 N2          NB. queued job

N = 1 T.''
wthr N

'domain error' -: ". etx '0 t. ($0)'
'domain error' -: ". etx '+ t. 0'
'domain error' -: ". etx '+ t. 1'
'domain error' -: ". etx '+ t. ''abc'''
'domain error' -: ". etx '+ t. (<0)'
'domain error' -: ". etx '+ t. (''worker'';''abc'')'
'domain error' -: ". etx '+ t. (''worker'';''worker'')'
'domain error' -: ". etx '+ t. ((''worker'';0),&< (''worker'';0))'
'domain error' -: ". etx '+ t. (<''worker'';2)'
> ] t. (($0);'worker') 1

4!:55 ;:'N N1 N2 f f1 f2 g g1 wthr'

epilog''

