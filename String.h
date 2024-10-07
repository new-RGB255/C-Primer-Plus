#ifndef STRING_H
#define STRING_H
#include<iostream>

namespace microstring {

	class String {
	public:
		//сят╙
		friend std::istream& operator>>(std::istream& is, String& st);
		friend std::ostream& operator<<(std::ostream& os, const String& st);
		friend bool operator<(const String& st1, const String& st2);
		friend bool operator>(const String& st1, const String& st2);
		friend bool operator==(const String& st1, const String& st2);
	private:
		char* str;
		int len;
		static int num_strings;
		static const int CINLIM = 80;
	public:
		String(const char* s);
		String();
		~String();
		String(const String& st);
		String& operator=(const String& st);
		String& operator=(const char* s);
		int length() const { return len; }
		static int howmany();
		char& operator[](int i);
		const char& operator[](int i) const;
	};
}

#endif // !STRING_H
