#pragma once

#include "VarType.h"

class Content : public BaseContent
{
public:
	Content() { name = "Content"; }


	Var_Int(a, 1);	
	Var_Int(d, 22);
	Var_Bool(b, false);
	Var_String(c, "ccc");
	Var_Bool(e, true);

	virtual void StartTest() override 
	{
		INFO("a:%d, d:%d, b:%d, c:%s, e:%d\n", a, d, b, c.c_str(), e);
	}
};

