/* Copyright (c) 1990-2024, Jsoftware Inc.  All rights reserved.           */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Conjunctions                                                            */

#include "j.h"

// obv1 and obv2 merely pass the call to f.  Since we took the inplace flags for the compound from the original a, we can pass them on too
static DF1(obv1cell){F1PREFIP;DECLFG;A z;PROLOG(0103); z=CALL1IP(f1,w,fs); EPILOG(z);}
static DF1(obv1){PREF1(obv1cell); R obv1cell(jt,w,self);}
static DF2(obv2cell){F2PREFIP;DECLFG;A z;PROLOG(0104); z=CALL2IP(f2,a,w,fs); EPILOG(z);}
static DF2(obv2){PREF2(obv2cell); R obv2cell(jt,a,w,self);}

// Set ASGSAFE from a&w; set INPLACE from a
F2(jtobverse){F2PREFIP;ASSERTVV(a,w); R fdef(0L,COBVERSE,VERB,obv1,obv2,a,w ,0L,((FAV(a)->flag&FAV(w)->flag&VASGSAFE)+(FAV(a)->flag&(VJTFLGOK1|VJTFLGOK2))),mr(a),lr(a),rr(a));}

// Adverse.  Run f, and if that fails (and not with THROW/EXIT), run g (or use its value if it's a noun)
static DF1(ad1){DECLFG;A z;
 ARGCHK1(w); A *old=jt->tnextpushp;
 WITHDEBUGOFF(z=CALL1(f1,  w,fs);)
 if(unlikely(jt->jerr==EVTHROW))R 0;  // THROW is caught only by try.
 if(unlikely(jt->jerr==EVEXIT))R 0;  // EXIT is never caught
 if(BETWEENC(jt->jerr,EVATTN,EVBREAK))CLRATTN  // if the error was ATTN/BREAK, clear the source of the error
 RESETERR;
 if(likely(z))RETF(z);  // normal return
 tpop(old);  // the error exit leaves the stack unpopped
 R AT(gs)&NOUN?gs:CALL1(g1,  w,gs);
}

static DF2(ad2){DECLFG;A z;
 ARGCHK2(a,w); A *old=jt->tnextpushp;
 WITHDEBUGOFF(z=CALL2(f2,a,w,fs);)
 if(unlikely(jt->jerr==EVTHROW))R 0;  // THROW is caught only by try.
 if(unlikely(jt->jerr==EVEXIT))R 0;  // EXIT is never caught
 if(BETWEENC(jt->jerr,EVATTN,EVBREAK))CLRATTN  // if the error was ATTN/BREAK, clear the source of the error
 RESETERR;
 if(likely(z))RETF(z);  // normal return
 tpop(old);  // the error exit leaves the stack unpopped
 R AT(gs)&NOUN?gs:CALL2(g2,a,w,gs);
}

// Set ASGSAFE from operands.  Noun operand is always safe
F2(jtadverse){F2PREFIP;ASSERTVVn(a,w); R fdef(0L,CADVERSE,VERB,ad1,ad2,a,w ,0L,(FAV(a)->flag&(AT(w)&VERB?FAV(w)->flag:~0)&VASGSAFE),RMAX,RMAX,RMAX);}

