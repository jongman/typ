title: 메모: The Statistical Sleuth Cheat Sheet
date: 2013-05-01
categories: 메모, 통계
hidden: true

이 메모는 [이 책](http://www.proaxis.com/~panorama/home.htm)에 언급된 내용들에 대한 간략한 cheat sheet이다. 이 글은 남에게 보여주기 위해 쓴 것이 아니라 단지 개인적인 용도를 위해 정리한 것이고, 나는 통계학의 전문가와는 거리가 아주 멀기 때문에, 틀린 내용이 얼마든지 있을 수 있다. 틀린 점은 이메일이나 트위터로 알려주면 고맙겠다.

<!-- PREVIEW_END -->

----

### paired data

* [Paired difference t-test](http://en.wikipedia.org/wiki/Paired_difference_test): 통제 변인 외에 모든 요소가 같은 관찰값들이 주어졌을 때. 정규분포가 아닐 경우 [Wilcoxon signed-rank test](http://en.wikipedia.org/wiki/Wilcoxon_signed-rank_test)도 사용 가능.
* [Sign test](http://en.wikipedia.org/wiki/Sign_test): nonparametric이고 statistical power가 없지만 아주 간단함.

### un-paired, two sample

* [Independent two sample t-test](http://en.wikipedia.org/wiki/Student's_t-test#Independent_two-sample_t-test): 두 개의 모집단에서 상호독립으로 샘플을 draw 했을 때. 두 집단의 표준편차가 다를 경우 [Welch's t-test](http://en.wikipedia.org/wiki/Welch%27s_t_test)를 쓰자.
* [Mann-Whitney Rank sum test](http://en.wikipedia.org/wiki/Mann%E2%80%93Whitney_U): 모집단 분포가 정규분포가 아닐때(outlier 가 있을 때) 유용.

### multiple samples

* [ANOVA](http://en.wikipedia.org/wiki/Analysis_of_variance): 모든 샘플의 평균이 같은가?를 검증. full model과 reduced model의 파워를 비교함. 모든 샘플을 두 개의 서브셋으로 나눠서 이들이 같은가? 식으로도 쓸 수 있다.

### general


### linear regression

### categorical data

* categorical variable들을 사용하는 경우 관찰 결과는 frequency table로 주어진다.
* explanatory와 response variable을 특정할 수 있을 경우, 각 모집단의 출현 proportion($p$) 혹은 odd($p/(1-p)$)가 과연 다른가? 를 검증. 
* 특정할 수 없을 경우 테이블의 가로줄과 세로줄이 상호 독립인가? 를 검증.
* 많은 경우 odd가 proportion보다 나은 기준이다. 그 중에서도 odd의 차이보다 비율(odds ratio)가 유의미할 수 있다. Odds ratio는 prospective와 retrospective study가 바뀌어도 유지된다.
* log of odds ratio가 좀더 정규분포에 가까워 흔히 이용된다.
* [Pearson's chi-squared test](http://en.wikipedia.org/wiki/Pearson%27s_chi-squared_test) for goodness of fit: full model과 reduced model의 파워를 비교함.
* [Permutation test](http://en.wikipedia.org/wiki/Permutation_test#Permutation_tests): Fisher's exact test. Null hypothesis가 참일 때 관찰값보다 extreme한 값이 나오는 경우의 수를 셈. Confidence interval을 줄 수 없음. 계산적으로 비쌈.
* Mantel-Haenszel test: confounding factor 별로 나눠진 여러 개의 contingency table이 주어질때 이들의 결과를 합침.

### logistic regression

* [GLM](http://en.wikipedia.org/wiki/Generalized_linear_model): $logit(\pi)$ is a linear combination of explanatory variables.
* Maximum Likelihood Estimate를 구한다. unbias외의 여러 좋은 점이 있음.
* 각 coefficient에 대해 z-ratio를 구해 유의미성을 구할 수 있다.
* [Deviance test](http://en.wikipedia.org/wiki/Deviance_(statistics)): Full model과 reduced model의 파워 차이를 구한다. likelihood의 차이는 대략 chi-squared distribution을 따름.
