/* Copyright 1990-2014, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Global Definitions                                                      */

#ifndef SYS // include js.h only once - dtoa.c
#include "js.h"
#endif

// If you are porting to a new compiler or architecture, see the bottom of this file
// for instructions on defining the CTTZ macros

#if SY_WINCE
#include "..\cesrc\cecompat.h"
#endif

#if (SYS & SYS_PCWIN)
#define HEAPCHECK  heapcheck()
#else
#define HEAPCHECK
#endif

#if (SYS & SYS_ATARIST)
#define __NO_INLINE__           1
#endif

#if (SYS & SYS_UNIX - SYS_SGI)
#include <memory.h>
#include <sys/types.h>
#endif

#if 1
#include <float.h>
#include <limits.h>
#define link unused_syscall_link
#define qdiv unused_netbsd_qdiv
#include <stdlib.h>
#undef link
#undef qdiv
#else
#define const /*nothing*/   /* blame rx.h */
#endif

#if ! SY_WINCE
#include <errno.h>
#include <stdio.h>
#endif

#include <math.h>
#include <string.h>  


#if SY_64
#define IMAX            9223372036854775807L
#define FMTI            "%lli"
#define FMTI02          "%02lli"
#define FMTI04          "%04lli"
#define FMTI05          "%05lli"

#if SY_WIN32
#define strtoI         _strtoi64
#else
#define strtoI          strtoll
#endif

#else
#define IMAX            2147483647L
#define FMTI            "%li"
#define FMTI02          "%02li"
#define FMTI04          "%04li"
#define FMTI05          "%05li"
#define strtoI          strtol
#endif

#define IMIN            (~IMAX)   /* ANSI C LONG_MIN is  -LONG_MAX */


#if (SYS & SYS_AMIGA)
#define XINF            "\177\377\000\000\000\000\000\000"
#define XNAN            "\177\361\000\000\000\000\000\000"
#endif

#if (SYS & SYS_ARCHIMEDES)
#define XINF            "\000\000\360\177\000\000\000\000"
#define XNAN            "\000\000\370\377\000\000\000\000"
#endif

#if (SYS & SYS_DEC5500) || SY_WINCE_SH
#define XINF            "\000\000\000\000\000\000\360\177"
#define XNAN            "\000\000\000\000\000\000\370\377"
#endif

#if (SYS & SYS_MACINTOSH)
/* for old versions of ThinkC */
/* #define XINF         "\177\377\000\000\000\000\000\000\000\000\000\000" */
/* #define XNAN         "\377\377\100\000\100\000\000\000\000\000\000\000" */
/* for ThinkC 7.0 or later */
#define XINF            "\177\377\177\377\000\000\000\000\000\000\000\000"
#define XNAN            "\377\377\377\377\100\000\000\000\000\000\000\000"
#endif

#if (SYS & SYS_SUN4+SYS_SUNSOL2)
#define XINF            "\177\360\000\000\000\000\000\000"
#define XNAN            "\177\377\377\377\377\377\377\377"
#endif

#if (SYS & SYS_VAX)
#define XINF            "\377\177\377\377\377\377\377\377"
#define XNAN            "\377\177\377\377\377\377\377\376" /* not right */
#endif

#if (SY_WINCE_MIPS || SY_WINCE_SH)
#if WIN32_PLATFORM_PSPC
#define XINF            "\000\000\000\000\000\000\360\177"
#define XNAN            "\377\377\377\377\377\377\367\177"
#else
#define XINF            "\000\000\000\000\000\000\360\177"
#define XNAN            "\001\000\000\000\000\000\360\177"
#endif
#endif

#if SY_WINCE_ARM
#define XINF            "\000\000\000\000\000\000\360\177"
#define XNAN            "\000\000\000\000\000\000\370\177"
#endif

#if C_LE
#ifndef XINF
#define XINF            "\000\000\000\000\000\000\360\177"
#define XNAN            "\000\000\000\000\000\000\370\377"
#endif
#endif

#ifndef XINF
#define XINF            "\177\360\000\000\000\000\000\000"
#define XNAN            "\177\370\000\000\000\000\000\000"
#endif


#ifndef PI
#define PI              ((D)3.14159265358979323846)
#endif
#define P2              ((D)6.28318530717958647693)
#ifndef OVERFLOW
#define OVERFLOW        ((D)8.988465674311578e307)
#endif
#ifndef UNDERFLOW
#define UNDERFLOW       ((D)4.450147717014403e-308)
#endif


#define NALP            256             /* size of alphabet                */
#define NETX            2000            /* size of error display buffer    */
#define NPP             20              /* max value for quad pp           */
#define RMAX            IMAX            /* max rank                        */
#define NPATH           1024            /* max length for path names,      */
                                        /* including trailing 0 byte       */
#define NFDEP           20000L             // fn call depth
#define NFCALL          (MAX(40,NFDEP/10)) // call depth for named calls - can be expensive
#define NTSTACK         2000L           /* size of stack for temps         */

#define IIDOT           0               /* modes for indexofsub()          */
#define IICO            1
#define INUBSV          2
#define INUB            3
#define ILESS           4
#define INUBI           5
#define IEPS            6
#define II0EPS          7
#define II1EPS          8
#define IJ0EPS          9
#define IJ1EPS          10
#define ISUMEPS         11
#define IANYEPS         12
#define IALLEPS         13
#define IIFBEPS         14

#define IPHOFFSET       30              /* offset for prehashed versions   */
#define IPHIDOT         30
#define IPHICO          31
#define IPHLESS         34
#define IPHEPS          36
#define IPHI0EPS        37
#define IPHI1EPS        38
#define IPHJ0EPS        39
#define IPHJ1EPS        40
#define IPHSUMEPS       41
#define IPHANYEPS       42
#define IPHALLEPS       43
#define IPHIFBEPS       44

#define jfloor          floor

#define BB              8      /* # bits in a byte */
#if SY_64
#define BW              64     /* # bits in a word */
#else
#define BW              32
#endif

#define ABS(a)          (0<=(a)?(a):-(a))
#define ACX(a)          {AC(a)=IMAX/2;}
#define ASSERT(b,e)     {if(!(b)){jsignal(e); R 0;}}
#define ASSERTD(b,s)    {if(!(b)){jsigd((s)); R 0;}}
#define ASSERTMTV(w)    {RZ(w); ASSERT(1==AR(w),EVRANK); ASSERT(!AN(w),EVLENGTH);}
#define ASSERTN(b,e,nm) {if(!(b)){jt->curname=(nm); jsignal(e); R 0;}}
#define ASSERTSYS(b,s)  {if(!(b)){jsignal(EVSYSTEM); jtwri(jt,MTYOSYS,"",(I)strlen(s),s); R 0;}}
#define ASSERTW(b,e)    {if(!(b)){if((e)<=NEVM)jsignal(e); else jt->jerr=(e); R;}}
#define CALL1(f,w,fs)   ((f)(jt,    (w),(A)(fs)))
#define CALL2(f,a,w,fs) ((f)(jt,(a),(w),(A)(fs)))
#define DF1(f)          A f(J jt,    A w,A self)
#define DF2(f)          A f(J jt,A a,A w,A self)
#define DO(n,stm)       {I i=0,_n=(n); for(;i<_n;i++){stm}}
#define DQ(n,stm)       {I i=(n)-1;    for(;i>=0;--i){stm}}
#define ds(c)           pst[(UC)(c)]
#define EPILOG(z)       R gc(z,_ttop)
#define FDEPDEC(d)      {jt->fdepi-=d;}
#define FDEPINC(d)      {ASSERT(jt->fdepn>=d+jt->fdepi,EVSTACK); jt->fdepi+=d;}
#define FCONS(x)        fdef(CFCONS,VERB,jtnum1,jtnum2,0L,0L,(x),0L,RMAX,RMAX,RMAX)
#define FEQ(u,v)        (ABS((u)-(v))<=jt->fuzz*MAX(ABS(u),ABS(v)))
#define F1(f)           A f(J jt,    A w)
#define F2(f)           A f(J jt,A a,A w) 
#define F1RANK(m,f,self)    {RZ(   w); if(m<AR(w)         )R rank1ex(  w,(A)self,(I)m,     f);}  // if there is more than one cell, run rank1ex on it.  m=monad rank, f=function to call for monad cell
#define F2RANK(l,r,f,self)  {RZ(a&&w); if(l<AR(a)||r<AR(w))R rank2ex(a,w,(A)self,(I)l,(I)r,f);}  // If there is more than one cell, run rank2ex on them.  l,r=dyad ranks, f=function to call for dyad cell
#define GA(v,t,n,r,s)   RZ(v=ga(t,(I)(n),(I)(r),(I*)(s)))
#define HN              3L
#define IC(w)           (AR(w) ? *AS(w) : 1L)
#define ICMP(z,w,n)     memcmp((z),(w),(n)*SZI)
#define ICPY(z,w,n)     memcpy((z),(w),(n)*SZI)
#define INF(x)          ((x)==inf||(x)==infm)
#define IX(n)           apv((n),0L,1L)
#define JATTN           {if(*jt->adbreak&&!jt->breakignore){jsignal(EVATTN); R 0;}}
#define JBREAK0         {if(2<=*jt->adbreak&&!jt->breakignore){jsignal(EVBREAK); R 0;}}
#define MAX(a,b)        ((a)>(b)?(a):(b))
#define MC              memcpy
#define MIN(a,b)        ((a)<(b)?(a):(b))
#define MLEN            (SY_64?63:31)
#define NAN0            (_clearfp())
#define NAN1            {if(_SW_INVALID&_clearfp()){jsignal(EVNAN); R 0;}}
#define NAN1V           {if(_SW_INVALID&_clearfp()){jsignal(EVNAN); R  ;}}
#define PROLOG          I _ttop=jt->tbase+jt->ttop
#define R               return
#define RE(exp)         {if((exp),jt->jerr)R 0;}
#define RER             {if(er){jt->jerr=er; R;}}
#define RESETERR        {jt->etxn=jt->jerr=0;}
#define RNE(exp)        {R jt->jerr?0:(exp);}
#define RZ(exp)         {if(!(exp))R 0;}
#define SBSV(x)         (jt->sbsv+(I)(x))
#define SBUV(x)         (jt->sbuv+(I)(x))
#define SGN(a)          ((0<(a))-(0>(a)))
#define SMAX            65535
#define SMIN            (-65536)
#define SZA             ((I)sizeof(A))
#define SZD             ((I)sizeof(D))
#define SZI             ((I)sizeof(I))
#define VAL1            '\001'
#define VAL2            '\002'

#if C_LE
#define B0000   0x00000000
#define B0001   0x01000000
#define B0010   0x00010000
#define B0011   0x01010000
#define B0100   0x00000100
#define B0101   0x01000100
#define B0110   0x00010100
#define B0111   0x01010100
#define B1000   0x00000001
#define B1001   0x01000001
#define B1010   0x00010001
#define B1011   0x01010001
#define B1100   0x00000101
#define B1101   0x01000101
#define B1110   0x00010101
#define B1111   0x01010101
#define BS00    0x0000
#define BS01    0x0100
#define BS10    0x0001
#define BS11    0x0101
#else
#define B0000   0x00000000
#define B0001   0x00000001
#define B0010   0x00000100
#define B0011   0x00000101
#define B0100   0x00010000
#define B0101   0x00010001
#define B0110   0x00010100
#define B0111   0x00010101
#define B1000   0x01000000
#define B1001   0x01000001
#define B1010   0x01000100
#define B1011   0x01000101
#define B1100   0x01010000
#define B1101   0x01010001
#define B1110   0x01010100
#define B1111   0x01010101
#define BS00    0x0000
#define BS01    0x0001
#define BS10    0x0100
#define BS11    0x0101
#endif

#include "ja.h" 
#include "jc.h" 
#include "jtype.h" 
#include "jt.h" 
#include "jlib.h"
#include "je.h" 
#include "jerr.h" 
#include "va.h" 
#include "vq.h" 
#include "vx.h" 
#include "vz.h"
#include "vdx.h"  
#include "m.h"
#include "a.h"
#include "s.h"


// CTTZ(w) counts trailing zeros in low 32 bits of w.  Result is undefined if w is 0.
// CTTZZ(w) does the same, but returns 32 if w is 0
// CTLZ would be a better primitive to support, except that LZCNT executes as BSR on some Intel processors,
// but produces incompatible results! (BSR returns bit# of leading 1, LZCNT returns #leading 0s)
// since we don't require CTLZ yet, we defer that problem to another day

// CTTZ uses the single-instruction count-trailing-zeros instruction to convert
// a 1-bit mask to a bit number.  If this instruction is available on your architecture/compiler,
// you should use the compiler intrinsic to create this instruction, and define the CTTZ and CTTZZ
// macros to use the instruction inline.  It is used enough in the J engine to make a difference.

// If you set AUDITCOMPILER to 1, i.c will include code to test CTTZ (and signed shift) on startup and crash if it
// does not perform properly, as a debugging aid.

// If CTTZ is not defined, the default routine defined in u.c will be used.  You can look there
// for the complete spec for CTTZ and CTTZZ.

#if SY_WIN32 
#include <intrin.h>
#define CTTZ(w) _tzcnt_u32((UINT)(w))
#define CTTZZ(w) ((w)==0 ? 32 : CTTZ(w))
#endif

#if SY_LINUX || SY_MAC
#define CTTZ(w) __builtin_ctzl((UINT)(w))
#define CTTZZ(w) ((w)==0 ? 32 : CTTZ(w))
#endif

// Insert other compilers/architectures here

// Insert CTLZ here if CTTZ is not available

// If your machine supports count-leading-zeros but not count-trailing-zeros, you can define the macro
// CTLZ, which returns the number of high-order zeros in the low 32 bits of its argument, and the following
// CTTZ will be defined:
#if defined(CTLZ) && !defined(CTTZ)
#define CTTZ(w) (31-CTLZ((w)&-(w)))
#define CTTZZ(w) (0xffffffff&(w) ? CTTZ(w) : 32)
#endif

// If CTTZ is not defined, the following code will use the default from u.c:
#if !defined(CTTZ)
extern I CTTZ(I);
extern I CTTZZ(I);
#endif

// Set these switches for testing
#define AUDITBP 0  // Verify that bp() returns expected data
#define AUDITCOMPILER 0  // Verify compiler features CTTZ, signed >>


// JPFX("here we are\n")
// JPF("size is %i\n", v)
// JPF("size and extra: %i %i\n", (v,x))
#define JPFX(s)  {char b[1000]; sprintf(b, s);    jsto(gjt,MTYOFM,b);}
#define JPF(s,v) {char b[1000]; sprintf(b, s, v); jsto(gjt,MTYOFM,b);}
extern J gjt; // global for JPF (procs without jt)

// #if SY_WINCE_MIPS || defined(__arm__)
// changed to add option -fsigned-char for android and raspberry
#if SY_WINCE_MIPS
/* strchr fails for CE MIPS - neg chars - spellit fails in ws.c for f=.+.  */
#define strchr(a,b)     (C*)strchr(a, (UC)b)
#endif

#if SYS & SYS_UNIX
#include <fenv.h>
#define _isnan       isnan
#define _SW_INVALID  FE_INVALID

static inline UINT _clearfp(void){int r=fetestexcept(FE_ALL_EXCEPT);
 feclearexcept(FE_ALL_EXCEPT); return r;
}
#endif
