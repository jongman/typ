title: 강의노트: Single Variable Calculus
date: 2014-01-21
categories: 강의노트, WIP
hidden: 1

**WORK IN PROGRESS**

이 메모는 [이 Coursera 코스](https://class.coursera.org/calcsing-004/)를 리캡하면서 정리한 내용이다. 실제로는 [이 위키](http://calculus.seas.upenn.edu/?n=Main.HomePage)의 내용을 다시 정리한 것이다.

이 메모는 **아직 업데이트 되고 있다.**

<!-- PREVIEW_END -->

[TOC]

## Chapter 1: Functions

* Euler's formula: $e^{ix} = \cos x + i \sin x$
* Definition of exponential function:
	* $e^{x} = 1 + x + \frac{x^2}{2!} + \cdots = \sum_{i=0}^{\infty}\frac{x^i}{i!}$ <!--_-->
	* which we treat as an infinitely long polynomials -- a more proper treatment coming later.
* Plugging the above definition to Euler's formula, we get expressions for sin and cos.
	* $\cos x = 1 - \frac{x^2}{2!} + \frac{x^4}{4!} - \cdots$ (Takes even powers)
	* $\sin x = x - \frac{x^3}{3!} + \frac{x^5}{5!} - \cdots$ (Takes odd powers)
* These polynomials are called Taylor series. Definition of Taylor series expanded at $x=0$:
	* $f(x) = f(0) + \frac{f'(0)}{1!}x + \frac{f''(0)}{2!}x^2 + \cdots = \sum_{i=0}^{k}\frac{f^{(i)}}{i!}x^{i}$ <!--_-->
	* It's a way of approximating functions by polynomials in the neighbor of 0.
* Calculating Taylor series from its definition is a daunting task at times. A few tricks are introduced to make the calculation easier:
	* Substitution: if you are calculating expansion of $f \circ g$, put $g$'s expansion in place of $x$ in $f$'s expansion.
	* Combining similar terms: when calculating expansion of $f\cdot g$, substitute their expansions in and group similar terms.
	* Hyperbolic trig functions: additional weapons, just like ordinary trigs which come with their own set of identities.
		* Definitions:
			* $\sinh(x) = \frac{e^{x} - e^{-x}}{2}$
			* $\cosh(x) = \frac{e^{x} + e^{-x}}{2}$
			* $\tanh(x) = \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}} = \frac{\sinh(x)}{\cosh(x)}$
		* Identities:
			* $\cosh^2(x) - \sinh^2(x) = 1$ (which is trivial if you expand them by definition)
	* Manipulating Taylor series: for example, if you want to calculate Taylor series of $f'$, expand $f$ and differentiate them.
	* Ignoring higher order terms: when using substitution, just carry a few terms into the calculation if you are looking for a first few terms.

## Chapter 2: Differentiation

## Chapter 3: Integration

## Chapter 4: Applications

## Chapter 5: Discretization


