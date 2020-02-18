#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <vector>
#include <iostream>

class Input
{
public:
	Input(const Input& input) = delete;
	Input& operator=(const Input& input) = delete;
	static Input* GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new Input();
			return s_Instance;
		}
	}
	static std::unordered_map<int, bool> s_Keys;
	static void SetKey(int key, bool isDown)
	{
		s_Keys[key] = isDown;
	}
	static bool GetKey(int key)
	{
		if (s_Keys.find(key) == s_Keys.end())
			return false;
		if (s_Keys.find(key) != s_Keys.end())
			return s_Keys[key];
	}
private:
	Input() {}
	static Input* s_Instance;
};


#endif

