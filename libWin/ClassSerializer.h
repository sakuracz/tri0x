#ifndef CLASSSERIALIZER_H_
#define CLASSSERIALIZER_H_

#include <string>
#include <fstream>

const long TruePattern	= 0xfab1fab2;
const long FalsePattern	= 0xbad1bad2;

class Serializer
{
public:
	Serializer(std::string const & fileName)
		: _stream(fileName.c_str(), std::ios_base::out)
	{
		if(!_stream.is_open())
			throw "Couldn't open file";
	}
	void PutLong(long l)
	{
		_stream.write(reinterpret_cast<char *>(&l), sizeof(long));
		if(_stream.bad())
			throw "File write failed";
	}
	void PutDouble(double d)
	{
		_stream.write(reinterpret_cast<char *>(&d), sizeof(double));
		if(_stream.bad())
			throw "File write failed";
	}
	void PutBool(bool b)
	{
		long l = b ? TruePattern : FalsePattern;
		PutLong(l);
		if(_stream.bad())
			throw "File write failed";
	}

	void TwoColDouble(double one, double two)
	{
		_stream << one << "\t"  << two << std::endl;
		if(_stream.bad())
			throw "File write failed";
	};
private:
	std::ofstream _stream;
};

class DeSerializer
{
public: 
	DeSerializer(std::string const & fileName)
		: _stream(fileName.c_str(), std::ios_base::in)
	{
		if(!_stream.is_open())
			throw "Couldn't open file";
	}
	long GetLong()
	{
		if(_stream.eof())
			throw "Unexpected end of file";
		long l;
		_stream.read(reinterpret_cast<char *>(&l), sizeof(long));
		if(_stream.bad())
			throw "File read failed";
		return l;
	}
	double GetDouble()
	{
		if(_stream.eof())
			throw "Unexpected end of file";
		double d;
		_stream.read(reinterpret_cast<char *>(&d), sizeof(double));
		if(_stream.bad())
			throw "File read failed";
		return d;
	}
	bool GetBool()
	{
		long b = GetLong();
		if(_stream.bad())
			throw "File read failed";
		if(b == TruePattern)
			return true;
		else if(b == FalsePattern)
			return false;
		else
			throw "Data corruption error";
	}
private:
	std::ifstream _stream;
};

#endif