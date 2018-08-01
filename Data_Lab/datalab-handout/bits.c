/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  	int ans = ~((~x) | (~y));
	return ans;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  	int t = n << 3;
	int ans = x >> t;
	ans = ans & 0xff;
	return ans;

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	x = x >> n;
	int c = 1 << 31;
	int t = c >> n << 1;//如果是c>>(n-1)则绝大多数情况是对的，但n为0的情况有误！
	t = ~t;
  	return x & t;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
//抄的，大概就是二分法,感觉这是网上比较好理解的一种
int bitCount(int x) {
	int count;
	int tmpMask1 = (0x55) | (0x55<<8);
	int mask1 = (tmpMask1) | (tmpMask1<<16);
	int tmpMask2 = (0x33) | (0x33<<8);
	int mask2 = (tmpMask2) | (tmpMask2<<16);
	int tmpMask3 = (0x0f) | (0x0f<<8);
	int mask3 = (tmpMask3) | (tmpMask3<<16);
	int mask4 = (0xff) | (0xff<<16);
	int mask5 = (0xff) | (0xff<<8);
	count = (x&mask1) + ((x>>1)&mask1);
	count = (count&mask2) + ((count>>2)&mask2);
	count = (count&mask3) + ((count>>4)&mask3);
	count = (count&mask4) + ((count>>8)&mask4);
	count = (count&mask5) + ((count>>16)&mask5); 
	return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	
	/*把所有位数全加起来，和上题类似，但是反过来了
	x |= x >> 16;
	x |= x >> 8;
	x |= x >> 4;
	x |= x >> 2;
	x |= x >> 1;
	return (x & 1) ^ 1;
	*/
	//法二：只有0和Tmin补码的非是他们本身，即符号位一样，其余数和他们的补码的符号位是不同的
	int t = (~x) + 1;//看符号位是否相同
	int k = (x>>31)&1;//区别0和Tmin
	return ((((t^x)>>31)&1)|k)^1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	//补码的扩展数原理
	return !((x << (32-n))>>(32-n) ^ x);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	//直接根据书上的定义求，合并下两种情况就行了
    	int t = (x >> 31) & ((1 << n)-1);
   	return (x+t) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  	return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	int t = x >> 31;
	return (!(t&1))&!!x;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	//主要问题就是溢出问题
	//xy同号则y-x>=0即可
	//xy异号则x为负数，y为正数即可
	int s1 = (x>>31)&1;
	int s2 = (y>>31)&1;
	int num = y+~x+1;
	int t = (num>>31)&1;
	int signsame = (!(s1^s2))&(!t);
	int signdiff = s1&(!s2);
	return signsame | signdiff;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	//不会QAQ
	int s1 = !!(x>>16)<<4;
  	x >>= s1;
 	int s2 = !!(x>>8)<<3;
 	x >>= s2;
	int s3 = !!(x>>4)<<2;
 	x >>= s3;
 	int s4 = !!(x>>2)<<1;
 	x >>= s4;
 	int s5 = !!(x>>1);
	return s1+s2+s3+s4+s5;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	unsigned s = 0x80000000;
	unsigned NaN = 0x7FC00000;
	unsigned inf = 0xFFC00000;
	if(uf == NaN || uf == inf)
		return uf;
	return uf ^ s;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	//看了很多答案,讲的都不清楚，直接抄的，主要有几个细节不懂，整体思路还好
	//https://www.jianshu.com/p/0add4903025e这个解释的算是比较好的了  
	unsigned sign=0,shiftleft=0,flag=0,tmp;
	  unsigned absx=x;
	  if( x==0 ) return 0;
	  if( x<0 ){
	     sign=0x80000000;
	     absx=-x;
  	}
	  while(1){
	     tmp=absx;
   	     absx<<=1;
             shiftleft++;
             if( tmp&0x80000000 ) break;
        }
	 //这里他说是舍入，但我感觉他和书上的舍入不一样啊
 	 if( (absx & 0x01ff) > 0x0100 ) flag=1;
	 if( (absx & 0x03ff) == 0x0300 ) flag=1;
  
	 return sign+(absx>>9)+((159-shiftleft)<<23)+flag;//这里159和书上的那个Bias有关
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
        unsigned exponent = uf & 0x7F800000;  
	unsigned sign = uf & 0x80000000;  
   	if (exponent) {  
      		 if (  exponent != 0x7F800000 ) {
       			 uf = uf + 0x00800000;    
       		 }
   	}
    	else
       	uf = ( uf << 1) | sign ;
    	return uf;
}

//相当一部分不是自己独立做的，应该是我学的太渣了吧，先往后看，有空再回来做点书上的题
