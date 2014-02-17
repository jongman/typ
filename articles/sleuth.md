title: 강의노트: The Statistical Sleuth Cheat Sheet
date: 2013-05-01
categories: 강의노트, 통계

이 메모는 [이 책](http://www.proaxis.com/~panorama/home.htm)에 언급된 내용들에 대한 간략한 cheat sheet이다. 이 글은 남에게 보여주기 위해 쓴 것이 아니라 단지 개인적인 용도를 위해 정리한 것이고, 나는 통계학의 전문가와는 거리가 아주 멀기 때문에, 틀린 내용이 얼마든지 있을 수 있다. 틀린 점은 이메일이나 트위터로 알려주면 고맙겠다.

<!-- PREVIEW_END -->

----

### T-tests for two sample data

* [Paired difference t-test](http://en.wikipedia.org/wiki/Paired_difference_test): 통제 변인 외에 모든 요소가 같은 관찰값들의 쌍이 주어졌을 때. 정규분포가 아닐 경우 [Wilcoxon signed-rank test](http://en.wikipedia.org/wiki/Wilcoxon_signed-rank_test)도 사용 가능.
* [Sign test](http://en.wikipedia.org/wiki/Sign_test): nonparametric이고 statistical power가 없지만 아주 간단함.
* [Independent two sample t-test](http://en.wikipedia.org/wiki/Student's_t-test#Independent_two-sample_t-test): 두 개의 모집단에서 상호독립으로 샘플을 draw 했을 때. 두 집단의 표준편차가 다를 경우 [Welch's t-test](http://en.wikipedia.org/wiki/Welch%27s_t_test)를 쓰자.
* [Mann-Whitney Rank sum test](http://en.wikipedia.org/wiki/Mann%E2%80%93Whitney_U): 모집단 분포가 정규분포가 아닐때(outlier 가 있을 때) 유용.

### ANOVA

* 기본적으로 full model과 reduced model의 sum of squared error를 비교한다: [extra-sum-of-squares principle](http://www.jerrydallal.com/LHSP/extra.htm)
* One-way [ANOVA](http://en.wikipedia.org/wiki/Analysis_of_variance): 모든 샘플의 평균이 같은가?를 검증. \$F = \frac{(extra-sum-of-squares) / (extra-degrees-of-freedom)}{\hat{\sigma}^{2}_{full}}\$ <!--_-->이때 이 식의 분자는 그룹간의 variance, 분모는 그룹 내의 variance라고도 할 수 있다.  
* others-equal 모델: 그룹중 하나 찍어서 얘는 나머지랑 다르고, 나머지는 다 고만고만하다는 것을 보일 때.
* [Two way ANOVA](http://en.wikipedia.org/wiki/Two-way_analysis_of_variance)

### linear regression

* slope와 intercept의 confidence interval/p-value를 이용해 변수간 관계 유추하는 데 씀.
* [regression to the mean](http://en.wikipedia.org/wiki/Regression_toward_the_mean): "회귀regression"이라는 단어의 원인. 흔한 fallacy.
* scatterplot of residual vs fitted value is sometimes more informative than response-explanatory plot.
* ANOVA를 이용한 assessment (그냥 ANOVA는 sum of squares = between groups + within groups 하지만, 리그레션 ANOVA는 regression + residual로 나눔)
* 여러 개의 explanatory variable 값에 replicated value가 있을 경우 lack of fit test를 할 수 있다. separate means vs linear regression. 물론 replicated value가 없으면 separate means가 의미가 없으므로 안되지.
* \$R^2\$: the proportion of variance explained
* weighted regression: possible reasons
	* responses are estimates; SD are available. SD가 작은 샘플에 높은 가중치를 줘야겠지.
	* responses are avarages; sample size is available. 위와 같다.
	* variance is proportional to X
* **including additional variables can actually _decrease_ the precision of the result**. Adding variables to a simple linear regression changes the standard error of a coefficient in the following ways:
	* The standard error can decrease when the multiple regression has a smaller RMSE
	* The standard error will _increase_ when the additional variable is well explained by other variables (*multicollinearity*)
* variable selection: forward selection, backward elimination, and stepwise regression.
	* choosing two fits with different number of variables: [Cp Statistic](http://en.wikipedia.org/wiki/Mallows's_Cp), [BIC](http://en.wikipedia.org/wiki/Bayesian_information_criterion). [AIC](http://en.wikipedia.org/wiki/Akaike_information_criterion). BIC (approximately) maximizes the posterior probability.

### model checking 

* dealing with outliers: try fitting without them and see if results change.
* multiple ways to find potential outliers: 
	* [leverage](http://en.wikipedia.org/wiki/Leverage_(statistics)): standardized feature value
	* [studentized residual](http://en.wikipedia.org/wiki/Studentized_residual)
	* [Cook's distance](http://en.wikipedia.org/wiki/Cook's_distance)
* partial residual plots: \$\mu(brain|body,gest) = \beta_{0} + \beta_{1}body + f(gest)\$일 때, \$f(gest)\$를 특정 형태로 (대개 linear 혹은 qudratic) 가정하고 리그레션을 돌린 후, \$brain - \beta_{0} - \beta_{1}body\$와 \$gest\$를 플롯.

### strategy for data analysis

1. preliminaries: define question. review study design.
2. explore: use graphical tools, fit a tentative model, look for outliers
3. formulate an inferential model
4. check the model: if appropriate, fit a richer model. examine residuals, nonconstant variance. test if we can drop extra terms in the rich model.
5. ??
6. profit!

### working with time series

* serial correlation check
	* subtract mean. count _runs_ of consecutive negative/positive values. Similar to [this](http://en.wikipedia.org/wiki/Wald%E2%80%93Wolfowitz_runs_test).
	* correlation has normal distribution with mean=0 and std=\$1/\sqrt{n}\$.
* [AR(1)](https://en.wikipedia.org/wiki/Autoregressive_model)
	* estimation: subtract mean. (approximately) take correlation between adjacent values. 
	* filtering: get rid of autoregressiveness. \$X_t = X_t - \alpha \cdot X_{t-1}\$

### summarizing multivariate responses

* [PCA](https://en.wikipedia.org/wiki/Principal_component_analysis): PCA is sensitive to scale, so standardize accordingly.
* [Canonical Correlation Analysis](http://en.wikipedia.org/wiki/Canonical_correlation): 두 random variable의 집합 X와 Y가 있을 때, 각 집합의 원소들의 선형결합 두 개를 찾아 이들의 correlation을 최대화.
* [Discrimnant Function Analysis](http://en.wikipedia.org/wiki/Discriminant_function_analysis): finds linear combinations of variables that best separates the data. (Basic clustering approach)

### working with categorical data

* categorical variable들을 사용하는 경우 관찰 결과는 frequency table로 주어진다.
* explanatory와 response variable을 특정할 수 있을 경우, 각 모집단의 출현 proportion(\$p\$) 혹은 odd(\$p/(1-p)\$)가 과연 다른가? 를 검증. 
* 특정할 수 없을 경우 테이블의 가로줄과 세로줄이 상호 독립인가? 를 검증.
* 많은 경우 odd가 proportion보다 나은 기준이다. 그 중에서도 odd의 차이보다 비율(odds ratio)가 유의미할 수 있다. Odds ratio는 prospective와 retrospective study가 바뀌어도 유지된다.
* log of odds ratio가 좀더 정규분포에 가까워 흔히 이용된다.
* [Pearson's chi-squared test](http://en.wikipedia.org/wiki/Pearson%27s_chi-squared_test) for goodness of fit: full model과 reduced model의 파워를 비교함.
* [Permutation test](http://en.wikipedia.org/wiki/Permutation_test#Permutation_tests): Fisher's exact test. Null hypothesis가 참일 때 관찰값보다 extreme한 값이 나오는 경우의 수를 셈. Confidence interval을 줄 수 없음. 계산적으로 비쌈.
* Mantel-Haenszel test: confounding factor 별로 나눠진 여러 개의 contingency table이 주어질때 이들의 결과를 합침.

### logistic regression

* [GLM](http://en.wikipedia.org/wiki/Generalized_linear_model): \$logit(\pi)\$ is a linear combination of explanatory variables.
* Maximum Likelihood Estimate를 구한다. unbias외의 여러 좋은 점이 있음.
* [Wald Test](http://en.wikipedia.org/wiki/Wald_test): 각 coefficient에 대해 z-ratio를 구해 각 explanatory variable의 유의미성을 구할 수 있다. 
* [Deviance test](http://en.wikipedia.org/wiki/Deviance_(statistics)): Full model과 reduced model의 파워 차이를 구한다. likelihood의 차이는 대략 chi-squared distribution을 따름. Wald test보다 귀찮지만 더 reliable하다.

#### logistic regression w/ repetitive observations

* 각 explanatory variable마다 여러 개의 관찰값이 있는 경우 yes의 수 \$Y\$가 binomial(\$m\$, \$\pi\$)를 따르는 binomial count 모델로 모델링할 수도 있다.
* model adequecy: 이때 각 explanatory variable의 조합을 repetitive sample로 생각하고, response variable의 평균을 구한 full 모델을 쓰자. 이 때 deviance residual은 대~충 chi-squared distribution을 따른다. 이 p-value가 작을 경우에는 model is inadequate.
* extra-binomial variation: when \$\pi\$ differs for each response, or trials are not independent. We add "dispersion factor" \$\psi\$ to the variation. Fit richer model and compare deviance.

#### logistic regression w/ poisson-distributed counts

* log of count is linear function of explanatory variables, count following Poisson distribution.
* As long as the distrubution of the response variable is specified, can estimate MLE.
