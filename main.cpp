#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

class solution {
public:
    std::vector<std::string> numDecodings(const std::string & s) {
	std::vector<std::string> result;
	std::vector<std::vector<std::string>> decodings = splitString(s, std::vector<std::string>());
	for (auto& dec : decodings) {
	    result.push_back(std::accumulate(dec.begin(), dec.end(), std::string(),
					     [&](const std::string & s1, const std::string & s2){
						 return s1+translate(s2);
					     }));
	}
	std::sort(result.begin(), result.end());
	auto it = std::unique(result.begin(), result.end());
	result.resize(std::distance(result.begin(), it));
	return result;
    }

private:
    std::string translate(const std::string & numStr) {
	return std::string(1,char('A'+stoi(numStr)-1));
    }
    
    size_t getLength(const std::vector<std::string> & vec) {
	return std::accumulate(vec.begin(), vec.end(), 0, [](int i, const std::string &s){
		return i+s.size();
	    });
    }
    
    std::vector<std::vector<std::string>> splitString(const std::string & s, const std::vector<std::string> & curr) {
	std::vector<std::vector<std::string>> result;
	if (getLength(curr) == s.size()) {
	    result.push_back(curr);
	}
	else {
	    std::vector<std::string> next = getNext(s, curr);
	    for (auto nx : next) {
		auto cpy = curr;
		cpy.push_back(nx);
		auto temp = splitString(s, cpy);
		std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
	    }
	}
	return result;
    }

    std::vector<std::string> getNext(const std::string & s, const std::vector<std::string> & curr) {
	std::vector<std::string> next;
	// if (curr.empty()) {
	//     size_t len = 1;
	//     while (stoi(s.substr(0,len)) <= 26) {
	// 	next.push_back(s.substr(0,len));
	// 	len++;
	//     }
	// }
	// else {
	    size_t start = getLength(curr);
	    size_t len = 1;
	    while (len <= s.size() && stoi(s.substr(start,len)) <= 26) {
		next.push_back(s.substr(start,len));
		len++;
	    }
	// }
	return next;
    }
};

int main() {
    std::string s{"1234321"};
    solution soln;
    auto decodings = soln.numDecodings(s);
    std::cout << "All possible decodings are:\n";
    std::copy(decodings.begin(), decodings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
