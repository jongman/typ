title: 메모: t-test를 통한 가설 검증 레시피
date: 2013-01-01
categories: 메모, 통계

개인적으로 학부 졸업하고 나서 가장 아쉬운 것 중 하나가 학부 다닐 때 통계학을 제대로 공부하지 않은 것이다. 통계가 왜 중요한가? 어떤 것을 잘 하기 위해 필요한 첫 번째 단계는 그것을 얼마나 잘 하고 있는 지 재는 것이고, 이것을 제대로 재기 위해서는 통계가 필요하기 때문이다. 

* 어떤 프로그램에 새로운 최적화 기술을 적용했다고 하자. 1000개의 패킷에 대해 처리 시간을 수집했는데, 최적화 전에는 평균 50.6us였지만 최적화 후 50.1us로 줄었다고 하자. 과연 0.5us 빨라진 걸까? 아니면 그냥 운인 것이고 전혀 빨라진 게 아닐까?
* 웹 애플리케이션 첫 페이지를 새로 디자인했다. 새 디자인과 옛 디자인을 A/B 테스트한 결과 각각의 가입 비율을 찾았는데, 이전 디자인에서는 45% 였지만 새 디자인에서는 50% 였다고 하자. 이 상승이 얼마나 의미가 있는지, 운이 아닌지 확인할 방법이 있을까?

이 메모는 [이 책](http://www.proaxis.com/~panorama/home.htm)을 읽으면서 가설 검증에 관련된 챕터 내용들을 정리한 것이다. 이 글은 남에게 보여주기 위해 쓴 것이 아니라 단지 개인적인 용도를 위해 정리한 것이고, 나는 통계학의 전문가와는 거리가 아주 멀기 때문에, 틀린 내용이 얼마든지 있을 수 있다. 틀린 점은 이메일이나 트위터로 알려주면 고맙겠다.

<!-- PREVIEW_END -->

----

## 테스트의 종류

다양한 종류의 가설 검정 기법이 있으며 어떤 자료를 비교하는지, 샘플은 몇 개인지에 따라 각각 다른 기법을 써야 한다.

## Paired t-test

모든 관찰값이 쌍을 이루고 있는 경우이다. 이 경우 한 쌍은 테스트하고 싶은 변수 외의 모든 요소가 같아야 한다. 

#### 예제 실험

같은 가정에서 자란 일란성 쌍둥이인데, 한명은 정신분열이고 한명은 아닌 경우들을 찾는다. 이 때 이 둘의 왼쪽 해마의 크기를 MRI를 이용해 비교하자. 이 때 각 샘플은 정신분열이라는 점만 빼면 모든 점이 똑같다.

각 샘플마다, 정신분열이 아닌 사람의 해마 부피에서 정신분열인 사람의 해마 부피를 뺀다. 이 차이의 집합이 이 문제의 샘플이 된다. 따라서 단 1개의 샘플이 있게 된다. 

해마 부피 차이의 기대값은 0일까?

#### 검증하기

1. 차이의 모집단 분포가 평균값 \$\mu\$, 표준편차 \$\sigma\$를 갖는다고 하자. 
1. 이 때 이 때 크기가 \$n\$인 샘플의 평균값의 분포는 평균 \$\mu\$, 표준편차 \$\frac{\sigma}{\sqrt{n}}\$를 갖게 된다. 
1. Central Limit Theorem에 의해, 이 평균값의 분포는 \$n\$이 커지면 커질 수록 정규 분포를 갖게 될 것이다. 
1. 따라서 평균값의 분포를 정규화하면 표준 정규 분포를 갖게 되고, 이 분포 상에서 우리가 관찰한 평균값의 \$Z\$-score를 찾아보면 이 샘플이 단순히 우연에 의해 출현할 가능성을 알 수 있다.
1. 하지만 우리는 \$\mu\$와 \$\sigma\$를 모르기 때문에 이것을 실제값의 근사값인 sample mean과 sample standard error로 대체해서 정규화를 하도록 하자.
1. 이렇게 대체한 estimate로 표준화한 평균값을 \$t\$-ratio라고 하고, Student's \$t\$-distribution을 띤다.
1. 다행히 이 분포 또한 알려져 있으며, \$n\$이 크면 커질 수록 정규분포에 근접한다 (sample mean과 sample standard error가 \$n\$이 커질 수록 정확해 질 테니 당연한 얘기다).
1. 따라서 계산한 \$t\$-ratio 보다 절대값이 큰 경우들의 비율이 얼마나 되는지를 통해, 이 샘플이 우연히 얻어졌을 가능성인 \$p\$-value를 계산할 수 있다.

#### 구현하기

scipy 패키지에 \$t\$ 분포의 구현이 있기 때문에 간단하게 구현할 수 있다. 

	from pandas import read_csv
	from math import sqrt
	from scipy.stats import t

	def paired_t_test(diff):
		n = len(diff)
		mean = diff.mean()
		std = diff.std()

		se = std / sqrt(n)
		df = n - 1

		t_ratio = mean / se

		print 't ratio (assuming mean is zero): %.8lf' % t_ratio
		
		rv = t(df)
		p_value = (1.0 - rv.cdf(abs(t_ratio))) * 2

		print 'two-sided p value: %.8lf' % p_value

		# t-stat = (mean - pop_mean) / se
		# pop_mean = mean - t-stat * se
		pop_mean = lambda t_stat: mean - t_stat * se

		lo, hi = rv.ppf([0.025, 0.975])
		print '95%% confidence interval: %.4lf ~ %.4lf' % (pop_mean(lo), pop_mean(hi))

결과는 이렇게 나온다.

	t ratio (assuming mean is zero): 3.22892779
	two-sided p value: 0.00606155
	95% confidence interval: 0.3306 ~ 0.0667

## Two-sample \$t\$-test

가장 흔한 경우로, 두 개의 서로 다른 분포에서 얻은 두 개의 샘플이 있다고 하자. 이 두 분포의 평균이 다를까? 다르다면 얼마나 다를까?

#### 예제 실험

혹독한 겨울 폭풍이 몰아친 이후 야생동물 보호 센터(?)로 보내진 59마리의 참새 중, 35마리는 살아남고 24마리는 죽었다. 이들의 덩치와 살아남을 가능성 사이에 관계가 있는지 알아보기 위해 이들의 날개뼈 길이를 쟀다.

#### 검증하기

1. 두 서로 다른 분포에서 하나씩 샘플을 뽑는다고 하자. 역시, 각 샘플의 크기가 커질수록 각 샘플 평균의 분포는 정규분포에 근접한다.
1. 따라서 샘플 평균의 차이 또한 정규 분포에 근접하게 된다. 따라서 샘플 평균의 차이의 표준편차의 estimate만 구할 수 있으면 똑같이 \$t\$-test를 할 수 있다.
1. 다행히 샘플 평균 차이의 standard error를 다음과 같이 구할 수 있다. 
	1. \$t\$-test는 두 모집단의 분산이 같다고 가정한다. 
	1. 분산은 샘플의 크기에 따라 대략 선형 증가하므로, 두 샘플의 분산을 샘플 크기(정확히는 degree of freedom)으로 가중평균하는 방식으로 표준 편차를 구한다.
	1. 책에 주어진 마법의 식에 따라 샘플 평균 차이의 standard error를 구한다.
1. Profit!

#### 수식

Pooled sample standard deviation(\$s_p\$)으로부터 차이의 standard error 구하기:

    $$
    SE(\bar{Y}_{2} - \bar{Y}_{1}) = s_{p} \sqrt{ \frac{1}{n_1} + \frac{1}{n_2}}
    $$

#### 구현하기

	def two_sample_t_test(sample1, sample2):
		n1, n2 = len(sample1), len(sample2)
		mean1, mean2 = sample1.mean(), sample2.mean()
		var1, var2 = sample1.var(), sample2.var()

		df = n1 + n2 - 2
		pooled_sd = sqrt((var1 * (n1 - 1) + var2 * (n2 - 1)) / df)
		print 'pooled SD = %.8lf' % pooled_sd

		diff_se = pooled_sd * sqrt(1.0 / n1 + 1.0 / n2)

		print 'Diff SE = %.8lf' % diff_se

		t_ratio = (mean1 - mean2) / diff_se

		print 't ratio (assuming diff is zero): %.8lf' % t_ratio

		rv = t(df)
		p_value = (1.0 - rv.cdf(abs(t_ratio))) * 2
		
		print 'two-sided p value: %.8lf' % p_value


		# t-stat = (diff - pop_mean) / diff_se
		# pop_mean = diff - t-stat * se
		pop_mean = lambda t_stat: (mean1 - mean2) - t_stat * diff_se

		lo, hi = rv.ppf([0.025, 0.975])
		print '95%% confidence interval: %.4lf ~ %.4lf' % (pop_mean(lo), pop_mean(hi))

## \$t\$-test 의 가정

\$t\$-test는 모집단이 정규분포를 띠며, 두 집단의 표준 편차가 같다고 가정한다. 샘플의 수가 크면 Central Limit Theorem에 의해 샘플의 평균값은 정규분포를 띠므로 이 가정이 깨져도 상관없다고 주장하고 싶지만, 모집단의 표준 편차를 샘플 표준 오차로 근사하는 과정이 이 가정을 사용하기 때문에 이 가정은 아주 중요하다.

다행히 모집단이 정규분포가 아니라도 \$t\$-test는 상당부분 성립함이 널리 알려져 있다. 안 되는 시나리오들을 정리해 보면

두 모집단의 표준 편차|샘플 크기|스큐        |판정
---------------------|---------|------------|------
같을때				 |다를때   |클때        |망했다
같을때               |         |아주 다를 때|망했다
다를때				 |다를때   |            |망했다

outlier의 존재와 serial/cluster effect의 존재 또한 \$t\$-test 의 가정을 망쳐놓을 수 있다.

* 두 샘플의 표준 편차가 다른데 평균이 더 큰 샘플의 표준 편차도 더 크다면, 로그 변환을 통해 \$t\$-test의 조건을 만족시킬 수 있는 경우가 있다.
* outlier가 있는 경우 Wilcoxon test등의 outlier에 강한 테스트를 쓴다.
* Serial/cluster effect는 결국 confounding variable로 설명할 수 있다. 샘플 과정에서 우리가 모르는 바이어스가 있다거나, 시간에 따른 변화들이 없나 살핀다.
* 샘플들의 분포 등을 확인하는 가장 좋은 길은 결국 직접 그려보는 것이다.

## 샘플이 여러 개 있는 경우

ANOVA는 다음 글에서 따로 다루겠다.
