#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class Entry
{
typedef std::vector<std::string> strvec;
public:
    Entry() : patterns{std::vector<std::string>(10)}, sum{0} {}
    ~Entry() {}

    /// Proccesses entry, from tokenizing to calculating local result
    void getdata(const std::string & str);

    /// Returns final result
    int result() const { return sum; }

private:
    strvec patterns;

    int sum;

    /// Tokenizes string @p str into vector @p v , sorts each string
    void tokenize(const std::string & str, std::vector<std::string> & v);

    /// Assigns correct strings to patterns
    void analyze(std::vector<std::string> & mappings);

    /// @returns number of common chars
    int common(const std::string & str1, const std::string & str2);

    /// Decodes 
    void decode(std::vector<std::string> & code);

};

#endif