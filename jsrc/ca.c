/* Copyright (c) 1990-2024, Jsoftware Inc.  All rights reserved.           */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Conjunctions: Atop and Ampersand                                        */

#include "j.h"

// <.@ >.@ and the like, monad 
static DF1(jtonf1){PROLOG(0021);DECLFG;A z;I flag=sv->flag,m=jt->xmode;
 PREF1(jtonf1);
 if(primitive(gs))if(flag&VFLR)jt->xmode=XMFLR; else if(flag&VCEIL)jt->xmode=XMCEIL;  // scaf avoid repeated primitive calls inside rank
 if(RAT&AT(w))RZ(w=pcvt(XNUM,w));
 RZ(z=CALL1(f1,CALL1(g1,w,gs),fs));
 jt->xmode=m;
 EPILOG(z);
}

// <.@ >.@ and the like, dyad 
static DF2(jtuponf2){PROLOG(0022);DECLFG;A z;I flag=sv->flag,m=jt->xmode;
 ARGCHK2(a,w);
 if(primitive(gs))if(flag&VFLR)jt->xmode=XMFLR; else if(flag&VCEIL)jt->xmode=XMCEIL;  // scaf avoid repeated primitive calls inside rank
 if(RAT&AT(a))RZ(a=pcvt(XNUM,a));
 if(RAT&AT(w))RZ(w=pcvt(XNUM,w));
 RZ(z=INT&AT(a)&AT(w)&&FAV(gs)->id==CDIV?intdiv(a,w):CALL1(f1,CALL2(g2,a,w,gs),fs));
 jt->xmode=m;
 EPILOG(z);
}

static X jtxmodpow(J jt,A a,A w,A h){A ox,z;
 if(!(XNUM&AT(a)))RZ(a=cvt(XNUM,a));
 if(!(XNUM&AT(w)))RZ(w=cvt(XNUM,w));
 if(!(XNUM&AT(h)))RZ(h=cvt(XNUM,h));
 ox=jt->xmod; jt->xmod=h;
 GAT0(z,XNUM,1,0); XAV(z)[0]=xpow(XAV(a)[0],XAV(w)[0]);
 jt->xmod=ox;
 RNE(z);
}

#define DMOD 46340         /* <. %: _1+2^31 */

#if SY_64
#define XMOD 3037000499    /* <. %: _1+2^63 */
#define doubletype unsigned __int128
#else
#define XMOD 94906265      /* <. %: _1+2^53 */
#define doubletype uint64_t
static I dmodpow(D x,I n,D m){D z=1; while(n){if(1&n)z=fmod(z*x,m); x=fmod(x*x,m); n>>=1;} R(I)z;}
#endif

// m&|x^n by repeated squaring.  m>0, 0<=x<m<%:IMAX.  We expect large powers so we take the reciprocal of m
// mrecip is 2^64/m
static UI imodpow(UI x,I n,UI m,UI mrecip){
 if(unlikely(m==1))R 0; UI z=1; // if n=0 result is 1 unless m=1, then 0
#define modm(x) ({UI t; doubletype tt; tt=(doubletype)(x)*(doubletype)mrecip; t=tt>>BW; t=(x)-t*m; if(unlikely(t>=m))t-=m; t;})
 // x%m using mrecip.  x*mrecip is truncated, which gives the remainder.  mrecip may be 2^-64 low, so the remainder may be x*m/2^64 high, i. e. m^3/2^64.  This is never more than m too high, so a single correction suffices
 // we expect the correction to be rare so we use a branch
// #define modm(x) (x)%m
 while(n){UI zz=z*x; zz=modm(zz); x=x*x; x=modm(x); z=n&1?zz:z; n>>=1;}  //  repeated square/mod
 R z;
}
static DF2(jtmodpow2){A h;B b,c;I m,n,x,z;
 h=FAV(self)->fgh[2]; 
 if(unlikely(((AT(a)|AT(w))&(NOUN&~(INT+XNUM)))!=0)){  // convert any non-INT arg to INT if it can be done exactly
  if(RAT&AT(a))RZ(a=pcvt(XNUM,a)) else if(!(AT(a)&INT+XNUM))RZ(a=pcvt(INT,a)); 
  if(RAT&AT(w))RZ(w=pcvt(XNUM,w)) else if(!(AT(w)&INT+XNUM))RZ(w=pcvt(INT,w));
  if(((AT(a)|AT(w))&(NOUN&~(INT+XNUM)))!=0)R residue(h,expn2(a,w));  // if not (both args INT and power positive) revert to long form
 }
 // both args are integral, but possibly extended
 PREF2(jtmodpow2);
 if(((AT(h)|AT(a)|AT(w))&XNUM)&&!((AT(a)|AT(w))&(NOUN&~(XNUM+INT)))){A z;  // if all values are integral and one is XNUM, process as extended
  z=xmodpow(a,w,h); if(!jt->jerr)R z; RESETERR; R residue(h,expn2(a,w)); 
 }
 // all values are INT
 n=AV(w)[0];
 if(unlikely(n<0))R residue(h,expn2(a,w));  // if negative exponent revert to long form
 m=AV(h)[0]; x=AV(a)[0];  // m=modulus, x=base
 if(unlikely(!m))R expn2(a,w);   // if 0 divisor, same as infinite modulus
 if(b=0>m)m=-m; if(c=0>x)x=(I)(0-(UI)x);  // b=m neg, c=x neg; take abs of m and x (might be IMIN)
 if(((I)(XMOD-(UI)m)|x)<0)R cvt(INT,xmodpow(a,w,h));  // if m>XMOD, or x=IMIN, revert to extended calculation but convert result back to INT
 if(unlikely(x>=m))x=x%m;  // bring x in range if needed
 if(c)x=m-x;  // if x was neg, correct modulus to modular negative
#if SY_64
 z=imodpow(x,n,m,FAV(self)->localuse.lu1.mrecip);
#else
 z=m>DMOD?dmodpow((D)x,n,(D)m):imodpow(x,n,m,FAV(self)->localuse.lu1.mrecip);
#endif
 R sc(z-((-b)&m));  // if m neg, move result to range -m..-1
}    /* a m&|@^ w ; m guaranteed to be INT or XNUM */

static DF1(jtmodpow1){A g=FAV(self)->fgh[1]; R rank2ex0(FAV(g)->fgh[0],w,self,jtmodpow2);}  // m must be an atom; I think n can have shape.  But we treat w as atomic
     /* m&|@(n&^) w ; m guaranteed to be INT or XNUM */

// #@> y
static DF1(jttallyatopopen){F1PREFIP; A z; ARGCHK1(w); I an=AN(w); GATV(z,INT,an,AR(w),AS(w)) I *zv=IAV(z);
 if(likely(AT(w)&BOX)){A *wv=AAV(w); DO(an, A wc=C(wv[i]); I ic; SETIC(wc,ic); zv[i]=ic;)}
 else{mvc(an*SZI, zv, SZI, (iotavec-IOTAVECBEGIN+1));}
 RETF(z);
}


// u@v and u@:v
FORK1(on1cell,0x160)
DF1(on1){PREF1(on1cell); R on1cell(jt,w,self);}  // pass inplaceability through

FORK2(jtupon2cell,0x1c0)
DF2(jtupon2){PREF2(jtupon2cell); R jtupon2cell(jt,a,w,self);}  // pass inplaceability through

// special case for rank 0.  Transfer to loop.  
// if there is only one cell, process it through on1, which understands this type
static DF1(jton10){R jtrank1ex0(jt,w,self,on1cell);}  // pass inplaceability through
static DF2(jtupon20){R jtrank2ex0(jt,a,w,self,jtupon2cell);}  // pass inplaceability through
// these versions are called for f@atomic; they warn if executed on more than one atom
static DF1(jton10atom){F1PREFIP; if(unlikely(AN(w)>1&&JT(jt,deprecct)!=0))RZ(jtdeprecmsg(jt,5,"(005) f@atomic executed on multiple cells; use f\"0@:atomic (or f@:atomic if f has 0 rank)\n")); R jtrank1ex0(jt,w,self,on1cell);}  // pass inplaceability through
static DF2(jtupon20atom){F2PREFIP; if(unlikely((AN(a)|AN(w))>1&&JT(jt,deprecct)!=0))RZ(jtdeprecmsg(jt,6,"(006) f@atomic executed on multiple cells; use f\"0@:atomic (or f@:atomic if f has 0 rank)\n")); R jtrank2ex0(jt,a,w,self,jtupon2cell);}  // pass inplaceability through

// special lightweight case for u@[ and u@].
static DF1(onright1){F1PREFIP; R (FAV(FAV(self)->fgh[0])->valencefns[0])(jtinplace,w,FAV(self)->fgh[0],FAV(self)->fgh[0]);}  // pass straight through.  All we do here is set self.  Leave inplaceability unchanged
static DF2(onleft2){F2PREFIP; R (FAV(FAV(self)->fgh[0])->valencefns[0])((J)(((I)jtinplace&~(JTINPLACEA+JTINPLACEW))+(((I)jtinplace>>(JTINPLACEAX-JTINPLACEWX))&(JTINPLACEA>>(JTINPLACEAX-JTINPLACEWX)))),a,FAV(self)->fgh[0],FAV(self)->fgh[0]);}  // move inplaceable a to w
static DF2(onright2){F2PREFIP; R (FAV(FAV(self)->fgh[0])->valencefns[0])((J)((I)jtinplace&~JTINPLACEA),w,FAV(self)->fgh[0],FAV(self)->fgh[0]);}  // keep inplaceable w

// u@n
static DF1(onconst1){DECLFG;R CALL1(f1,gs,fs);}
static DF2(onconst2){DECLFG;R CALL1(f1,gs,fs);}


// x u&v y
FORK2(on2cell,0x148)

static DF2(on2){PREF2(on2cell); R on2cell(jt,a,w,self);}

static DF2(on20){R jtrank2ex0(jt,a,w,self,on2cell);}  // pass inplaceability through

// handler for comparison compounds including ones that go through i.
// We have to look at the ranks to decide what function to execute or whether to revert
DF2(atcomp){A z;AF f;
 ARGCHK2(a,w);
 // call analysis routine with the arguments.  Low 2 bits of return are postprocessing flags
 f=atcompf(a,w,self);
 I postflags=(I)f&3;  // extract postprocessing from return
#if !defined(__wasm__)
 f=(AF)((I)f&-4);    // restore function address
#else
 f=(AF)(((UI)f)>>2);    // restore function address
#endif
 // If the compound includes CT, apply it
 PUSHCCTIF(FAV(self)->localuse.lu1.cct,FAV(self)->localuse.lu1.cct!=0.0)
 if(f!=0){
  // a suitable processing function was found apply it
  z=f(jt,a,w,self);
  // postprocessing needed: 0x=none, 10=+./ (result is binary 0 if search completed), 11=*./ (result is binary 1 if search completed)
  if(likely(z!=0)){if(postflags&2){z=num((IAV(z)[0]!=AN(AR(a)>=AR(w)?a:w))^(postflags&1));}}
 }else z=(FAV(self)->fgh[2]?jtfolk2:jtupon2)(jt,a,w,self);   // revert if can't use special code
 POPCCT
 RETF(z);
}

// The combining modifiers keep track of some flags used by partitions and Result Assembly.
//
// VF2BOXATOP? in the verb V means that V ends with <@(f) or <@:(f) and thus produces a single box per execution.
// Compounds can call f directly and tell RA to supply the boxing.  If they do, they must be careful not to recognize the flag
// until it is executed at a rank that will produce a single boxed result.
//
// VF2RANKONLY? is set when V is u"r.   A sequence of these can be combined into a single rank loop for any monad and for dyads as long as the maximum number of ranks -
// two for each argument - is not exceeded.
//
// VF2RANKATOP? is set when V starts with a rank loop, perhaps with F?RANK.  The rank loop for V can be subsumed into an outer rank loop as long as the rank
// limits are not exceeded.
//
// VF2WILLOPEN indicates that monad V's first action will be opening its argument.  Knowing that the next verb in a sequence WILLOPEN, RA can produce a boxed result
// more efficiently: it need not make the result recursive, it can include a virtual block as contents without realizing them, and it can avoid EPILOG
//
// VF2WILLOPENPROP indicates that monad V's can accept a nonrecursive argument containing boxes, and it will not raise the usecount of the argument or any of its
// contents, including by executing EPILOG on them, if JTWILLBEOPENED was set on input to the verb.  Such a verb can propagate WILLOPEN status from its input to
// its output: the verb does not itself guarantee opening, but it does guarantee that if the caller promises to open, the verb will not stand in the way.
//
// VF2USESITEMCOUNT indicates that monad V's first action is RAZE; thus, WILLOPEN will also be set.  If the next verb in a sequence is USESITEMCOUNT,
// RA can perform the first step of raze processing (counting the items and checking shapes) as the items are calculated.  This will save a pass over
// tzhe items, which is valuable if the result is larger than cache.
//
// u@v
F2(jtatop){F2PREFIP;A f,g,h=0,x;AF f1=on1,f2=jtupon2;B b=0,j;C c,d,e;I flag, flag2=0,m=-1;V*av,*wv;
 ASSERTVVn(a,w);
 av=FAV(a); c=av->id;
 A z; fdefallo(z)
 if(unlikely((AT(w)&NOUN)!=0)){  // u@n
  if(c==CEXEC){  // ".@n
   // See if the argument is a string containing a single name.  If so, pass the name into the verb.
   // We can't lex a general sentence because lexing requires context to know how to treat assignments.  And,
   // there's no use for ".@const besides delayed name resolution
   // We give the w the strange flagging of NAME AND ALSO LIT - it will be handled as a name when executed, but as a string for representations
   if(AR(w)<=1 && (g=tokens(vs(w),1)) && AN(g)==1 && AT(AAV(g)[0])&NAME){w=rifvs(AAV(g)[0]); AT(w)|=LIT;}
  }
  fdeffill(z,0,CAT,VERB, onconst1,onconst2, a,w,h, VFLAGNONE, RMAX,RMAX,RMAX); R z;
 }
 wv=FAV(w); d=wv->id;
 if((d&~1)==CLEFT){
  // the very common case u@] and u@[.  Take ASGSAFE and inplaceability from u.  No IRS.
  // We must copy forwarded flags from f to f@][.  These are WILLOPEN/USESITEMCOUNT.  WILLOPEN/USESITEMCOUNT are copied from the  // monad into the monad and (A if @[, W if @])
  // BOXATOP is set if a is <
  flag2|=(c==CBOX)*(VF2BOXATOP2+VF2BOXATOP1)+(av->flag2&VF2WILLOPEN1+VF2WILLOPEN1PROP+VF2USESITEMCOUNT1)*(1+(d&1)?VF2WILLOPEN2WX/VF2WILLOPEN1:VF2WILLOPEN2AX/VF2WILLOPEN1);
  fdeffill(z,flag2,CAT,VERB, onright1,d&1?onright2:onleft2, a,w,0, (av->flag&VASGSAFE)+(av->flag&VJTFLGOK1)*((VJTFLGOK2+VJTFLGOK1)/VJTFLGOK1), RMAX,RMAX,RMAX); R z;  // scaf ra not needed on w
 }
 // Set flag with ASGSAFE status from f/g; keep INPLACE? in sync with f1,f2.  But we can turn off inplacing that is not supported by v, which may
 // save a few tests during execution and is vital for handling <@v, where we may execute v directly without going through @ and therefore mustn't inplace
 // unless v can handle it
 flag = ((av->flag&wv->flag)&VASGSAFE)+(wv->flag&(VJTFLGOK1|VJTFLGOK2));
 // special cases of u
 UI mrecip=0;  // used only for m&|@^, where it is non0
#define IDBIT(c) ((UI8)1<<((c)&0x3f))   // mask for c
#define SPECAT (IDBIT(CBOX)|IDBIT(CNOT)|IDBIT(CGRADE)|IDBIT(CSLASH)|IDBIT(CPOUND)|IDBIT(CCEIL)|IDBIT(CFLOOR)|IDBIT(CRAZE)|IDBIT(CQUERY)|IDBIT(CQRYDOT)|IDBIT(CICAP)|IDBIT(CAMP)|IDBIT(CSTAR)|IDBIT(CSLDOT)|IDBIT(CQQ)|IDBIT(CEXP))  // mask for all special cases
 if((I)(SPECAT>>(c&0x3f))&BETWEENC(c,CNOT,CQQ)){
  switch(c&0x3f){
  case CBOX&0x3f:    flag2 |= (VF2BOXATOP1|VF2BOXATOP2); break;  // mark this as <@f 
  case CNOT&0x3f:    if(d==CMATCH){f2=jtnotmatch; flag+=VIRS2; flag&=~VJTFLGOK2;} break;
  case CGRADE&0x3f:  if(d==CGRADE){f1=jtranking; flag+=VIRS1; flag&=~VJTFLGOK1;} break;
  case CSLASH&0x3f:  if(d==CCOMMA)f1=jtredravel; if(d==CDOLLAR&&FAV(av->fgh[0])->id==CSTAR)f1=jtnatoms;  // f/@, */@$
   // warn on f/@atomic.  We need atomic in both monad and dyad; we use the fact that ATOMIC1 and FLGOK1
   // are both set only in atomic primitives
   if(unlikely((wv->lrr|wv->mr|(~wv->flag&(VISATOMIC1|VJTFLGOK1)))==0))if(unlikely(JT(jt,deprecct)!=0))RZ(jtdeprecmsg(jt,8,"(008) f/@g is the same as g when g is atomic\n"));
   break;
  case CPOUND&0x3f:  f1=d==CCOMMA?jtnatoms:f1; f1=d==CDOLLAR?jtrank:f1; f1=d==COPE?jttallyatopopen:f1; break;    // #@,  #@$    #@>
  case CSTAR&0x3f:   f1=d==CPOUND?jtisitems:f1; break;  // *@#
  case CCEIL&0x3f:   f1=jtonf1; f2=jtuponf2; flag+=VCEIL; flag&=~(VJTFLGOK1|VJTFLGOK2); break;
  case CFLOOR&0x3f:  f1=jtonf1; f2=jtuponf2; flag+=VFLR; flag&=~(VJTFLGOK1|VJTFLGOK2);  break;
  case CICAP&0x3f:   if(d==CNE){f1=jtnubind; flag&=~VJTFLGOK1;} else if(FIT0(CNE,wv)){f1=jtnubind0; flag&=~VJTFLGOK1;}else if(d==CEBAR){f2=jtifbebar; flag&=~VJTFLGOK2;} break;
  case CQUERY&0x3f:  if((d&-2)==CPOUND){f2=jtrollk; flag&=~VJTFLGOK2;} break;  // # $
  case CQRYDOT&0x3f: if((d&-2)==CPOUND){f2=jtrollkx; flag&=~VJTFLGOK2;} break;  // # $
  case CRAZE&0x3f:  // detect ;@(<@(f/\));.
   if(d==CCUT&&boxatop(w)){  // w is <@g;.k
    if((((I)1)<<(wv->localuse.lu1.gercut.cutn+3))&0x36) { // fetch k (cut type); bits are 3 2 1 0 _1 _2 _3; is 1/2-cut?
     A wf=wv->fgh[0]; V *wfv=FAV(wf); A g=wfv->fgh[1]; V *gv=FAV(g);  // w is <@g;.k  find g
     if((gv->id&~(CBSLASH^CBSDOT))==CBSLASH) {  // g is gf\ or gf\.
      A gf=gv->fgh[0]; V *gfv=FAV(gf);  // find gf
      if(gfv->id==CSLASH){  // gf is gff/  .  We will analyze gff later
       f1=jtrazecut1; f2=jtrazecut2; flag&=~(VJTFLGOK1|VJTFLGOK2);
      }
     }
    }
   }
   break;
  case CSLDOT&0x3f:  if(d==CSLASH&&AT(wv->fgh[0])&VERB&&FAV(wv->fgh[0])->flag&VISATOMIC2 && CSLASH==ID(av->fgh[0])&&AT(FAV(av->fgh[0])->fgh[0])&VERB&&FAV(FAV(av->fgh[0])->fgh[0])->flag&VISATOMIC2){f2=jtpolymult; flag&=~VJTFLGOK2;} break;  // f//.@(g/) for atomic fg
  case CQQ&0x3f:     if(d==CTHORN&&CEXEC==ID(av->fgh[0])&&av->fgh[1]==num(0)){f1=jtdigits10; flag&=~VJTFLGOK1;} break;  // "."0@":
  case CEXP&0x3f:    if(d==CCIRCLE){f1=jtexppi; flag&=~VJTFLGOK1;} break;   // ^@o.
  case CAMP&0x3f: 
   x=av->fgh[0];
   if(RAT&AT(x))RZ(x=pcvt(XNUM,x));
   if((d==CEXP||d==CAMP&&CEXP==ID(wv->fgh[1]))&&AT(x)&INT+XNUM&&!AR(x)&&CSTILE==ID(av->fgh[1])){  // m&|@^ and m&|@(n&^) where m is atomic INT/XNUM
    h=x; UI m=ABS(IAV(x)[0]);
    // precalculate 2^64/m so it is there if we need it
    if(AT(x)&INT&&m>1){mrecip=((UI)IMIN/m); mrecip=(mrecip<<1)+((((UI)IMIN-mrecip*m)<<1)>=m);}  // 2^64%m, possibly low by as much as 2^-64
    if(d==CEXP){f2=jtmodpow2; flag&=~VJTFLGOK2;} else{f1=jtmodpow1; flag&=~VJTFLGOK1;}
   }
  }
 }
 // special cases of v
 // comparison combinations
 // we calculate m for the combining operator: i.&0 (0), i.&1 (1), i:&0 (2), i:&1 (3),, +/ (4), +,/ (5), *./ (6)  [formerly I. was 7]
 // m is (u char code + n)&7 where n is 0, but 1 in i&1 types.  We set n to -1 if there is no comparison operator
 // cd comes from the comparison operator, here only E. (6) e.[!.n] (7)
 // comparison flag is cd+8*m
 C cd; D cct;  // local copy of id of w;  cct for comparison combination, 0=use default
 if(unlikely(d==CFIT)){cct=FAV(wv->fgh[0])->localuse.lu1.cct; cd=FAV(wv->fgh[0])->id;}else{cct=0.0; cd=d;}
 if(unlikely((cd&~1)==CEBAR)){I n=-1;
// obsolete  if(((d&~1)==CEBAR)||(d==CFIT&&(cct=FAV(wv->fgh[0])->localuse.lu1.cct,cd=FAV(wv->fgh[0])->id)==CEPS)){I n=-1;
  I cb=0;  // will be the id of the combining operator
  if(c==CSLASH){cb=FAV(av->fgh[0])->id; n=BETWEENC(cb,CPLUS,CSTARDOT)?0:n; cb+=1;}  // +/@ set cb to id of + +. *., plus 1 to match code for combining op
  else if(c==CAMP){cb=FAV(av->fgh[0])->id; A cr=av->fgh[1]; cr=(cb&~2)==CIOTA?cr:0; n=cr==num(0)?0:n; n=cr==num(1)?1:n;} // i.&0  already has combining op, set n if 0 or 1
  f2=n>=0?atcomp:f2;  // if valid comparison type, switch to it
  flag+=((6+(cd&1))+8*((cb+n)&7))&REPSGN(~n); flag&=REPSGN(n)|~VJTFLGOK2;  // only if n>=0, set comp type & clear FLGOK2
 }

 if(unlikely(d==COPE))if(!(flag2&VF2BOXATOP1))flag2|=VF2ATOPOPEN1;  // @>, but not <@> which would be confused with &.>
 if(unlikely(d==CCOMMA))if(av->valencefns[0]==jtisitems)f1=jtisnotempty;  // *@#@,

 // Copy the open/raze status from v into u@v (PROP/ITEMCOUNT valid only if v has infinite rank, because otherwise there might be result assembly;
 // but v will never have those flags set if it doesn't have infinite rank)
 flag2 |= wv->flag2&(VF2WILLOPEN1|VF2WILLOPEN2W|VF2WILLOPEN2A|VF2USESITEMCOUNT1|VF2USESITEMCOUNT2W|VF2USESITEMCOUNT2A);
 // If v propagates OPEN status, copy from av
 flag2|=((wv->flag2&(VF2WILLOPEN1PROP|VF2WILLOPEN2WPROP|VF2WILLOPEN2APROP))&REPSGN(SGNIF(av->flag2,VF2WILLOPEN1X)))<<(VF2WILLOPEN1X-VF2WILLOPEN1PROPX);
 // if u and v both propagate, the compound does so also
 flag2|=((wv->flag2&(VF2WILLOPEN1PROP|VF2WILLOPEN2WPROP|VF2WILLOPEN2APROP))&REPSGN(SGNIF(av->flag2,VF2WILLOPEN1PROPX)));

 // Install the flags to indicate that this function starts out with a rank loop, and thus can be subsumed into a higher rank loop
 // If the compound has rank 0, switch to the loop for that; if rank is infinite, avoid the loop; if v is atomic, switch to the loop that gives a msg if executed on non-atom
 if(likely(f1==on1)){flag2|=VF2RANKATOP1; f1=wv->mr==0?jton10:f1; f1=wv->flag&VISATOMIC1?jton10atom:f1; f1=wv->mr==RMAX?on1cell:f1;}
 if(likely(f2==jtupon2)){flag2|=VF2RANKATOP2; f2=wv->lrr==0?jtupon20:f2; f2=wv->flag&VISATOMIC2?jtupon20atom:f2; f2=wv->lrr==(UI)R2MAX?jtupon2cell:f2;}
 fdeffillall(z,flag2,CAT,VERB, f1,f2, a,w,h, flag, (I)wv->mr,(I)lrv(wv),rrv(wv),fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.cct=cct);
 if(unlikely(mrecip!=0))FAV(z)->localuse.lu1.mrecip=mrecip;   // replace cct with mrecip if it is defined
 R z;
}

// u@:v
F2(jtatco){F2PREFIP;A f,g;AF f1=on1cell,f2=jtupon2cell;C c,d,e;I flag, flag2=0,m=-1;V*av,*wv;
 ASSERTVV(a,w);
 av=FAV(a); c=av->id; f=av->fgh[0]; g=av->fgh[1]; e=ID(f);   /// c=op for a, d=op for w   if a is compound r m [s], f is r and e is its id; and g is s
 wv=FAV(w); d=wv->id;
 A z; fdefallo(z)
 if((d&~1)==CLEFT){
  // the very common case u@:] and u@:[.  Take ASGSAFE and inplaceability from u.  No IRS.
  // We must copy forwarded flags from f to f@][.  These are WILLOPEN/USESITEMCOUNT.  WILLOPEN/USESITEMCOUNT are copied from the monad into the monad and (A if @[, W if @])
  // BOXATOP is set if a is <
  flag2|=(c==CBOX)*(VF2BOXATOP2+VF2BOXATOP1)+(av->flag2&VF2WILLOPEN1+VF2WILLOPEN1PROP+VF2USESITEMCOUNT1)*(1+(d&1)?VF2WILLOPEN2WX/VF2WILLOPEN1:VF2WILLOPEN2AX/VF2WILLOPEN1);
  fdeffill(z,flag2,CATCO,VERB, onright1,d&1?onright2:onleft2, a,w,0, (av->flag&VASGSAFE)+(av->flag&VJTFLGOK1)*((VJTFLGOK2+VJTFLGOK1)/VJTFLGOK1), RMAX,RMAX,RMAX); R z;  // must go through onright1 to set self
 }
 // Set flag with ASGSAFE status from f/g; keep INPLACE? in sync with f1,f2.  But we can turn off inplacing that is not supported by v, which may
 // save a few tests during execution and is vital for handling <@v, where we may execute v directly without going through @ and therefore mustn't inplace
 // unless v can handle it
 flag = ((av->flag&wv->flag)&VASGSAFE)+(wv->flag&(VJTFLGOK1|VJTFLGOK2));
#define SPECATCO (IDBIT(CEXP)|IDBIT(CBOX)|IDBIT(CGRADE)|IDBIT(CSLASH)|IDBIT(CPOUND)|IDBIT(CCEIL)|IDBIT(CFLOOR)|IDBIT(CSEMICO)|IDBIT(CNOT)|IDBIT(CQUERY)|IDBIT(CQRYDOT)|IDBIT(CICAP)|IDBIT(CAMP)|IDBIT(CSTAR))  // mask for all special cases
 if(unlikely((I)(SPECATCO>>(c&0x3f))&BETWEENC(c,CNOT,CPOUND))){
  switch(c&0x3f){
  case CBOX&0x3f:    flag2 |= (VF2BOXATOP1|VF2BOXATOP2); break;  // mark this as <@f
#if SLEEF && (C_AVX2 || EMU_AVX2)
  case CEXP&0x3f:    if(d==CPOLY){f2=jtpoly2; flag+=VIRS2+(VFATOPPOLYEXP<<VFATOPPOLYX);} break;   // ^@:p.
#endif
  case CNOT&0x3f:    if(d==CMATCH){f2=jtnotmatch; flag+=VIRS2; flag&=~VJTFLGOK2;} break;  // x -.@:-: y
  case CGRADE&0x3f:  if(d==CGRADE){f1=jtranking; flag+=VIRS1; flag&=~VJTFLGOK1;} break;  // /:@:/: y
  case CCEIL&0x3f:   f1=jtonf1; f2=jtuponf2; flag=VCEIL; flag&=~(VJTFLGOK1|VJTFLGOK2); break;  // [x] >.@:g y
  case CFLOOR&0x3f:  f1=jtonf1; f2=jtuponf2; flag=VFLR; flag&=~(VJTFLGOK1|VJTFLGOK2); break;  // [x] <.@:g y
  case CQUERY&0x3f:  if((d&~1)==CPOUND){f2=jtrollk; flag&=~VJTFLGOK2;}  break;  // x ?@:# y or x ?@:$ y
  case CQRYDOT&0x3f: if((d&~1)==CPOUND){f2=jtrollkx; flag&=~VJTFLGOK2;} break;  // x ?.@:# y or x ?.@:$ y
  case CICAP&0x3f:   if(d==CNE){f1=jtnubind; flag&=~VJTFLGOK1;} else if(FIT0(CNE,wv)){f1=jtnubind0; flag&=~VJTFLGOK1;}else if(d==CEBAR){f2=jtifbebar; flag&=~VJTFLGOK2;} break;  // I.@:~: y  I.@:(~:!.0) y  x I.@:E. y
  case CAMP&0x3f:    {m=(e&~2)==CIOTA?e:m; I j=-1; j=g==num(0)?0:j;  j=g==num(1)?1:j; m|=j; break;}   // i.@0/1@:g    i:@0/1@:g
  case CSLASH&0x3f:  //  f/@:g where f is not a gerund
   if(FAV(f)->flag&FAV(w)->flag&VISATOMIC2){f2=jtfslashatg;}  // f/@:g when f and g are both atomic
   if(d==CCOMMA){f1=jtredravel;}
   else if(d==CDOLLAR&&FAV(av->fgh[0])->id==CSTAR){f1=jtnatoms;}
   else {e+=1; m=BETWEENC(e,CPLUS+1,CSTARDOT+1)?e:m;}  // +/@: +./@: */.*   m holds combination op, or -1 if no comparison
   break;
  case CPOUND&0x3f:  if(d==CCOMMA)f1=jtnatoms; if(d==CDOLLAR)f1=jtrank; break; //  #@:,
  case CSTAR&0x3f:   if(d==CPOUND)f1=jtisitems; break;  // *@:#
  case CSEMICO&0x3f:  // u@:(v;.k)
   if(d==CCUT){I j;
    j=wv->localuse.lu1.gercut.cutn;   // cut type, valid EXCEPT for <;.0 which is detected by function:
    if(wv->valencefns[1]==jtboxcut0){f2=jtrazecut0; flag&=~VJTFLGOK2;}  // detect ;@:(<;.0), used for substring extraction
    else if(boxatop(w)){  // w is <@g;.j   detect ;@:(<@(f/\);._2 _1 1 2
     if((((I)1)<<(j+3))&0x36) { // fbits are 3 2 1 0 _1 _2 _3; is 1/2-cut?
      A wf=wv->fgh[0]; V *wfv=FAV(wf); A g=wfv->fgh[1]; V *gv=FAV(g);  // w is <@g;.k  find g
      if((gv->id&~(CBSLASH^CBSDOT))==CBSLASH) {  // g is gf\ or gf\.
       A gf=gv->fgh[0]; V *gfv=FAV(gf);  // find gf
       if(gfv->id==CSLASH){  // gf is gff/  .  We will analyze gff later
        f1=jtrazecut1; f2=jtrazecut2; flag&=~(VJTFLGOK1|VJTFLGOK2);
       }
      }
     }
    }
   }
  }
 }
// e has been destroyed

 // comparison combinations
 D cct=0.0;  // cct to use, 0='use default'
 if(unlikely(0<=m)){
  // the left side is a comparison combiner.  See if the right is a comparison
  e=d;  // repurpose e as comparison op
  e=d==CFIT&&(cct=wv->localuse.lu1.cct,1)?FAV(wv->fgh[0])->id:e;  // e is the comparison op
  if(BETWEENC(e,CEQ,CEPS)){
   // valid comparison combination.  m is the combiner, e is the comparison
   f2=atcomp;  // if valid comparison type, switch to it
   flag+=(e-CEQ)+8*(m&7); flag&=~VJTFLGOK2;  // set comp type & clear FLGOK2
  }
 }

 // Copy the open/raze status from v into u@v
 flag2 |= wv->flag2&(VF2WILLOPEN1|VF2WILLOPEN2W|VF2WILLOPEN2A|VF2USESITEMCOUNT1|VF2USESITEMCOUNT2W|VF2USESITEMCOUNT2A);
 // If v propagates OPEN status, copy from av
 flag2|=((wv->flag2&(VF2WILLOPEN1PROP|VF2WILLOPEN2WPROP|VF2WILLOPEN2APROP))&REPSGN(SGNIF(av->flag2,VF2WILLOPEN1X)))<<(VF2WILLOPEN1X-VF2WILLOPEN1PROPX);
 // if u and v both propagate, the compound does so also
 flag2|=(wv->flag2&(VF2WILLOPEN1PROP|VF2WILLOPEN2WPROP|VF2WILLOPEN2APROP))&REPSGN(SGNIF(av->flag2,VF2WILLOPEN1PROPX));

 fdeffillall(z,flag2,CATCO,VERB, f1,f2, a,w,0L, flag, RMAX,RMAX,RMAX,fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.cct=cct); R z;
}

// u&:v
F2(jtampco){F2PREFIP;AF f1=on1cell,f2=on2cell;C c,d;I flag,flag2=0,linktype=0;V*wv;
 ASSERTVV(a,w);
 A z; fdefallo(z)
 c=FAV(a)->id; wv=FAV(w); d=wv->id;  // c=pseudochar for u, d=pseudochar for v
 // Set flag wfith ASGSAFE status from f/g; keep INPLACE? in sync with f1,f2.  Inplace only if monad v can handle it
 flag = ((FAV(a)->flag&wv->flag)&VASGSAFE)+((wv->flag&VJTFLGOK1)*((VJTFLGOK2+VJTFLGOK1)/VJTFLGOK1));
 if(unlikely(c==CBOX)){flag2 |= VF2BOXATOP1;}  // mark this as <@f - monad only
 else if(unlikely(BOTHEQ8(c,d,CSLASH,CCOMMA))){f1=jtredravel;}    // f/&:, y
 else if(unlikely(BOTHEQ8(c,d,CRAZE,CCUT)))if(boxatop(w)){  // w is <@g;.k    detect ;&:(<@(f/\));._2 _1 1 2 y
  if((((I)1)<<(wv->localuse.lu1.gercut.cutn+3))&0x36) { // fetch k (cut type); bits are 3 2 1 0 _1 _2 _3; is 1/2-cut?
   A wf=wv->fgh[0]; V *wfv=FAV(wf); A g=wfv->fgh[1]; V *gv=FAV(g);  // w is <@g;.k  find g
   if((gv->id&~(CBSLASH^CBSDOT))==CBSLASH) {  // g is gf\ or gf\.
    A gf=gv->fgh[0]; V *gfv=FAV(gf);  // find gf
    if(gfv->id==CSLASH){  // gf is gff/  .  We will analyze gff later
     f1=jtrazecut1; flag&=~(VJTFLGOK1);
    }
   }
  }
 }
 else if(unlikely(BOTHEQ8(c,d,CGRADE,CGRADE))){f1=jtranking;  flag&=~VJTFLGOK1;flag+=VIRS1;}  // /:&:/: monad
 else if(unlikely(BOTHEQ8(c,d,CCOMMA,CBOX))){f2=jtjlink; linktype=ACINPLACE;}  // x ,&< y   supports IP 

 // Copy the monad open/raze status from v into u&:v
 flag2 |= wv->flag2&(VF2WILLOPEN1|VF2USESITEMCOUNT1);

 // Install the flags to indicate that this function starts out with a rank loop, and thus can be subsumed into a higher rank loop
 flag2|=(f1==on1cell)<<VF2RANKATOP1X;  flag2|=VF2RANKATOP2; 
 fdeffillall(z,flag2,CAMPCO,VERB, f1,f2, a,w,0L, flag, RMAX,RMAX,RMAX,fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.linkvb=linktype) R z;
}

// m&v and u&n.  Never inplace the noun argument, since the verb may
// be repeated; preserve the inplacing of the argument given (i. e. move w to a for u&n).  Bit 1 of jtinplace is always 0 for monad.
// We marked the derived verb inplaceable only if the dyad of u/v was inplaceable
// This supports IRS so that it can pass the rank on to the called function; no need to revalidate here
// We pass the WILLOPEN flags through
static DF1(withl){F1PREFIP;DECLFG; A z; I r=(RANKT)jt->ranks; IRSIP2(fs,w,gs,RMAX,(RANKT)jt->ranks,g2,z); RETF(z);}
static DF1(withr){F1PREFIP;DECLFG; jtinplace=(J)(intptr_t)((I)jtinplace+((I)jtinplace&JTINPLACEW)); A z; I r=(RANKT)jt->ranks; IRSIP2(w,gs,fs,(RANKT)jt->ranks,RMAX,f2,z); RETF(z);}

// Here for m&i. and m&i:, computing a prehashed table from a.  Make sure we use the precision in effect when the hash was made
// v->fgh[2] is the info/hash/bytemask result from calculating the prehash
static DF1(ixfixedleft){V*v=FAV(self); PUSHCCT(v->localuse.lu1.cct) A z=indexofprehashed(v->fgh[0],w,v->fgh[2]); POPCCT R z;}  // must use the ct when table was created
// Here for compounds like (i.&0@:e.)&n  e.&n -.&n that compute a prehashed table from w
static DF1(ixfixedright){V*v=FAV(self); PUSHCCT(v->localuse.lu1.cct) A z=indexofprehashed(v->fgh[1],w,v->fgh[2]); POPCCT R z;}


static DF2(with2){A z; R df1(z,w,powop(self,a,0));}

// u&v
F2(jtamp){F2PREFIP;A h=0;AF f1,f2;B b;C c;I flag,flag2=0,linktype=0,mode=-1,p,r;V*v;
 ARGCHK2(a,w);
 D cct;  // cct that was used for this comparison compound, if any
 A z; fdefallo(z)
#if 1
 if(AT(a)&AT(w)&VERB){
  // u&v
  f1=on1; f2=on2;
  v=FAV(w); c=v->id; r=v->mr;   // c=pseudochar for v; overall rank is monad rank of v
  // Set flag with ASGSAFE status from f/g; keep INPLACE? in sync with f1,f2.  To save tests later, inplace only if monad v can handle it
  flag = ((FAV(a)->flag&v->flag)&VASGSAFE)+((v->flag&VJTFLGOK1)*((VJTFLGOK2+VJTFLGOK1)/VJTFLGOK1));
  if(unlikely((c&~(CFORK^CAMP))==CFORK)){C d=CLEFT;  // u&(FORK/&)
   if(c==CFORK)d=ID(v->fgh[2]);  // d is CLEFT if &, 0 if capped fork, otherwise from h of fork
   if(CIOTA==FAV(v->fgh[1])->id&&(d&~1)==CLEFT&&equ(ds(CALP),v->fgh[0])){  // (FORK/&) is a.&i. or (a. i. ][)
    d=FAV(a)->id;
    if(BETWEENC(d,CEQ,CGT)){f2=jtcharfn2; flag&=~VJTFLGOK2;}  // any comparison - comp&(a.&i. or (a. i. ][))
   }
  }
  // the special cases, except for ,&<, are very rare because it is idiomatic to use @ for monads
#define SPECAND (IDBIT(CCOMMA)|IDBIT(CBOX)|IDBIT(CGRADE)|IDBIT(CSLASH)|IDBIT(CPOUND)|IDBIT(CCEIL)|IDBIT(CFLOOR)|IDBIT(CRAZE))  // mask for all special cases
  if(unlikely((I)(SPECAND>>(c&0x3f))&BETWEENC(c,CCOMMA,CPOUND))){
   if(unlikely(BOTHEQ8(FAV(a)->id,c,CCOMMA,CBOX))){f2=jtjlink; linktype=ACINPLACE;}  // x ,&< y   supports IP 
   else switch(FAV(a)->id&0x3f){
// obsolete    case CCOMMA: if(c==CBOX){f2=jtjlink; linktype=ACINPLACE;} break;  // x ,&< y   supports IP 
   case CBOX&0x3f:   flag |= VF2BOXATOP1; break;  // <&u mark this as <@f for the monad
   case CGRADE&0x3f: if(c==CGRADE){f1=jtranking; flag+=VIRS1; flag&=~VJTFLGOK1;} break;  // /:&/: y
   case CSLASH&0x3f: if(c==CCOMMA){f1=jtredravel; } break;   // f/&, y
   case CPOUND&0x3f: f1=c==COPE?jttallyatopopen:f1; break;    //  #&>
   case CCEIL&0x3f:  f1=jtonf1; flag+=VCEIL; flag&=~VJTFLGOK1; break;  // >.&g
   case CFLOOR&0x3f: f1=jtonf1; flag+=VFLR; flag&=~VJTFLGOK1; break;   // <.&g
   case CRAZE&0x3f:  // detect ;&(<@(f/\));.
    if(c==CCUT&&boxatop(w)){  // w is <@g;.k
     if((((I)1)<<(v->localuse.lu1.gercut.cutn+3))&0x36) { // fetch k (cut type); bits are 3 2 1 0 _1 _2 _3; is 1/2-cut?
      A wf=v->fgh[0]; V *wfv=FAV(wf); A g=wfv->fgh[1]; V *gv=FAV(g);  // w is <@g;.k  find g
      if((gv->id&~(CBSLASH^CBSDOT))==CBSLASH) {  // g is gf\ or gf\.
       A gf=gv->fgh[0]; V *gfv=FAV(gf);  // find gf
       if(gfv->id==CSLASH){  // gf is gff/  .  We will analyze gff later
        f1=jtrazecut1; flag&=~(VJTFLGOK1);
       }
      }
     }
    }
    break;
   }
  }

  if(c==COPE)flag2|=flag2&VF2BOXATOP1?VF2ATOPOPEN2A|VF2ATOPOPEN2W:VF2ATOPOPEN1|VF2ATOPOPEN2A|VF2ATOPOPEN2W;  // &>, but not <&> which would be confused with &.>

  flag2 |= v->flag2&(VF2WILLOPEN1|VF2USESITEMCOUNT1);  // Copy the monad open/raze status from v into u&v

  // Install the flags to indicate that this function starts out with a rank loop, and thus can be subsumed into a higher rank loop
  // If the compound has rank 0, switch to the loop for that; if infinite rank, avoid the loop
  // Even though we don't test for infinite, allow this node to be flagged as rankloop so it can combine with others
  if(likely(f1==on1)){flag2|=VF2RANKATOP1; f1=r==RMAX?on1cell:f1; f1=r==0?jton10:f1;}
  if(likely(f2==on2)){flag2|=VF2RANKATOP2; f2=r==RMAX?on2cell:f2; f2=r==0?on20:f2;}
  fdeffillall(z,flag2,CAMP,VERB, f1,f2, a,w,0L, flag, r,r,r,fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.linkvb=linktype);
  R z;
 }else ASSERT((AT(a)|AT(w))&VERB,EVDOMAIN)  // m&n not allowed
  // continuing must be m&v or u&n
  A va=AT(a)&VERB?a:w, na=AT(a)&VERB?w:a;
  f1=AT(a)&VERB?withr:withl; I visa=AT(a)&VERB?~2:0; c=FAV(va)->id;  // visa is ~2 if a is verb, 0 if w
  // set flag according to ASGSAFE of verb, and INPLACE and IRS from the dyad of the verb
  p=FAV(va)->flag; flag=((p&(VJTFLGOK2|VIRS2))>>1)+(FAV(va)->flag&VASGSAFE);
  // the noun will be INCORPed by fdef

  // look for supported forms: comparison, i.-family, 128!:3.  But not if the arg is atomic or empty - no value in that
  if((-AN(na)&-AR(na))<0){  // noun is not atomic and not empty
   if(unlikely(b=c==CFIT)){c=FAV(FAV(va)->fgh[0])->id; p=FAV(FAV(va)->fgh[0])->flag;}  // if verb is u1!.n1, replace the id and flag with that of u1, and remember cct from n1
   // check the supported cases one by one
   if(unlikely((c&(visa^~2))==CIOTA)){  // m&i.   m&i:
    PUSHCCTIF(FAV(va)->localuse.lu1.cct,b) h=indexofsub(IIDOT+((c&(CIOTA^CICO))>>1),a,mark); cct=jt->cct; POPCCT f1=ixfixedleft; flag&=~VJTFLGOK1; RZ(h)  // m&i[.:][!.f], and remember cct when we created the table
   }else if(unlikely(visa==((7^~2)^(p&7)))){  // e.-compound&n  p=7 & a is verb
    mode=((II0EPS-1+((p&VFCOMPCOMP)>>3))&0xf)+1;  // e.-compound&n including e. -. ([ -. -.) or any i.&1@:e.  - LESS/INTER not in 32-bit
    if(mode==IINTER){cct=FAV(va)->localuse.lu1.cct; b=cct!=0;}  // ([-.-.) always has cct, but it might be 0 indicating default
    {PUSHCCTIF(FAV(va)->localuse.lu1.cct,b) h=indexofsub(mode,w,mark); cct=jt->cct; POPCCT f1=ixfixedright; flag&=~VJTFLGOK1; RZ(h)}  // m&i[.:][!.f], and remember cct when we created the table
   }else if(unlikely((c^visa)==CWORDS)){RZ(a=fsmvfya(a)); f1=jtfsmfx; flag&=~VJTFLGOK1;   // m&;:
   }else if(unlikely((c^visa)==CIBEAM)){if(FAV(w)->localuse.lu1.foreignmn[0]==128&&FAV(w)->localuse.lu1.foreignmn[1]==3){RZ(h=crccompile(a)); f1=jtcrcfixedleft; flag&=~VJTFLGOK1; } // m&128!:3  scaf use rtn addr
   }
  }
  fdeffillall(z,0,CAMP,VERB, f1,with2, a,w,h, flag, RMAX,RMAX,RMAX,fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.cct=cct);
  R z;
#else

 switch(CONJCASE(a,w)){
 case NV:
  f1=withl; v=FAV(w); c=v->id;
  // set flag according to ASGSAFE of verb, and INPLACE and IRS from the dyad of the verb
  flag=((v->flag&(VJTFLGOK2|VIRS2))>>1)+(v->flag&VASGSAFE);
  // a will be INCORPed by fdef

  if((-AN(a)&-AR(a))<0){  // a is not atomic and not empty
    // c holds the pseudochar for the v op.  If v is u!.0, replace c with the pseudochar for n
    // Also set b on any u!.n
   if(unlikely(b=c==CFIT))c=FAV(v->fgh[0])->id;
   if((c&~2)==CIOTA){if(b)cct=v->localuse.lu1.cct; mode=c==CIOTA?IIDOT:IICO;}
  }
  if(unlikely(0<=mode)){
   {PUSHCCTIF(cct,b) h=indexofsub(mode,a,mark); cct=jt->cct; POPCCT f1=ixfixedleft; flag&=~VJTFLGOK1; RZ(h)}  // m&i[.:][!.f], and remember cct when we created the table
  }else switch(c){
   case CWORDS: RZ(a=fsmvfya(a)); f1=jtfsmfx; flag&=~VJTFLGOK1; break;
   case CIBEAM: if(FAV(w)->localuse.lu1.foreignmn[0]==128&&FAV(w)->localuse.lu1.foreignmn[1]==3){RZ(h=crccompile(a)); f1=jtcrcfixedleft; flag&=~VJTFLGOK1;} break;
  }
  fdeffillall(z,0,CAMP,VERB, f1,with2, a,w,h, flag, RMAX,RMAX,RMAX,fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.cct=cct);
  R z;
 case VN: 
  f1=withr; v=FAV(a);
  // set flag according to ASGSAFE of verb, and INPLACE and IRS from the dyad of the verb 
  // kludge mark it not ASGSAFE in case it is a name that is being reassigned.  We could use nvr stack to check for that.
  flag=((v->flag&(VJTFLGOK2|VIRS2))>>1)+(v->flag&VASGSAFE);
  // w will be INCORPed by fdef
  if((-AN(w)&-AR(w))<0){
    // 
    // c holds the pseudochar for the v op.  If v is u!.n, replace c with the pseudochar for n
    // Also set b if the fit is !.n
    c=v->id;p=v->flag;if(unlikely(b=c==CFIT)){cct=v->localuse.lu1.cct; p=FAV(v->fgh[0])->flag;}
   if(unlikely(7==(p&7))){
    mode=((II0EPS-1+((p&VFCOMPCOMP)>>3))&0xf)+1;  // e.-compound&n including e. -. ([ -. -.) or any i.&1@:e.  - LESS/INTER not in 32-bit
    if(mode==IINTER){cct=v->localuse.lu1.cct; b=cct!=0;}  // ([-.-.) always has cct, but it might be 0 indicating default
    {PUSHCCTIF(cct,b) h=indexofsub(mode,w,mark); cct=jt->cct; POPCCT f1=ixfixedright; flag&=~VJTFLGOK1; RZ(h)}  // m&i[.:][!.f], and remember cct when we created the table
   }
  }
  fdeffillall(z,0,CAMP,VERB, f1,with2, a,w,h, flag, RMAX,RMAX,RMAX,fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.cct=cct);
  R z;
 case VV:
  // u&v
  f1=on1; f2=on2;
  v=FAV(w); c=v->id; r=v->mr;   // c=pseudochar for v
  // Set flag with ASGSAFE status from f/g; keep INPLACE? in sync with f1,f2.  To save tests later, inplace only if monad v can handle it
  flag = ((FAV(a)->flag&v->flag)&VASGSAFE)+((v->flag&VJTFLGOK1)*((VJTFLGOK2+VJTFLGOK1)/VJTFLGOK1));
  if(unlikely((c&~4)==CFORK)){C d=CLEFT;  // u&(FORK/&)
   if(c==CFORK)d=ID(v->fgh[2]);  // d is CLEFT if &, 0 if capped fork, otherwise from h of fork
   if(CIOTA==FAV(v->fgh[1])->id&&(d&~1)==CLEFT&&equ(ds(CALP),v->fgh[0])){  // (FORK/&) is a.&i. or (a. i. ][)
    d=FAV(a)->id;
    if(BETWEENC(d,CEQ,CGT)){f2=jtcharfn2; flag&=~VJTFLGOK2;}  // any comparison - comp&(a.&i. or (a. i. ][))
   }
  }
  switch(FAV(a)->id){
  case CBOX:   flag |= VF2BOXATOP1; break;  // mark this as <@f for the monad
  case CGRADE: if(c==CGRADE){f1=jtranking; flag+=VIRS1; flag&=~VJTFLGOK1;} break;  // /:&/: y
  case CSLASH: if(c==CCOMMA){f1=jtredravel; } break;   // f/&, y
  case CCOMMA: if(c==CBOX){f2=jtjlink; linktype=ACINPLACE;} break;  // x ,&< y   supports IP 
  case CPOUND: f1=c==COPE?jttallyatopopen:f1; break;    //  #&>
  case CCEIL:  f1=jtonf1; flag+=VCEIL; flag&=~VJTFLGOK1; break;  // >.&g
  case CFLOOR: f1=jtonf1; flag+=VFLR; flag&=~VJTFLGOK1; break;   // <.&g
  case CRAZE:  // detect ;@(<@(f/\));.
   if(c==CCUT&&boxatop(w)){  // w is <@g;.k
    if((((I)1)<<(v->localuse.lu1.gercut.cutn+3))&0x36) { // fetch k (cut type); bits are 3 2 1 0 _1 _2 _3; is 1/2-cut?
     A wf=v->fgh[0]; V *wfv=FAV(wf); A g=wfv->fgh[1]; V *gv=FAV(g);  // w is <@g;.k  find g
     if((gv->id&~(CBSLASH^CBSDOT))==CBSLASH) {  // g is gf\ or gf\.
      A gf=gv->fgh[0]; V *gfv=FAV(gf);  // find gf
      if(gfv->id==CSLASH){  // gf is gff/  .  We will analyze gff later
       f1=jtrazecut1; flag&=~(VJTFLGOK1);
      }
     }
    }
   }
   break;
  }
  if(c==COPE)flag2|=flag2&VF2BOXATOP1?VF2ATOPOPEN2A|VF2ATOPOPEN2W:VF2ATOPOPEN1|VF2ATOPOPEN2A|VF2ATOPOPEN2W;  // &>, but not <&> which would be confused with &.>

  // Copy the monad open/raze status from v into u&v
  flag2 |= v->flag2&(VF2WILLOPEN1|VF2USESITEMCOUNT1);

  // Install the flags to indicate that this function starts out with a rank loop, and thus can be subsumed into a higher rank loop
  // If the compound has rank 0, switch to the loop for that; if infinite rank, avoid the loop
  // Even though we don't test for infinite, allow this node to be flagged as rankloop so it can combine with others
  if(f1==on1){flag2|=VF2RANKATOP1; f1=r==RMAX?on1cell:f1; f1=r==0?jton10:f1;}
  if(f2==on2){flag2|=VF2RANKATOP2; f2=r==RMAX?on2cell:f2; f2=r==0?on20:f2;}
  fdeffillall(z,flag2,CAMP,VERB, f1,f2, a,w,0L, flag, r,r,r,fffv->localuse.lu0.cachedloc=0,FAV(z)->localuse.lu1.linkvb=linktype);
  R z;
 default: ASSERTSYS(0,"amp");
 case NN: ASSERT(0,EVDOMAIN);
 }
#endif
}
