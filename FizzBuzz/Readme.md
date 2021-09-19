# extendable-FizzBuzz
Ref : https://www.tomdalling.com/blog/software-design/fizzbuzz-in-too-much-detail/
레퍼런스는 수도코드로 표현되어 있는데, 저는 C++로 구현했습니다.

> 1부터 15까지 숫자 중
3의 배수일 때 Fizz, 5의 배수일 때 Buzz를 출력하고, 3과 5의 배수일 때 FizzBuzz를 출력하고, 나머지 경우면 그냥 숫자를 출력하는 함수를 작성해주세요.

라고 리퀘스트가 들어왔다고 해봅시다.


## Naive Approach

```C++
for(int i = 1; i <= 15; i++)
{
	if (i%3 == 0 && i % 5 == 0)
		std::cout << "FizzBuzz";
	else  if(i%3 == 0)
		std::cout << "Fizz";
	else  if (i%5 == 0)
		std::cout << "Buzz";
	else
		std::cout << i;
	std::cout << endl;
}
```
정도로 구현할 수 있겠네요.
조건문을 공부하려고 하는 개발자라면 접해봤을 수도 있겠습니다.

여기서 만약에 클라이언트가 새로운 조건을 추가하고 싶어한다고 가정해보죠. 
> 7의 배수에는 Zazz를 출력했으면 좋겠어요. 
> 5랑 7이면 BuzzZazz, 3,5,7이면 FizzBuzzZazz. 되죠?
> 
조건 한 개 추가했을 뿐인데, 경우의 수가 여러 개 추가됩니다. **"7로만 나눠지는 경우",** **"3과 7"**, **"5와 7"**, **"3,5,7 모두"**. 기존 경우가 4가지였으니 두 배가 된 겁니다.
조건이 더 많아지면 어떻게 될까요? 11, 13, 17로 나눠떨어지는 수가 추가한다면 if-else문에 몇개를 더 추가해야 할까요? 2^n으로 늘어나는 경우의 수는 누가 추가해야 할까요? 바로 너입니다.

## Rules

그러니 확장성을 고려해서 다시 설계해 봅시다. 규칙으로 들어온 수가 무엇이든, 몇 개가 있든 작동했으면 좋겠네요. 

해당 int로 나누어 떨어질 때 string을 담은 자료구조를 하나 만들어봅시다.
```C++
#include <map>
#include <string>

std::map<int, std::string> Rules { {3,"Fizz"},{5,"Buzz"} }
```
그리고 코드를 이렇게 구현해주면...

```C++
for (int i = 1; i <= n; i++)
{
	std::string s = "";

	//conditions
	bool bDefault = true;
	for (const  auto& iter : Rules)
	{
		if (i % iter.first == 0)
		{
			s += Rules[iter.first];
			bDefault = false;
		}
	}
	//default
	if (bDefault)
	{
		s = std::to_string(i);
	}
	
	std::cout << s << std::endl;
}
```
매 숫자마다 Rules에 해당하는 게 있는지 확인할 수 있겠네요.

## 추가 확장

여기서 클라이어트가 **"나누어 떨어짐"** 말고 다른 조건을 가져온다고 가정해보면 어떨까요?
> 1부터 10까지 중 to_string(i)인 경우는 숫자 대신에 Yass로 출력되게 할 수는 없나요?

범위가 15까지밖에 안 되니까 반복문을 두 개로 나눌 생각을 하셨습니까? 당장 임시방편은 가능하겠지만 코드가 확장될 때, 예를 들면 범위가 1~100으로 확장되고, Yass가 10~30, 50~70, 90~100으로 나뉘는 등 반복문을 새로 쪼개야 하는 상황이 오면 결국 확장성에서 또 발목을 잡히게 됩니다.

이런 경우는 해당 조건을 함수로 만들어서 Rules에 담아야 하겠네요.

```C++
std::map<Condition,std::string> Rules_extended;

Rules_extended[Div(3)] = "Fizz";
Rules_extended[Div(5)] = "Buzz";
Rules_extended[Between(1,10)] = "Yass";
```
Condition 객체를 만드는 방법은... 생각 좀 해보고 다음 시간에 적겠습니다.


## 추가 확장 두번째

생각해 왔습니다!
모던 C++의 std::function을 이용하는 방법입니다.
std::function은 C++의 Callable 객체를 담을 수 있는데, Rule 구조체를 만들고 여기 들어가는 Callable에 원하는 판정을 넣어 주면 되겠네요.

```C++
struct Rule 
{
	Rule(const std::function<bool(int)>& rule, const std::string& msg) : inner_rule(rule), msg(msg) {  }
	
	std::function<bool(int)> inner_rule;
	std::string msg;
};

Rule rule_Div3		([](int num) -> bool {return num % 3 == 0; }, "Fizz");
Rule rule_Div5		([](int num) -> bool {return num % 5 == 0; }, "Buzz");
Rule rule_Div7		([](int num) -> bool {return num % 7 == 0; }, "Jazz");
```

Rule의 생성자에 일일이 익명함수 전체를 짜 넣는 건 코드 중복이네요. 일반적으로 흑마술로 취급받는 방법이지만 **매크로**를 써 코드를 줄여 봅시다.

```C++
#define RULE_LAMBDA(rule_disc) ([](int num) -> bool {return (rule_disc) ;})

//마음껏 함수를 정의할 수 있게 되었습니다.
Rule rule_Smaller10	(RULE_LAMBDA(num < 10), "Yass");
Rule rule_Between15_30	(RULE_LAMBDA(num > 15 && num < 30),"Qizz");

std::vector<Rule> Rules_lambda {rule_Div3, rule_Div5, rule_Div7, rule_Smaller10, rule_Between15_30};
```
이제 Rule이 문자열도 머금고 있으니까 std::map 대신 벡터에 담았습니다. 이제 fizzbuzz 내의 Iteration 부분에서 ```C++ std::map```을 이용하던 부분만 ```C++ std::vector```로 바꿔주면 되겠네요. 

```C++
//fizzbuzz 함수 부분
	bool bDefault = true;
	for (const auto& iter : Rules_lambda) 
	{
		if (iter.inner_rule(i)) 
		{
			s += iter.msg;
			bDefault = false;
		}
	}
```

.h와 .cpp파일을 만들어서 붙일 때, 방금 새로 정의한 struct Rule과 std::vector는 static 키워드를 달아 줬습니다. (main에서 발생하는 LNK2005에러 해결)

## 추가 확장 

다음 문제는, 문자열 출력 이슈가 있겠네요.
> 예시 1. Yass는 딱 자기만 나오게, 딴 조건이랑 같이 나오는 FizzYass나 BuzzYass같은 경우는 피했으면 좋겠어요.
> 예시 2. 21 같은 경우 좀 보세요. FizzJassQizz라고 뜨지 않습니까. 얼마나 못생겼어요??
> 예시 3. 특정 규칙/숫자/범위 에서는 특정 문자열(들)만 나오게 하고 싶어요.
> 예시 4. 요컨대, **String 출력에도 규칙을 넣을 수 없을까요?**

클라이언트가 이런 경우를 던져 주면 어떻게 처리할 수 있을까요?

예시 2 같은 경우는 코드 외부적인 이유(디자인 등)로 인해 클라이언트가 선호하지 않는다고 가정해 보겠습니다.
이 단계에서 확장하는 룰은 다음처럼 정리해볼 수 있겠네요.
1. string rule이 default인 경우 들어오는 문자 그대로 출력한다.
2. out_string에는 우선순위가 있어 높은 우선순위가 낮은 우선순위를 지배한다. 

