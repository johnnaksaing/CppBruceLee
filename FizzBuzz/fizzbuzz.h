#pragma once
#include <map>
#include <iostream>
#include <string>

static std::map<int, std::string> Rules{ {3,"Fizz"},{5,"Buzz"} };

#define RULE_LAMBDA(rule_disc) ([](int num) -> bool {return (rule_disc) ;})

struct Rule 
{
	Rule(const std::function<bool(int)>& rule, const std::string& msg) : inner_rule(rule), msg(msg) {  }
	Rule(const std::string& msg, const std::function<bool(int)>& rule) : inner_rule(rule), msg(msg) {  }
	
	std::function<bool(int)> inner_rule;
	std::string msg;
};

static Rule rule_Div3([](int num) -> bool {return num % 3 == 0; }, "Fizz");
static Rule rule_Div5([](int num) -> bool {return num % 5 == 0; }, "Buzz");
static Rule rule_Div7([](int num) -> bool {return num % 7 == 0; }, "Jazz");


static Rule rule_Smaller10(RULE_LAMBDA(num < 10), "Yass");
static Rule rule_Between15_30(RULE_LAMBDA(num > 15 && num < 30), "Qizz");

static std::vector<Rule> Rules_lambda{ rule_Div3, rule_Div5, rule_Div7, rule_Smaller10, rule_Between15_30 };

void fizzBuzz(int n);