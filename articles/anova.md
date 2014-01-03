title: 메모: ANOVA
date: 2013-01-04
hidden: 1

\$I\$개의 모집단에서 각각 얻은 \$I\$개의 샘플이 있다고 하자. 이 때,

> 모든 모집단의 평균이 같을까?

같은 질문에 대답하기 위해서는 One-way ANOVA를 써야 한다.

* Full model: 각 집합마다 별도의 mean. N-I degrees of freedom.
* Reduced model: 모든 집합에 하나의 mean. N-1 degrees of freedom.

분자는 Full model의 sum of squares - Reduced model의 sum of squares
분모는 Full model에서 estimate한 variance

만약 Full model == Reduced model이라면.. 

왜 두개가 같은 걸 estimate 하려는 건지 모르겠다. -\_-;

mean이 같다고 가정하면 각 샘플의 평균은 \mu를 평균으로 갖고 \sigma/4 를 표준편차로 가질 것이다. 따라서 이 샘플의 평균 샘플의 분산이 \sigma/4 의 estimate가 된다. 이 때 \sigma
