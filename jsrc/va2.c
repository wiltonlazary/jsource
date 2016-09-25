/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Verbs: Atomic (Scalar) Dyadic                                           */

#include "j.h"
#include "ve.h"
#include "vcomp.h"

static VA va[]={
/*       */ {
 {{0,0}, {0,0}, {0,0},                                /* BB BI BD              */
  {0,0}, {0,0}, {0,0},                                /* IB II ID              */
  {0,0}, {0,0}, {0,0},                                /* DB DI DD              */
  {0,0}, {0,0}, {0,0}, {0,0}},                        /* ZZ XX QQ Symb         */
 {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},   /* ins: B I D Z X Q Symb */
 {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},   /* pfx: B I D Z X Q Symb */
 {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}} }, /* sfx: B I D Z X Q Symb */

/* 10    */ {
 {{(VF)bw0000II,  VI+VII}, {(VF)bw0000II,  VI+VII}, {(VF)bw0000II,  VI+VII}, 
  {(VF)bw0000II,  VI+VII}, {(VF)bw0000II,  VI},     {(VF)bw0000II,  VI+VII},
  {(VF)bw0000II,  VI+VII}, {(VF)bw0000II,  VI+VII}, {(VF)bw0000II,  VI+VII},
  {(VF)bw0000II,  VI+VII}, {(VF)bw0000II,  VI+VII}, {(VF)bw0000II,  VI+VII}, {0,0}}, 
 {{(VF)bw0000insI,VI+VII}, {(VF)bw0000insI,VI}},
 {{(VF)bw0000pfxI,VI+VII}, {(VF)bw0000pfxI,VI}},
 {{(VF)bw0000sfxI,VI+VII}, {(VF)bw0000sfxI,VI}} },

/* 11    */ {
 {{(VF)bw0001II,  VI+VII}, {(VF)bw0001II,  VI+VII}, {(VF)bw0001II,  VI+VII}, 
  {(VF)bw0001II,  VI+VII}, {(VF)bw0001II,  VI},     {(VF)bw0001II,  VI+VII},
  {(VF)bw0001II,  VI+VII}, {(VF)bw0001II,  VI+VII}, {(VF)bw0001II,  VI+VII},
  {(VF)bw0001II,  VI+VII}, {(VF)bw0001II,  VI+VII}, {(VF)bw0001II,  VI+VII}, {0,0}}, 
 {{(VF)bw0001insI,VI+VII}, {(VF)bw0001insI,VI}},
 {{(VF)bw0001pfxI,VI+VII}, {(VF)bw0001pfxI,VI}},
 {{(VF)bw0001sfxI,VI+VII}, {(VF)bw0001sfxI,VI}} },

/* 12    */ {
 {{(VF)bw0010II,  VI+VII}, {(VF)bw0010II,  VI+VII}, {(VF)bw0010II,  VI+VII}, 
  {(VF)bw0010II,  VI+VII}, {(VF)bw0010II,  VI},     {(VF)bw0010II,  VI+VII},
  {(VF)bw0010II,  VI+VII}, {(VF)bw0010II,  VI+VII}, {(VF)bw0010II,  VI+VII},
  {(VF)bw0010II,  VI+VII}, {(VF)bw0010II,  VI+VII}, {(VF)bw0010II,  VI+VII}, {0,0}}, 
 {{(VF)bw0010insI,VI+VII}, {(VF)bw0010insI,VI}},
 {{0,0}},
 {{(VF)bw0010sfxI,VI+VII}, {(VF)bw0010sfxI,VI}} },

/* 13    */ {
 {{(VF)bw0011II,  VI+VII}, {(VF)bw0011II,  VI+VII}, {(VF)bw0011II,  VI+VII}, 
  {(VF)bw0011II,  VI+VII}, {(VF)bw0011II,  VI},     {(VF)bw0011II,  VI+VII},
  {(VF)bw0011II,  VI+VII}, {(VF)bw0011II,  VI+VII}, {(VF)bw0011II,  VI+VII},
  {(VF)bw0011II,  VI+VII}, {(VF)bw0011II,  VI+VII}, {(VF)bw0011II,  VI+VII}, {0,0}}, 
 {{(VF)bw0011insI,VI+VII}, {(VF)bw0011insI,VI}},
 {{(VF)bw0011pfxI,VI+VII}, {(VF)bw0011pfxI,VI}},
 {{(VF)bw0011sfxI,VI+VII}, {(VF)bw0011sfxI,VI}} },

/* 14    */ {
 {{(VF)bw0100II,  VI+VII}, {(VF)bw0100II,  VI+VII}, {(VF)bw0100II,  VI+VII}, 
  {(VF)bw0100II,  VI+VII}, {(VF)bw0100II,  VI},     {(VF)bw0100II,  VI+VII},
  {(VF)bw0100II,  VI+VII}, {(VF)bw0100II,  VI+VII}, {(VF)bw0100II,  VI+VII},
  {(VF)bw0100II,  VI+VII}, {(VF)bw0100II,  VI+VII}, {(VF)bw0100II,  VI+VII}, {0,0}}, 
 {{(VF)bw0100insI,VI+VII}, {(VF)bw0100insI,VI}},
 {{0,0}},
 {{(VF)bw0100sfxI,VI+VII}, {(VF)bw0100sfxI,VI}} },

/* 15    */ {
 {{(VF)bw0101II,  VI+VII}, {(VF)bw0101II,  VI+VII}, {(VF)bw0101II,  VI+VII}, 
  {(VF)bw0101II,  VI+VII}, {(VF)bw0101II,  VI},     {(VF)bw0101II,  VI+VII},
  {(VF)bw0101II,  VI+VII}, {(VF)bw0101II,  VI+VII}, {(VF)bw0101II,  VI+VII},
  {(VF)bw0101II,  VI+VII}, {(VF)bw0101II,  VI+VII}, {(VF)bw0101II,  VI+VII}, {0,0}}, 
 {{(VF)bw0101insI,VI+VII}, {(VF)bw0101insI,VI}},
 {{(VF)bw0101pfxI,VI+VII}, {(VF)bw0101pfxI,VI}},
 {{(VF)bw0101sfxI,VI+VII}, {(VF)bw0101sfxI,VI}} },

/* 16    */ {
 {{(VF)bw0110II,  VI+VII}, {(VF)bw0110II,  VI+VII}, {(VF)bw0110II,  VI+VII}, 
  {(VF)bw0110II,  VI+VII}, {(VF)bw0110II,  VI},     {(VF)bw0110II,  VI+VII},
  {(VF)bw0110II,  VI+VII}, {(VF)bw0110II,  VI+VII}, {(VF)bw0110II,  VI+VII},
  {(VF)bw0110II,  VI+VII}, {(VF)bw0110II,  VI+VII}, {(VF)bw0110II,  VI+VII}, {0,0}}, 
 {{(VF)bw0110insI,VI+VII}, {(VF)bw0110insI,VI}},
 {{(VF)bw0110pfxI,VI+VII}, {(VF)bw0110pfxI,VI}},
 {{(VF)bw0110sfxI,VI+VII}, {(VF)bw0110sfxI,VI}} },

/* 17    */ {
 {{(VF)bw0111II,  VI+VII}, {(VF)bw0111II,  VI+VII}, {(VF)bw0111II,  VI+VII}, 
  {(VF)bw0111II,  VI+VII}, {(VF)bw0111II,  VI},     {(VF)bw0111II,  VI+VII},
  {(VF)bw0111II,  VI+VII}, {(VF)bw0111II,  VI+VII}, {(VF)bw0111II,  VI+VII},
  {(VF)bw0111II,  VI+VII}, {(VF)bw0111II,  VI+VII}, {(VF)bw0111II,  VI+VII}, {0,0}}, 
 {{(VF)bw0111insI,VI+VII}, {(VF)bw0111insI,VI}},
 {{(VF)bw0111pfxI,VI+VII}, {(VF)bw0111pfxI,VI}},
 {{(VF)bw0111sfxI,VI+VII}, {(VF)bw0111sfxI,VI}} },

/* 18    */ {
 {{(VF)bw1000II,  VI+VII}, {(VF)bw1000II,  VI+VII}, {(VF)bw1000II,  VI+VII}, 
  {(VF)bw1000II,  VI+VII}, {(VF)bw1000II,  VI},     {(VF)bw1000II,  VI+VII},
  {(VF)bw1000II,  VI+VII}, {(VF)bw1000II,  VI+VII}, {(VF)bw1000II,  VI+VII},
  {(VF)bw1000II,  VI+VII}, {(VF)bw1000II,  VI+VII}, {(VF)bw1000II,  VI+VII}, {0,0}}, 
 {{(VF)bw1000insI,VI+VII}, {(VF)bw1000insI,VI}},
 {{0,0}},
 {{(VF)bw1000sfxI,VI+VII}, {(VF)bw1000sfxI,VI}} },

/* 19    */ {
 {{(VF)bw1001II,  VI+VII}, {(VF)bw1001II,  VI+VII}, {(VF)bw1001II,  VI+VII}, 
  {(VF)bw1001II,  VI+VII}, {(VF)bw1001II,  VI},     {(VF)bw1001II,  VI+VII},
  {(VF)bw1001II,  VI+VII}, {(VF)bw1001II,  VI+VII}, {(VF)bw1001II,  VI+VII},
  {(VF)bw1001II,  VI+VII}, {(VF)bw1001II,  VI+VII}, {(VF)bw1001II,  VI+VII}, {0,0}}, 
 {{(VF)bw1001insI,VI+VII}, {(VF)bw1001insI,VI}},
 {{(VF)bw1001pfxI,VI+VII}, {(VF)bw1001pfxI,VI}},
 {{(VF)bw1001sfxI,VI+VII}, {(VF)bw1001sfxI,VI}} },

/* 1a    */ {
 {{(VF)bw1010II,  VI+VII}, {(VF)bw1010II,  VI+VII}, {(VF)bw1010II,  VI+VII}, 
  {(VF)bw1010II,  VI+VII}, {(VF)bw1010II,  VI},     {(VF)bw1010II,  VI+VII},
  {(VF)bw1010II,  VI+VII}, {(VF)bw1010II,  VI+VII}, {(VF)bw1010II,  VI+VII},
  {(VF)bw1010II,  VI+VII}, {(VF)bw1010II,  VI+VII}, {(VF)bw1010II,  VI+VII}, {0,0}}, 
 {{(VF)bw1010insI,VI+VII}, {(VF)bw1010insI,VI}},
 {{0,0}},
 {{(VF)bw1010sfxI,VI+VII}, {(VF)bw1010sfxI,VI}} },

/* 1b    */ {
 {{(VF)bw1011II,  VI+VII}, {(VF)bw1011II,  VI+VII}, {(VF)bw1011II,  VI+VII}, 
  {(VF)bw1011II,  VI+VII}, {(VF)bw1011II,  VI},     {(VF)bw1011II,  VI+VII},
  {(VF)bw1011II,  VI+VII}, {(VF)bw1011II,  VI+VII}, {(VF)bw1011II,  VI+VII},
  {(VF)bw1011II,  VI+VII}, {(VF)bw1011II,  VI+VII}, {(VF)bw1011II,  VI+VII}, {0,0}}, 
 {{(VF)bw1011insI,VI+VII}, {(VF)bw1011insI,VI}},
 {{0,0}},
 {{(VF)bw1011sfxI,VI+VII}, {(VF)bw1011sfxI,VI}} },

/* 1c    */ {
 {{(VF)bw1100II,  VI+VII}, {(VF)bw1100II,  VI+VII}, {(VF)bw1100II,  VI+VII}, 
  {(VF)bw1100II,  VI+VII}, {(VF)bw1100II,  VI},     {(VF)bw1100II,  VI+VII},
  {(VF)bw1100II,  VI+VII}, {(VF)bw1100II,  VI+VII}, {(VF)bw1100II,  VI+VII},
  {(VF)bw1100II,  VI+VII}, {(VF)bw1100II,  VI+VII}, {(VF)bw1100II,  VI+VII}, {0,0}}, 
 {{(VF)bw1100insI,VI+VII}, {(VF)bw1100insI,VI}},
 {{0,0}},
 {{(VF)bw1100sfxI,VI+VII}, {(VF)bw1100sfxI,VI}} },

/* 1d    */ {
 {{(VF)bw1101II,  VI+VII}, {(VF)bw1101II,  VI+VII}, {(VF)bw1101II,  VI+VII}, 
  {(VF)bw1101II,  VI+VII}, {(VF)bw1101II,  VI},     {(VF)bw1101II,  VI+VII},
  {(VF)bw1101II,  VI+VII}, {(VF)bw1101II,  VI+VII}, {(VF)bw1101II,  VI+VII},
  {(VF)bw1101II,  VI+VII}, {(VF)bw1101II,  VI+VII}, {(VF)bw1101II,  VI+VII}, {0,0}}, 
 {{(VF)bw1101insI,VI+VII}, {(VF)bw1101insI,VI}},
 {{0,0}},
 {{(VF)bw1101sfxI,VI+VII}, {(VF)bw1101sfxI,VI}} },

/* 1e    */ {
 {{(VF)bw1110II,  VI+VII}, {(VF)bw1110II,  VI+VII}, {(VF)bw1110II,  VI+VII}, 
  {(VF)bw1110II,  VI+VII}, {(VF)bw1110II,  VI},     {(VF)bw1110II,  VI+VII},
  {(VF)bw1110II,  VI+VII}, {(VF)bw1110II,  VI+VII}, {(VF)bw1110II,  VI+VII},
  {(VF)bw1110II,  VI+VII}, {(VF)bw1110II,  VI+VII}, {(VF)bw1110II,  VI+VII}, {0,0}}, 
 {{(VF)bw1110insI,VI+VII}, {(VF)bw1110insI,VI}},
 {{0,0}},
 {{(VF)bw1110sfxI,VI+VII}, {(VF)bw1110sfxI,VI}} },

/* 1f    */ {
 {{(VF)bw1111II,  VI+VII}, {(VF)bw1111II,  VI+VII}, {(VF)bw1111II,  VI+VII}, 
  {(VF)bw1111II,  VI+VII}, {(VF)bw1111II,  VI},     {(VF)bw1111II,  VI+VII},
  {(VF)bw1111II,  VI+VII}, {(VF)bw1111II,  VI+VII}, {(VF)bw1111II,  VI+VII},
  {(VF)bw1111II,  VI+VII}, {(VF)bw1111II,  VI+VII}, {(VF)bw1111II,  VI+VII}, {0,0}}, 
 {{(VF)bw1111insI,VI+VII}, {(VF)bw1111insI,VI}},
 {{(VF)bw1111pfxI,VI+VII}, {(VF)bw1111pfxI,VI}},
 {{(VF)bw1111sfxI,VI+VII}, {(VF)bw1111sfxI,VI}} },

/* 21 !  */ {
 {{(VF)leBB, VB        }, {(VF)binDD,VD+VDD+VRI}, {(VF)binDD,VD+VDD}, 
  {(VF)binDD,VD+VDD+VRI}, {(VF)binDD,VD+VDD+VRI}, {(VF)binDD,VD+VDD}, 
  {(VF)binDD,VD+VDD    }, {(VF)binDD,VD+VDD    }, {(VF)binDD,VD    }, 
  {(VF)binZZ,VZ+VZZ}, {(VF)binXX,VX+VXX}, {(VF)binQQ,VX+VQQ}, {0,0}}, 
 {{(VF)leinsB,VB}},
 {{(VF)lepfxB,VB}},
 {{(VF)lesfxB,VB}} },

/* 25 %  */ {
 {{(VF)divBB,VD}, {(VF)divBI,VD}, {(VF)divBD,VD},
  {(VF)divIB,VD}, {(VF)divII,VD}, {(VF)divID,VD},
  {(VF)divDB,VD}, {(VF)divDI,VD}, {(VF)divDD,VD}, 
  {(VF)divZZ,VZ+VZZ}, {(VF)divXX,VX+VXX}, {(VF)divQQ,VQ+VQQ}, {0,0}},
 {{(VF)divinsD,VD+VDD}, {(VF)divinsD,VD+VDD}, {(VF)divinsD,VD}, {(VF)divinsZ,VZ}},
 {{(VF)divpfxD,VD+VDD}, {(VF)divpfxD,VD+VDD}, {(VF)divpfxD,VD}, {(VF)divpfxZ,VZ}},
 {{(VF)divsfxD,VD+VDD}, {(VF)divsfxD,VD+VDD}, {(VF)divsfxD,VD}, {(VF)divsfxZ,VZ}} },

/* 2a *  */ {
 {{(VF)andBB,  VB}, {(VF)tymesBI,VI}, {(VF)tymesBD,VD},
  {(VF)tymesIB,VI}, {(VF)tymesII,VI}, {(VF)tymesID,VD},
  {(VF)tymesDB,VD}, {(VF)tymesDI,VD}, {(VF)tymesDD,VD}, 
  {(VF)tymesZZ,VZ+VZZ}, {(VF)tymesXX,VX+VXX}, {(VF)tymesQQ,VQ+VQQ}, {0,0}},
 {{(VF)andinsB,VB}, {(VF)tymesinsI,VI}, {(VF)tymesinsD,VD}, {(VF)tymesinsZ,VZ}, {0,0},          {0,0},          {0,0}},
 {{(VF)andpfxB,VB}, {(VF)tymespfxI,VI}, {(VF)tymespfxD,VD}, {(VF)tymespfxZ,VZ}, {(VF)tymespfxX,VX}, {(VF)tymespfxQ,VQ}, {0,0}},
 {{(VF)andsfxB,VB}, {(VF)tymessfxI,VI}, {(VF)tymessfxD,VD}, {(VF)tymessfxZ,VZ}, {(VF)tymessfxX,VX}, {(VF)tymessfxQ,VQ}, {0,0}} },

/* 2b +  */ {
 {{(VF)plusBB,VI    }, {(VF)plusII,VI+VII}, {(VF)plusBD,VD}, 
  {(VF)plusII,VI+VII}, {(VF)plusII,VI    }, {(VF)plusID,VD}, 
  {(VF)plusDB,VD    }, {(VF)plusDI,VD    }, {(VF)plusDD,VD}, 
  {(VF)plusZZ,VZ+VZZ}, {(VF)plusXX,VX+VXX}, {(VF)plusQQ,VQ+VQQ}, {0,0}},
 {{(VF)plusinsB,VI}, {(VF)plusinsI,VI}, {(VF)plusinsD,VD}, {(VF)plusinsZ,VZ}, {0,0},         {0,0},         {0,0}},
 {{(VF)pluspfxB,VI}, {(VF)pluspfxI,VI}, {(VF)pluspfxD,VD}, {(VF)pluspfxZ,VZ}, {(VF)pluspfxX,VX}, {(VF)pluspfxQ,VQ}, {0,0}},
 {{(VF)plussfxB,VI}, {(VF)plussfxI,VI}, {(VF)plussfxD,VD}, {(VF)plussfxZ,VZ}, {(VF)plussfxX,VX}, {(VF)plussfxQ,VQ}, {0,0}} },

/* 2d -  */ {
 {{(VF)minusBB,VI    }, {(VF)minusII,VI+VII}, {(VF)minusBD,VD}, 
  {(VF)minusII,VI+VII}, {(VF)minusII,VI    }, {(VF)minusID,VD},
  {(VF)minusDB,VD    }, {(VF)minusDI,VD    }, {(VF)minusDD,VD}, 
  {(VF)minusZZ,VZ+VZZ}, {(VF)minusXX,VX+VXX}, {(VF)minusQQ,VQ+VQQ}, {0,0}},
 {{(VF)minusinsB,VI}, {(VF)minusinsI,VI}, {(VF)minusinsD,VD}, {(VF)minusinsZ,VZ}, {0,0},          {0,0},          {0,0}},
 {{(VF)minuspfxB,VI}, {(VF)minuspfxI,VI}, {(VF)minuspfxD,VD}, {(VF)minuspfxZ,VZ}, {(VF)minuspfxX,VX}, {(VF)minuspfxQ,VQ}, {0,0}},
 {{(VF)minussfxB,VI}, {(VF)minussfxI,VI}, {(VF)minussfxD,VD}, {(VF)minussfxZ,VZ}, {0,0},          {0,0},          {0,0}} },

/* 3c <  */ {
 {{(VF)ltBB,VB}, {(VF)ltBI,VB}, {(VF)ltBD,VB},
  {(VF)ltIB,VB}, {(VF)ltII,VB}, {(VF)ltID,VB},
  {(VF)ltDB,VB}, {(VF)ltDI,VB}, {(VF)ltDD,VB}, 
  {(VF)ltDD,VB+VDD}, {(VF)ltXX,VB+VXFC}, {(VF)ltQQ,VB+VQQ}, {(VF)ltSS,VB}},
 {{(VF)ltinsB,VB}},
 {{(VF)ltpfxB,VB}},
 {{(VF)ltsfxB,VB}} },

/* 3d =  */ {
 {{(VF)eqBB,VB}, {(VF)eqBI,VB}, {(VF)eqBD,VB},
  {(VF)eqIB,VB}, {(VF)eqII,VB}, {(VF)eqID,VB},
  {(VF)eqDB,VB}, {(VF)eqDI,VB}, {(VF)eqDD,VB}, 
  {(VF)eqZZ,VB+VZZ}, {(VF)eqXX,VB+VXEQ}, {(VF)eqQQ,VB+VQQ}, {(VF)eqII,VB}},
 {{(VF)eqinsB,VB}},
 {{(VF)eqpfxB,VB}},
 {{(VF)eqsfxB,VB}} },

/* 3e >  */ {
 {{(VF)gtBB,VB}, {(VF)gtBI,VB}, {(VF)gtBD,VB},
  {(VF)gtIB,VB}, {(VF)gtII,VB}, {(VF)gtID,VB},
  {(VF)gtDB,VB}, {(VF)gtDI,VB}, {(VF)gtDD,VB}, 
  {(VF)gtDD,VB+VDD}, {(VF)gtXX,VB+VXCF}, {(VF)gtQQ,VB+VQQ}, {(VF)gtSS,VB}},
 {{(VF)gtinsB,VB}},
 {{(VF)gtpfxB,VB}},
 {{(VF)gtsfxB,VB}} },

/* 5e ^  */ {
 {{(VF)geBB, VB}, {(VF)powBI,VD}, {(VF)powBD,VD},
  {(VF)powIB,VI}, {(VF)powII,VD}, {(VF)powID,VD},
  {(VF)powDB,VD}, {(VF)powDI,VD}, {(VF)powDD,VD}, 
  {(VF)powZZ,VZ+VZZ}, {(VF)powXX,VX+VXX}, {(VF)powQQ,VQ+VQQ}, {0,0}},
 {{(VF)geinsB,VB}},
 {{(VF)gepfxB,VB}},
 {{(VF)gesfxB,VB}} },

/* 7c |  */ {
 {{(VF)ltBB, VB    }, {(VF)remII,VI+VII}, {(VF)remDD,VD+VDD},
  {(VF)remII,VI+VII}, {(VF)remII,VI    }, {(VF)remID,VI    },
  {(VF)remDD,VD+VDD}, {(VF)remDD,VD+VDD}, {(VF)remDD,VD    }, 
  {(VF)remZZ,VZ+VZZ}, {(VF)remXX,VX+VXX}, {(VF)remQQ,VQ+VQQ}, {0,0}},
 {{(VF)ltinsB,VB}},
 {{(VF)ltpfxB,VB}},
 {{(VF)ltsfxB,VB}} },

/* 82 <. */ {
 {{(VF)andBB,VB}, {(VF)minBI,VI}, {(VF)minBD,VD},
  {(VF)minIB,VI}, {(VF)minII,VI}, {(VF)minID,VD},
  {(VF)minDB,VD}, {(VF)minDI,VD}, {(VF)minDD,VD}, 
  {(VF)minDD,VD+VDD}, {(VF)minXX,VX+VXX}, {(VF)minQQ,VQ+VQQ}, {(VF)minSS,VSB}},
 {{(VF)andinsB,VB}, {(VF)mininsI,VI}, {(VF)mininsD,VD}, {(VF)mininsD,VD+VDD}, {(VF)mininsX,VX}, {0,0},        {(VF)mininsS,VSB}},
 {{(VF)andpfxB,VB}, {(VF)minpfxI,VI}, {(VF)minpfxD,VD}, {(VF)minpfxD,VD+VDD}, {(VF)minpfxX,VX}, {(VF)minpfxQ,VQ}, {(VF)minpfxS,VSB}},
 {{(VF)andsfxB,VB}, {(VF)minsfxI,VI}, {(VF)minsfxD,VD}, {(VF)minsfxD,VD+VDD}, {(VF)minsfxX,VX}, {(VF)minsfxQ,VQ}, {(VF)minsfxS,VSB}}},

/* 83 <: */ {
 {{(VF)leBB,VB}, {(VF)leBI,VB}, {(VF)leBD,VB},
  {(VF)leIB,VB}, {(VF)leII,VB}, {(VF)leID,VB},
  {(VF)leDB,VB}, {(VF)leDI,VB}, {(VF)leDD,VB}, 
  {(VF)leDD,VB+VDD}, {(VF)leXX,VB+VXCF}, {(VF)leQQ,VB+VQQ}, {(VF)leSS,VB}},
 {{(VF)leinsB,VB}},
 {{(VF)lepfxB,VB}},
 {{(VF)lesfxB,VB}} },

/* 84 >. */ {
 {{(VF)orBB,VB}, {(VF)maxBI,VI}, {(VF)maxBD,VD},
  {(VF)maxIB,VI}, {(VF)maxII,VI}, {(VF)maxID,VD},
  {(VF)maxDB,VD}, {(VF)maxDI,VD}, {(VF)maxDD,VD}, 
  {(VF)maxDD,VD+VDD}, {(VF)maxXX,VX+VXX}, {(VF)maxQQ,VQ+VQQ}, {(VF)maxSS,VSB}},
 {{(VF)orinsB,VB}, {(VF)maxinsI,VI}, {(VF)maxinsD,VD}, {(VF)maxinsD,VD+VDD}, {(VF)maxinsX,VX}, {0,0},        {(VF)maxinsS,VSB}},
 {{(VF)orpfxB,VB}, {(VF)maxpfxI,VI}, {(VF)maxpfxD,VD}, {(VF)maxpfxD,VD+VDD}, {(VF)maxpfxX,VX}, {(VF)maxpfxQ,VQ}, {(VF)maxpfxS,VSB}},
 {{(VF)orsfxB,VB}, {(VF)maxsfxI,VI}, {(VF)maxsfxD,VD}, {(VF)maxsfxD,VD+VDD}, {(VF)maxsfxX,VX}, {(VF)maxsfxQ,VQ}, {(VF)maxsfxS,VSB}}},

/* 85 >: */ {
 {{(VF)geBB,VB}, {(VF)geBI,VB}, {(VF)geBD,VB},
  {(VF)geIB,VB}, {(VF)geII,VB}, {(VF)geID,VB},
  {(VF)geDB,VB}, {(VF)geDI,VB}, {(VF)geDD,VB}, 
  {(VF)geDD,VB+VDD}, {(VF)geXX,VB+VXFC}, {(VF)geQQ,VB+VQQ}, {(VF)geSS,VB}},
 {{(VF)geinsB,VB}},
 {{(VF)gepfxB,VB}},
 {{(VF)gesfxB,VB}} },

/* 88 +. */ {
 {{(VF)orBB,VB     }, {(VF)gcdII,VI+VII}, {(VF)gcdDD,VD+VDD},
  {(VF)gcdII,VI+VII}, {(VF)gcdII,VI    }, {(VF)gcdDD,VD+VDD},
  {(VF)gcdDD,VD+VDD}, {(VF)gcdDD,VD+VDD}, {(VF)gcdDD,VD    }, 
  {(VF)gcdZZ,VZ+VZZ}, {(VF)gcdXX,VX+VXX}, {(VF)gcdQQ,VQ+VQQ}, {0,0}},
 {{(VF)orinsB,VB}},
 {{(VF)orpfxB,VB}},
 {{(VF)orsfxB,VB}} },

/* 89 +: */ {
 {{(VF)norBB,VB    }, {(VF)norBB,VB+VBB}, {(VF)norBB,VB+VBB},
  {(VF)norBB,VB+VBB}, {(VF)norBB,VB+VBB}, {(VF)norBB,VB+VBB},
  {(VF)norBB,VB+VBB}, {(VF)norBB,VB+VBB}, {(VF)norBB,VB+VBB}, 
  {(VF)norBB,VB+VBB}, {(VF)norBB,VB+VBB}, {(VF)norBB,VB+VBB}, {0,0}},
 {{(VF)norinsB,VB}},
 {{(VF)norpfxB,VB}},
 {{(VF)norsfxB,VB}} },

/* 8a *. */ {
 {{(VF)andBB,VB    }, {(VF)lcmII,VI+VII}, {(VF)lcmDD,VD+VDD},
  {(VF)lcmII,VI+VII}, {(VF)lcmII,VI    }, {(VF)lcmDD,VD+VDD},
  {(VF)lcmDD,VD+VDD}, {(VF)lcmDD,VD+VDD}, {(VF)lcmDD,VD    }, 
  {(VF)lcmZZ,VZ+VZZ}, {(VF)lcmXX,VX+VXX}, {(VF)lcmQQ,VQ+VQQ}, {0,0}},
 {{(VF)andinsB,VB}},
 {{(VF)andpfxB,VB}},
 {{(VF)andsfxB,VB}} },

/* 8b *: */ {
 {{(VF)nandBB,VB},     {(VF)nandBB,VB+VBB}, {(VF)nandBB,VB+VBB},
  {(VF)nandBB,VB+VBB}, {(VF)nandBB,VB+VBB}, {(VF)nandBB,VB+VBB},
  {(VF)nandBB,VB+VBB}, {(VF)nandBB,VB+VBB}, {(VF)nandBB,VB+VBB}, 
  {(VF)nandBB,VB+VBB}, {(VF)nandBB,VB+VBB}, {(VF)nandBB,VB+VBB}, {0,0}},
 {{(VF)nandinsB,VB}},
 {{(VF)nandpfxB,VB}},
 {{(VF)nandsfxB,VB}} },

/* 95 ~: */ {
 {{(VF)neBB,VB}, {(VF)neBI,VB}, {(VF)neBD,VB},
  {(VF)neIB,VB}, {(VF)neII,VB}, {(VF)neID,VB},
  {(VF)neDB,VB}, {(VF)neDI,VB}, {(VF)neDD,VB}, 
  {(VF)neZZ,VB+VZZ}, {(VF)neXX,VB+VXEQ}, {(VF)neQQ,VB+VQQ}, {0,0}},
 {{(VF)neinsB,VB}},
 {{(VF)nepfxB,VB}},
 {{(VF)nesfxB,VB}} },

/* d1 o. */ {
 {{(VF)cirDD,VD+VDD}, {(VF)cirDD,VD+VDD}, {(VF)cirBD,VD},
  {(VF)cirDD,VD+VDD}, {(VF)cirDD,VD+VDD}, {(VF)cirID,VD},
  {(VF)cirDD,VD+VDD}, {(VF)cirDD,VD+VDD}, {(VF)cirDD,VD}, 
  {(VF)cirZZ,VZ+VZZ+VRD}, {(VF)cirDD,VD+VDD}, {(VF)cirDD,VD+VDD}, {0,0}},
 {{0,0}},
 {{0,0}},
 {{0,0}} }
};


static UC vaptr[256]={
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* 0 */
// C0  C1          ^D                    TAB LF          CR         
   1,  2,  3,  4,  5,  6,  7,  8,    9, 10, 11, 12, 13, 14, 15, 16, /* 1 */
// <-----------------------bitwise functions -------------------->
   0, 17,  0,  0,  0, 18,  0,  0,    0,  0, 19, 20,  0, 21,  0,  0, /* 2 */
//     !   "   #   $   %   &   '     (   )   *   +   ,   -   .   /  
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0, 22, 23, 24,  0, /* 3 */
// NOUN    HOOK FK ADVF                      :   ;   <   =   >   ?  
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* 4 */
// @                                                                
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0, 25,  0, /* 5 */
//                                               [   \   ]   ^   _  
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* 6 */
// `                                                                
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0, 26,  0,  0,  0, /* 7 */
//                                               {   |   }   ~      
   0,  0, 27, 28, 29, 30,  0,  0,   31, 32, 33, 34,  0,  0,  0,  0, /* 8 */
// =.  =:  <.  <:  >.  >:  _.        +.  +:  *.  *:  -.  -:  %.  %: 
   0,  0,  0,  0,  0, 35,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* 9 */
// ^.  ^:  $.  $:  ~.  ~:  |.  |:    ..  .:  :.  ::  ,.  ,:  ;.  ;: 
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* a */
// #.  #:  !.  !:  /.  /:  \.  \:    [.  [:  ].  ]:  {.  {:  }.  }: 
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* b */
// ".  ":  `.  `:  @.  @:  &.  &:    ?.  ?:  a.  A.  a:  b.  c.     
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* c */
// C.  d.  D.  D:  e.  E.  f.  F:    H.  i.  i:  I.  I:  j.  L.  L: 
   0,  0,  0, 36,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* d */
// m.  M.  n.  o.  p.  p:  Q:  q:    r.  s:  S:  t.  t:  T.  u.  u: 
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* e */
// v.  x.  x:  y.                    0:  }ip }cs {:: {:: }:: &.: p..
   0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0, /* f */
// ,ip                                                           FF  
  };   /* index in va[] for each ID */
/*   1   2   3   4   5   6   7     8   9   a   b   c   d   e   f   */

C jtvaid(J jt,A w){A x;C c;I k;V*v;
 v=VAV(w); c=v->id;
 if(c==CBDOT){x=v->f; if(INT&AT(x)&&!AR(x)&&(k=*AV(x),16<=k&&k<=31))c=(C)k;}
 R vaptr[(UC)c]?c:0;
}

static A jtva2(J,A,A,C);

// If each argument has a single direct-numeric atom, go process through speedy-singleton code
#define CHECKSSING(a,w,f) RZ(a&&w); if(AN(a)==1 && AN(w)==1 && !((AT(a)|AT(w))&~(B01+INT+FL)))R f(jt,a,w); F2PREFIP;
#define CHECKSSINGSB(a,w,f) RZ(a&&w); if(HOMO(AT(a),AT(w)) && AN(a)==1 && AN(w)==1 && !((AT(a)|AT(w))&~(B01+INT+FL+SBT)))R f(jt,a,w); F2PREFIP;
#define CHECKSSINGOP(a,w,f,op) RZ(a&&w); if(AN(a)==1 && AN(w)==1 && !((AT(a)|AT(w))&~(B01+INT+FL)))R f(jt,a,w,op); F2PREFIP;
#define CHECKSSINGOPSB(a,w,f,op) RZ(a&&w); if(HOMO(AT(a),AT(w)) && AN(a)==1 && AN(w)==1 && !((AT(a)|AT(w))&~(B01+INT+FL+SBT+LIT+C2T+C4T)))R f(jt,a,w,op); F2PREFIP;
#define CHECKSSINGPROV(a,w,f) RZ(a&&w); if(AN(a)==1 && AN(w)==1 && !((AT(a)|AT(w))&~(B01+INT+FL)))R f(jt,a,w); F2PREFIP;
#define CHECKSSINGNZ(a,w,f) RZ(a&&w); if(AN(a)==1 && AN(w)==1 && !((AT(a)|AT(w))&~(B01+INT+FL))){A z = f(jt,a,w); if(z)R z;} F2PREFIP;

// These are the entry points for the individual verbs.  They pick up the verb-name
// and transfer to jtva2 which does the work

F2(jtbitwise0000){CHECKSSINGOP(a,w,jtssbitwise,0) R va2(a,w,(C)16);}
F2(jtbitwise0001){CHECKSSINGOP(a,w,jtssbitwise,1) R va2(a,w,(C)17);}
F2(jtbitwise0010){CHECKSSINGOP(a,w,jtssbitwise,2) R va2(a,w,(C)18);}
F2(jtbitwise0011){CHECKSSINGOP(a,w,jtssbitwise,3) R va2(a,w,(C)19);}

F2(jtbitwise0100){CHECKSSINGOP(a,w,jtssbitwise,4) R va2(a,w,(C)20);}
F2(jtbitwise0101){CHECKSSINGOP(a,w,jtssbitwise,5) R va2(a,w,(C)21);}
F2(jtbitwise0110){CHECKSSINGOP(a,w,jtssbitwise,6) R va2(a,w,(C)22);}
F2(jtbitwise0111){CHECKSSINGOP(a,w,jtssbitwise,7) R va2(a,w,(C)23);}

F2(jtbitwise1000){CHECKSSINGOP(a,w,jtssbitwise,8) R va2(a,w,(C)24);}
F2(jtbitwise1001){CHECKSSINGOP(a,w,jtssbitwise,9) R va2(a,w,(C)25);}
F2(jtbitwise1010){CHECKSSINGOP(a,w,jtssbitwise,10) R va2(a,w,(C)26);}
F2(jtbitwise1011){CHECKSSINGOP(a,w,jtssbitwise,11) R va2(a,w,(C)27);}

F2(jtbitwise1100){CHECKSSINGOP(a,w,jtssbitwise,12) R va2(a,w,(C)28);}
F2(jtbitwise1101){CHECKSSINGOP(a,w,jtssbitwise,13) R va2(a,w,(C)29);}
F2(jtbitwise1110){CHECKSSINGOP(a,w,jtssbitwise,14) R va2(a,w,(C)30);}
F2(jtbitwise1111){CHECKSSINGOP(a,w,jtssbitwise,15) R va2(a,w,(C)31);}

F2(jtbitwiserotate){CHECKSSINGOP(a,w,jtssbitwise,16) R genbitwiserotate(a,w);}
F2(jtbitwiseshift){CHECKSSINGOP(a,w,jtssbitwise,17) R genbitwiseshift(a,w);}
F2(jtbitwiseshifta){CHECKSSINGOP(a,w,jtssbitwise,18) R genbitwiseshifta(a,w);}

F2(jteq     ){CHECKSSINGOPSB(a,w,jtsseqne,0) R va2(a,w,CEQ     );}
F2(jtlt     ){CHECKSSINGSB(a,w,jtsslt) R va2(a,w,CLT     );}
F2(jtminimum){CHECKSSINGSB(a,w,jtssmin) R va2(a,w,CMIN    );}
F2(jtle     ){CHECKSSINGSB(a,w,jtssle) R va2(a,w,CLE     );}
F2(jtgt     ){CHECKSSINGSB(a,w,jtssgt) R va2(a,w,CGT     );}
F2(jtmaximum){CHECKSSINGSB(a,w,jtssmax) R va2(a,w,CMAX    );}
F2(jtge     ){CHECKSSINGSB(a,w,jtssge) R va2(a,w,CGE     );}
F2(jtplus   ){CHECKSSING(a,w,jtssplus) R va2(a,w,CPLUS   );}
F2(jtgcd    ){CHECKSSING(a,w,jtssgcd) R va2(a,w,CPLUSDOT);}
F2(jtnor    ){CHECKSSING(a,w,jtssnor) R va2(a,w,CPLUSCO );}
F2(jttymes  ){CHECKSSING(a,w,jtssmult) R va2(a,w,CSTAR   );}
F2(jtlcm    ){CHECKSSING(a,w,jtsslcm) R va2(a,w,CSTARDOT);}
F2(jtnand   ){CHECKSSING(a,w,jtssnand) R va2(a,w,CSTARCO );}
F2(jtminus  ){CHECKSSING(a,w,jtssminus) R va2(a,w,CMINUS  );}
F2(jtdivide ){CHECKSSING(a,w,jtssdiv) R va2(a,w,CDIV    );}
F2(jtexpn2  ){CHECKSSINGNZ(a,w,jtsspow) R va2(a,w,CEXP    );}
F2(jtne     ){CHECKSSINGOPSB(a,w,jtsseqne,1) R va2(a,w,CNE     );}
F2(jtoutof  ){CHECKSSING(a,w,jtssoutof) R va2(a,w,CBANG   );}
F2(jtcircle ){R va2(a,w,CCIRCLE );}
F2(jtresidue){RZ(a&&w); R INT&AT(w)&&equ(a,num[2])?intmod2(w):va2(a,w,CSTILE);}


// These are the unary ops that are implemented using a canned argument

// Shift the w-is-inplaceable flag to a.  Bit 1 is known to be 0 in any call to a monad
#define IPSHIFTWA (jt = (J)(((I)jt+JTINPLACEW)&-JTINPLACEA))

F1(jtnot   ){R w&&AT(w)&B01+SB01?eq(zero,w):minus(one,w);}
F1(jtnegate){R minus(zero,  w);}
F1(jtdecrem){IPSHIFTWA; R minus(w,     one);}
F1(jtincrem){R plus(one,   w);}
F1(jtduble ){R tymes(num[2],w);}
F1(jtsquare){R tymes(w,     w);}
F1(jtrecip ){R divide(one,   w);}
F1(jthalve ){IPSHIFTWA; R divide(w,     num[2]);}

static void zeroF(J jt,B b,I m,I n,B*z,void*x,void*y){memset(z,C0,m*n);}
static void  oneF(J jt,B b,I m,I n,B*z,void*x,void*y){memset(z,C1,m*n);}

A jtcvz(J jt,I cv,A w){I t;
 t=AT(w);
 if(cv&VRD&&!(t&FL) )R pcvt(FL,w);
 if(cv&VRI&&!(t&INT))R icvt(w);
 R w;
}    /* convert result */

#define VAF(fname,ptr,fp,fm,ft)   \
 void fname(J jt,C id,I t,VF*ado,I*cv){VA2*p;  \
  if(jt->jerr==EWOV){                          \
   jt->jerr=0;                                 \
   *ado=(id==CPLUS?fp:id==CMINUS?fm:ft);       \
   *cv=VD;                                     \
  }else if(t&NUMERIC+SBT){                     \
   p=(va+vaptr[(UC)id])->ptr+(t&B01?0:t&INT?1:t&FL?2:t&CMPX?3:t&XNUM?4:t&RAT?5:6);  \
   *ado=p->f; *cv=p->cv;                       \
  }else *ado=0;                                \
 }

VAF(jtvains,pins, plusinsO,minusinsO,tymesinsO)
VAF(jtvapfx,ppfx, pluspfxO,minuspfxO,tymespfxO)
VAF(jtvasfx,psfx, plussfxO,minussfxO,tymessfxO)

#define VARCASE(e,c) (70*(e)+(c))

// Table converting operand types to slot numbers in a va[] entry
// Employed when one arg is known to be CMPX/XNUM/RAT.  Indexed by
// bitmask of RAT,CMPX,FL.  Entry 9=CMPX; otherwise entry 8=some FL, otherwise
// entry 10 for XNUM, 11 for some RAT 
static UC xnumpri[] = {10 ,8 ,9 ,9 ,11 ,8 ,9 ,9};

// Analyze the verb and arguments and come up with *ado, address of the routine to handle one
// list of arguments producing a list of results; and *cv, the conversion control which specifies
// the precision inputs must be converted to, and what the result type will be.
// The flags in cv have doubled letters (e.g. VDD) for input precision, single letters (e. g. VD) for result
// Returned value is 0 for failure, 1 for success
B jtvar(J jt,C id,A a,A w,I at,I wt,VF*ado,I*cv){B b;I t,x;VA2 *p;
 // If there is a pending error, it might be one that can be cured with a retry; for example, fixed-point
 // overflow, where we will convert to float.  If the error is one of those, get the routine and conversion
 // for it, and return.
 if(jt->jerr){
  switch(VARCASE(jt->jerr,id)){
   default:      R 0;
   case VARCASE(EWIMAG,CCIRCLE ): *ado=(VF)cirZZ;   *cv=VZ+VZZ+VRD; break;
   case VARCASE(EWIMAG,CEXP    ): *ado=(VF)powZZ;   *cv=VZ+VZZ+VRD; break;
   case VARCASE(EWIRR ,CBANG   ): *ado=(VF)binDD;   *cv=VD+VDD;     break;
   case VARCASE(EWIRR ,CEXP    ): *ado=(VF)powDD;   *cv=VD+VDD;     break;
   case VARCASE(EWRAT ,CDIV    ): *ado=(VF)divQQ;   *cv=VQ+VQQ;     break;
   case VARCASE(EWRAT ,CEXP    ): *ado=(VF)powQQ;   *cv=VQ+VQQ;     break;
   case VARCASE(EWDIV0,CDIV    ): *ado=(VF)divDD;   *cv=VD+VDD;     break;
   case VARCASE(EWOV  ,CPLUS   ): *ado=(VF)plusIO;  *cv=VD+VII;     break;
   case VARCASE(EWOV  ,CMINUS  ): *ado=(VF)minusIO; *cv=VD+VII;     break;
   case VARCASE(EWOV  ,CSTAR   ): *ado=(VF)tymesIO; *cv=VD+VII;     break;
   case VARCASE(EWOV  ,CPLUSDOT): *ado=(VF)gcdIO;   *cv=VD+VII;     break;
   case VARCASE(EWOV  ,CSTARDOT): *ado=(VF)lcmIO;   *cv=VD+VII;     break;
   case VARCASE(EWOV  ,CSTILE  ): *ado=(VF)remDD;   *cv=VD+VDD;     break;
  }
  RESETERR;
 }else if(!((t=UNSAFE(at|wt))&~NUMERIC)){
  // Normal case where we are not retrying: here for numeric arguments
  // vaptr converts the character pseudocode into an entry in va;
  // that entry contains 34 (ado,cv) pairs, indexed according to verb/argument types.
  // the first 9 entries [0-8] are a 3x3 array of the combinations of the main numeric types
  // B,I,D; then [9] CMPX [10] XINT (but not RAT) [11] RAT [12] SBT (symbol)
  // then [13-19] are for verb/, with precisions B I D Z X Q Symb
  // [20-26] for verb\, and [27-33] for verb\.
  if(t<CMPX) {
   // Here for the fast and important case, where the arguments are both B01/INT/FL
   // The index into va is atype*3 + wtype, calculated sneakily
   p = &va[vaptr[(UC)id]].p2[((at>>1)+((at+wt)>>2))&(CMPX-1)];
   *cv = p->cv;
  } else {
   // Here one of the arguments is CMPX/RAT/XNUM  (we don't support XD and XZ yet)
   // They are in priority order CMPX, FL, RAT, XNUM.  Extract those bits and look up
   // the type to use
   p = &va[vaptr[(UC)id]].p2[xnumpri[((t>>3)&3)+((t>>5)&4)]];  // bits: RAT CMPX FL
   x = p->cv;
   // Some entries specify no input conversion in the (DD,DD) slot.  I don't know why.  But if
   // an input is FL (and remember, the other input is known here to be CMPX, RAT, or XNUM),
   // we'd better specify an input conversion of VDD, unless one is explicitly given, as it will be for the CMPX slot
   if((t&FL)&&!(x&(VBB|VII|VDD|VZZ))){x = (x&(~VARGMSK))|VDD;}   // This is part of where XNUM/RAT is promoted to FL
   *cv = x;
  }
  *ado = p->f;   // finish getting the output values - cv was done above
 }else{
  // Normal case, but nonnumeric.  This will be a domain error except for = and ~:, and a few symbol operations
  b=!HOMO(at,wt); *cv=VB;  // b = 'inhomogeneous types (always compare not-equal)'; cv indicates no input conversion, boolean result
  jt->rela=ARELATIVE(a)*(I)a;   // set flags indicating 'indirect datatype' for use during compare
  jt->relw=ARELATIVE(w)*(I)w;
  switch(id){
    // for =, it's just 0 for inhomogeneous types, or the routines to handle the other comparisons
   case CEQ: *ado=b?(VF)zeroF:at&SBT?(VF)eqII:at&BOX?(VF)eqAA:
                  at&LIT?(wt&LIT?(VF)eqCC:wt&C2T?(VF)eqCS:(VF)eqCU):
                  at&C2T?(wt&LIT?(VF)eqSC:wt&C2T?(VF)eqSS:(VF)eqSU):
                          wt&LIT?(VF)eqUC:wt&C2T?(VF)eqUS:(VF)eqUU; break;
    // similarly for ~:
   case CNE: *ado=b?(VF) oneF:at&SBT?(VF)neII:at&BOX?(VF)neAA:
                  at&LIT?(wt&LIT?(VF)neCC:wt&C2T?(VF)neCS:(VF)neCS):
                  at&C2T?(wt&LIT?(VF)neSC:wt&C2T?(VF)neSS:(VF)neSU):
                          wt&LIT?(VF)neUC:wt&C2T?(VF)neUS:(VF)neUU; break;
   default:
    // If not = ~:, it had better be a symbol operation.
    ASSERT(at&SBT&&wt&SBT,EVDOMAIN);
    p = &va[vaptr[(UC)id]].p2[12];  // fetch the 'symbol' entry
    ASSERT(p->f,EVDOMAIN);   // not all verbs support symbols - fail if this one doesn't
    *ado=p->f; *cv=p->cv;  // return the values read
 }}
 R 1;
}    /* function and control for rank */


// All dyadic arithmetic verbs f enter here, and also f"n.  a and w are the arguments, id
// is the pseudocharacter indicating what operation is to be performed
static A jtva2(J jt,A a,A w,C id){A z;B b,c,sp=0;C*av,*wv,*zv;I acn,acr,af,ak,an,ar,*as,at,cv,f,m,
     mf,n,nf,*oq=jt->rank,q,r,*s,*sf,t,wcn,wcr,wf,wk,wn,wr,*ws,wt,zcn,zk,zn,zt;VF ado;
   // oq is used to stack jt->rank in case it is altered by subroutines and we have to retry
 RZ(a&&w);
 an=AN(a); ar=AR(a); as=AS(a); at=AT(a);   // #,x  #$x  address of $x   type of x
 wn=AN(w); wr=AR(w); ws=AS(w); wt=AT(w);   // #,y  #$y  address of $y   type of y
 // If an operand is empty, turn it to Boolean, and if the OTHER operand is non-numeric, turn that to Boolean too (leaving
 //  rank and shape untouched).  This change to the other operand is notional only - we won't actually convert
 // when there is an empty - but it guarantees that execution on n empty never fails.
 // If we switch a sparse nonnumeric matrix to boolean, that may be a space problem; but we don't
 // support nonnumeric sparse now
 if(an==0){at=B01;if(!(wt&NUMERIC))wt=B01;}  // switch empty arg to Boolean & ensure compatibility with other arg
 if(wn==0){wt=B01;if(!(at&NUMERIC))at=B01;}
 // if an operand is sparse, remember that fact and replace its type with the corresponding non-sparse type
 if(SPARSE&at){sp=1; at=DTYPE(at);}
 if(SPARSE&wt){sp=1; wt=DTYPE(wt);}
 // Analyze the rank and calculate cell shapes and counts.  Not byte sizes yet, since there may be conversions
 // We detect agreement error before domain error
 if(jt->rank){
  // Here, a rank was specified.
  r=jt->rank[0]; acr=MIN(ar,r); af=ar-acr; acn=prod(acr,as+af);  // r=left rank of verb, acr=effective rank, af=left frame, acn=left #cells
  r=jt->rank[1]; wcr=MIN(wr,r); wf=wr-wcr; wcn=prod(wcr,ws+wf); // r=right rank of verb, wcr=effective rank, wf=right frame, wcn=left #cells
      // note: the prod above can never fail, because it gives the actual # cells of an existing noun
  // Now that we have used the rank info, clear jt->rank.  All verbs start with jt->rank=0 unless they have "n applied
  // we do this before we generate failures
  jt->rank=0;
  // if the frames don't agree, that's always an agreement error
  ASSERT(!ICMP(as,ws,MIN(af,wf)),EVLENGTH);  // frames must match to the shorter length; agreement error if not
  c=af<=wf; f=c?wf:af; q=c?af:wf; sf=c?ws:as;   // c='right frame is longer'; f=#longer frame; q=#shorter frame; sf->shape of arg with longer frame
  b=acr<=wcr; zcn=b?wcn:acn; m=b?acn:wcn; n=m?zcn/m:0; r=b?wcr:acr; s=b?ws+wf:as+af;   // b='right cell has larger rank'; zcn=#cells in arg with larger rank (=#result cells);
    // m=#cells in arg with shorter rank; n=#times shorter-rank cells must be repeated; r=larger of cell-ranks; s->shape of larger-rank cell
 }else{
  // No rank specified.  Since all these verbs have rank 0, that simplifies quite a bit
  ASSERT(!ICMP(as,ws,MIN(ar,wr)),EVLENGTH);   // agreement error if not prefix match
  af=wf=f=0; acr=ar; wcr=wr; sf=0; mf=nf=1;  // with mf==1, there will be only one call to ado, so most of these names could be left alone except for sparse, and compiler warnings
  b=ar<=wr; zn=b?wn:an; m=b?an:wn; n=m?zn/m:0; r=b?wr:ar; s=b?ws:as;   // treat the entire operands as one big cell; get the rest of the values needed
  c=2;  // flag to indicate 'no rank specified'
 }
 if(id==CEXP&&1==wn&&FL&wt&&0.5==*DAV(w))R sqroot(a);  // Now that we have checked for agreement, switch ^&0.5 to %: to use hardware.  jt->rank is immaterial in that case
// analyze the verb/operands, returning ado, the address of the action routine for the
 // computation, and cv, the flags indicating the types selected for the arguments and the result.
 // Extract zt, the type of the result, and t, the type to use for the arguments
 RZ(var(id,a,w,at,wt,&ado,&cv)); zt=rtype(cv); t=atype(cv);
 // If a single input type has been selected (as it will have been for all verbs except = and ~: which
 // can handle any types); AND if both arguments are non-sparse: convert them to the selected type.
 // Incompatible arguments were detected in var().  If there is an empty operand, skip conversions which
 // might fail because the type in t is incompatible with the actual type in a
 if(t&&!sp&&an&&wn){B xn = !!(t&XNUM);
  // Conversions to XNUM use a routine that pushes/sets/pops jt->mode, which controls the
  // type of conversion to XNUM in use.
  if(TYPESNE(t,at))RZ(a=xn?xcvt((cv&VXCVTYPEMSK)>>VXCVTYPEX,a):cvt(t,a));
  if(TYPESNE(t,wt))RZ(w=xn?xcvt((cv&VXCVTYPEMSK)>>VXCVTYPEX,w):cvt(t,w));
 }
 // From here on we have possibly changed the address of a and w, but we are still using shape pointers,
 // rank, type, etc. using the original input block.  That's OK.

 // finish up the computation of sizes.  We have to defer this till after var() because
 // if we are retrying the operation, we may be in error state until var clears it; and prod and mult can fail,
 // so we have to RE when we call them
 if(sp){z=vasp(a,w,id,ado,cv,t,zt,af,acr,wf,wcr,f,r); if(!jt->jerr)R z;}  // handle sparse srrays separately
 else{
   // If rank given, calculate the numbers of loops to do
  if(c!=2) {  // if rank was given initially...
   RE(mf=prod(q,sf)); RE(nf=prod(f-q,q+sf));//else mf=nf=0;  // mf=#cells in common frame, nf=#times shorter-frame cell must be repeated.  Not needed if no cells
   RE(zn=mult(mf,mult(nf,zcn)));  // zn=total # result atoms  (only if non-sparse)
   // if the cell-shapes don't match, that's an agreement error UNLESS the frame contains 0; in that case it counts as
   // 'error executing on the cell of fills' and produces a scalar 0 as the result for that cell, which we handle by changing the result-cell rank to 0
   // Nonce: continue giving the error even when frame contains 0 - remove 1|| to conform to fill-cell rules
   if(ICMP(as+af,ws+wf,MIN(acr,wcr))){if(1||zn)ASSERT(0,EVLENGTH)else r = 0;}
   // if looping required, calculate the strides for input & output
   if((mf|nf)>1){zk=zcn*bp(zt); ak=acn*bp(AT(a)); wk=wcn*bp(AT(w));}//else {ak=wk=zk=0;}
   // zk=result-cell size in bytes; ak,wk=left,right arg-cell size in bytes.  Not needed if not looping
  }
  // Not sparse.  Allocate a result area of the right type, and copy in its cell-shape after the frame
  GA(z,zt,zn,f+r,sf); ICPY(f+AS(z),s,r); 
  if(!zn)R z;  // If the result is empty, the allocated area says it all
  av=CAV(a); wv=CAV(w); zv=CAV(z);   // point to the data
  // Call the action routines: 
  if(1==nf) DO(mf,        ado(jt,b,m,n,zv,av,wv); zv+=zk; av+=ak; wv+=wk;)  // if the short cell is not repeated, loop over the frame
  else if(c)DO(mf, DO(nf, ado(jt,b,m,n,zv,av,wv); zv+=zk;         wv+=wk;); av+=ak;)  // if right frame is longer, repeat cells of a
  else      DO(mf, DO(nf, ado(jt,b,m,n,zv,av,wv); zv+=zk; av+=ak;        ); wv+=wk;);  // if left frame is longer, repeat cells of w
  // The work has been done.  If there was no error, check for optional conversion-if-possible
  if(!jt->jerr)R cv&VRI+VRD?cvz(cv,z):z;
 }
 // If we got an internal-only error during execution of the verb, restart to see if it's
 // a recoverable error such an overflow during integer addition.  We have to restore
 // jt->rank, which might have been modified
 R NEVM<jt->jerr?(jt->rank=oq,va2(a,w,id)):0;
}    /* scalar fn primitive and f"r main control */

/*
 acn wcn zcn  # atoms in a cell
 acr wcr r    cell rank
 af  wf  f    frame
 ak  wk  zk   # bytes in a cell
 an  wn  zn   overall # atoms
 ar  wr  f+r  overall rank

 b    1 iff cell rank of a <= cell rank of w
 c    1 iff frame     of a <= frame of w
 m    # of atoms in the cell with the smaller rank
 mf   agreed # of frames
 n    excess # of cell atoms
 nf   excess # of frames
 f    max of frame of a, frame of w
 q    min of frame of a, frame of w
 r    max of cell rank  of a, cell rank  of w
 s    max of cell shape of a, cell shape of w
 sf   max of frame shape of a, frame shape of w
*/



static DF2(jtsumattymes){A z;B b;I an,ar,*as,at,m,n,nn,r,*s,t,wn,wr,*ws,wt,zn;
 RZ(a&&w&&self);
 an=AN(a); ar=AR(a); as=AS(a); at=an?AT(a):B01;
 wn=AN(w); wr=AR(w); ws=AS(w); wt=wn?AT(w):B01; 
 t=maxtype(at,wt); b=ar<=wr; r=b?wr:ar; s=b?ws:as; nn=*s;
 zn=(b?wn:an)/nn; m=(b?an:wn)/nn; m=m?m:1; n=zn/m;
 switch(CTTZNOFLAG(t)){
  case B01X:
   {B*av=BAV(a),u,*wv=BAV(w);I*zu,*zv;
    GATV(z,INT,zn,r-1,1+s); zu=AV(z);
    if(1==n){
              zv=zu; DO(m,                     *zv++ =*av++**wv++;);
     DO(nn-1, zv=zu; DO(m,                     *zv+++=*av++**wv++;););
    }else if(b){
              zv=zu; DO(m, u=*av++;      DO(n, *zv++ =u**wv++;););
     DO(nn-1, zv=zu; DO(m, u=*av++; if(u)DO(n, *zv+++=u**wv++;) else wv+=n;););
    }else{
              zv=zu; DO(m, u=*wv++;      DO(n, *zv++ =u**av++;););
     DO(nn-1, zv=zu; DO(m, u=*wv++; if(u)DO(n, *zv+++=u**av++;) else av+=n;););
   }}
   break;
#if !SY_64
  case INTX:
   {D u,*zu,*zv;I*av=AV(a),*wv=AV(w);
    GATV(z,FL,zn,r-1,1+s); zu=DAV(z);
    if(1==n){
              zv=zu; DO(m,                        *zv++ =*av++*(D)*wv++;);
     DO(nn-1, zv=zu; DO(m,                        *zv+++=*av++*(D)*wv++;););
    }else if(b){
              zv=zu; DO(m, u=(D)*av++;      DO(n, *zv++ =u**wv++;););
     DO(nn-1, zv=zu; DO(m, u=(D)*av++; if(u)DO(n, *zv+++=u**wv++;) else wv+=n;););
    }else{
              zv=zu; DO(m, u=(D)*wv++;      DO(n, *zv++ =u**av++;););
     DO(nn-1, zv=zu; DO(m, u=(D)*wv++; if(u)DO(n, *zv+++=u**av++;) else av+=n;););
    }
    RZ(z=icvt(z));
   }
   break;
#endif
  case FLX:   
   {D*av=DAV(a),u,v,*wv=DAV(w),*zu,*zv;
    GATV(z,FL,zn,r-1,1+s); zu=DAV(z);
    NAN0;
    if(1==n){
              zv=zu; DO(m, u=*av++;            v=*wv++; *zv++ =u&&v?u*v:0;  );
     DO(nn-1, zv=zu; DO(m, u=*av++;            v=*wv++; *zv+++=u&&v?u*v:0;  ););
    }else if(b){
              zv=zu; DO(m, u=*av++;      DO(n, v=*wv++; *zv++ =u&&v?u*v:0;););
     DO(nn-1, zv=zu; DO(m, u=*av++; if(u)DO(n, v=*wv++; *zv+++=   v?u*v:0;) else wv+=n;););
    }else{
              zv=zu; DO(m, u=*wv++;      DO(n, v=*av++; *zv++ =u&&v?u*v:0;););
     DO(nn-1, zv=zu; DO(m, u=*wv++; if(u)DO(n, v=*av++; *zv+++=   v?u*v:0;) else av+=n;););
    }
    NAN1;
 }}
 R z;
}    /* a +/@:* w for non-scalar a and w */

static C sumbf[]={CSTARDOT,CMIN,CSTAR,CPLUSDOT,CMAX,CEQ,CNE,CSTARCO,CPLUSCO,CLT,CLE,CGT,CGE};

#define SUMBFLOOPW(BF)     \
 {DO(q, memset(tv,C0,p); DO(255, DO(dw,tv[i]+=BF(*u,*v); ++u; ++v;);); DO(zn,zv[i]+=tu[i];));  \
        memset(tv,C0,p); DO(r,   DO(dw,tv[i]+=BF(*u,*v); ++u; ++v;);); DO(zn,zv[i]+=tu[i];) ;  \
 }
#define SUMBFLOOPX(BF)     \
 {DO(q, memset(tv,C0,p); DO(255, DO(dw,tv[i]+=BF(*u,*v); ++u; ++v;);                           \
                               av+=zn; u=(UI*)av; wv+=zn; v=(UI*)wv;); DO(zn,zv[i]+=tu[i];));  \
        memset(tv,C0,p); DO(r,   DO(dw,tv[i]+=BF(*u,*v); ++u; ++v;);                           \
                               av+=zn; u=(UI*)av; wv+=zn; v=(UI*)wv;); DO(zn,zv[i]+=tu[i];) ;  \
 }
#if SY_ALIGN
#define SUMBFLOOP(BF)   SUMBFLOOPW(BF)
#else
#define SUMBFLOOP(BF)   if(zn%SZI)SUMBFLOOPX(BF) else SUMBFLOOPW(BF)
#endif

static A jtsumatgbool(J jt,A a,A w,C id){A t,z;B*av,*wv;I dw,n,p,q,r,*s,zn,*zv;UC*tu;UI*tv,*u,*v;
 RZ(a&&w);
 s=AS(w); n=*s;
 zn=AN(w)/n; dw=(zn+SZI-1)/SZI; p=dw*SZI;
 q=n/255; r=n%255;
 GATV(z,INT,zn,AR(w)-1,1+s); zv=AV(z); memset(zv,C0,zn*SZI);
 GATV(t,INT,dw,1,0); tu=UAV(t); tv=(UI*)tu;
 av=BAV(a); u=(UI*)av; 
 wv=BAV(w); v=(UI*)wv;
 switch(id){
  case CMIN: 
  case CSTAR: 
  case CSTARDOT: SUMBFLOOP(AND ); break;
  case CMAX:
  case CPLUSDOT: SUMBFLOOP(OR  ); break;
  case CEQ:      SUMBFLOOP(EQ  ); break;
  case CNE:      SUMBFLOOP(NE  ); break;
  case CSTARCO:  SUMBFLOOP(NAND); break;
  case CPLUSCO:  SUMBFLOOP(NOR ); break;
  case CLT:      SUMBFLOOP(LT  ); break;
  case CLE:      SUMBFLOOP(LE  ); break;
  case CGT:      SUMBFLOOP(GT  ); break;
  case CGE:      SUMBFLOOP(GE  ); break;
 }
 R z;
}    /* a +/@:g w  for boolean a,w where a-:&(* /@$)w; see also plusinsB */

DF2(jtfslashatg){A fs,gs,y,z;B b,bb,sb=0;C*av,c,d,*wv;I ak,an,ar,*as,at,cv,cvf,m,
     n,nn,r,*s,t,wk,wn,wr,*ws,wt,yt,zn,zt;V*sv;VF ado,adof;
 RZ(a&&w&&self);
 an=AN(a); ar=AR(a); as=AS(a); at=an?AT(a):B01; sv=VAV(self); 
 wn=AN(w); wr=AR(w); ws=AS(w); wt=wn?AT(w):B01; b=ar<=wr; r=b?wr:ar; s=b?ws:as; nn=r?*s:1;
 ASSERT(!ICMP(as,ws,MIN(ar,wr)),EVLENGTH);
 if(SPARSE&(at|wt)||!an||!wn||2>nn){b=CFORK==sv->id; R df1(df2(a,w,b?sv->h:sv->g),b?sv->g:sv->f);}
 zn=(b?wn:an)/nn; m=(b?an:wn)/nn; m=m?m:1; n=zn/m;
 if(CFORK==sv->id){fs=sv->g; gs=sv->h;}else{fs=sv->f; gs=sv->g;}
 y=VAV(fs)->f; c=ID(y); d=ID(gs);
 RZ(var(d,mtv,mtv,at,wt,&ado, &cv )); yt=rtype(cv ); t=atype(cv);
 RZ(var(c,mtv,mtv,yt,yt,&adof,&cvf)); zt=rtype(cvf);
 if(c==CPLUS){
  if(at&B01&&wt&B01&&1==n&&(0==zn%SZI||!SY_ALIGN)&&strchr(sumbf,d))R sumatgbool(a,w,d);
  if(d==CSTAR){
   if(ar&&wr&&TYPESEQ(at,wt)&&at&B01+FL+(INT*!SY_64))R sumattymes(a,w,self);
   if(!ar||!wr){
    z=!ar?tymes(a,df1(w,fs)):tymes(w,df1(a,fs));
    if(jt->jerr==EVNAN)RESETERR else R z;
  }}
  sb=1&&yt&B01;
 }
 if(!(sb||TYPESEQ(yt,zt)))R df1(df2(a,w,gs),fs);
 if(t){
  bb=1&&t&XNUM;
  if(TYPESNE(t,at))RZ(a=bb?xcvt((cv&VXCVTYPEMSK)>>VXCVTYPEX,a):cvt(t,a));
  if(TYPESNE(t,wt))RZ(w=bb?xcvt((cv&VXCVTYPEMSK)>>VXCVTYPEX,w):cvt(t,w));
 }
 ak=(an/nn)*bp(AT(a)); wk=(wn/nn)*bp(AT(w));  
 GA(y,yt,zn,1,0); 
 GA(z,zt,zn,r-1,1+s);
 if(sb){A t;I j,tn,*zv;UC*tc;UI*ti,*yv;  /* +/@:g for boolean-valued g */
  av=CAV(a); wv=CAV(w); yv=(UI*)AV(y); zv=AV(z); memset(zv,C0,zn*SZI);
  tn=(zn+SZI-1)/SZI; GATV(t,INT,tn,1,0); tc=UAV(t); ti=(UI*)tc;
  for(j=nn;0<j;j-=255){
   memset(ti,C0,tn*SZI); 
   DO(MIN(j,255), ado(jt,b,m,n,yv,av,wv); av+=ak; wv+=wk; DO(tn,ti[i]+=yv[i];););
   DO(zn, zv[i]+=tc[i];);
 }}else{A z1;B p=0;C*yv,*zu,*zv;
  av=CAV(a)+ak*(nn-1); wv=CAV(w)+wk*(nn-1); yv=CAV(y); zv=CAV(z);
  GA(z1,zt,zn,r-1,1+s); zu=CAV(z1);
  ado(jt,b,m,n,zv,av,wv);
  DO(nn-1, av-=ak; wv-=wk; ado(jt,b,m,n,yv,av,wv); adof(jt,b,zn,1L,p?zv:zu,yv,p?zu:zv); p=!p;);
  if(NEVM<jt->jerr){jt->jerr=0; z=df1(df2(a,w,gs),fs);}else if(p)z=z1;
 }
 RE(0); R z;
}    /* a f/@:g w */
