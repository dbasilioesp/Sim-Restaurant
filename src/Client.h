#pragma once
class Client
{
	int id;
	int group;
	bool served;
public:
	Client(int id);
	~Client(void);
	int getId();
	void setGroup(int i);
	int getGroup();
	void setServed(bool s);
	bool isServed();
};

