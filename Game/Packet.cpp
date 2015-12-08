#include "stdafx.h"
#include "Packet.h"

Packet::Packet(uint8_t* bytPacket, int size)
{
	this->bytPacket.assign(bytPacket, bytPacket + size);
}

Packet::Packet()
{
}

uint8_t* Packet::getBytes()
{
	return &this->bytPacket[0];
}


Packet& Packet::operator<<(uint8_t data)
{
	this->bytPacket.push_back(*(char*)&data);
	return *this;
}

Packet& Packet::operator<<(int8_t data)
{
	this->bytPacket.push_back(*(char*)&data);
	return *this;
}

Packet& Packet::operator<<(uint16_t data)
{
	for (int i = sizeof(data) - 1; i >= 0; i--)
		this->bytPacket.push_back(*((char*)&data + i));
	return *this;
}

Packet& Packet::operator<<(int16_t data)
{
	for (int i = sizeof(data) - 1; i >= 0; i--)
		this->bytPacket.push_back(*((char*)&data + i));
	return *this;
}

Packet& Packet::operator<<(uint32_t data)
{
	for (int i = sizeof(data) - 1; i >= 0; i--)
		this->bytPacket.push_back(*((char*)&data + i));
	return *this;
}

Packet& Packet::operator<<(int32_t data)
{
	for (int i = sizeof(data) - 1; i >= 0; i--)
		this->bytPacket.push_back(*((char*)&data + i));
	return *this;
}

Packet& Packet::operator<<(uint64_t data)
{
	for (int i = sizeof(data) - 1; i >= 0; i--)
		this->bytPacket.push_back(*((char*)&data + i));
	return *this;
}

Packet& Packet::operator<<(int64_t data)
{
	for (int i = sizeof(data) - 1; i >= 0; i--)
		this->bytPacket.push_back(*((char*)&data + i));
	return *this;
}

Packet& Packet::operator<<(const char* data)
{
	uint32_t length = strlen(data);
	this->operator<<(length);
	for (int i = 0; i < length; i++)
		this->bytPacket.push_back(data[i]);

	return *this;
}

Packet& Packet::operator<<(bool data)
{
	this->bytPacket.push_back(data == false ? (char)0 : (char)1);
	return *this;
}

Packet& Packet::operator>>(int8_t& data)
{
	if (this->bytPacket.size() >= sizeof(int8_t))
	{
		data = *(int8_t*)(&this->bytPacket[0]);
		this->bytPacket.erase(this->bytPacket.begin());
	}
	return *this;
}

Packet& Packet::operator>>(uint8_t& data)
{
	if (this->bytPacket.size() >= sizeof(uint8_t))
	{
		data = *(uint8_t*)(&this->bytPacket[0]);
		this->bytPacket.erase(this->bytPacket.begin());
	}
	return *this;
}

Packet& Packet::operator>>(int16_t& data)
{
	if (this->bytPacket.size() >= sizeof(int16_t))
	{
		data = ntohs(*(int16_t*)(&this->bytPacket[0]));
		this->bytPacket.erase(this->bytPacket.begin(), this->bytPacket.begin() + 2);
	}
	return *this;
}

Packet& Packet::operator>>(uint16_t& data)
{
	if (this->bytPacket.size() >= sizeof(uint16_t))
	{
		data = ntohs(*(uint16_t*)(&this->bytPacket[0]));
		this->bytPacket.erase(this->bytPacket.begin(), this->bytPacket.begin() + 2);
	}
	return *this;
}



Packet& Packet::operator>>(int32_t& data)
{
	if (this->bytPacket.size() >= sizeof(int32_t))
	{
		data = ntohl(*(int32_t*)(&this->bytPacket[0]));
		this->bytPacket.erase(this->bytPacket.begin(), this->bytPacket.begin() + 4);
	}
	return *this;
}

Packet& Packet::operator>>(uint32_t& data)
{
	if (this->bytPacket.size() >= sizeof(uint32_t))
	{
		data = ntohl(*(uint32_t*)(&this->bytPacket[0]));
		this->bytPacket.erase(this->bytPacket.begin(), this->bytPacket.begin() + 4);
	}
	return *this;
}

Packet& Packet::operator>>(int64_t& data)
{
	if (this->bytPacket.size() >= sizeof(int64_t))
	{
		data = ntohll(*(int64_t*)(&this->bytPacket[0]));
		this->bytPacket.erase(this->bytPacket.begin(), this->bytPacket.begin() + 8);
	}
	return *this;
}

Packet& Packet::operator>>(uint64_t& data)
{
	if (this->bytPacket.size() >= sizeof(uint64_t))
	{
		data = ntohll(*(uint64_t*)(&this->bytPacket[0]));
		this->bytPacket.erase(this->bytPacket.begin(), this->bytPacket.begin() + 8);
	}
	return *this;
}


Packet& Packet::operator>>(char* data)
{
	uint32_t length;
	this->operator>>(length);

	if (length >= 0 && this->bytPacket.size() >= length)
	{
		int i = 0;
		for (; i < length; i++)
		{
			data[i] = this->bytPacket[0];
			this->bytPacket.erase(this->bytPacket.begin());
		}
		data[i] = 0;
	}

	return *this;
}

Packet& Packet::operator>>(bool& data)
{
	if (this->bytPacket.size() >= 1)
	{
		this->bytPacket[0] == 1 ? data = true : data = false;
		this->bytPacket.erase(this->bytPacket.begin());
	}
	
	return *this;
}


Packet::~Packet()
{
}
