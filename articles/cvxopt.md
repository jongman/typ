title: 강의노트: Convex Optimization
date: 2014-01-21
categories: 강의노트, WIP
hidden: 1

**WORK IN PROGRESS**

이 메모는 [Stanford online EDX course](https://class.stanford.edu/courses/Engineering/CVX101/Winter2014/about)를 공부하면서 정리한 내용이다. 개인적인 메모용으로 정리한 것이기 때문에 틀릴 여지가 아주 많으며, Convex Optimization에 대해 제대로 배우고 싶은 경우 이것을 보는 것보다 [해당 교수의 책](http://www.stanford.edu/~boyd/cvxbook/)을 참조하라.

이 메모는 **아직 업데이트 되고 있다.**

<!-- PREVIEW_END -->

[TOC]

## Chapter 2: Convex Sets

### Examples of convex sets

* First, we define some examples of convex sets.
* Affine set
	* A set of vectors is **affine** iff any line that goes through two vectors belonging to the set, also belongs to the set: $a, b \in C \implies \theta a + (1 - \theta) b = b + \theta(a - b) \in C$.
	* By induction, you can see that for any number of vectors in $C$, taking a linear combination of them with coefficients summing up to 1 (this is called an *affine combination*) are also within the affine set.
	* Take a random point $x_0 \in C$ and and let $V = {x - x_0 | x \in C}$: then $V$ is a subspace. i.e. closed under scalar multiplication and sums.
		* Therefore, the affine set can also be specified as a subspace and an offset: a good example is a solution set to a system of linear equations!
		* The dimension of this subspace is defined to be the dimension of the original affine set.
	* An **affine hull** of $C$ is defined to be the set of _all_ affine combinations of $C$. Note the way this is defined is analogous to that of convex hull.
	* Notion of relative interior and relative boundary are introduced. $x$ is in the relative interior $\mathbf{relint}C$ iff there is a ball with a positive radius centered at $x$ which intersection with $\mathbf{aff}C$ fits inside $C$.
		* Note it doesn't need a ball to be in $C$ -- its intersection with $\mathbf{aff}C$ needs to be in $C$.
		* Also note relative interior and boundary is not defined when the affine hull spans the entire space ($\mathbf{R}^n$).
* Convex set
	* A set $C$ is convex iff any line segment between two elements in $C$ belongs to $C$ as well.
	* A convex combination is defined as a linear combination of vectors with **nonnegative** coefficients summing up to 1. (This is a special version of affine; therefore an affine set is always convex) It can be shown that a convex set always contains all convex combinations of its elements. 
	* The set of all convex combinations of elements belonging to a set $C$ is called a convex hull; which is the smallest convex set that contains $C$.
* Examples of convex sets
	* Cone: A set is called a cone if it contains all linear combinations of its elements with nonnegative coefficients. That is, $\theta_1, \theta_2 \ge 0$ and $x_1, x_2 \in C$ implies $\theta_1 x_1 + \theta_2 x_2 \in C$.
		* Similarly, a linear combination with nonnegative coefficients is called a conic combination.
	* Hyperplane: defined by a normal vector and an offset. $\{x | a^Tx = b\}$
	* Hyperspace: defined by a hyperplane, and inequality: this is convex but not affine.
	* Euclidean balls: regular balls we are accustomed to; defined by a center vector and a radius. Always uses Euclidean norm, as expected.
	* Elipsoids: stretched versions of Euclidean balls $\{ x | (x-x_c)^T P^{-1} (x-x_c) \le 1 \}$. $P$ is positive definite and symmetric.
	* Norm balls: Euclidean balls with arbitrary norm (see A.1.2); they are convex.
	* Norm cones: $C = \{ (x,t) | \|x\| \le t \}$
	* Polyhedra: intersection of finite number of hyperplanes and hyperspaces.
