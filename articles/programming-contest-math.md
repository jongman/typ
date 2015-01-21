title: 프로그래밍 대회를 위한 수학 커리큘럼
date: 2014-01-14
hidden: 1

**WORK IN PROGRESS**
**작업중**
**WORK IN PROGRESS**
**작업중**
**WORK IN PROGRESS**
**작업중**
**WORK IN PROGRESS**
**작업중**

[TOC]

## 이산 수학

### 점화식 풀이 기법들

* 2차 선형동차점화식 (Linear homogenous recurrence)
	* 다음과 같은 형태: $a_{k} = \alpha \cdot a_{k-1} + \beta \cdot b_{k-2}$. 
	* $a_{n}=r^{n}$ 꼴이라고 생각하고 대입해 보면 $r^{2} - \alpha\cdot r - \beta = 0$을 얻는다. 이 방정식의 해 $r$에 대해 $r^{n}$은 해가 됨. 
	* 해가 둘 있을 경우, $a\cdot r_{1}^{n} + b\cdot r_{2}^{n}$ 꼴의 선형 결합도 해가 된다 (당연). 이 계수들을 초기상태에 맞도록 지정.
	* Application:
		* 피보나치 수열의 일반항은?
		* $p$의 확률로 이기는 bet을 한다. (승-패)가 $W$가 되거나 $-L$이 될 때까지 하는데, 이 때 $W$ 승으로 끝날 확률은? (ICPC WF '13 B)
	* 일반화: 3차, 4차, 5차.. 라도 같은 요령으로 풀 수 있다 (3차, 4차 방정식을 풀기 힘들어서 그렇지)
		* 중근이면 어떻게? 만약 $r$이 $m+1$번 중근으로 등장한다면 $r^{n}, n\cdot r^{n}, \cdots, n^{m}\cdot r^{n}$ 의 선형결합이 들어간다.
* 선형비동차점화식 (Linear non-homogenous recurrence)
	* $a_{k} = \alpha_{k-1}a_{k-1} + \cdots + \alpha_{k-n}a_{k-n} + f(n)$ (마지막의 $f(n)$에 주의!)
	* 해법
		* $a_n = b_n + h_n$으로 분해 ($b_n$은 점화식만 만족하고 초기상태는 만족하지 않는 답. 대개 $f(n)$과 비슷한 형태를 갖는다.
		* $h_n$을 찾고 $a_n$의 계수를 초기상태 성립하도록 맞춰 주면 됨.

* [간단한 정리](http://www.eecs.yorku.ca/course_archive/2008-09/S/1019/Website_files/21-linear-recurrences.pdf)

### 이항계수와 숫자 세기

* 이항계수 (Binomial coefficient): $nCr = \left ( n \atop r \right ) = \frac{n!}{(n-r)!r!}$
	* 점화식: $\left( n \atop r \right ) = \left( n-1 \atop r-1 \right) \left( n-1 \atop r \right)$
	* Identity: $\left( n \atop 0 \right ) = \left ( n \atop n \right ) = 1$, $\sum_{i=0}^{n}\left(n \atop i\right) = 2^{n}$.<!--_-->
* 이항계수를 이용해 순열 수 세기: $n$개의 원소 중에서 $r$개를 뽑을 수 있는 경우의 수는?
	* 유의해야 할 것
		* 중복 여부: 같은 원소를 두 번 뽑을 수 있는가?
		* 순서 여부: 같은 원소를 순서만 다르게 뽑았으면 다른 경우로 치는가?
	* 공식
		* 중복 없이, 순서 있을 때: $\frac{n!}{(n-r)!} = nPr$
		* 중복 있고, 순서 있을 때: $n^{r}$
		* 중복 없이, 순서 없을 때: $\left ( n \atop r \right)$
		* 중복 있고, 순서 없을 때: $\left ( n + r - 1 \atop r \right )$ ($n$개의 원소와 $r-1$개의 막대기를 내려놓는 방법의 수)
* [카탈란 수](http://en.wikipedia.org/wiki/Catalan_number): 다양한 문제의 답이 된다.
	* [예제 문제들](http://en.wikipedia.org/wiki/Catalan_number#Applications_in_combinatorics): 길이가 2n인 괄호 수식의 수, n+1개의 리프를 가진 풀 바이너리 트리의 수, etc.
	* 수식: $C_n = \frac{1}{n+1} \left( 2n \atop n \right )$
* [Multinomial coefficient](http://en.wikipedia.org/wiki/Multinomial_theorem#Multinomial_coefficients)
* [탑코더 튜토리얼](http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=combinatorics)

### [포함-배제 법칙](http://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle)

* 공집합이 있는 n개의 집합의 합집합의 크기를 구하려면:
	* 각 집합의 크기를 모두 더한다.
	* 각 2개 집합에 대해 공집합의 크기를 모두 뺀다.
	* 각 3개 집합에 대해 공집합의 크기를 모두 더한다.
	* ...
* [탑코더 튜토리얼](http://apps.topcoder.com/forums/?module=Thread&threadID=685138&start=0&mc=2#1279067)
* Application: [Derangement](http://en.wikipedia.org/wiki/Derangement) 계산하기 - n개의 원소를 섞되, 그 중 아무 것도 원래 위치에 있지 않는 경우의 수는?
	* Let: $A_i$ = $i$가 제 자리로 간 순열의 개수. 
	* $\sum_{i=0}^{n}(-1)^{n-i}\left( n \atop i \right)i!$<!--_-->

### [번사이드 정리](http://en.wikipedia.org/wiki/Burnside's_lemma)

* [페트르님의 정리](http://petr-mitrichev.blogspot.kr/2008/11/burnsides-lemma.html)
* 경우의 수를 세는데, 특정 transform operation(회전, 반사, ..)해서 같은 경우들은 하나로 친다. 전체 경우의 수는?
	1. 각 operation마다 이 operation을 했을 때 변하지 않는 경우의 수를 센다 (단, "아무것도 하지 않는다"라는 operation도 있어야 함!)
	2. 전체 경우의 수를 더한 후, operation의 수로 나눈다. (답이 맞다면 항상 나누어 떨어져야 한다)
* Application:
	* $n\times n$ ($n$은 편의를 위해 짝수) 크기의 격자를 $x$개의 색깔로 칠하는 경우의 수는? 단 회전해서 같은 경우는 같은 것으로 친다.
		* 아무것도 하지 않을 때: 모든 격자가 변하지 않는다. $x^{n*n}$
		* 90도 회전, 270도: 4개씩 칸을 그룹지어, 각 그룹은 같은 색이어야 한다. 따라서 $x^{n*n/4}$
		* 180도 회전: 2개씩 칸을 그룹지어, 각 그룹은 같은 색이어야 한다. 따라서 $x^{n*n/2}$개의 경우의 수
	* 최종 답은 이들의 평균!
	* 만약 $n$이 홀수라면 어떨까?

### 키르히호프 정리

### 생성함수 

## 게임이론

### [스프라그-그룬디 정리](http://en.wikipedia.org/wiki/Sprague%E2%80%93Grundy_theorem)

* [튜토리얼 링크](http://www.gabrielnivasch.org/fun/combinatorial-games/sprague-grundy), [탑코더 튜토리얼](http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=algorithmGames), [또다른 튜토리얼](http://blog.plover.com/math/sprague-grundy.html)
* [Nim 게임](http://en.wikipedia.org/wiki/Nim)
	* 규칙
		* 조약돌 $k$ 무더기가 있다고 하자. 각 무더기에 포함된 조약돌의 개수는 다를 수 있다.
		* 각 플레이어는 무더기를 하나 선택해서 그 무더기에서 1개 이상의 조약돌을 가져온다. (무더기에 남은 조약돌을 전부 가져와도 된다.)
		* 마지막 조약돌을 가져가는 플레이어가 승리한다.
	* Nim 게임의 해법
		* 각 무더기의 조약돌 수를 전부 XOR한다. 0이면 패배! 0 이상이면 승리!
* 일반화하기:
	* 모든 [impartial](http://en.wikipedia.org/wiki/Impartial_game)(어느 플레이어든지 놓을 수 있는 수가 같다), [normal play](http://en.wikipedia.org/wiki/Normal_play_convention)(마지막에 수를 두는 사람이 이긴다) 게임은 비슷한 해법으로 풀 수 있다.
		* 다음과 같은 규칙:
			* 게임은 한 개 이상의 서브게임으로 구성된다.
			* 각 서브게임은 상태들의 DAG로 구성된다. 
			* 각 플레이어는 하나의 서브게임을 골라 해당 서브게임의 상태를 한 번 움직인다.
			* 더 이상 움직일 수 없는 사람이 진다.
	* 어떻게 풀까?
		* 게임의 각 상태에 대해 Grundy 수를 계산한다. 
		* 우선 하나의 서브게임만 보자.
			* 지는 상태(마지막 상태)의 Grundy 수는 0이다.
			* 그 외의 상태에서는 이 상태에서 나가는 상태들의 Grundy 수를 모은 뒤, 그 중에 포함되지 않은 가장 작은 0 이상의 정수(minimum excluded number)가 Grundy 수가 된다.
		* 여러 개의 서브게임이 있다면 각 서브게임의 상태를 XOR한다.
	* Nim에서는: $n$개의 조약돌이 남아있다면 Grundy 수는 $n$
* Application: fill in!

## 확률론

### 기대값의 선형성

* $E(\sum_{i}A_i) = \sum_i E(A_i)$
* 당연한 얘기같지만 가끔 예상치 못한 간단한 답을 준다! 합을 어떻게 나누느냐에 따라 중요.
* Application
	* $N+1$층짜리 건물의 1층에 엘리베이터가 섰는데, $M$명이 탔다. 각 사람이 가는 층은 랜덤하게 결정된다. 엘리베이터가 서는 횟수의 기대값은?
		* 각 층별로 설 때 1이 되는 indicator function의 기대치를 구해서 더한다.
	* [또 다른 예제](http://petr-mitrichev.blogspot.kr/2013/11/this-week-in-competitive-programming.html): 평면상에 $N$개의 점이 있다. 각 점마다 해당 점이 존재하거나 지워질 확률이 주어진다. Convex hull 넓이의 기대값은?
		* 각 간선별로 외적값의 기대치를 더한다.

## 정수론

### 모듈라 연산

* N으로 나눈 결과값을 구할 때, 연산 중간 결과도 N으로 나눠도 된다. 
	* $(a + b) \mathrm{mod}N = (a \mathrm{mod}N + b\mathrm{mod}N) \mathrm{mod}N$
	* $(a - b) \mathrm{mod}N = (a \mathrm{mod}N + b\mathrm{mod}N + N) \mathrm{mod}N$
	* $(a * b) \mathrm{mod}N = (a \mathrm{mod}N * b\mathrm{mod}N) \mathrm{mod}N$
* 단 나눗셈에는 성립하지 않는다. $a$로 나누기 위해서는, 곱셈의 역원을 대신 곱해줘야 한다. [모듈라 곱셈의 역원](http://en.wikipedia.org/wiki/Modular_multiplicative_inverse)은 두 가지 방법으로 구할 수 있다.
	* 한 가지 방법은 오일러 정리를 이용하는 것이다.
		* $a^{\phi(N)} \equiv 1 (\mathrm{mod}N)$
		* 이 때 $phi(N)$은 오일러 피 함수. 아래를 참조하라. 단 이거 계산하는건 배보다 배꼽이 더 클 수도.
		* $N$이 소수라면 $\phi(N)=N-2$이니 간단.
		* 이것을 거듭제곱 빨리 구하기로 구하면 된다.
	* 두번째 방법(아마 더 효율적)은 확장 유클리드 알고리즘을 쓰는것이다. 아래를 참조하라.

### 확장 유클리드 알고리즘

* 목적: 상수 $a$, $b$에 대해 $ax + by = \mathrm{gcd}(a, b)$를 만족하는 $x$, $y$를 찾아준다. 
* Naive derivation:
	* 유클리드 gcd 알고리즘에서, $gcd()$의 입력이 되는 숫자들은 항상 최초 숫자들의 선형 결합으로 표현할 수 있다.
	* 따라서 각 숫자 $a$와 $b$를 넘길 때, 이들을 최초 숫자들의 선형 결합으로 표현한 방법 또한 넘겨주면 간단하게 풀 수 있다.
	* 물론 이대로 구현하면 아주 귀찮다. 대신에 $gcd(a, b)$ 함수가 최대공약수와 함께 $ax+by=g$ 의 해 $x$, $y$를 반환하도록 하면 쉽게 풀 수 있다.

C++ 구현

	struct Solution { int gcd, x, y; };
	Solution extendedEuclid(int a, int b) {
	  int q = a / b, r = a % b;
	  if(r == 0) return Solution{b, 0, 1}; 
	  Solution s = extendedEuclid(b, r);                                                                                                            
	  // now, we have
	  // s.gcd = s.x * b + s.y * r
	  //       = s.x * b + s.y * (a - q * b)
	  //       = s.y * a + (s.x - q * s.y) * b
	  return Solution{s.gcd, s.y, s.x - q * s.y};
	}

* Application:
	* 위에서 얘기했듯이, 모듈라 연산에서 곱셈의 역원 구하기. $\mathrm{mod } N$인 모듈로 연산을 할 때, $a$와 $N$이 서로소라 하자. ($N$이 소수면 항상 참) 따라서 $a$와 $N$의 egcd 결과는 항상 $ax + Ny = 1$이 된다. $N$로 나눠보면 $ax = 1 (\mathrm{mod }N)$. 따라서 $x$는 $a$의 곱셈 역원이다. (단, 결과값이 음수라면 $N$을 더해줘야 함)

### 중국인 나머지 정리

### 루카스의 정리

### 뫼비우스 함수

### 오일러 피 함수

## 분할 정복을 이용한 빠른 수식 계산

### 빠른 거듭 제곱 계산

* 분할 정복: 내 책을 봐라 -\_-
	* $x^{2n} = (x^n) \cdot (x^n)$
	* $x^{(2n+1)} = x \cdot x^{2n}$

### 빠른 등비 수열의 합

* 분할 정복: 역시 내 책을 봐라 -\_-
	* $A^{2n} + A^{2n-1} + A^{2n-2} + \cdots + A^{1}$
	* $= (A^{2n} + A^{n}) + (A^{2n-1} + A^{n-1}) + \cdots$
	* $= (1 + A^n)(A^{n} + A^{n-1} + \cdots + A^{1})$

## 선형 시스템

### 가우스 소거법

### 심플렉스법

* 진짜로 이거 필요할까? -\_-

### 리니어 시스템과 플로우

## 기초 수치 해석

### Newton method

### [Adaptive Simpson 수치 적분](http://en.wikipedia.org/wiki/Adaptive_Simpson's_method)

* $f(x)$ 함수의 구현이 주어질 때, 해당 함수를 여러번 호출해서 해당 함수의 부정적분 없이도 정적분을 계산하는 기법들.
	* [Simpson법](http://en.wikipedia.org/wiki/Simpson's_rule)은 해당 함수를 2차함수로 근사해서 적분한다. 따라서 해당 함수가 2차 이하라면 항상 정확한 답이 나온다.
	* Adaptive Simpson 적분 알고리즘은 해당 함수가 2차 함수에서 얼마나 벗어나는지 확인하고, 많이 벗어난다면 분할 정복한다. 자세한 백그라운드는 나도 모르니 싣지 않는다. 구현은 다음과 같다.

C++ 구현

	template<typename Function>
	double simpson(Function f, double a, double b) {
	  double c = (a + b) / 2.0;
	  double h3 = fabs(b - a) / 6.0;
	  return h3 * (f(a) + 4.0 * f(c) + f(b));
	}

	// sum은 처음에 simpson(f, a, b)로 초기화한다.
	// 오차가 eps 이상으로 추정되는 경우 분할정복한다.
	template<typename Function>
	double adaptiveSimpson(Function f, double a, double b, double sum, double eps) {
	  double c = (a + b) / 2.0;
	  double left = simpson(f, a, c);
	  double right = simpson(f, c, b);
	  if(fabs(left + right - sum) <= 15 * eps) 
		return left + right - (left + right - sum) / 15;
	  return adaptiveSimpson(f, a, c, left, eps/2) + adaptiveSimpson(f, c, b, right, eps/2);
	}

## 긴 정수 곱셈

### 카라츠바 알고리즘

* 카라츠바 알고리즘은 긴 정수 둘을 곱하는 분할 정복 알고리즘이다. $B$진수 $n$자리 긴 정수 $a$, $b$를 곱한다고 하자. ($n$은 2의 자승으로 가정한다.)
* 이 때 두 숫자를 모두 절반($n/2$ 자리씩)으로 다음과 같이 자르자.
	* $a = a_{1} \times B^{n/2} + a_{0}$
	* $b = b_{1} \times B^{n/2} + b_{0}$
* 이 때 다음과 같이 두자.
	* $z_0 = a_0 \times b_0$
	* $z_2 = a_1 \times b_1$
	* $z_1 = (a_0 + a_1) \times (b_0 + b_1) - z_0 - z_1 = a_0 \times b_1 + a_1 \times b_0$
* 그러면 
	* $a \cdot b = (a_1 \cdot B^{n/2} + a_0) \cdot (b_1 \cdot B^{n/2} + b_0) = (a_1 \cdot b_1) \cdot B^{n} + (a_0 \cdot b_1 + a_1 \cdot b_0) \cdot B^{n/2} + (a_0 \cdot b_0)$
	* $= z_2 \cdot B^{n} + z_1 \cdot B^{n/2} + z_0$
* $B^{n}$으로의 곱은 선형시간에 할 수 있다는 점을 감안하면, $n/2$ 크기의 정수 곱셈 세 번만 하면 되기 때문에 확실히 빠르다!


### FFT와 다항식 곱셈

* 빠른 다항식 곱셈 알고리즘이 있으면 긴 정수 곱셈도 빠르게 할 수 있다. 긴 정수를 몇 자리씩 끊어서 다항식의 계수로 삼은 뒤, 두 다항식을 곱하고, 마지막에 올림 처리만 해 주면 되기 때문.
* 다항식 곱셈 또한 물론 단순한 방법은 $O(n^2)$인데, FFT를 이용하면 $O(n \lg n)$에 할 수 있다.
* FFT 곱셈은 다항식에 두 가지 표현 방식이 있다는 것을 이용한다:
    * 계수 목록 형태: 대부분 사용하는 방식
    * x, y쌍 형태: $2n$개의 상수 $x_0, x_1, \cdots, x_{n-1}$에 대해 $f_(x_0), f_(x_1), \cdots$를 저장하는 방식
* $n$개의 샘플은 $n$차 방정식을 유니크하게 정의하기 때문에 이 두 표현 방식은 동등하다.
    * 하지만 $f(x)\cdot g(x)$를 x, y쌍 형태에서는 그냥 원소별로 곱해주면 된다!
* FFT는 특정 성질을 띠는 $x$들을 선택해, 이 두 형태간의 변환을 $O(n \lg n)$에 수행한다.
* 곱셈 자체는 $O(n)$이다.
* 자세히는 인간적으로 CLRS를 보자...

C++ 구현:
    
    #include<vector>
    #include<complex>
    #include<cmath>

    using namespace std;

    typedef complex<double> Complex;
    typedef vector<Complex> ComplexVector;
    typedef vector<int> Polynomial;

    const double PI = 2.0 * acos(0.0);

    // Given a n-th polynomial p, return its values at
    // w^0, w^1, .., w^(n-1). n is assumed to be a power of 2.
    // Since the size of the input and output are the same, the output is stored at
    // p.
    void dft(ComplexVector& p, Complex w) {
      int n = p.size();
      if(n == 1) return;

      // divide
      ComplexVector even(n / 2), odd(n / 2);
      for(int i = 0; i < n/2; ++i) {
        even[i] = p[i * 2];
        odd[i] = p[i * 2 + 1];
      }

      // conquer
      dft(even, w * w); 
      dft(odd, w * w);

      // merge
      Complex w_power = 1;
      for(int i = 0; i < n/2; ++i) {
        Complex offset = w_power * odd[i];
        p[i      ] = even[i] + offset;
        p[i + n/2] = even[i] - offset;
        w_power *= w;
      }
    }

     
    // returns smallest power of 2 s.t. p2 >= n.
    int roundUp(int n) {
      int p2 = 1;
      while(p2 < n) p2 *= 2;
      return p2;
    }

    Polynomial operator * (const Polynomial& a, const Polynomial& b) {
      // last *2 is needed because C can have twice the degree from original polys
      int n = roundUp(max(a.size(), b.size())) * 2;

      // Complex representations of a and b
      ComplexVector ac(a.begin(), a.end()), bc(b.begin(), b.end());
      ac.resize(n); 
      bc.resize(n);

      // FFT 
      Complex w = polar(1.0, 2 * PI / n);
      dft(ac, w);
      dft(bc, w);
      // Pointwise multiplication
      for(int i = 0; i < n; ++i) 
        ac[i] *= bc[i];

      // Inverse FFT
      dft(ac, polar(1.0, -2 * PI / n));
      for(int i = 0; i < n; ++i) 
        ac[i] /= double(n);

      // Trim zero paddings
      while(!ac.empty() && fabs(real(ac.back())) < 1e-9) 
        ac.pop_back();

      // return real
      Polynomial ret(ac.size());
      for(int i = 0; i < ac.size(); ++i) 
        ret[i] = int(round(real(ac[i])));

      return ret;
    }


### 긴 정수 곱셈의 응용

## 알면 유용한 사실들

* 약수의 개수
* 원점에서 (a,b)까지 선분 위 격자점의 개수는 gcd(a,b)
* pi(x) ~= x/log(x)
* 
