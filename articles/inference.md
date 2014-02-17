title: 강의노트: Statistical Inference writeup
date: 2014-01-02
categories: 강의노트, 통계, WIP
hidden: 1

**WORK IN PROGRESS**

이 메모는 [이 책](http://www.amazon.com/Statistical-Inference-George-Casella/dp/0534243126)을 혼자 읽으면서 정리한 내용이다. 이 글은 남에게 보여주기 위해 쓴 것이 아니라 단지 개인적인 용도를 위해 정리한 것이고, 나는 통계학의 전문가와는 거리가 아주 멀기 때문에, 틀린 내용이 얼마든지 있을 수 있다. 틀린 점은 이메일이나 트위터로 알려주면 고맙겠다.

이 메모는 **아직 업데이트 되고 있다.**

<!-- PREVIEW_END -->

[TOC]

----

### 1. Probability Theory

* 기초적인 집합론이랑 확률은 따로 정리 안함.
* [콜모고로프 공리](http://en.wikipedia.org/wiki/Probability_axioms#Axioms)에 의한 확률 함수의 정의. [$\sigma$-algebra](http://en.wikipedia.org/wiki/Sigma-algebra)에 대해 정의됨. 콜모고로프 공리로 정의된 확률함수는 현실 세계와의 관계는 없음. 
* [Bonferroni's Inequality](http://en.wikipedia.org/wiki/Boole's_inequality#Bonferroni_inequalities) is useful for having a gut estimation of lower bound for events that are hard or impossible to calculate probabilities for. It is equivalent to Boole's inequality.
	* Is a generalization of: $P(A \cap B) \ge P(A) + P(B) - 1$. 
	* Proof: $P(A \cup B) = P(A) + P(B) - P(A \cap B)$. Rearranging, we get $P(A \cap B) = P(A) + P(B) - P(A \cup B) \ge P(A) + P(B) - 1$.
* Random variables: function mapping from sample space to real numbers.

### 2. Transformations and Expectations

#### Transformations of random variables

* Section 2.1 covers functions of random variables and how to derive their cdf from the cdf of the original random variable.
	* The only way to do this seems to be for monotone functions, or at least piecewise monotone functions. (You should be able to partition $\chi$ (the domain of the original random variable) into contiguous sets where in each partition, the function is monotone.)
	* What if the function $Y = g(X)$ is monotone? 
		* If it is monotonically increasing, $F_Y(y) = P(Y \le y) = P(g(x) \le y) = P(x \le g^{-1}(y)) = F_X(g^{-1}(y))$.
		* If it is monotonically decreasing, $F_Y(y) = P(Y \le y) = P(g(x) \le y) = P(x \ge g^{-1}(y)) = 1 - F_X(g^{-1}(y))$.
	* When you have pdf of original variable, you don't have to integrate and convert the CDF; instead you can derive the following relationship using chain rule. 
		* $f_Y(y) = f_X(g^{-1}(y)) \left | \frac{d}{dy}g^{-1}(y) \right |$ 
	* If $g$ is _not_ monotonic, but its domain can be partitioned into multiple contiguous intervals $A_1, A_2, \cdots$, then let $g^{-1}_1, g^{-1}_2, \cdots$ be inverses of $g$ on each of those intervals. And we have
		* $f_Y(y) = \sum(f_X(g_{i}^{-1}(y))\left| \frac{d}{dy}g^{-1}_i(y) \right|$
		* So we can sum each interval! A marvelous, and very useful, result.
	* **Probability integral transformation**: If $X$ has a cdf $F_X$, and we say $Y = F_X(X)$, then $Y$ is uniformly distributed on $(0,1)$.
		* This can be understood intuitively -- let $F_X(x) = y$. Then $P(Y \le y) = P(X \le x) = F_X(x) = y$. This of course assumes monotonicity (thus 1-to-1) on $F_X$'s part, which is not always true, but this can be treated technically.

#### Expected values

* Section 2.2 talks about definition of expected values and their properties.
	* Linearity of expectation follows from integration which is how EVs are defined. 
	* When you are doing nonlinear transformation of expected values, you have two choices:
		1. Calculate EVs directly from definition
		2. Find pdf of $y = g(x)$ by 1. transforming cdf of $X$ and differentiating or 2. using the above theorem. Then you can integrate regarding $y$.

#### Moments and moment generating functions

* Section 2.3 talks about moments and mgfs.
	* Definitions
		* The $n$th moment of $X$, $\mu'_n$ is defined by $E(X^{n})$.
		* The $n$th central moment of $X$, $\mu_n$ is defined by $E((X - \mu)^{n})$.
		* Moment generation function of random variable $X$ is defined as: $M_X(t) = E(e^{tX}) = \int_x e^{tx} f_X(x) dx$. 
	* Variance is defined in terms of the second central moment. Also, of course, $\mathrm{Var}X = \mathrm{E}X^2 - (\mathrm{E}X)^2$.
	* $\mathrm{Var}(aX+b) = a^2 \mathrm{Var}(X) + b$
	* Moment generating functions can generate moments: $\frac{d^{n}}{dt^{n}}M_X(0) = EX^{n}$. This can be proven from the definition easily.
	* All distribution can have an infinite number of moments. These can be used to uniquely identify distributions. In all cases, all the moments must exist. And either
		a. Both random variables have bounded support
		b. All mgfs exist and they agree in some neighborhood of 0
	* A theorem regarding the convergence of mgfs (2.3.12) is introduced as an example application but I believe it hard to be practical?

### 3. Common Families of Distribution

#### Discrete distributions

* Section 3.2 introduces various discrete distributions and their properties.
* **Discrete uniform distribution**: the simplest of sorts.
	* pmf, EV and Var: both can be trivially derived by summation identities.
		* $P(X = x | N) = \frac{1}{N}$, $x \in {1, 2, 3, \cdots, N}$
		* $EX = \frac{N+1}{2}$, $\mathrm{Var}X = \frac{(N+1)(N-1)}{12}$.
* **Hypergeometric distribution**: Say we have a population of size $N$, of which $M$ has a desired property. We take a sample of size $K$ (typically $K \ll M$). What is the probability that $x$ of those samples have this probability?
	* pmf, EV and var: pmf is derived from counting principles, EV and Var from a similar manner to binomial distribution: rewrite the sum as sum of hypergeometric pmf for a smaller parameter set which equals 1.
		* $P(X=x|N,M,K) = \frac{\left(M \atop x\right ) \left( {N-M} \atop {K-x} \right )}{\left( N \atop K \right )}$
		* $EX = \frac{KM}{N}$, $\mathrm{Var}X = \frac{KM}{N}\left( \frac{(N-M)(N-K)}{N(N-1)} \right )$. (Var's derivation is omitted)
* **Binomial distribution**
	* pmf, EV and Var:
		* $P(X = x|N, p) = \left(N \atop x \right )p^x (1-p)^{N-x}$
		* $EX = np$, $\mathrm{Var}X = np(1-p)$.
* **Poisson distribution**
	* pmf, EV and Var:
		* $P(X=x|\lambda) = \frac{e^{-\lambda}\lambda^{x}}{x!}$
		* $EX = \mathrm{Var}X = \lambda$.
	* When a binomial distribution has $p$ very small, it can be reasonably approximated by a Poisson distribution as shown using mgf in chapter 2. Let $\lambda = np$.
* **Negative binomial distribution**: If we want to know the number of Bernoulli trials required to get $r$ successes? => Interested in number of failures before $r$th success.
	* pmf, EV and Var:
		* $P(Y=y) = (-1)^y \left ( -r \atop y \right )p^r(1-p)^y = \left({r + y - 1} \atop y\right)p^r(1-p)^y$
		* $EY = r\frac{1-p}{p}$ (Proof: you can find expected number of failures before each success and sum them because linearity. Hooray!)
		* $\mathrm{Var}Y = \frac{r(1-p)}{p^2} = \mu + \frac{1}{r}\mu^2$
	* Negative binomial family includes Poisson as a limiting case.. not sure if this is of significance.
* **Geometric distribution** is a simple case of negative binomial distribution with $r=1$. Let $X$ be the number of trial at which the first success occurs.
	* pmf, EV and Var:
		* $P(X=x) = p(1-p)^{x-1}$
		* $EX = \frac{1}{p}$
		* $\mathrm{Var}X = \frac{1-p}{p^2}$
	* "Memoryless" property: history so far has no influence (= no memory) on what will happen whatsoever:
		* $P(X>s|X>t) = P(X>s-t)$

#### Continuous distributions

* Section 3.3 introduces continuous distributions.
* **Uniform distribution**
* **Gamma distribution**
	* Gamma function $\Gamma$ is defined as:
		* $\Gamma(\alpha) = \int_{0}^{\infty}t^{\alpha-1}e^{-t}dt$
		* which has a closed form when $\alpha$ is a positive integer. 
		* Also, the gamma function serves as a generalization of factorial function: 
			* $\Gamma(\alpha+1) = \alpha\Gamma(\alpha)$ if $\alpha > 0$.
			* Thus, $\Gamma(n) = (n-1)!$ for integers.
			* This property makes Gamma functions easy to evaluate only if we know its values between 0 and 1.
	* The function $f(t) = \frac{t^{\alpha-1}e^{-t}}{\Gamma(\alpha)}$ is a pdf now.
	* The full Gamma family includes one more parameter:
		* $f(x|\alpha, \beta) = \frac{1}{\Gamma(\alpha)\beta^{\alpha}}x^{\alpha-1}e^{-x/\beta}$
		* $\alpha$ is the shape parameter (determines peakedness), $\beta$ is the scale parameter (determines spreadness).
	* pdf, EV and Var:
		* $EX = \alpha\beta$
		* $\mathrm{Var}X = \alpha\beta^2$
	* Relations to other distributions 
		* $P(X\le x) = P(Y \ge \alpha)$ where $Y \sim \mathrm{Poisson}(x/\beta)$.
		* When $\alpha=p/2$ ($p$ is an integer) and $\beta=2$, it becomes a chi-squared pdf with $p$ degrees of freedom.
		* When we set $\alpha=1$, it becomes the exponential distribution pdf with scale parameter $\beta$. (The exponential distributoin is like a continuous cousin of the geometric distribution.)
		* It is also related to the Weibull distribution, which is useful for analyzing failure time data and modeling hazard functions.
	* Application: mostly related with lifetime testing, etc
* **Normal distribution**: without doubt, the most important distribution. 
	* $f(X=x|\mu, \sigma^2) = \frac{1}{\sqrt{2\pi}\sigma}e^{-e(x-\mu)^2/(2\sigma^2)}$
	* Proving the pdf integrates to 1 is kind of clunky. I guess the [derivation](http://courses.ncssm.edu/math/Talks/PDFS/normal.pdf) indeed is.
	* Properties
		* Mean is $\mu$, standard deviation is $\sigma$. We usually work with standard normal distribution and rescale it back.
		* 68% - 95% - 99% rule
	* Normal distribution can be used to approximate a lot of other distributions, thanks to the Central Limit Rule. 
		* As an example, when $n$ is large and $p$ is not extreme (in the middle-ish), you can use normal distribution to approximate it.
		* In many cases it helps to use **continuity correction**
			* Say $Y \sim \mathrm{Binomial}(n, p)$ and $X \sim \mathrm{Normal}(np, n(1-p)p)$. 
			* We can say $P(a \le Y \le b) \approx P(a \le X \le b)$, but usually $P(a-\frac{1}{2} \le X \le b+\frac{1}{2})$ is a much better approximation, the reason being clear from a graphical representation.
* **Beta distribution**
	* Can be used to model proportions, as it gives total probability of 1 under a closed interval (0, 1).
	* Given that $B(\alpha, \beta) = \int_0^1x^{\alpha-1}(1-x)^{\beta-1}dx$,
	* $f(x|\alpha, \beta) = \frac{1}{B(\alpha, \beta)}x^{\alpha-1}(1-x)^{\beta-1}$. 
	* Relations
		* Beta function is closely related to Gamma functions:
			* $B(\alpha, \beta) = \frac{\Gamma(\alpha)\Gamma(\beta)}{\Gamma(\alpha+\beta)}$
		* Beta distribution is also related with the F distribution:
	* It can have varying shapes depending on the parameters: unimodal, monotonic, u-shaped, uniform, etc.
	* $EX = \frac{\alpha}{\alpha+\beta}$
	* $\mathrm{Var}X = \frac{\alpha\beta}{(\alpha+\beta)^2(\alpha+\beta+1)}$
* **Cauchy distribution**: a symmetric, bell-like curve with infinite expected value. Therefore, it is mostly used as an extreme case where we test conjectures. However, sometimes it shows up unexpectedly; for example ratio of two normally distributed variables follows the Cauchy distribution.
	* $f(x|\theta) = \frac{1}{\pi(1 + (x - \theta)^2}$
* **Lognormal distribution**: log of which is the normal distribution. Looks like Gamma distribution. 
	* $f(x|\mu, \sigma^2) = \frac{1}{\sqrt{2\pi}\sigma x}e^{-(\log x - \mu)^2 / (2 \sigma^2)}$
	* $EX = e^{\mu + (\sigma^2 / 2)}$
	* $\mathrm{Var} X = e^{2(\mu+\sigma^2)} - e^{2\mu+\sigma^2}$
* **Double exponential distribution**: formed by reflecting the exponential distribution around its mean.

#### Exponential families of distributions

* Section 3.4 introduces exponential families.
* Definition
	* A family of pdfs or pmfs is an exponential family if it can be expressed as:
		* $f(x|\theta) = h(x)c(\theta)\mathrm{exp}\left(\sum_{i=1}^{k}w_i(\theta)t_i(x)\right)$
		* where $\theta$ is a **vector-valued** parameter.
	* Many common families are exponential; normal, gamma, beta, binomial, Poisson, etc.
* Such form has some algebraic advantages, because the following identity:
	* $E\left( \sum_{i=1}^{k}\frac{\partial w_i(\theta)}{\partial\theta_j} t_i(X) \right) = -\frac{\partial}{\partial\theta_j}\log c(\theta)$
	* $\mathrm{Var}\left(\sum_{i=1}^{k}\frac{\partial w_i(\theta)}{\partial\theta_j}t_i(X) \right) = -\frac{\partial^2}{\partial^2\theta_j}\log c(\theta) - E\left(\sum_{i=1}^{k}\frac{\partial^2w_i(\theta)}{\partial\theta^2_j}t_i(X)\right)$
	* ... seem to be very very shitty but substitutes integration/summation with differentiation which are usually more tractable
	* when the range of values for $x$ depend on a parameter, we have to encode it into the function with an indicator function with both it cannot be an exponential family (how are binomial distribution exponential then? => only exponential when $n$ is known: $n$ is not a parameter anymore.)
* Example: binomial distribution mean
	* According to the above formula, $c(p) = (1-p)^n$ $w_1(p) = \log(\frac{p}{1-p})$, $t_1(x)=x$.
	* $E\left( \frac{1}{p(1-p)}X \right) = \frac{n}{1-p}$
	* which, upon arranging, gives the expected value without too much hassle.
* Notion of **natural parameter spaces**: don't know if this is of practical significance, but..
	* The above definition can be reparameterized as:
	* $f(x|\eta) = h(x)c^{\ast}\mathrm{exp}\left( \sum\eta_i t_i(x) \right)$
	* Then, for given $\eta$, $c^{\ast}$ is determined uniquely as the pdf needs to integrate to 1.
		* If the integral $\int h(x)\mathrm{exp}(\cdots)$ is finite, $c^{\ast}$ is the inverse of the integral.
		* All $\eta$ that makes that integral finite is called the **natural parameter space** $\mathcal{H}$ for the family. Which makes kind of sense.
		* $\mathcal{H}$ is convex. (....)
* Full and curved exponential families: if $k > d$ for dimension $d$ of the vector $\theta$, it is called a curved family. If $d=k$, it is called a full exponential family.

#### Scaling and locating families

* Section 3.5 introduces the notion of scaling and locating pdfs to create a family. Standard ideas, really.

#### Inequalities and identities

* Section 3.6 introduces many named inequalities/identities regarding probablities and distributions.
* **Chebychev's inequality**: if $g(x)$ is a nonnegative function, $P(g(X) \ge r) \le \frac{\mathrm{E}g(X)}{r}$
	* Seemed like a random result at first glance, but it is indeed useful. 
	* Let $g(x)=(x-\mu)^2/\sigma^2$. Then, let $r=t^2$ and we get $P((x-\mu)^2 \ge t^2\sigma^2) = P(|x-\mu| \ge t\sigma) \le \frac{1}{t^2}$
	* Let $t=2$ gives us $P(|x-\mu| \ge 2\sigma) \le \frac{1}{4}$! So a lower bound of area under 2 standard deviations from mean is at least 75%, no matter what the distribution is!
	* Of course, depending on the distribution, it is possible to get tighter bounds. Normal distribution is a (rather) obvious example.
* Identities: there are many recursive identities (remember what we did with binomial distributions earlier). The rest of the section discusses various such identities many of which rely on integration by parts.
	* Gamma distribution recursion: above mentions you can evaluate Gamma pdf recursively, exploiting that $\Gamma(n) = (n-1)\cdot\Gamma(n-1)$. This is how we do it.
	* [Stein's Lemma](http://en.wikipedia.org/wiki/Stein's_lemma): with $X \sim N(\theta, \sigma^2)$ and $g$ that is differentiable and satisfies $\mathrm{E}|g'(X)| < \infty$, then $\mathrm{E}[g(X)(X-\theta)] = \sigma^2\mathrm{E}g'(X)$ => useful for calculating higher order moments. Wikipedia also notes that it is useful in [MPT](http://en.wikipedia.org/wiki/Modern_portfolio_theory).. interesting.
	* Hwang's identity is like a discrete version of Stein's.		

### 4. Multiple Random Variables

#### Joint and Marginal Distributions

* Actually, mostly intuitive and trivial. We extend the notions of pmf/pdfs by adding variables. So will not discuss in detail here.
	* Joint pdf, joint pmfs take multiple variables.
* Marginal distributions (distribution of a subset of variables without referencing the other variables) are introduced.
	* For example, $f_X(x) = \sum_{y \in \mathit{R}}f_{X,Y}(x, y)$ for a pair of discrete variables $(X, Y)$.
	* Intuitively, they are "compressed" versions of joint pdf/pmfs. In the above example, a 2-dimensional probability function was compressed to 1-dimensional by compressing them along the y-axis.

#### Conditional Distributions and Independence

* Also, very intuitive. Conditional distributions are "sliced" versions of joint pdf/pmfs.
* Some of the random variables are observed; what are the distribution of the remaining variables? Are they affected?
* The derivation of conditional pmf is straightforward for discrete random variables. It is the ratio of the joint pmf and the marginal pmf.
	* For example, $f(y|x) = \frac{f_{X,Y}(x,y)}{f_X(x)}$
	* Somewhat surprising is this relation holds without problems for continuous random variables as well.
* Independence of two random variables
	* Definition: two variables $X$ and $Y$ are independent when $f(x, y) = f_X(x)f_Y(y)$.
	* Theorem: two variables $X$ and $Y$ are independent iff $f(x, y) = g(x)h(y)$ -- in other words, if the joint pdf can be decomposed into a product of two functions, one on $X$ and one on $Y$.
	* Tip: you can check independence of $X$ and $Y$ by noting the set of vectors where the joint pdf is greater than 0. Can you determine if a given sample belongs to the set by looking at each variable separately? If not, they are not independent. Of course, the inverse may not hold.
* Consequences
	* If two variables are independent: 
		* $E(g(X)h(Y)) = E(g(X))E(h(Y))$ 
		* Covariance is 0
		* You can get the mgf of their sum by multiplying individual mgfs. This can be used to derive the formula for adding two normal variables.

#### Bivariate Transformations

* Mainly talks about strategies of taking transformations (sum, product, division..) of two random variables. This is analogous to section 2.1 where we discussed transformations of a single variable.
	* Problem: Say you have a random vector $(X, Y)$ and want to know about $U = f(X, Y)$. 
	* Strategy: We have a recipe for transforming a bivariate vector into another. So we transform $(X, Y)$ into $(U, V)$ and take the marginal pdf to get the distribution of $U$. Obviously, $V$ is chosen that it is easy to get the marginal pdf of $U$.
* Recipe: 
	* Basically similar to the transformation recipe in 2.1. However, the derivative of the inverse function is replaced by the _Jacobian of the transformation_; which is defined as the determinant of the matrix of partial deriviatives. $J = \frac{\partial x}{\partial u} \frac{\partial y}{\partial v} - \frac{\partial x}{\partial v} \frac{\partial y}{\partial u}$.
	* Given this, we have $f_{U,V}(u, v) = f_{X,Y}(h_1(u, v), h_2(u, v))|J|$
		* where 
			* $g_1(x, y) = u$, $h_1(u, v) = x$
			* $g_2(x, y) = v$, $h_2(u, v) = y$
	* For example, if we are interested in $XY$, let $U = XY$, $V = Y$. Then we can define $h_1$ and $h_2$ easily.
	* Similar to the formula in 2.1, this assumes that the transformation is 1 to 1 (therefore the inverse exists). This is not always true; but you can use the same trick where we partition the domain into sets where in each set the transformation is 1 to 1.
		* $f_{U,V}(u, v) = \sum_{i=1}^{k}f_{X,Y}(h_{1i}(u, v), h_{2i}(u, v))|J_i|$ (formula 4.3.6)
	
#### Hierarchical Models and Mixture Distributions

* Hierarchical models arise when we model a distribution where a parameter has its own distribution. This is sometimes useful in gaining a deeper understanding of how things work. 
	* For example, an insect lays a large number of eggs (Poisson distribution) and individual eggs survive with a given probability (Binomial). What is the expected number of surviving insects? Now we have $X|Y \sim \mathrm{binomial}(Y, p)$ and $Y \sim \mathrm{Poisson}(\lambda)$.
* This section also introduces a trivial, but useful equality:
	* $EX = E(E(X|Y))$
	* If you think about it this is absolutely trivial; but recognizing this sometimes makes calculations really easy. A noncentral chi-squared distribution is given as an example.
* A formula for variance in hierarchical model is given as well:
	* $\mathrm{Var}X = \mathrm{E}(\mathrm{Var}(X|Y)) + \mathrm{Var}(\mathrm{E}(X|Y))$ which seems very elegant.

#### Covariance and Correlation

* This section introduces covariances and correlations. Important stuff, but the treatment is rather basic..
* Definitions and identities
	* $\mathrm{Cov}(X,Y) = \mathrm{E}[(X - \mu_X)(Y - \mu_Y)] = EXY - \mu_X \mu_Y$
	* $\rho_{XY} = \frac{\mathrm{Cov}(X,Y)}{\sigma_X \sigma_Y}$
	* $\mathrm{Var}(aX + bY) = a^2 \mathrm{Var}X + b^2 \mathrm{Var}Y + 2ab\mathrm{Cov}(X,Y)$
* Bivariate normal distribution is introduced as well.

#### Multivariate Distributions

* Section 4.6 generalizes the discussion on bivariate distributions. Nothing very new here.
* Multinomial distribution is introduced as a generalization of binomial distribution.
* There is also a recipe introduced for transforming a vector of random variables. Since Jacobian is well defined for larger matrices, the recipe is more or less the same from the bivariate recipe.

#### Inequalities

Section 4.7 introduces inequalities that are applicable to multivariate functions. Apparently, all of these have many forms, being applied in different contexts -- those have popped up in CvxOpt as well. (Looks like the most primitive form comes from the field of mathematical analysis.)

* Holder's inequality: Let $p, q$ be two positive numbers s.t. $1/p + 1/q = 1$ and $X, Y$ be random variables. Then,
	* $|EXY| \le E|XY| \le (E|X|^p)^{1/p}(E|Y|^q)^{1/q}$
* Cauchy-Schwarz inequality: A special case of Holder's inequality when $p=q=2$.
	* $|EXY| \le E|XY| \le \sqrt{E|X|^2 E|Y|^2}$
	* In vector terms, it means $ x \cdot y \le |x| \cdot |y|$. I think this is intuitive -- taking inner product gives chance of things cancelling out each other. Just like triangle inequality.
	* This can be used to prove the range of correlation coefficient is $[-1,1]$. Just take $(X-\mu_X)(Y-\mu_Y)$ and apply CS inequality. 
* Minkowski's inequality: this feels like, in spirit, like the additive version of Holder's inequality.
	* $[E|X+Y|^{p}]^{1/p} \le [E|X|^p]^{1/p} + [E|Y|^p]^{1/p}$

Inequalities on convex/concave functions are mentioned as well.

* Jensen's inequality: Given a convex function $g$, $\mathrm{E}g(X) \ge g(\mathrm{E}X)$.

### 5. Properties of a Random Sample

* This chapter deals with several things. 
	* Definition of random sample
	* Distribution of functions of random sample (sum, mean, ..) and how they converge as we increase the sample size
	* And of course, the LLN and the CLT.
	* Generating random samples.

#### Basic Concepts of Random Samples

* A random sample $X_1, \cdots, X_n$ is a set of independent and identically distributed random variables. 
* This means we are sampling with replacement from an infinite population. This is not always true, but in many cases is a good approximation.

#### Sums of Random Variables from a Random Sample

* Sum of random variables can be, obviously, calculated by the transformation strategies from Chapter 4. However, since each random variable is iid, they can be simplified greatly.
* If vector-or-scalar valued _statistic_ $Y$ is defined as $T(X_1, X_2, \cdots)$, the distribution of $Y$ is called the _sampling distribution_ of $Y$.
* Two most basic statistics are introduced:
	* Sample mean: $\bar{X} = \frac{1}{n}\sum_{i=1}^{n}X_i$
	* Sample variance: $S^2 = \frac{1}{n-1}\sum_{i=1}^{n}(X_i - \bar{X})^2$
		* Why $n-1$ instead of $n$ in the denominator? This was chosen so that $ES^2 = \sigma^2$. If we were to use $n$\, $S^2$ would be a biased estimator of $sigma^2$. See below.
		* Also, an interesting equality: $(n-1)s^2 = \sum_{o=1}^{n}x_i^2 - n\bar{x}^2$. I guess 
* Factoids about the sampling distribution of these statistics:
	* $E\bar{X} = \mu$: So the expected value of sample mean is the population mean. LLN will state that it will converge to the population mean as the sample size grows.

