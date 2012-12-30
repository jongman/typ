categories: 알고리즘, 번역
title: 철자 교정기 작성하기
date: 2011-08-24

블로그 개장 기념으로 역시 내가 좋아하는 또다른 에세이 중 하나인 [Peter Norvig](http://norvig.com/)의 [How to Write a Spelling Corrector](http://norvig.com/spell-correct.html)를 번역해 보았다. 영문을 대상으로 한 철자 교정기라서 국문에 그대로 적용할 수는 없지만, 굉장히 흥미롭게 읽을 수 있다.

나는 이 글이 정말 굉장히 좋은 글이라고 생각하는데, 단순히 이론을 잘 설명하고 있으며, 코드가 간결하고 우아하다는 표면적인 이유 외에도 딱히 정답이 없는 문제에 접근하기 위한 사고 과정을 잘 설명하고 있다는 것이다. 동작할 수 있는 가장 단순한 방법을 만들고, 이것의 성능을 측정하고, 어떻게 이것을 개선하면 좋을지에 대해서도 잘 설명하고 있다. 우리 시대의 가장 [유명한 인공지능 연구자 중 하나](http://norvig.com/bio.html)가 이런 문제 해결 과정을 직접 설명해 주는 것을 듣기란 쉽지 않다.

번역상의 오탈자는 코멘트로 신고 바란다. 

<!-- PREVIEW_END -->

---

지난 주에 나는 구글이 검색어의 철자를 그렇게 빠르고 정확하게 교정하는 것이 놀랍다는 말을 두 명의 친구들(딘과 빌)로부터 각각 들었다. 실제로 구글에 [마춤법](http://www.google.com/search?sourceid=chrome&ie=UTF-8&q=%EB%A7%88%EC%B6%A4%EB%B2%95)이라고 검색해 보면 대략 0.1초 안에 *이것을 찾으셨나요? [철자](http://www.google.co.kr/#hl=ko&newwindow=1&sa=X&ei=qD5QTrCSDunk0QG5rPCCBw&ved=0CCoQBSgA&q=%EB%A7%9E%EC%B6%A4%EB%B2%95&spell=1&bav=on.2,or.r_gc.r_pw.&fp=c16bbd82e235a9c3&biw=837&bih=1080)* 같은 결과를 받게 된다. (야후나 마이크로소프트의 검색 결과도 다르지 않다.) 사실 나는 그런 말을 들어서 놀랐다. 굉장히 유능한 엔지니어이자 수학자인 딘과 빌 같은 사람들은 철자 교정과 같은 통계적 언어 처리에 대해서는 충분히 잘 알 것이라고 생각했기 때문이다. 하지만 그들이 이런 주제에 대해 딱히 알아야 할 이유는 없다: 그들의 지식이 문제가 아니라 내 생각이 문제인 셈이다.

두 친구들 외에도 많은 사람들에게 도움이 되기를 바라며 철자 교정기의 동작 과정에 대해 설명해 보겠다. 물론 실제 서비스에 사용되는 철자법 교정기의 내부는 여기에서 전부 다루기에는 너무 복잡하다([여기](http://static.googleusercontent.com/external_content/untrusted_dlcp/research.google.com/en/us/pubs/archive/36180.pdf)와 [여기](http://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=52A3B869596656C9DA285DCE83A0339F?doi=10.1.1.146.4390&rep=rep1&type=pdf)에 관련된 자료가 좀 있다). 그러니 이 글에서는 그 원리를 이해하는 데 도움이 될 만한 간단하고 짧은 철자법 교정기를 하나 작성해 보려고 한다. 나의 목표는 한 페이지 안에 들어갈 정도로 짧으면서, 80퍼센트에서 90퍼센트의 정확률을 보이고 초당 최소 10단어 정도는 처리하는 구현을 만드는 것이다.

다음 21줄의 [파이썬](http://python.org/) 2.5 코드로 완전한 철자 교정기를 구현할 수 있다.

	import re, collections

	def words(text): return re.findall('[a-z]+', text.lower()) 

	def train(features):
		model = collections.defaultdict(lambda: 1)
		for f in features:
			model[f] += 1
		return model

	NWORDS = train(words(file('big.txt').read()))

	alphabet = 'abcdefghijklmnopqrstuvwxyz'

	def edits1(word):
	   splits     = [(word[:i], word[i:]) for i in range(len(word) + 1)]
	   deletes    = [a + b[1:] for a, b in splits if b]
	   transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]
	   replaces   = [a + c + b[1:] for a, b in splits for c in alphabet if b]
	   inserts    = [a + c + b     for a, b in splits for c in alphabet]
	   return set(deletes + transposes + replaces + inserts)

	def known_edits2(word):
		return set(e2 for e1 in edits1(word) for e2 in edits1(e1) if e2 in NWORDS)

	def known(words): return set(w for w in words if w in NWORDS)

	def correct(word):
		candidates = known([word]) or known(edits1(word)) or known_edits2(word) or [word]
		return max(candidates, key=NWORDS.get)

위 코드에 정의된 `correct` 함수는 단어를 입력받아 가장 그럴듯한 정정 결과를 반환한다. 예를 들면 다음과 같다.

	>>> correct('speling')
	'spelling'
	>>> correct('korrecter')
	'corrector'

위 코드에 보인 `edits1` 함수는 처음에 내가 작성한 것이 아니라 다리우스 베이컨이 제시한 방법의 변형이다. 이 방법이 내가 원래 작성했던 방법보다 더 명료한 것 같아 이와 같이 바꿨다. 다리우스는 함수에 있던 버그도 잡아 주었다.

## 동작 원리: 확률 이론

이 코드의 동작 원리를 설명하기 위해서는 이론 얘기를 조금 해야 한다. 우리가 하려는 일은 단어가 주어졌을 때 가장 가능성이 높은 교정 결과를 찾아내는 것이다(물론 이 교정 결과는 원래 단어일 수도 있다). 물론 모든 경우에 항상 옳은 결과를 찾아낼 수 있는 방법은 없다(예를 들어 `lates`가 검색어로 주어졌다면, `late`로 교정해야 할 지, `latest`로 교정해야 할 지 알 수 없기 때문이다). 따라서 원래 단어 w가 주어졌을 때 각 교정 결과 후보 c에 조건부 확률 값을 배정하고 그 중 확률을 최대화하는 후보를 선택하는 것으로 하자. 이런 c를 다음과 같이 쓸 수 있다.

$$
	\arg\max_{c} P\left(c|w\right)
$$

[베이즈 정리](http://ko.wikipedia.org/wiki/%EB%B2%A0%EC%9D%B4%EC%A6%88_%EC%A0%95%EB%A6%AC)에 의하면 이것을 다음과 같이 고쳐 쓸 수도 있다.

$$
	\arg\max_{c} \frac{ P(w|c) \cdot P(c) }{ P(w) }
$$

이 식에서 P(w)는 모든 후보 c에 대해 같은 값이므로 생략하도록 하자. 그러면 다음 식을 얻을 수 있다.

$$
	\arg\max_{c} P(w|c) \cdot P(c) 
$$

이 식을 세 부분으로 나눌 수 있다. 오른쪽에서부터 설명해 보자.

1. P(c)는 w와 상관 없이 결과 후보 c 자체의 출현 확률을 나타낸다. 이것은 우리가 다루는 언어에 따라 달라지므로, 이것을 언어 모델(language model)이라고 부른다. 예를 들어 "영어 문장에서 c가 출현할 확률은 얼마나 되는가?" 라는 질문에 답하는 과정이 언어 모델인 셈이다. 잘 작성된 언어 모델에서 the가 출현할 확률 P("the")는 상대적으로 꽤 출현 확률이 높겠지만, P("zxzxzxzyyy")의 출현 확률은 거의 없을 것이다.
2. P(w|c)는 검색어를 입력한 사람이 c를 치려다가 실수로 w를 입력할 확률을 나타낸다. 이것을 오류 모델(error model)이라고 부른다. 
3. argmax<sub>c</sub>는 가능한 모든 c에 대해 두 확률의 곱을 계산해 보고, 곱을 최대화하는 결과를 반환하라는 것을 의미한다.

이쯤 되어서 왜 P(c|w)같은 간단한 식을 그냥 두지 않고 아래 있는 더 복잡한 수식으로 바꾸나? 하는 의문이 들 법도 하다. 왜냐면 P(c|w)를 계산하기 위해서는 두 개의 요소를 고려해야 하는데, 이들을 따로 나눠 이름을 붙이면 더 다루기 수월해지기 때문이다. 예를 들어 w="thew"가 입력되었다고 하자. 그럼 두 개의 후보 c="the"와 c="thaw" 중 더 확률 P(c|w)가 높은 것은 어느 쪽일까? 흠, a를 e로 바꾸기만 하면 되니 "thaw"가 그럴듯해 보인다. 하지만 "the"도 그럴듯해 보이는 것이, the는 영어에서 굉장히 흔하게 등장하는 단어인데다 e를 치면서 실수로 옆에 있는 w를 치는 일도 충분히 가능하기 때문이다. 이렇듯 P(c|w)를 직접 계산하려고 해도 위에서 언급한 두 개의 요소를 모두 고려해야 하므로, 차라리 명시적으로 이들을 분리하고 이름 붙이는 것이 낫다. 

자, 이제 프로그램의 동작 원리에 대해 설명해 보자. 먼저 P(c)를 계산하는 부분에 대해 이야기해 보겠다. 이 코드는 대략 백만 개의 단어를 포함하는 커다란 텍스트 파일 [big.txt](http://norvig.com/big.txt)를 읽어들인다. 이 파일은 [구텐베르크 프로젝트](http://www.gutenberg.org/wiki/Main_Page)에 공개된 책 몇 권, [Wiktionary](http://en.wiktionary.org/wiki/Wiktionary:Frequency_lists), 그리고 [British National Corpus](http://www.kilgarriff.co.uk/bnc-readme.html)에서 얻은 가장 흔한 영단어 목록을 합친 것이다. (이 코드를 처음 작성할 때 나는 귀국 비행기 안에 있었는데, 그 때 내 랩탑에는 셜록 홈즈 전권밖에 없었다. 나중에 문서를 추가하는 것이 정확도에 도움이 되지 않을 때까지 다른 여러 문서를 추가했다. 자세한 것은 평가 섹션을 참조하라.)

`big.txt`를 읽어들인 후에는 텍스트에 개별 단어들을 `words` 함수를 써서 추출한다. 이 함수는 각 연속된 알파벳 문자열들을 단어로 분리하며, 모든 알파벳을 소문자로 변환한다. 따라서 "The"가 "the"로 변환되고, "don't" 는 "don"과 "t" 두 개의 단어가 된다. 파일을 읽어들인 뒤에는 `train` 함수에서 확률 모델을 훈련하는데, 말은 거창하지만 사실 각 단어가 몇 번이나 등장하는지 세어보는 것이다. 다음 코드를 참조하자.

	def words(text): return re.findall('[a-z]+', text.lower()) 

	def train(features):
		model = collections.defaultdict(lambda: 1)
		for f in features:
			model[f] += 1
		return model

	NWORDS = train(words(file('big.txt').read()))

이 시점에서 `NWORD[w]`는 파일 안에서 단어 `w`가 몇 번이나 출현했는지를 나타낸다. 이 때 따로 신경써야 할 점이 하나 있는데, 바로 새로운 단어들이다. 우리가 수집한 자료에 등장하지 않는 단어가 정답인 경우엔 어떻게 해야 할까? 우리가 본 적이 없다고 해서 반드시 틀린 단어라고 가정할 수는 없다. 이럴 때 쓸 수 있는 일반적인 접근 방법이 몇 가지 있는데, 여기서는 가장 쉬운 것을 택하자. 바로 새로운 단어들은 모두 한 번 봤다고 가정하는 것이다. 이와 같은 기법은 단어들의 확률 분포에서 0이어야 할 부분들을 최소값인 1로 늘림으로써 분포를 평평하게 하는 효과가 있어서, 일반적으로 **평활법(smoothing)**이라고 부른다. 이것은 파이썬의 일반 `dict` 구조체 (다른 언어에서는 해시 테이블이라고 흔히 부르는) 대신 `collections.defaultdict`를 사용하는 방법으로 쉽게 구현할 수 있다. 이 클래스는 `dict`와 똑같이 작동하지만 처음 보는 키의 기본 키를 우리가 지정할 수 있다는 차이점이 있다. 여기서는 1을 사용한다.

이제 단어 w가 주어졌을 때 가능한 교정 결과 후보들을 세어보는 과정을 다뤄 보자. 일반적으로 두 단어가 얼마나 비슷한가를 나타내는 기준으로 **편집 거리(edit distance)**라는 것이 있다. 이것은 한 단어를 다른 단어로 바꾸기 위해 필요한 연산의 최소 수를 의미한다. 한 연산은 한 글자를 지우거나(삭제), 인접한 두 글자를 바꾸거나(뒤집기), 한 글자를 다른 글자로 바꾸거나(변경), 새 글자를 추가할 수(삽입) 있다. 어떤 단어 w가 주어질 때 w에서 편집 거리가 1인 단어들을 모두 생성하는 함수를 아래와 같이 구현할 수 있다.

	def edits1(word):
	   splits     = [(word[:i], word[i:]) for i in range(len(word) + 1)]
	   deletes    = [a + b[1:] for a, b in splits if b]
	   transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]
	   replaces   = [a + c + b[1:] for a, b in splits for c in alphabet if b]
	   inserts    = [a + c + b     for a, b in splits for c in alphabet]
	   return set(deletes + transposes + replaces + inserts)

이 함수의 결과 집합은 꽤나 클 수 있다. 단어의 길이가 n이라고 하면, n개의 삭제, n-1개의 뒤집기, 26n개의 변경, 26(n+1)개의 삽입 연산이 가능하므로 전부 하면 54n+25개의 후보가 있을 수 있다(물론 이 중 몇 개는 중복될 것이다). 예를 들어, `len(edits1('something'))` 으로 `edits1('something')`의 원소의 수를 세어 보면 494를 얻을 수 있다.

철자법 교정에 관한 논문들에서는 80% 에서 95% 의 철자법 오타 결과는 원문과 편집 거리가 1밖에 되지 않는다고 흔히 주장한다. 나는 개발을 위해 270개의 오타 모음을 간단히 모아서 확인해 보았는데, 이 중 원문과의 편집 거리가 1인 오타는 76%밖에 되지 않았다. 내가 수집한 오타들이 일반적인 오타들보다 어려울 가능성도 있지만, 이것으로는 영 만족스럽지 않아서 편집 거리 2인 단어들도 검사하기로 결정했다. `edits1`의 결과 단어들에 `edits1`을 한번씩 다시 적용하면 이것을 쉽게 할 수 있다.

	def edits2(word):
		return set(e2 for e1 in edits1(word) for e2 in edits1(e1))

이걸 작성하는 것은 간단하지만, 이제는 계산량이 꽤나 많아지게 된다. `len(edits2('something'))`는 무려 114,324가 된다. 그렇지만 이 경우 대부분의 오타를 감안할 수 있게 된다. 270개의 예제에서 원문과의 편집 거리가 2 보다 큰 예제는 고작 3개밖에 없었다. 예제의 98.9%는 `edits2`로 커버할 수 있다는 말이므로, 나에겐 이것으로 충분하다. 편집 거리 3 이상인 단어들을 만들 필요는 없으므로 간단한 최적화를 하도록 하자. 모든 후보를 생성하는 대신, 실제로 우리가 알고 있는 단어들만을 반환하는 것이다. `known_edits2` 함수가 이와 같은 작업을 한다:

	def known_edits2(word):
		return set(e2 for e1 in edits1(word) for e2 in edits1(e1) if e2 in NWORDS)

이렇게 코드를 바꾸면 `known_edits2('something')`은 `edits2`의 11만개 대신 이제 고작 smoothing, seething, something, soothing 의 4개 단어만을 반환한다. 이 최적화로 수행 시간의 10% 정도를 절약할 수 있었다.

이제 남은 문제는 오류 모델 P(w|c)를 만드는 부분이다. 내겐 이 부분이 특히 까다로웠는데, 비행기 안에서 인터넷도 쓸 수 없이 앉아 있으니 모델을 생성할 훈련용 데이터를 구할 수도 없는 노릇이었다. 물론 주먹구구로 모델을 만들 수는 있다. 두 개의 자음을 서로 바꿔 쓰는 것보다 모음 두 개를 바꿔 쓸 가능성이 더 크고, 첫 글자는 다른 글자들보다 틀릴 가능성이 적다거나 하는 식으로. 하지만 이 주장을 뒷받침할 자료는 없었고, 때문에 간단한 지름길을 택하기로 했다: 입력 단어에서 편집 거리가 1인 모든 단어는 편집 거리가 2인 단어보다 무한히 더 가능성이 높고, 편집 거리가 0이고 우리가 알고 있는 단어마다 무한히 가능성이 낮다고 가정하는 것이다. 여기서 우리가 알고 있는 단어란 언어 모델, 즉 훈련용 데이터에 포함된 단어를 나타낸다. 이 전략을 다음과 같이 구현해 볼 수 있다.

	def known(words): return set(w for w in words if w in NWORDS)

	def correct(word):
		candidates = known([word]) or known(edits1(word)) or known_edits2(word) or [word]
		return max(candidates, key=NWORDS.get)

`correct` 함수는 주어진 입력 `word`에서 편집 거리가 가장 가까운 알려진 단어들의 목록을 `candidates`에 저장한다. 그 후에는 `NWORDS` 모델에 의해 알려진 대로 P(c)가 가장 큰 단어를 반환한다.

## 평가

이제 프로그램이 얼마나 정확하게 동작하는지 확인해 볼 차례다. 나는 비행기 안에서 몇 개의 예제를 테스트해 보았는데, 그럴 듯 했다. 비행기가 내린 후에 나는 로저 미튼의 [버크벡 철자법 오류 코퍼스](http://ota.ahds.ac.uk/texts/0643.html)를 옥스퍼드 문헌 목록에서 다운받았다. 이 코퍼스에서 두 개의 테스트 셋을 뽑아냈는데, 첫 번째는 개발하는 데 사용했다. 다시 말해 내가 프로그램을 짜는 중에 이 셋을 볼 수 있다는 것이다. 두 번째는 최종 테스트 셋으로, 내가 볼 수도 없고 프로그램이 틀렸을 경우에도 확인할 수 없다는 것이다. 이렇게 두 개의 테스트 셋을 준비하는 것은 좋은 습관이다. 이와 같은 습관이 없이 모든 테스트 셋을 보면서 프로그램을 개발하면, 이 테스트 셋에만 적합하도록 프로그램을 튜닝한 뒤 프로그램의 성능이 실제보다 우수하다고 착각하기 십상이다. 아래는 이 두 종류의 테스트의 일부와 이들을 수행하는 함수의 구현을 보여준다. 코드의 나머지와 전체 테스트를 보고 싶으면 [spell.py](http://norvig.com/spell.py)를 참조하라.

	tests1 = { 'access': 'acess', 'accessing': 'accesing', 'accommodation':
		'accomodation acommodation acomodation', 'account': 'acount', ...}

	tests2 = {'forbidden': 'forbiden', 'decisions': 'deciscions descisions',
		'supposedly': 'supposidly', 'embellishing': 'embelishing', ...}

	def spelltest(tests, bias=None, verbose=False):
		import time
		n, bad, unknown, start = 0, 0, 0, time.clock()
		if bias:
			for target in tests: NWORDS[target] += bias
		for target,wrongs in tests.items():
			for wrong in wrongs.split():
				n += 1
				w = correct(wrong)
				if w!=target:
					bad += 1
					unknown += (target not in NWORDS)
					if verbose:
						print '%r => %r (%d); expected %r (%d)' % (
							wrong, w, NWORDS[w], target, NWORDS[target])
		return dict(bad=bad, n=n, bias=bias, pct=int(100. - 100.*bad/n), 
					unknown=unknown, secs=int(time.clock()-start) )

	print spelltest(tests1)
	print spelltest(tests2) ## only do this after everything is debugged

수행해 보면 다음과 같은 결과를 얻을 수 있다.

	{'bad': 68, 'bias': None, 'unknown': 15, 'secs': 16, 'pct': 74, 'n': 270}
	{'bad': 130, 'bias': None, 'unknown': 43, 'secs': 26, 'pct': 67, 'n': 400}

270개의 개발용 테스트 셋을 처리하는 데는 13초가 걸렸으며 (초당 17개) 74%의 정확도를 얻었고, 최종 테스트 셋에서는 초당 15개의 입력을 처리하며 67%의 정확도를 얻었음을 볼 수 있다.

**업데이트**: 이 에세이의 첫 버전에서는 코드의 버그로 인해 두 테스트 셋 모두에서 원래보다 높은 점수를 기록했다. 까다로운 버그기는 했지만 잡기 불가능한 것은 아니었으며, 잘못된 버전을 읽은 독자에게 사과한다. `spelltest` 함수의 첫 버전에서는 `bias`가 존재하는지 확인하는 `if`문이 없었다 (그리고 초기값이 `None`이 아니라 0이었다). 나는 `bias=0` 일 경우, `NWORDS[target] += bias`는 아무런 효과가 없을 거라고 생각했다. 하지만 부가 효과가 있었다. 이 코드를 수행한 후에는 `target in NWORDS`가 항상 참이 되는 것이다. 원래는 정답 단어가 우리의 사전에 없는 경우에도 이 코드로 인해 우리가 항상 알고 있게 되었으므로, 코드가 반칙을 한 셈이다. 참으로 부끄러운 오류이다. `defaultdict`를 사용해서 프로그램을 간결하게 한 것은 좋았지만, 일반 `dict` 자료 구조를 대신 사용했다면 이런 일은 없었을 것이다.

**2차 업데이트**: 또 다시 `defaultdict`의 습격이 있었다. 다리우스 베이컨이 `correct` 함수에서 내가 `NWORDS[w]`에 접근함으로써 `w`를 우리가 알고 있지 않은 경우에도 `defaultdict`에 추가하고 있다고 알려주었다. 따라서 두 번째로 접근할 때는 해당 단어가 있다고 인식하게 된다. 다리우스의 제안에 따라 `NWORDS.get` 을 사용하면 이 문제를 피해갈 수 있다. (이것이 동작하는 것은 `max(None, i)` 는 모든 정수 `i`에 대해 `i`이기 때문이다.)

결과적으로 원래의 목표 중 단순함과 개발 시간, 수행 시간은 만족시킬 수 있었지만 정확도에 대해선 그러지 못했다.

## 추후 개선점

어떻게 해야 이 코드를 개선할 수 있을지 생각해 보자 (실제로 [이 책의 한 챕터](http://norvig.com/ngrams/)에서 이 개선점들을 적용한 바 있다). 이 확률 모델의 세 부분 P(c)와 P(w|c), argmax<sub>c</sub> 를 각각 살펴보도록 하자. 각 부분이 잘못 처리한 예제들을 우선 살펴보고, 그 외의 예제들도 살펴보자.

**첫 번째**로는 언어 모델 P(c)를 살펴보자. 우리가 작성한 언어 모델에는 큰 오류의 원인이 두 개 있는데, 그 중 더 심각한 것은 알지 못하는 단어다. 개발용 테스트 셋에는 우리가 알지 못하는 단어가 15개로, 전체의 5%였다. 최종 테스트 셋에서는 43개로 11%나 되었다. `verbose=true`로 두고 `spelltest` 를 수행해 보면 다음과 같은 결과들을 볼 수 있다.

	correct('economtric') => 'economic' (121); expected 'econometric' (1)
	correct('embaras') => 'embargo' (8); expected 'embarrass' (1)
	correct('colate') => 'coat' (173); expected 'collate' (1)
	correct('orentated') => 'orentated' (1); expected 'orientated' (1)
	correct('unequivocaly') => 'unequivocal' (2); expected 'unequivocally' (1)
	correct('generataed') => 'generate' (2); expected 'generated' (1)
	correct('guidlines') => 'guideline' (2); expected 'guidelines' (1)

이 출력은 `correct`의 입력과 결과(`NWORDS`에서 결과 단어가 몇 번이나 출현했는지와 함께), 그리고 테스트 셋에서 요구하는 정답과 정답의 출현 횟수를 보여준다. 이 예제에서 모든 정답들의 출현 횟수는 1로 되어 있고, 이것은 해당 단어를 원래 알지 못했다는 말이다. 우리 프로그램이 `econometric` 이라는 단어가 존재한다는 것을 아예 모른다면 해당 단어로 오타를 정정할 수 있을 리 없다. 물론 훈련용 코퍼스에 문서를 더 추가해서 이 문제를 해결할 수도 있겠지만, 후보가 많아진다는 이야기는 오답이 될 수 있는 후보가 늘어난다는 뜻이기도 하다. 위 예제의 뒤 네 개 예제는 사전에 이미 있는 단어의 변형임을 눈여겨 보자. 따라서 동사 뒤에 `-ed`를 붙이거나 명사 뒤에 `-s`를 붙이는 것도 괜찮다고 생각하는 언어 모델을 만들 수 있다.

언어 모델에서 나타날 수 있는 두 번째 문제는 잘못된 확률값이다. 정답과 오답이 사전에 모두 출현하지만 오답이 더 많이 출현하는 경우다. 하지만 이 오류가 오답의 유일한 원인인 경우를 찾지는 못했다. 여기서 다루는 다른 요인들이 훨씬 큰 악영향을 미친다.

더 많은 단어를 알거나, 모르는 단어들에 대해 더 잘 짐작할 수 있는 언어 모델이 있었다면 얼마나 잘 했을까를 짐작하기 위해 반칙을 조금 하도록 하자. 모든 경우에 우리가 정답 단어를 1번 혹은 10번은 본 적이 있다고 가정하는 것이다. 이것은 언어 모델에 우리가 문서를 적절히 추가하는 것과 같은 효과를 갖는다. `spelltest`의 입력 변수 `bias`를 사용하면 이와 같은 테스트를 할 수 있다. `bias`를 올릴 때 개발과 테스트 셋에서의 성능은 다음과 같이 변화한다.

    Bias    Dev.    Test
    0       74%     67%
    1       74%     70%
    10      76%     73%
    100     82%     77%
    1000    89%     80%

두 테스트 셋 모두에서 훨씬 좋은 성적을 내며 결과적으로는 정확도가 80-90%까지 올라가는 것을 볼 수 있다. 따라서 더 좋은 언어 모델이 있다면 우리의 정확도 목표에 도달할 수도 있다는 결론을 얻을 수 있다. 물론 이것이 너무 낙관적인 결과일 수도 있다. 더 많은 단어를 아는 언어 모델을 만들다 보면 더 많은 오답 후보를 추가하게 되는데, 우리의 테스트에서는 그런 효과를 고려하지 않았기 때문이다.

모르는 단어를 해결하는 다른 방법은 모르는 단어도 'correct'의 결과로 반환할 수 있도록 하는 것이다. 만약에 원래 입력이 'electroencephalographicallz'였다면, 이 단어를 모르더라도 비교적 그럴 듯한 교정 결과는 마지막의 z를 y로 바꾼 'electroencephalographically'일 것이다. 단어의 음절이나 접미사(-ally 같은)에 대해 알고 있는 언어 모델을 만든다면 이런 문제를 해결할 수도 있을 것이다. 더 쉬운 방법으로는 인접한 2글자, 3글자, 4글자 부분 문자열들에 대한 통계를 갖고 있는 언어 모델을 만들 수도 있다.

다음으로 오류 모델 P(w|c)를 살펴보자. 지금까지 오류 모델은 별 것 없었다. 편집 거리가 작으면 작을 수록 오류가 작았기 때문이다. 오류 모델 때문에 생긴 다음 오답들을 살펴보자.

첫 번째로, 정답이 편집 거리 2인데 편집 거리 1인 답을 반환한 경우:
	
	correct('reciet') => 'recite' (5); expected 'receipt' (14)
	correct('adres') => 'acres' (37); expected 'address' (77)
	correct('rember') => 'member' (51); expected 'remember' (162)
	correct('juse') => 'just' (768); expected 'juice' (6)
	correct('accesing') => 'acceding' (2); expected 'assessing' (1)

두 번째 예를 보면, 'adres'에서 'acres'로 가기 위해 d를 c로 바꾸는 연산 하나는 'd'를 'dd'로 만들고 's'를 'ss'로 만드는 두 연산보다 비용이 높았어야 할 것이다.

**두 번째**로, 정답과 오답의 편집 거리가 같은 경우를 살펴보자.

	correct('thay') => 'that' (12513); expected 'they' (4939)
	correct('cleark') => 'clear' (234); expected 'clerk' (26)
	correct('wer') => 'her' (5285); expected 'were' (4290)
	correct('bonas') => 'bones' (263); expected 'bonus' (3)
	correct('plesent') => 'present' (330); expected 'pleasant' (97)

같은 결론을 얻을 수 있다. 'thay'에서 'a'를 'e'로 바꾸는 연산은 'y'를 't'로 바꾸는 연산보다 비용이 작아야 할 것이다. 얼마나 작아야 할까? 'that'이 'they'보다 훨씬 많이 출현하기 때문에, 2.5배는 더 작아야 한다.

편집 거리에서 각 연산의 비용을 좀 더 잘 정하면 좋겠다는 결론을 얻을 수 있다. 이런 직관을 이용해 같은 글자를 추가하거나 모음에 모음을 추가하는 연산의 가중치를 다른 연산보다 인위적으로 낮추는 식으로 모델을 튜닝할 수 있지만, 데이터를 모으는 것이 더 좋을 것이다. 철자 오류 코퍼스를 모으고, 인접한 글자들에 대해 삽입, 변경, 삭제, 뒤집기의 각 편집 연산이 얼마나 자주 출현하는지 확인하는 것이다. 이것을 제대로 하기 위해서는 지나치게 많은 데이터가 필요하다. 왼쪽에 있는 두 글자가 무엇인지, 오른쪽에 있는 두 글자가 무엇인지를 경우의 수에 넣으면 이미 26<sup>6</sup>개의 경우의 수가 나오는데 이것은 3억이 넘는 수이다. 각 경우가 얼마나 자주 출현하는지 보려면 각 경우에 최소 몇 개의 샘플은 봐야 하니까, 대략 10억개, 더 안전하게는 100억개의 자료가 있어야 이런 결과를 얻을 수 있다. 

이 때 언어 모델과 오류 모델이 서로 얽혀 있다는 점에 유의하자. 지금 우리 프로그램의 오류 모델은 너무 단순하기 때문에 우리가 언어 모델에 문서를 더 추가하는 것을 방해한다 (편집 거리 2인 정답이 있을 때, 너무 많은 희귀 단어를 추가하다가 편집 거리 1인 오답이 추가되면 우리 프로그램은 항상 오답을 반환할 것이다). 좀 더 나은 오류 모델이 있다면 희귀 단어를 좀 더 적극적으로 사전에 추가할 수 있을 것이다. 현재 프로그램에서 희귀 단어가 문제되는 다음 경우들을 보자.

	correct('wonted') => 'wonted' (2); expected 'wanted' (214)
	correct('planed') => 'planed' (2); expected 'planned' (16)
	correct('forth') => 'forth' (83); expected 'fourth' (79)
	correct('et') => 'et' (20); expected 'set' (325)

**세 번째**로 모든 가능성을 검사하는 부분인 argmaxc 를 살펴보자. 우리 프로그램은 원문과 편집 거리 2 이하인 후보들을 모두 생성한다. 실제로 개발 셋에서는 270개 중 3개만이 원문과 편집 거리 2가 넘게 떨어져 있었지만, 최종 테스트 셋에서는 400개 중 23개나 있다. 다음이 그 목록이다.

	purple perpul
	curtains courtens
	minutes muinets
	successful sucssuful
	hierarchy heiarky
	profession preffeson
	weighted wagted
	inefficient ineffiect
	availability avaiblity
	thermawear thermawhere
	nature natior
	dissension desention
	unnecessarily unessasarily
	disappointing dissapoiting
	acquaintances aquantences
	thoughts thorts
	criticism citisum
	immediately imidatly
	necessary necasery
	necessary nessasary
	necessary nessisary
	unnecessary unessessay
	night nite
	minutes muiuets
	assessing accesing
	necessitates nessisitates

일부 연산을 이용해 편집 거리 3인 후보들을 만들 수 있도록 함으로써 이 문제를 해결할 수도 있다. 예를 들어 편집 거리 3인 후보들을 만들 때는 모음 옆에 모음을 삽입하거나, 모음을 교체하거나, 'c'를 's'로 바꾸는 등의 그럴 듯한 연산만을 허용하는 것이다. 그러면 이 케이스들을 대부분 처리할 수 있을 것이다.

**네 번째**로 정확도를 올리기 위한 이들보다 더 좋은 방법이 있다. `correct`가 단어 하나만을 입력받는 것이 아니라, 더 많은 문맥에 대한 정보를 받아들일 수 있도록 하는 것이다. 많은 경우 단어 하나만을 가지고는 어느 것이 정답이어야 할지 알기 힘들다. 오타로 입력된 원문이 사전에 이미 존재하는 경우가 좋은 예이다.

	correct('where') => 'where' (123); expected 'were' (452)
	correct('latter') => 'latter' (11); expected 'later' (116)
	correct('advice') => 'advice' (64); expected 'advise' (20)

단어만 보고 `correct('where')`가 언제 'where'이고 언제 'were'이어야 할 거라고 어떻게 알 수 있겠는가? 하지만 입력이 `correct('They where going')` 과 같은 형태였다면 'were'가 정답일 거라고 더 쉽게 예상할 수 있을 것이다.

인접한 단어들은 두 개 이상의 그럴 듯한 후보 중 답을 결정할 때도 유용하다. 다음 예를 보자.

	correct('hown') => 'how' (1316); expected 'shown' (114)
	correct('ther') => 'the' (81031); expected 'their' (3956)
	correct('quies') => 'quiet' (119); expected 'queries' (1)
	correct('natior') => 'nation' (170); expected 'nature' (171)
	correct('thear') => 'their' (3956); expected 'there' (4973)
	correct('carrers') => 'carriers' (7); expected 'careers' (2)

'thear'만 보고 이것이 'there'가 되어야 할 지, 'their'가 되어야 할 지 알 수 있을까? 단어 하나만 보고는 어렵지만, 애초에 입력이 `correct("There's no there thear")` 였으면 훨씬 알아보기 쉬웠을 것이다.

단어 여러개를 입력 받는 모델을 만들기 위해서는 역시 엄청나게 많은 자료가 필요하다. 다행히도 구글이 대략 1조 단어 분량의 문서에서 최대 5개까지의 인접한 단어 목록에 대해 각 목록이 출현한 회수를 모은 자료를 [공개한 바 있다](http://googleresearch.blogspot.com/2006/08/all-our-n-gram-are-belong-to-you.html).

90% 정도의 정확도를 달성하기 위해서는 인접한 단어를 항상 고려해야 할 것이라는 것이 내 생각이다. 하지만 그건 먼 미래를 위해 남겨두자.

**다섯 번째**로, 훈련용 데이터를 개선하는 방법이 있다. 훈련용 데이터를 위해 우리는 대략 백만 개의 단어를 모으고 이들의 철자법은 항상 옳다고 가정했다. 하지만 훈련용 데이터가 오타를 포함할 가능성도 분명히 있다. 이들을 찾아 교정하는 것도 정확도를 올리기 위한 방법이 될 수 있다. 물론 백만 단어 분량의 훈련용 데이터를 교정하기란 쉽지 않다. 대신 테스트 셋에 있는 오류를 교정해서 정확도를 올릴 수도 있다. 실제로 나는 오답으로 분류되었지만 우리 프로그램이 제안한 답이 테스트 셋의 정답보다 나은 경우들도 찾아냈다.

	correct('aranging') => 'arranging' (20); expected 'arrangeing' (1)
	correct('sumarys') => 'summary' (17); expected 'summarys' (1)
	correct('aurgument') => 'argument' (33); expected 'auguments' (1)

그리고 어떤 dialect (딱히 번역할 말이 없어서 원문을 썼다) 에 대해 훈련을 할지도 결정할 수도 있다. 예를 들어 다음 세 개의 오류는 미국식 영어와 영국식 영어의 차이 때문에 발생했다 (우리의 훈련용 데이터는 두 가지 모두를 포함하고 있다).

	correct('humor') => 'humor' (17); expected 'humour' (5)
	correct('oranisation') => 'organisation' (8); expected 'organization' (43)
	correct('oranised') => 'organised' (11); expected 'organized' (70)

**마지막**으로, 결과는 그대로 두고 프로그램을 훨씬 빠르게 최적화할 수도 있다. 인터프리터 언어 대신 컴파일되는 언어를 사용하는 방법이 가장 간단한 방법일 것이다. 어떤 자료형에 대해서도 사용할 수 있는 파이썬의 `dict` 대신 문자열에 최적화된 자료형을 사용하는 것도 한 가지 방법이다. 계산 결과를 캐싱함으로써 여러번 반복하지 않을 수도 있다. 단 한 가지 조언이 있다면, 실제 최적화를 구현하기 전에 항상 어디에서 시간이 가장 많이 소모되는지를 살펴 보라.

## 더 읽을 거리

* 로저 미튼의 철자 교정에 대한 [서베이](http://www.dcs.bbk.ac.uk/~roger/spellchecking.html)
* Jurafsky 와 Martin 의 교과서인 [Speech and Language Processing](http://www.cs.colorado.edu/~martin/slp.html)에는 철자 교정에 관련된 내용이 잘 나와 있다.
* Manning 과 Schutze 의 교과서인 [Foundations of Statistical Natural Language Processing](http://nlp.stanford.edu/fsnlp/)에는 통계적 자연어 처리에 관한 내용이 잘 나와 있지만, 철자 교정에 관한 내용은 없는 것 같다 (최소한 찾아보기에는 없었다).
* 오픈 소스 철자법 교정기인 [aspell](http://aspell.net/)에는 꽤 재미있는 자료가 많은데, 내가 사용한 것보다 나아 보이는 [테스트 데이터](http://aspell.net/test/) 도 있다.
* [LingPipe](http://alias-i.com/lingpipe) 프로젝트에는 이를 철자법 교정을 위해 사용하기 위한 [튜토리얼](http://alias-i.com/lingpipe/demos/tutorial/querySpellChecker/read-me.html) 이 있다.

## 오류

원래 내 프로그램은 20줄이었지만, Ivan Peev가 내가 사용하고 있던 `string.lowercase`는 로케일과 파이썬 버전에 따라 a-z 외에 다른 글자를 저장할 수도 있다고 알려주었다. 때문에 `alphabet` 변수를 추가해서 21줄이 되었다. `string.ascii_lowercase` 를 쓸 수도 있었다.

편집 거리 1인 후보의 개수가 내가 생각했던 55n+25개가 아니라 54n+25개임을 알려준 Jay Liang에게 감사한다.

훈련용 데이터에 없던 단어들에 관련된 문제가 있음을 알려준 Dmitriy Ryaboy에게 감사한다. 덕분에 `NWORDS[target] += bias` 의 버그를 찾을 수 있었다.

## 다른 구현

내가 이 글을 올린 이후 다른 많은 사람들이 다른 프로그래밍 언어로 이 철자법 교정기를 구현하였다. 이 글의 목적은 파이썬을 홍보하는 것이 아니라 알고리즘을 보여주는 것이었지만, 언어를 비교하거나 특정 언어로 된 구현을 원하는 사람에게는 다음 목록이 유용할 것 같다.

<table border=1> 
<tr><th>언어<th>코드 줄수<th>작성자 및 구현 링크
<tr><td>Awk<td>15<td><a href="http://pacman.blog.br/wiki/index.php?title=Um_Corretor_Ortogr%C3%A1fico_em_GAWK">Tiago "PacMan" Peczenyj</a> 
<tr><td>Awk<td>28<td><a href="http://feedback.exalead.com/feedbacks/191466-spell-checking">Gregory Grefenstette</a> 
<tr><td>C<td>184<td><a href="http://blog.marcelotoledo.org/2007/08/10/how-to-write-a-spelling-corrector/">Marcelo Toledo</a> 
<tr><td>C++<td>98<td><a href="http://scarvenger.wordpress.com/2007/12/11/how-to-write-a-spelling-corrector/">Felipe Farinon</a> 
<tr><td>C#<td>43<td><a href="http://www.codegrunt.co.uk/?page=cSharp#norvigSpell">Lorenzo Stoakes</a> 
<tr><td>C#<td>69<td><a href="http://frederictorres.blogspot.com/2011/04/how-to-write-spelling-corrector-from.html">Frederic Torres</a> 
<tr><td>Clojure<td>18<td><a href="http://en.wikibooks.org/wiki/Clojure_Programming/Examples#Norvig.27s_Spelling_Corrector">Rich Hickey</a> 
<tr><td>D<td>23<td><a href="http://leonardo-m.livejournal.com/59589.html">Leonardo M</a> 
<tr><td>Erlang<td>87<td><a href="http://www.pixzone.com/blog/223/spell-corrector-aka-google-suggest-in-erlang-first-part/">Federico Feroldi</a> 
<tr><td>F#<td>16<td><a href="http://www.jelovic.com/weblog/?p=201">Dejan Jelovic</a> 
<tr><td>F#<td>34<td><a href="http://cs.hubfs.net/forums/thread/3085.aspx">Sebastian G</a> 
<tr><td>Groovy<td>22<td><a href="http://raelcunha.com/spell-correct.php#groovy">Rael Cunha</a> 
<tr><td>Haskell<td>24<td><a href="http://pithekos.net/brainwave/">Grzegorz</a> 
<tr><td>Java<td>35<td><a href="http://raelcunha.com/spell-correct.php">Rael Cunha</a> 
<tr><td>Java<td>372<td><a href="http://developer.gauner.org/jspellcorrect/">Dominik Schulz</a> 
<tr><td>Javascript<td>53<td><a href="http://astithas.blogspot.com/2009/08/spell-checking-in-javascript.html">Panagiotis Astithas</a> 
<tr><td>Lisp<td>26<td><a href="https://github.com/mikaelj/snippets/blob/master/lisp/spellcheck/spellcheck.lisp">Mikael Jansson</a> 
<tr><td>Perl<td>63<td><a href="http://www.riffraff.info/2007/5/20/a-spell-corrector-in-perl6-part-3">riffraff</a> 
<tr><td>PHP<td>68<td><a href="http://www.phpclasses.org/browse/package/4859.html">Felipe Ribeiro</a> 
<tr><td>PHP<td>103<td><a href="http://soundofemotion.com/spellcorrect.txt">Joe Sanders</a> 
<tr><td>Python<td>21<td>Peter Norvig
<tr><td>Rebol<td>133<td><a href="http://www.rebol.cz/~cyphre/spell.r">Cyphre</a> 
<tr><td>Ruby<td>34<td><a href="http://lojic.com/blog/2008/09/04/how-to-write-a-spelling-corrector-in-ruby/">Brian Adkins</a> 
<tr><td>Scala<td>23<td><a href="http://theyougen.blogspot.com/2009/12/peter-norvigs-spelling-corrector-in.html">Thomas Jung</a> 
<tr><td>Scheme<td>45<td><a href="http://practical-scheme.net/wiliki/wiliki.cgi?Gauche%3aSpellingCorrection&amp;l=en">Shiro</a> 
<tr><td>Scheme<td>89<td><a href="http://scheme.dk/blog/2007/04/writing-spelling-corrector-in-plt.html">Jens Axel</a> 
</table> 

[피터 노빅](http://norvig.com/)
