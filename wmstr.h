#include <string>
using std::string;

#include <vector>
using std::vector;

// en.wikipedia.org/wiki/UTF-8

namespace wmstr
{

/*
inline int seekForward(const string& str, int startPos, int distance)
{
	while (startPos < (int)str.size() && distance != 0)
	{
		startPos++;
		
		if ((str[startPos] & 0xC0) != 0x80)
			distance--;
	}
	
	return startPos;
}
*/

struct Itr
{
	Itr(const string& strIn): str(strIn)
	{}
	
	/*
	Itr(const string& strIn, int uIn, int bIn, int bNextIn): str(strIn)
	{
		u = uIn;
		b = bIn;
		bNext = bNextIn;
	}
	*/
	
	int u = -1; // the unicode position
	int b = 0; // the byte position, aka what you can use as an index to a string
	int bNext = 0; // where the next chatacter starts
	int bSize;
	const string& str; // the string
	
	// returns true until reaches the end
	inline bool onward()
	{
		if (!isEnd())
			u++;
		
		b = bNext;
		
		if (isEnd())
			return false;
		
		do
		{
			bNext++;
			
		} while (bNext < (int)str.size() && (str[bNext] & 0xC0) == 0x80);
		
		return true;
	}
	
	inline bool backItUp()
	{
		if (!isStart())
			u--;
		
		bNext = b;
		
		if (isStart())
			return false;
		
		do
		{
			b--;
			
		} while (b > 0 && (str[b] & 0xC0) == 0x80);
		
		return true;
	}
	
	inline bool onward(int distance)
	{
		if (distance<0)
		{
			while (distance < 0)
			{
				if (!backItUp())
					return false;
				
				distance++;
			}
		}
		else
		{
			while (distance > 0)
			{
				if (!onward())
					return false;
				
				distance--;
			}
		}
		
		return true;
	}
	
	inline bool backItUp(int distance)
	{
		return onward(-distance);
	}
	
	inline bool isStart()
	{
		return bNext == 0;
	}
	
	inline bool isEnd()
	{
		return b >= (int)str.size();
	}
	
	inline string get()
	{
		if (b == bNext) // if it is at the end or start
			return "";
		else
			return str.substr(b, bNext-b);
	}
};

inline Itr endOf(const string& str)
{
	Itr itr = Itr(str);
	
	while (itr.onward()) {}
	
	return itr;
}

inline Itr startOf(const string& str)
{
	Itr itr(str);
	itr.onward();
	return itr;
}

inline bool startsWith(const string& str, const string& prefix)
{
	return str.size() >= prefix.size() && str.substr(0, prefix.size()) == prefix;
}

inline bool endsWith(const string& str, const string& suffix)
{
	return str.size() >= suffix.size() && str.substr(str.size() - suffix.size(), str.npos) == suffix;
}

}

