#pragma once

#define TEXT_FORMAT 1
#define IMAGE_FORMAT 1
#define DATA_FORMAT 1

class Packet
{
private:
	int type;
	char data[1024];

public:
	Packet();
	~Packet();
};

