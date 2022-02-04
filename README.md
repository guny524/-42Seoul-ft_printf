# [42Seoul] ft_printf
> c 라이브러리를 사용하지 않고, 시스템 콜만을 사용하여 실제 printf를 똑같이 구현하는 프로젝트\
> [printf man으로 파헤치기](https://warm-salsa-f69.notion.site/printf-1-man-3e18cd43d4544c3ab95d525204ac3831)\
> [printf 구현하기](https://warm-salsa-f69.notion.site/printf-2-8aff4a45394347e5bee31d4b5011601a)
## 프로젝트 소개
- variable arguments list에 대해 사용법 뿐만 아니라 대략적인 원리도 알아야 한다.
- bonus를 구현하게 된다면 printf의 세부적인 option(flag)들을 공부하고, 구현하게 된다. printf manual 페이지에 적혀있지 않은 undefined behavior들을 어떻게 처리할지 고민하게 된다.
- 42 내에서 이 프로젝트를 하는 많은 사람들이 duixXp 별로 함수를 따로 만들지만, 개인적으로 프로젝트에서 요구하는 것 외에도 printf를 어떻게 구조화할지 고민했다.
1. 출력할 숫자의 signed 여부, byte size, base_len을 통해 하나의 출력 로직으로 통일
2. 정해진 출력 width를 넘으면 출력을 종료하고 -1을 리턴하는 문제를 check flag를 통해 미리 출력 width만 계산하게끔 구성

## 주의 사항
다음 사항을 지키지 않으면 0점 받을 것이다.
- 코드는 [norm](https://warm-salsa-f69.notion.site/Norm-85024906b60243e99a060194620cef3e)을 준수해서 작성되어야 한다.
- 어떤 상황에서도 프로그램은 segment fault, bus error, dangling pointer 등으로 중단되어서는 안 된다. (평가자가 특정 상황을 저격해서 만들어 낼 수 있음)
- heap에 할당된 모든 메모리는 적절하다 해제되어야 한다. 메모리 누수가 생겨서는 안 된다.
- gcc -Wall -Wextra -Werror 플래그로 컴파일해야 한다.
- Makefile은 relink 되어서는 안 된다.

## 사용가능한 함수 (그 외 외부 라이브러리 함수 사용불가)
- malloc, free
- write
- va_start, va_arg, va_copy, va_end

## 구현해야 할 것
### Mandatroy part
- 함수 원형 `int ft_printf(const char *, ...);`
- printf를 재구현 하라.
- 실제 printf와 달리 buffer management를 하면 안 된다.
- cspdiuxX%에 대해서 실제 printf랑 똑같이 동작하면 된다.
- make를 하면 libftprintf.a가 나와야 한다.
- libtool은 금지되고, ar을 써야 한다.

### Bonus Part
- 모든 conversion에 대해 '-0.# +' flag와 minimum field width의 다양한 조합에서도 동작해야 한다.
