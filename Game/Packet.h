#pragma once

#include <stdint.h>

class Packet
{
private:
	std::vector<uint8_t> bytPacket;

public:
	Packet(uint8_t* bytPacket, int size);
	Packet();

	uint8_t* getBytes();

	Packet& operator<<(bool data);
	Packet& operator<<(uint8_t data);
	Packet& operator<<(int8_t data);
	Packet& operator<<(uint16_t data);
	Packet& operator<<(int16_t data);
	Packet& operator<<(uint32_t data);
	Packet& operator<<(int32_t data);
	Packet& operator<<(uint64_t data);
	Packet& operator<<(int64_t data);
	Packet& operator<<(const char* data);

	Packet& operator>>(bool& data);
	Packet& operator>>(uint8_t& data);
	Packet& operator>>(int8_t& data);
	Packet& operator>>(uint16_t& data);
	Packet& operator>>(int16_t& data);
	Packet& operator>>(uint32_t& data);
	Packet& operator>>(int32_t& data);
	Packet& operator>>(uint64_t& data);
	Packet& operator>>(int64_t& data);
	Packet& operator>>(char* data);

	~Packet();
};