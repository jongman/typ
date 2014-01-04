title: 메모: Statistical Inference writeup
date: 2014-01-02
categories: 메모, 통계
hidden: 1

이 메모는 [이 책](http://www.amazon.com/Statistical-Inference-George-Casella/dp/0534243126)을 혼자 읽으면서 정리한 내용이다. 이 글은 남에게 보여주기 위해 쓴 것이 아니라 단지 개인적인 용도를 위해 정리한 것이고, 나는 통계학의 전문가와는 거리가 아주 멀기 때문에, 틀린 내용이 얼마든지 있을 수 있다. 틀린 점은 이메일이나 트위터로 알려주면 고맙겠다.

이 메모는 2014년 들어 쓰기 시작했으며, 아직 업데이트 되고 있다.

<!-- PREVIEW_END -->

----

### 1. Probability Theory

* 기초적인 집합론이랑 확률은 따로 정리 안함.
* [콜모고로프 공리](http://en.wikipedia.org/wiki/Probability_axioms#Axioms)에 의한 확률 함수의 정의. [\$\sigma\$-algebra](http://en.wikipedia.org/wiki/Sigma-algebra)에 대해 정의됨. 콜모고로프 공리로 정의된 확률함수는 현실 세계와의 관계는 없음. 
* [Bonferroni's Inequality](http://en.wikipedia.org/wiki/Boole's_inequality#Bonferroni_inequalities) is useful for having a gut estimation of lower bound for events that are hard or impossible to calculate probabilities for. It is equivalent to Boole's inequality.
	* Is a generalization of: \$P(A \cap B) \ge P(A) + P(B) - 1\$. 
	* Proof: \$P(A \cup B) = P(A) + P(B) - P(A \cap B)\$. Rearranging, we get \$P(A \cap B) = P(A) + P(B) - P(A \cup B) \ge P(A) + P(B) - 1\$.
* Random variables: function mapping from sample space to real numbers.

### 2. Transformations and Expectations

* Section 2.1 covers functions of random variables and how to derive their cdf from the cdf of the original random variable.
	* The only way to do this seems to be for monotone functions, or at least piecewise monotone functions. (You should be able to partition \$\chi\$ (the domain of the original random variable) into contiguous sets where in each partition, the function is monotone.)
	* What if the function \$Y = g(X)\$ is monotone? 
		* If it is monotonically increasing, \$F_Y(y) = P(Y \le y) = P(g(x) \le y) = P(x \le g^{-1}(y)) = F_X(g^{-1}(y))\$.
		* If it is monotonically decreasing, \$F_Y(y) = P(Y \le y) = P(g(x) \le y) = P(x \ge g^{-1}(y)) = 1 - F_X(g^{-1}(y))\$.
	* Of course, you can differentiate these cdfs to get pdfs of the transformations. You don't have to expand the full equation and differentiate it; you can use chain rule to use \$f_X\$.
	* **Probabiliy integral transformation**: If \$X\$ has a cdf \$F_X\$, and we say \$Y = F_X(X)\$, then \$Y\$ is uniformly distributed on \$(0,1)\$.
		* This can be understood intuitively -- let \$F_X(x) = y\$. Then \$P(Y \le y) = P(X \le x) = F_X(x) = y\$. This of course assumes monotonicity on \$F_X\$'s part, which is not always true, but this can be treated technically.
	* Section 2.2 talks about definition of expected values and their properties.
	* Linearity of expectation follows from integration which is how EVs are defined. 
	* When you are doing nonlinear transformation of expected values, you have two choices:
		1. Calculate EVs directly from definition
		2. Find pdf of \$y = g(x)\$ by transforming cdf of \$X\$ and differentiating; and then you can integrate regarding \$y\$.
* Section 2.3 talks about moments and mgfs.
	* Definitions
		* The \$n\$th moment of \$X\$, \$\mu'_n\$ is defined by \$E(X^{n})\$.
		* The \$n\$th central moment of \$X\$, \$\mu_n\$ is defined by \$E((X - \mu)^{n})\$.

