#pragma once

#include <string>
#include <vector>


#define Prop_Int(name, value) int name = value; PropInt m_##name{#name, &name, this}; 
#define Prop_Bool(name, value) bool name = value; PropBool m_##name{#name, &name, this}; 
#define Prop_String(name, value) std::string name = value; PropString m_##name{#name, &name, this}; 

enum PropType
{
	type_int,
	type_bool,
	type_string
};

struct Prop
{
	PropType type;
	const char* name = "undefined";
};


class BaseContent
{
public:
	const char* name = "undefined";
	std::vector<Prop*> props;

public:
	Prop** GetProps(int& size) { size = props.size(); return props.data(); }
	virtual void StartTest() {}
};


struct PropInt : Prop
{
	PropInt(const char* _name, int* val, BaseContent* content) :value(val)
	{
		name = _name;
		type = PropType::type_int;
		content->props.emplace_back(this);
	}

	int* value;
};

struct PropBool : Prop
{
	PropBool(const char* _name, bool* val, BaseContent* content) :value(val)
	{
		name = _name;
		type = PropType::type_bool;
		content->props.emplace_back(this);
	}

	bool* value;
};

struct PropString : Prop
{
	PropString(const char* _name, std::string* val, BaseContent* content) :value(val)
	{
		name = _name;
		type = PropType::type_string;
		content->props.emplace_back(this);
	}

	std::string* value;
};

